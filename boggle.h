#ifndef BOGGLE_H
#define BOGGLE_H

#include <fstream>
#include "cubie.h"

class Boggle
{
public:
    Boggle(char *cubeFile, char *wordFile );

    void printTouchLists();

    void printTouchList(int c);

    bool findWord(std::string& word, std::string& cube);

    static const int cubieCnt = 64;

private:
    void initCubbies(int plane);

    Cubie cubies[cubieCnt];
};

#endif // BOGGLE_H
