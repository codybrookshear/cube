#include "puzzle.h"
#include <stdio.h>
#include <string.h>

Puzzle::Puzzle()
    : cubes(), words()
{

}

void Puzzle::run(char *cubesFile, char *wordsFile)
{
    int inPuzzleCount = 0;
    char *word;
    char *cube;

    cubes.loadFile(cubesFile);
    words.loadFile(wordsFile);

    for (cube = cubes.getFirst(); cube = cubes.getNext(); cube != 0)
    {
	printf("cube: %s\n", cube);
	for (int i = 0; i < NUM_SQUARES; i++)
        {
            printf("cube[%d]=%c\n", i, cubes.getCurrent()[i]);
        }

	for (word = words.getFirst(); word = words.getNext(); word != 0)
        {
	    //printf("%s\n", word);
            bool found = findWord(word, cube);
            if (found)
            {
                inPuzzleCount++;
            }
        }

        printf("%d\n", inPuzzleCount);
        inPuzzleCount = 0;
    }
}

bool Puzzle::findWord(char* word, char* cube)
{
    // clear all paths from previous iterations out
    memset((void*)paths, (int)BK, sizeof(paths));
    pathsCount = 0;

    // add a path for any that matches the first letter of the word

    for (int square = 0; square < NUM_SQUARES; square++)
    {
        // find first char in Puzzle matching word[0]
        if (cube[square] == word[0])
        {
	    paths[pathsCount][0] = square;
            
            printf("set paths[%d][0]=%d, contains %c in %s\n", pathsCount, square, word[0], word);
	    ++pathsCount;
        }
    }

    if (pathsCount == 0)
    {
        return false;
    }
    else
    {
        return followWordPaths(word);
    }
}

bool Puzzle::followWordPaths(char* word)
{
    // for each letter in word
    size_t wordSize = strlen(word);

    for (size_t i = 1; i < wordSize; i++)
    {
        // paths could expand from iteration to iteration, so important to loop
        // based on size of vector at start of loop

        for (unsigned int p = 0; p < pathsCount; p++ )
        {
            addPaths(p, word[i]);
        }

        // remove paths that didn't get added to in for loop (didn't "make the cut")
        removePathsShorterThan(i+1);
    }

    // if we make it here and there are any paths remaining, that means we found
    // the word!
    if (pathsCount > 0)
         return true;

    return false;
}

bool Puzzle::addPaths(unsigned int p, char c)
{
    // add any squares that the last cubie in the path says we can get to and
    // that match character c

    bool firstTime = true;

    //const unsigned char* touchList = squares[paths[p]];

    // go through the list of all squares that the one at the end of our path
    // touches
    //for(int i = 0; touchList[i] != BK; ++i)
    //{
        /*if (getPathPosition(p, (*it)) == -1)
        {
            // the cubie is not already on our path (a single cubie can only be
            // used once on a given path)

            if (loadedPuzzle[(*it)] == c)
            {
                // this path made the cut! it touches the next req'd char

                if (firstTime)
                {
                    // first match, so just add cubie to our existing path
                    paths[p].push_back(*it);
                    firstTime = false;
                }
                else
                {
                    // we already found one path and added to it. in this case,
                    // we duplicate the existing path and change the last element
                    // and then add it to paths.
                    Path newPath(paths[p]);
                    newPath[newPath.size()-1] = (*it);
                    paths.push_back(newPath);
                }
            }
        }
    }*/
    return (!firstTime);  // will return true if we added to atleast one word
}

void Puzzle::removePathsShorterThan(unsigned int length)
{
    /*for (vector<Path>::iterator it = paths.begin() ; it != paths.end(); )
    {
        if ((*it).size() < length)
            it = paths.erase(it);
        else
            ++it;
    }*/
    //for (int i = 0; i < 
}

int Puzzle::getPathPosition(unsigned int p, int cubie)
{
    /*Path::size_type pSize = paths[p].size();
    for (Path::size_type i = 0; i < pSize; i++)
    {
        if (paths[p][i] == cubie)
            return i;
    }*/

    return -1;  // returns -1 if not found
}

