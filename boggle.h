#ifndef BOGGLE_H
#define BOGGLE_H

#include <fstream>
#include "cubie.h"

typedef std::vector<int> Path;

class Boggle
{
public:
    Boggle(char *cubeFile, char *wordFile );

    void printTouchLists();

    void printTouchList(int c);

    bool findWord(std::string& word, std::string& loadedCube);

    static const int cubieCnt = 64;

private:
    void initCubbies(int plane);

    bool followWordPaths(std::string &word, std::string &loadedCube);

    Cubie cubies[cubieCnt];

    std::vector<Path> paths;
};

#endif // BOGGLE_H
