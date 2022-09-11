#include "list.hpp"

void Swap(Block *a, Block *b)
{
    Item aux;
    aux = a->data;
    a->data = b->data;
    b->data = aux;
}

void FLVazia(Lista *l)
{
    l->first = new Block;
    l->last = 0;
    l->last = l->first;
    l->first->prox = NULL;
}

void LInsert(Lista *l, Item d)
{

    l->last->prox = new Block;
    l->last = l->last->prox;
    l->last->data = d;
    l->last->prox = NULL;
}

void LImprime(Lista *l)
{
    Block *aux;

    aux = l->first->prox;
    while (aux != NULL)
    {
        cout << "Palavra: " << aux->data.word << " || Normalização: " << aux->data.repetition_number << endl;
        aux = aux->prox;
    }
}

void InsertionSort(Lista *l)
{
    assert(l != NULL);

    if (l->first != NULL)
    {
        for (Block *i = l->first; i->prox != NULL; i = i->prox)
        {
            Block *menor = i;
            for (Block *j = i->prox; j != NULL; j = j->prox)
            {
                if (j->data.repetition_number < menor->data.repetition_number)
                {
                    menor = j;
                }
                Item aux = i->data;
                i->data = menor->data;
                menor->data = aux;
            }
        }
    }
}
