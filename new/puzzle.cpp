#include "puzzle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Puzzle::Puzzle()
    : squares(),
      loadedPuzzle(),
      word()
{

}

void Puzzle::loadPuzzles(char *puzzleFile)
{

}

void Puzzle::loadWords(char *wordFile)
{
    loadFile(wordFile, wordBuf, &wordBufSize);

    // point first word at start of buffer
    word = wordBuf;

    printf("%s %d\n", word, wordBufSize);
}

void Puzzle::loadFile(char *filename, char *buf, long *fsize)
{
    // copy the wordFile into memory to make sure we don't waste
    // time reading from disk repeatedly

    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);
    
    buf = (char*)malloc(fsize + 1);
    fread(buf, fsize, 1, f);
    fclose(f);

    buf[fsize] = 0;
    
    // convert all newlines to null chars
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '\n')
            buf[i] = '\0';
    }
}

bool Puzzle::getNextPuzzle()
{
    return false;
}

bool Puzzle::getNextWord()
{
    return false;
}

void Puzzle::run(char *PuzzleFile, char *wordFile)
{
    int inPuzzleCount = 0;

    loadPuzzles(PuzzleFile);
    loadWords(wordFile);

    while(getNextPuzzle())
    {
        while (getNextWord())
        {
            bool found = findWord();
            if (found)
            {
                inPuzzleCount++;
            }
        }

        printf("%d\n", inPuzzleCount);
        inPuzzleCount = 0;
    }
}

bool Puzzle::findWord()
{
    // clear all paths from previous iterations out
    memcpy((void*)paths, (void*)BK, NUM_SQUARES*NUM_SQUARES*sizeof(paths[0]));
    pathsCount = 0;
    //for (int i = 0; i < NUM_SQUARES; i++)
    //{
    //    for (int j = 0; j < NUM_SQUARES; j++)
    //       paths[i][j] = BK;
    //}

    // add a path for any that matches the first letter of the word

    for (int square = 0; square < NUM_SQUARES; square++)
    {
        // find first char in Puzzle matching word[0]
        if (loadedPuzzle[square] == word[0])
        {
	    paths[pathsCount][0] = square;
            ++pathsCount;
        }
    }

    if (pathsCount == 0)
    {
        return false;
    }
    else
    {
        return followWordPaths();
    }
}

bool Puzzle::followWordPaths()
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
/*
    const TouchList& touchList = squares[paths[p].back()].getTouchList();

    TouchList::const_iterator it = touchList.begin();

    // go through the list of all squares that the one at the end of our path
    // touches
    for(; it != touchList.end(); ++it)
    {
        if (getPathPosition(p, (*it)) == -1)
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
    }
*/
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

