#include "hash.hpp"

void Initialize(HashTable *h, int M)
{
    h->table = (DataTable *)malloc(M * sizeof(DataTable));

    for (int i = 0; i < M; i++)
    {
        h->table[i].key = (int *)calloc(4, sizeof(int));
    }

    h->M = M;
}

void Insert(HashTable *h, int *key, int **matrix, int hash, int matrixline, int matrixcolumn)
{
    int idx = hash;

    h->table[idx].key = key;

    h->table[idx].matrix = (int **)calloc(matrixline, 1 + sizeof(int *)); // alloc one extra ptr
    for (int i = 0; i < matrixline; i++)
    {
        h->table[idx].matrix[i] = (int *)calloc(matrixcolumn, sizeof(int));
    }
    h->table[idx].matrix[matrixline] = NULL; // set the extra ptr to NULL

    for (int i = 0; i < matrixline; i++)
    {
        for (int j = 0; j < matrixcolumn; j++)
        {
            h->table[idx].matrix[i][j] = matrix[i][j];
        }
    }

    cout << "\nA matriz informada acima foi inserida com sucesso na Hash com chave ' ";
    for (size_t i = 0; i < 4; i++)
    {
        cout << h->table[idx].key[i] << " ";
    }

    cout << "'\n\n";
}