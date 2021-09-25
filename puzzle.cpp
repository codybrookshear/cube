#include "puzzle.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

Puzzle::Puzzle()
    : cubes(), words(), model()
{

}

void Puzzle::run(char *cubesFile, char *wordsFile)
{
    int inPuzzleCount = 0;
    char *word;
    char *cubeLine;

    cubes.loadFile(cubesFile);
    words.loadFile(wordsFile);

    for (cubeLine = cubes.getFirst(); cubeLine[0] != '\0'; cubeLine = cubes.getNext())
    {
		//printCube(cubeLine);
		clock_t startTime = clock();

		model.load(cubeLine);

        for (word = words.getFirst(); word[0] != '\0'; word = words.getNext())
        {
            bool found = model.findWord(word);
            if (found)
            {
                inPuzzleCount++;
            }
        }

        printf("%d\n", inPuzzleCount);
        inPuzzleCount = 0;
		fprintf(stderr, "scored cube in %f seconds.\n",
			((double)(clock() - startTime) / CLOCKS_PER_SEC));
    }
}

void Puzzle::printCube(char* cubeLine)
{
	printf(" 0 ");

	for (int i = 0; i < NUM_CUBES; i++)
	{
		if (i != 0)
		{
			if ((i % 16) == 0)
				printf("\n");

			if ((i % 4) == 0)
				printf("\n%2d ", i);
		}
	    printf("%c ", cubeLine[i]);
	}
	printf("\n\n");
}


