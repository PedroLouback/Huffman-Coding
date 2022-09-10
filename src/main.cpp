#include "huffman.hpp"
#include "list.hpp"

int main()
{
    Lista l;
    Huffman huffman;

    FLVazia(&l);
    CreateHuffman(&huffman);

    ReadDocument(&l, &huffman);

    cout << "\nA compactação foi feita e se encontra no arquivo compact_text.bin!\n" << endl;

    return 0;
}