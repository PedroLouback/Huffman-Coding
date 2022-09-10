#include "huffman.hpp"

void CreateHuffman(Huffman *huffman)
{
    huffman->first = NULL;
    huffman->size = 0;
}

void InsertSorted(Huffman *huffman, No *no)
{
    No *aux;

    if (huffman->first == NULL)
    {
        huffman->first = no;
    }
    else if (no->group.repetition_number < huffman->first->group.repetition_number)
    {
        no->prox = huffman->first;
        huffman->first = no;
    }
    else
    {
        aux = huffman->first;
        while (aux->prox && aux->prox->group.repetition_number <= no->group.repetition_number)
            aux = aux->prox;
        no->prox = aux->prox;
        aux->prox = no;
    }
    huffman->size++;
}

void FillHuffman(Lista *l, Huffman *huffman)
{
    Block *aux = l->first->prox;
    No *new_no;
    while (aux != NULL)
    {
        if (aux->data.repetition_number > 0)
        {
            new_no = new No;
            if (new_no)
            {
                new_no->group.word = aux->data.word;
                new_no->group.repetition_number = aux->data.repetition_number;
                new_no->left = NULL;
                new_no->right = NULL;
                new_no->prox = NULL;
                InsertSorted(huffman, new_no);
            }
            else
            {
                cout << "\nErro ao alocar memoria em preencher a tabela Huffman" << endl;
                break;
            }
        }
        aux = aux->prox;
    }
}

void PrintHuffman(Huffman *huffman)
{
    No *aux = huffman->first->prox;

    cout << "Lista ordenada: Tamanho: " << huffman->size << endl;
    while (aux)
    {
        cout << aux->group.word << " - " << aux->group.repetition_number << endl;
        aux = aux->prox;
    }
}

No *RemoveHuffman(Huffman *huffman)
{
    No *aux = NULL;

    if (huffman->first)
    {
        aux = huffman->first;
        huffman->first = aux->prox;
        aux->prox = NULL;
        huffman->size--;
    }

    return aux;
}

No *HuffmanTree(Huffman *huffman)
{
    No *first, *second, *new_no;
    Item aux;
    while (huffman->size > 1)
    {
        first = RemoveHuffman(huffman);
        second = RemoveHuffman(huffman);
        new_no = new No;

        if (new_no)
        {
            new_no->group.word = '+';
            new_no->group.repetition_number = (first->group.repetition_number + second->group.repetition_number);
            new_no->left = first;
            new_no->right = second;
            new_no->prox = NULL;

            InsertSorted(huffman, new_no);
        }
        else
        {
            cout << "\nERRO ao alocar memoria em criar árvore de Huffman!" << endl;
            break;
        }
    }
    return huffman->first; // will return the beginning when there is only one node, or beginning, at the end if there is one node left
}

void PrintTree(No *root, int size)
{
    if (root->left == NULL && root->right == NULL)
        cout << "\nFolha: " << root->group.word << " || Altura: " << size;
    else
    {
        PrintTree(root->left, size + 1);
        PrintTree(root->right, size + 1);
    }
}

void ReadDocument(Lista *l, Huffman *huffman)
{
    Item aux;
    Block *aux2;
    ifstream file;
    string line, text;
    int verify = 1, repetition_count = 0, max_repetition = 0, min_repetition = 0;
    double normalization = 0;
    vector<string> tokens;
    vector<string> verified_words;
    No *tree;

    file.open("document.txt");

    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line);
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                tokens.push_back(WordTreatment(word));
            }
        }
    }

    // the recurrence will be checked by taking one by one, traversing the entire text counting the recurrence

    for (size_t i = 0; i < tokens.size(); i++)
    {
        verify = 0;
        for (size_t j = i + 1; j < tokens.size(); j++)
        {
            if (verify == 0)
            {
                for (size_t k = 0; k < verified_words.size(); k++)
                {
                    if (tokens.at(i) == verified_words.at(k)) // will check if a certain word has already been counted
                    {
                        verify = 2;
                        break;
                    }
                }
            }
            if (verify == 2)
            {
                break;
            }
            verify = 1;
            if (tokens.at(i) == tokens.at(j)) // the recurrence check will be done
            {
                if (repetition_count == 0)
                {
                    verified_words.push_back(tokens.at(i));
                }
                repetition_count++; // if it finds a recurrence, it increases the counter by one
            }
        }
        if (verify != 2 && (i < (tokens.size() - 1))) // total size -1 because the last word was being inserted again because the verification could not be done
        {
            aux.repetition_number = (repetition_count + 1);
            aux.word = tokens.at(i);
            LInsert(l, aux);
            repetition_count = 0;
        }
    }

    // search for maximum repetition
    aux2 = l->first->prox;
    max_repetition = aux2->data.repetition_number;
    while (aux2 != NULL)
    {
        if (aux2->data.repetition_number > max_repetition)
        {
            max_repetition = aux2->data.repetition_number;
        }
        aux2 = aux2->prox;
    }

    cout << "\n";

    aux2 = l->first->prox;
    min_repetition = aux2->data.repetition_number;
    while (aux2 != NULL)
    {
        if (aux2->data.repetition_number < min_repetition)
        {
            min_repetition = aux2->data.repetition_number;
        }
        aux2 = aux2->prox;
    }

    aux2 = l->first->prox;
    while (aux2 != NULL)
    {
        normalization = (aux2->data.repetition_number / (max_repetition - min_repetition));
        aux2->data.repetition_number = normalization;
        aux2 = aux2->prox;
    }

    FillHuffman(l, huffman); // fill the huffman struct and sort the number of repetitions

    tree = HuffmanTree(huffman);
}

string WordTreatment(string word)
{
    int size = word.size();
    string aux;

    for (int i = 0; i < size; i++)
    {
        if (word[i] != '.' && word[i] != ',' && word[i] != ':' && word[i] != ';' && word[i] != '?' && word[i] != '!' && word[i] != '(' && word[i] != ')' && word[i] != '[' && word[i] != ']' && word[i] != '{' && word[i] != '}' && word[i] != '+' && word[i] != '=' && word[i] != '-' && word[i] != '*' && word[i] != '/' && word[i] != '%' && !isdigit(word[i]))
        {
            word[i] = tolower(word[i]);
            aux += word[i];
        }
    }

    return aux;
}