#include <iostream>
#include <time.h>
#include "cube.h"
using namespace std;

int main(int argc, char* argv[])
{
    clock_t startTime = clock();

    if (argc != 3)
    {
        cout << "Usage:" << argv[0] << " <cube file> <dictionary>" << endl;
        return 0;
    }

    Cube cube(argv[1], argv[2]);

    cube.run();

    cerr << "scored cubes in "
         << ((double)(clock() - startTime)/CLOCKS_PER_SEC)
         << " seconds." << endl;

    return 0;
}

