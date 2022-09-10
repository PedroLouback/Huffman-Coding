#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>

using namespace std;

typedef struct Item Item;
typedef struct Block Block;
typedef struct Lista Lista;

struct Item
{
    string word;
    double repetition_number;
};

struct Block
{
    Item data;
    Block *prox;
};

struct Lista
{
    Block *first;
    Block *last;
    int size; // added list size
};

void FLVazia(Lista *l);
void LInsert(Lista *l, Item d);
void Swap(Block *a, Block *b);
void LImprime(Lista *l);

#endif