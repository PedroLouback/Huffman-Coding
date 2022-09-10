#include "huffman.hpp"
#include "list.hpp"

int main()
{
    Lista l;
    Huffman huffman;

    FLVazia(&l);
    CreateHuffman(&huffman);

    ReadDocument(&l, &huffman);

    cout << "\nA compactação foi feita e se encontra no arquivo binarytext.bin!" << endl;

    return 0;
}