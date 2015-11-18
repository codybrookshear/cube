#ifndef CUBE_H
#define CUBE_H

#include <fstream>
#include "cubie.h"

typedef std::vector<int> Path;

class Cube
{
public:
    Cube(char *cubeFile, char *wordFile );

    void run();  // read from files, run the program

private:
    bool findWord();

    void initCubbies(int plane);

    bool followWordPaths();

    bool addPaths(unsigned int p, char c);

    void removePathsShorterThan(unsigned int length);

    int getPathPosition(unsigned int p, int cubie);

    static const int cubieCnt = 64;

    std::ifstream cubeFile;

    std::ifstream wordFile;

    Cubie cubies[cubieCnt];

    std::vector<Path> paths;

    std::string loadedCube;

    std::string word;
};

#endif // CUBE_H
