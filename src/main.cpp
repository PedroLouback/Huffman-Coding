#include "huffman.hpp"
#include "list.hpp"

int main()
{
    Lista l;

    FLVazia(&l);

    ReadDocument(&l);

    cout << "A compactação foi feita e se encontra no arquivo compact_text.bin.\nAs palavras e suas respectivas sequências se encontram em sequence.txt.\n" << endl;

    return 0;
}