#ifndef CUBE_H
#define CUBE_H

#include <fstream>
#include "cubie.h"

typedef std::vector<int> Path;

/*! Main class that processes the cube and word files, maintains
 *  the path structures and outputs the results computed
 */
class Cube
{
public:
    /*! constructor
     *  \param cubeFile  file containing cube definitions
     *  \param wordFile  file conttaining words to check for (a "dictionary")
     */
    Cube(char *cubeFile, char *wordFile );

    /*! causes the cube and word files to be processed */
    void run();

private:
    /*! main loop used to traverse the cubies, creating paths were characters
     *  match the given word being searched for.
     *  \returns true if the word was found in the cube, false otherwise
     */
    bool findWord();

    /*! called in constructor, helper method to initialize the cubies array
     *  \param plane    The plane (0 through 3) to setup cubies for.
     */
    void initCubbies(int plane);

    /*! traverses each letter in the word (after 1st letter)
     *  \returns true if the word was found in the cube, false otherwise
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

    /*! number of cubies in the cube. every line in a cube file is this long */
    static const int cubieCnt = 64;

    /*! the stream opened up to read in the cube file */
    std::ifstream cubeFile;

    /*! the stream opened up to read in the word file */
    std::ifstream wordFile;

    /*! array of 64 cubies, stores lists of which cubies touch each other */
    Cubie cubies[cubieCnt];

    /*! during processing, keeps track of possible paths through the cube */
    std::vector<Path> paths;

    /*! contains a single 64 character line representing a cube, a read from
     *  the cube file
     */
    std::string loadedCube;

    /*! contains a single word the cube is currently being checked for */
    std::string word;
};

#endif // CUBE_H
