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
    bool findWord();

    void initCubbies(int plane);

    bool followWordPaths();

    bool addPaths(unsigned int p, char c);

    void removePathsShorterThan(unsigned int length);

    int getPathPosition(unsigned int p, int cubie);

    /*! the number of cubies in the cube. every line in a cube file is this long */
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
