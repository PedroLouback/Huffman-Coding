#include "huffman.hpp"

void ReadDocument(Lista *l)
{
    Item aux;
    ifstream file;
    string line, text;
    int repetition_count = 0, verify = 1;
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
            verify = 1;                       // colocar um jeito para que coloque no vector de verified apenas uma vez
            if (tokens.at(i) == tokens.at(j)) // the recurrence check will be done
            {
                verified_words.push_back(tokens.at(i));
                repetition_count++; // if it finds a recurrence, it increases the counter by one
            }
        }
        if (verify != 2)
        {
            aux.repetition_number = (repetition_count+1);
            aux.word = tokens.at(i);
            LInsert(l, aux);
            cout << aux.word << " - " << aux.repetition_number << endl;
            repetition_count = 0;
        }
    }

    LImprime(l);
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