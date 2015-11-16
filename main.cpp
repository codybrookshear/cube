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
    //b.printTouchLists();

    std::string cube("eqeffvxnhnalxvqbcaypicpvxtacesqgcyrnrygmmzhvxcvrdsutfwawokdqsyrs");
    b.setLoadedCube(cube);

    std::string word("efvx");
    b.setWord(word);

    bool found = b.findWord();
    cout << "found: " << found << endl;

    b.printPaths();

    return 0;
}

