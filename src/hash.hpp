#ifndef HASH_HPP
#define HASH_HPP

#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

typedef struct DataTable DataTable;
typedef struct HashTable HashTable;

struct DataTable
{
    int *key;
    int **matrix;
};

struct HashTable
{
    DataTable *table;
    int M;
};

void Initialize(HashTable *h, int M);
void Insert(HashTable *h, int *key, int **matrix, int hash, int matrixline, int matrixcolumn);

#endif