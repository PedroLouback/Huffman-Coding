#include "huffman.hpp"

#define MAX_TREE_HT 100

QueueNode *newNode(string words, double repetition_number)
{
    QueueNode *temp = new QueueNode;
    temp->left = temp->right = NULL;
    temp->group.word = words;
    temp->group.repetition_number = repetition_number;
    return temp;
}

Queue *createQueue(int capacity)
{
    Queue *queue = new Queue[(sizeof(Queue))];
    queue->front = queue->rear = -1;
    queue->capacity = capacity;
    queue->array = new QueueNode *[(queue->capacity * sizeof(QueueNode *))];
    return queue;
}

int isSizeOne(Queue *queue)
{
    return queue->front == queue->rear && queue->front != -1;
}

int isEmpty(Queue *queue)
{
    return queue->front == -1;
}

int isFull(Queue *queue)
{
    return queue->rear == queue->capacity - 1;
}

void InsertQueue(Queue *queue, QueueNode *item)
{
    if (isFull(queue))
        return;
    queue->array[++queue->rear] = item;
    if (queue->front == -1)
        ++queue->front;
}

QueueNode *RemoveQueue(Queue *queue)
{
    if (isEmpty(queue))
        return NULL;
    QueueNode *temp = queue->array[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        ++queue->front;
    return temp;
}

QueueNode *getFront(Queue *queue)
{
    if (isEmpty(queue))
        return NULL;
    return queue->array[queue->front];
}

QueueNode *findMin(Queue *firstQueue, Queue *secondQueue)
{
    if (isEmpty(firstQueue))
        return RemoveQueue(secondQueue);
    if (isEmpty(secondQueue))
        return RemoveQueue(firstQueue);
    if (getFront(firstQueue)->group.repetition_number < getFront(secondQueue)->group.repetition_number)
        return RemoveQueue(firstQueue);

    return RemoveQueue(secondQueue);
}

int isLeaf(QueueNode *root)
{
    return !(root->left) && !(root->right);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i];
    cout << endl;
}

QueueNode *HuffmanTree(vector<string> words, vector<double> freq, int size)
{
    QueueNode *left, *right, *top;

    Queue *firstQueue = createQueue(size);
    Queue *secondQueue = createQueue(size);

    for (int i = 0; i < size; i++)
        InsertQueue(firstQueue, newNode(words[i], freq[i]));

    while (!(isEmpty(firstQueue) && isSizeOne(secondQueue)))
    {
        left = findMin(firstQueue, secondQueue);
        right = findMin(firstQueue, secondQueue);

        top = newNode("$", left->group.repetition_number + right->group.repetition_number);
        top->left = left;
        top->right = right;
        InsertQueue(secondQueue, top);
    }
    return RemoveQueue(secondQueue);
}

void printCodes(QueueNode *root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root))
    {
        cout << root->group.word << ": ";
        printArr(arr, top);
    }
}

void HuffmanCodes(vector<string> words, vector<double> freq, int size)
{

    QueueNode *root = HuffmanTree(words, freq, size);

    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}
void ReadDocument(Lista *l)
{
    Item aux;
    Block *aux2;
    ifstream file;
    string line, text;
    int verify = 1, repetition_count = 0, max_repetition = 0, min_repetition = 0;
    double normalization = 0;
    vector<string> tokens;
    vector<string> verified_words;
    vector<string> words;
    vector<double> freq;

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

    InsertionSort(l);

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
        words.push_back(aux2->data.word);
        freq.push_back(aux2->data.repetition_number);
        aux2 = aux2->prox;
    }

    int size = sizeof(words) / sizeof(words[0]);
    HuffmanCodes(words, freq, size);
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