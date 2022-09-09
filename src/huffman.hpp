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

void ReadDocument(Lista *l);
string WordTreatment(string word);
void InsertionSort(Lista *l);

#endif