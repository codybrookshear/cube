#ifndef PUZZLE_H
#define PUZZLE_H

#include "puzzlefile.h"
#include "PuzzleModel.h"

/*! Main class that processes the Puzzle and word files, maintains
 *  the path structures and outputs the results computed
 */
class Puzzle
{
public:

    Puzzle();

    /*! causes the Puzzle and word files to be processed 
     *  \param PuzzleFile  file containing Puzzle definitions
     *  \param wordFile  file conttaining words to check for (a 
     *	"dictionary")*/
    void run(char *PuzzleFile, char *wordFile);

private:
	void printCube(char* cubeLine);
    PuzzleFile cubes;
    PuzzleFile words;
	PuzzleModel model;
};

#endif // PUZZLE_H
