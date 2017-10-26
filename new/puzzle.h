#ifndef SQUARE_H
#define SQUARE_H

#include "cubie.h"


/*! Main class that processes the Puzzle and word files, maintains
 *  the path structures and outputs the results computed
 */
class Puzzle
{
public:
    /*! constructor
     *  \param PuzzleFile  file containing Puzzle definitions
     *  \param wordFile  file conttaining words to check for (a "dictionary")
     */
    Puzzle();

    /*! causes the Puzzle and word files to be processed */
    void run(char *PuzzleFile, char *wordFile);

private:
    /*! main loop used to traverse the cubies, creating paths were characters
     *  match the given word being searched for.
     *  \returns true if the word was found in the Puzzle, false otherwise
     */
    bool findWord();

    /*! called in constructor, helper method to initialize the cubies array
     *  \param plane    The plane (0 through 3) to setup cubies for.
     */
    void initCubbies(int plane);

    /*! traverses each letter in the word (after 1st letter)
     *  \returns true if the word was found in the Puzzle, false otherwise
     */
    bool followWordPaths();

    /*! add any cubies that the last cubie in the path says we can get to and
     *  that match character c
     *  \param p    The index in paths[] array to process
     *  \param c    The character we are trying to match
     *  \returns    true if at least one path was modifed or added,
     *              false otherwise
     */
    bool addPaths(unsigned int p, char c);

    /*! searches paths[] array for any paths that are shorter than a given
     *  length, and removes them.
     *  \param length
     */
    void removePathsShorterThan(unsigned int length);

    /*! find the cubie in the given path
     *  \param p        The index of the path in the paths array to search
     *  \param cubie    The "number" of the cubie to find
     *  \returns        The index in the given path if the cubie is found,
     *                  -1 otherwise
     */
    int getPathPosition(unsigned int p, int cubie);

    void loadPuzzles(char *puzzleFile);

    void loadWords(char *wordFile);

    void loadFile(Char *filename);

    bool getNextPuzzle();

    bool getNextWord();

    /*! number of cubies in the Puzzle. every line in a Puzzle file is this long */
    static const int NUM_SQUARES = 64;

    /*! number of planes that make up the puzzle */
    static const int NUM_PLANES = 4;

    static const unsigned char BK = 0xFF;

    static const unsigned char MAX_BORDERING = 26;

    // a note about how this works
    // a single "plane" is made up of 16 squares in a 4x4 grid
    // the overall Puzzle is then 4 planes stacked on top of each other
    // the top plane (plane at index 0) looks like this:
    //
    //  0  1  2  3
    //  4  5  6  7
    //  8  9 10 11
    // 12 13 14 15
    //
    // the next plane, underneath the top plane starts with 16, 17, etc.
    // cubie[0] can touch 1, 4, and 5 on it's own plane, and 0, 1, 4, and 5
    // on the plane below it.
    /*! array of 64 cubies, stores lists of which cubies touch each other */
    unsigned char squares[NUM_SQUARES][MAX_BORDERING] =
    {
{1, 4, 5, 17, 20, 21, 16, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 0
{0, 2, 4, 5, 6, 16, 18, 20, 21, 22, 17, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 1
{1, 3, 5, 6, 7, 17, 19, 21, 22, 23, 18, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 2
{2, 6, 7, 18, 22, 23, 19, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 3
{0, 1, 5, 8, 9, 16, 17, 21, 24, 25, 20, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 4
{0, 1, 2, 4, 6, 8, 9, 10, 16, 17, 18, 20, 22, 24, 25, 26, 21, BK, BK, BK, BK, BK, BK, BK, BK }, // 5
{1, 2, 3, 5, 7, 9, 10, 11, 17, 18, 19, 21, 23, 25, 26, 27, 22, BK, BK, BK, BK, BK, BK, BK, BK }, // 6
{2, 3, 6, 10, 11, 18, 19, 22, 26, 27, 23, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 7
{4, 5, 9, 12, 13, 20, 21, 25, 28, 29, 24, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 8
{4, 5, 6, 8, 10, 12, 13, 14, 20, 21, 22, 24, 26, 28, 29, 30, 25, BK, BK, BK, BK, BK, BK, BK, BK }, // 9
{5, 6, 7, 9, 11, 13, 14, 15, 21, 22, 23, 25, 27, 29, 30, 31, 26, BK, BK, BK, BK, BK, BK, BK, BK }, // 10
{6, 7, 10, 14, 15, 22, 23, 26, 30, 31, 27, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 11
{8, 9, 13, 24, 25, 29, 28, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 12
{8, 9, 10, 12, 14, 24, 25, 26, 28, 30, 29, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 13
{9, 10, 11, 13, 15, 25, 26, 27, 29, 31, 30, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 14
{10, 11, 14, 26, 27, 30, 31, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 15
{1, 4, 5, 0, 17, 20, 21, 33, 36, 37, 32, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 16
{0, 2, 4, 5, 6, 1, 16, 18, 20, 21, 22, 32, 34, 36, 37, 38, 33, BK, BK, BK, BK, BK, BK, BK, BK }, // 17
{1, 3, 5, 6, 7, 2, 17, 19, 21, 22, 23, 33, 35, 37, 38, 39, 34, BK, BK, BK, BK, BK, BK, BK, BK }, // 18
{2, 6, 7, 3, 18, 22, 23, 34, 38, 39, 35, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 19
{0, 1, 5, 8, 9, 4, 16, 17, 21, 24, 25, 32, 33, 37, 40, 41, 36, BK, BK, BK, BK, BK, BK, BK, BK }, // 20
{0, 1, 2, 4, 6, 8, 9, 10, 5, 16, 17, 18, 20, 22, 24, 25, 26, 32, 33, 34, 36, 38, 40, 41, 42, 37 }, // 21
{1, 2, 3, 5, 7, 9, 10, 11, 6, 17, 18, 19, 21, 23, 25, 26, 27, 33, 34, 35, 37, 39, 41, 42, 43, 38 }, // 22
{2, 3, 6, 10, 11, 7, 18, 19, 22, 26, 27, 34, 35, 38, 42, 43, 39, BK, BK, BK, BK, BK, BK, BK, BK }, // 23
{4, 5, 9, 12, 13, 8, 20, 21, 25, 28, 29, 36, 37, 41, 44, 45, 40, BK, BK, BK, BK, BK, BK, BK, BK }, // 24
{4, 5, 6, 8, 10, 12, 13, 14, 9, 20, 21, 22, 24, 26, 28, 29, 30, 36, 37, 38, 40, 42, 44, 45, 46, 41 }, // 25
{5, 6, 7, 9, 11, 13, 14, 15, 10, 21, 22, 23, 25, 27, 29, 30, 31, 37, 38, 39, 41, 43, 45, 46, 47, 42 }, // 26
{6, 7, 10, 14, 15, 11, 22, 23, 26, 30, 31, 38, 39, 42, 46, 47, 43, BK, BK, BK, BK, BK, BK, BK, BK }, // 27
{8, 9, 13, 12, 24, 25, 29, 40, 41, 45, 44, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 28
{8, 9, 10, 12, 14, 13, 24, 25, 26, 28, 30, 40, 41, 42, 44, 46, 45, BK, BK, BK, BK, BK, BK, BK, BK }, // 29
{9, 10, 11, 13, 15, 14, 25, 26, 27, 29, 31, 41, 42, 43, 45, 47, 46, BK, BK, BK, BK, BK, BK, BK, BK }, // 30
{10, 11, 14, 15, 26, 27, 30, 42, 43, 46, 47, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 31
{17, 20, 21, 16, 33, 36, 37, 49, 52, 53, 48, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 32
{16, 18, 20, 21, 22, 17, 32, 34, 36, 37, 38, 48, 50, 52, 53, 54, 49, BK, BK, BK, BK, BK, BK, BK, BK }, // 33
{17, 19, 21, 22, 23, 18, 33, 35, 37, 38, 39, 49, 51, 53, 54, 55, 50, BK, BK, BK, BK, BK, BK, BK, BK }, // 34
{18, 22, 23, 19, 34, 38, 39, 50, 54, 55, 51, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 35
{16, 17, 21, 24, 25, 20, 32, 33, 37, 40, 41, 48, 49, 53, 56, 57, 52, BK, BK, BK, BK, BK, BK, BK, BK }, // 36
{16, 17, 18, 20, 22, 24, 25, 26, 21, 32, 33, 34, 36, 38, 40, 41, 42, 48, 49, 50, 52, 54, 56, 57, 58, 53 }, // 37
{17, 18, 19, 21, 23, 25, 26, 27, 22, 33, 34, 35, 37, 39, 41, 42, 43, 49, 50, 51, 53, 55, 57, 58, 59, 54 }, // 38
{18, 19, 22, 26, 27, 23, 34, 35, 38, 42, 43, 50, 51, 54, 58, 59, 55, BK, BK, BK, BK, BK, BK, BK, BK }, // 39
{20, 21, 25, 28, 29, 24, 36, 37, 41, 44, 45, 52, 53, 57, 60, 61, 56, BK, BK, BK, BK, BK, BK, BK, BK }, // 40
{20, 21, 22, 24, 26, 28, 29, 30, 25, 36, 37, 38, 40, 42, 44, 45, 46, 52, 53, 54, 56, 58, 60, 61, 62, 57 }, // 41
{21, 22, 23, 25, 27, 29, 30, 31, 26, 37, 38, 39, 41, 43, 45, 46, 47, 53, 54, 55, 57, 59, 61, 62, 63, 58 }, // 42
{22, 23, 26, 30, 31, 27, 38, 39, 42, 46, 47, 54, 55, 58, 62, 63, 59, BK, BK, BK, BK, BK, BK, BK, BK }, // 43
{24, 25, 29, 28, 40, 41, 45, 56, 57, 61, 60, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 44
{24, 25, 26, 28, 30, 29, 40, 41, 42, 44, 46, 56, 57, 58, 60, 62, 61, BK, BK, BK, BK, BK, BK, BK, BK }, // 45
{25, 26, 27, 29, 31, 30, 41, 42, 43, 45, 47, 57, 58, 59, 61, 63, 62, BK, BK, BK, BK, BK, BK, BK, BK }, // 46
{26, 27, 30, 31, 42, 43, 46, 58, 59, 62, 63, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 47
{33, 36, 37, 32, 49, 52, 53, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 48
{32, 34, 36, 37, 38, 33, 48, 50, 52, 53, 54, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 49
{33, 35, 37, 38, 39, 34, 49, 51, 53, 54, 55, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 50
{34, 38, 39, 35, 50, 54, 55, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 51
{32, 33, 37, 40, 41, 36, 48, 49, 53, 56, 57, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 52
{32, 33, 34, 36, 38, 40, 41, 42, 37, 48, 49, 50, 52, 54, 56, 57, 58, BK, BK, BK, BK, BK, BK, BK, BK }, // 53
{33, 34, 35, 37, 39, 41, 42, 43, 38, 49, 50, 51, 53, 55, 57, 58, 59, BK, BK, BK, BK, BK, BK, BK, BK }, // 54
{34, 35, 38, 42, 43, 39, 50, 51, 54, 58, 59, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 55
{36, 37, 41, 44, 45, 40, 52, 53, 57, 60, 61, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 56
{36, 37, 38, 40, 42, 44, 45, 46, 41, 52, 53, 54, 56, 58, 60, 61, 62, BK, BK, BK, BK, BK, BK, BK, BK }, // 57
{37, 38, 39, 41, 43, 45, 46, 47, 42, 53, 54, 55, 57, 59, 61, 62, 63, BK, BK, BK, BK, BK, BK, BK, BK }, // 58
{38, 39, 42, 46, 47, 43, 54, 55, 58, 62, 63, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 59
{40, 41, 45, 44, 56, 57, 61, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 60
{40, 41, 42, 44, 46, 45, 56, 57, 58, 60, 62, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 61
{41, 42, 43, 45, 47, 46, 57, 58, 59, 61, 63, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }, // 62
{42, 43, 46, 47, 58, 59, 62, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK }  // 63
    };

    /*! during processing, keeps track of possible paths through the Puzzle */
    unsigned char paths[NUM_SQUARES][NUM_SQUARES];
    /*! contains a single 64 character line representing a Puzzle, a read from
     *  the Puzzle file
     */
    char loadedPuzzle[NUM_SQUARES];

    /*! contains a single word the Puzzle is currently being checked for */
    char *word;

    /*! number of paths currently in use */
    int pathsCount;
};

#endif // Puzzle_H
