#include "huffman.hpp"

void ReadDocument(Lista *l)
{
    Item aux;
    Block *aux2;
    ifstream file;
    string line, text;
    int repetition_count = 0, verify = 1, max_repetition = 0, min_repetition = 0;
    vector<string> tokens;
    vector<string> verified_words;

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
                if(repetition_count == 0){
                    verified_words.push_back(tokens.at(i));
                }
                repetition_count++; // if it finds a recurrence, it increases the counter by one
            }
        }
        if (verify != 2 && (i < (tokens.size() - 1))) // total size -1 because the last word was being inserted again because the verification could not be done
        {
            aux.repetition_number = (repetition_count+1);
            aux.word = tokens.at(i);
            LInsert(l, aux);
            repetition_count = 0;
        }
    }

    LImprime(l);

    // search for maximum repetition
    aux2 = l->first->prox;
    max_repetition = aux2->data.repetition_number;
    while(aux2 != NULL){
        if(aux2->data.repetition_number > max_repetition){
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