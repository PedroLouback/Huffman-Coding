#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

#include "list.hpp"

using namespace std;

class QueueNode
{
public:
    Item group;
    QueueNode *left, *right;
};

class Queue
{
public:
    int front, rear;
    int capacity;
    QueueNode **array;
};

QueueNode *newNode(string word, double repetition_number);
Queue *createQueue(int capacity);
int isSizeOne(Queue *queue);
int isEmpty(Queue *queue);
int isFull(Queue *queue);
void InsertQueue(Queue *queue, QueueNode *item);
QueueNode *getFront(Queue *queue);
QueueNode *findMin(Queue *firstQueue, Queue *secondQueue);
int isLeaf(QueueNode *root);
void printArr(int arr[], int n);
QueueNode *HuffmanTree(vector<string> words, vector<double> freq, int size);
void printCodes(QueueNode *root, int arr[], int top);
void HuffmanCodes(vector<string> words, vector<double> freq, int size);
void ReadDocument(Lista *l);
string WordTreatment(string word);

#endif