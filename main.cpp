#include <iostream>
#include "boggle.h"
using namespace std;

int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        cout << "Usage:" << argv[0] << " <cube file> <dictionary>" << endl;
        return 0;
    }

    Boggle b(argv[1], argv[2]);
    b.printTouchLists();

    std::string cube("eqeffvxnhnalxvqbcaypicpvxtacesqgcyrnrygmmzhvxcvrdsutfwawokdqsyrs");
    std::string word("efvx");
    b.findWord(word, cube);

    return 0;
}

