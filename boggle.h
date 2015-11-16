#ifndef BOGGLE_H
#define BOGGLE_H

#include <fstream>
#include "cubie.h"

typedef std::vector<int> Path;

class Boggle
{
public:
    Boggle(char *cubeFile, char *wordFile );

    void printTouchLists(); // debug

    void printTouchList(int c); // debug

    void printPaths(); // debug

    void setLoadedCube(std::string& cube);

    void setWord(std::string& word);

    bool findWord();

    static const int cubieCnt = 64;

private:
    void initCubbies(int plane);

    bool followWordPaths();

    bool addPaths(Path &p, char c);

    void removePathsShorterThan(int length);

    Cubie cubies[cubieCnt];

    std::vector<Path> paths;

    std::string loadedCube;

    std::string word;
};

#endif // BOGGLE_H
