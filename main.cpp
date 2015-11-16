#include <iostream>
#include <time.h>
#include "boggle.h"
using namespace std;

int main(int argc, char* argv[])
{
    clock_t startTime = clock();

    if (argc != 3)
    {
        cout << "Usage:" << argv[0] << " <cube file> <dictionary>" << endl;
        return 0;
    }

    Boggle b(argv[1], argv[2]);

    b.run();

    cerr << "score X cubes with dimension 4 in "
         << ((double)(clock() - startTime)/CLOCKS_PER_SEC)
         << " seconds." << endl;

    return 0;
}

