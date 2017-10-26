#include "stdio.h"
#include <time.h>
#include "puzzle.h"

int main(int argc, char* argv[])
{
    clock_t startTime = clock();

    if (argc != 3)
    {
        printf("Usage: %s <cube-file> <dictionary-file>\n", argv[0]);
        return 0;
    }

    Puzzle p;

    p.run(argv[1], argv[2]);

    fprintf(stderr, "scored cubes in %f seconds.\n",
          ((double)(clock() - startTime)/CLOCKS_PER_SEC));

    return 0;
}

