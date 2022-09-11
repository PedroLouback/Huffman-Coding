#include "huffman.hpp"
#include "list.hpp"

int main()
{
    Lista l;
    Huffman huffman;

    FLVazia(&l);
    CreateHuffman(&huffman);

    ReadDocument(&l, &huffman);

    cout << "A compactação foi feita e se encontra no arquivo compact_text.bin.\nAs palavras e suas respectivas sequências se encontram em sequence.txt.\n" << endl;

    return 0;
}