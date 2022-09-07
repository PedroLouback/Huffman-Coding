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
        cout << aux->data.word << " - " << aux->data.repetition_number << endl;
        aux = aux->prox;
    }
}
