#include "huffman.hpp"
#include "list.hpp"

int main()
{
    Lista l;
    Huffman huffman;

    FLVazia(&l);
    CreateHuffman(&huffman);

    ReadDocument(&l, &huffman);

    return 0;
}