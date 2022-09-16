#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <assert.h>
#include "list.hpp"

using namespace std;

typedef struct no
{
    Item group;
    struct no *left, *right, *prox;
} No;

typedef struct
{
    No *first;
    int size;
} Huffman;

void CreateHuffman(Huffman *huffman);
void InsertSorted(Huffman *huffman, No *no);
void FillHuffman(Lista *l, Huffman *huffman);
void PrintHuffman(Huffman *Huffman);
void PrintTree(No *raiz, int size);
No *RemoveHuffman(Huffman *huffman);
void GenerateSequence(Lista *l, No *raiz, string way);
void PrintSequence();
void ReadDocument(Lista *l, Huffman *huffman);
void WriteBinaryFile(Lista *boolean_list, vector<string> tokens);
vector<string> RemoveVowels(vector<string> tokens);
string WordTreatment(string word);

#endif