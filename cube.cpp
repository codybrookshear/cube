#include "cube.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

Cube::Cube(char *cubeFile, char *wordFile)
    : cubeFile(cubeFile),
      wordFile(wordFile),
      cubies(),
      loadedCube(),
      word()
{
    // initialize all 64 cubies
    for (int plane = 0; plane < 4; plane++)
    {
        initCubbies(plane);
    }
}

void Cube::run()
{
    int inCubeCount = 0;

    // copy the wordFile into memory to make sure we don't waste
    // time reading from disk repeatedly
    std::stringstream ss;
    ss << wordFile.rdbuf();


    while(std::getline(cubeFile, loadedCube))
    {
        // start at the beginning of the word file for each "cube"
        ss.clear();
        ss.seekg(0, ios::beg);

        while (ss >> word)
        {
            bool found = findWord();
            if (found)
            {
                inCubeCount++;
            }
        }

        cout << inCubeCount << endl;
        inCubeCount = 0;
    }
}

bool Cube::findWord()
{
    // clear all paths from previous iterations out
    for (vector<Path>::iterator it = paths.begin() ; it != paths.end(); )
    {
        it = paths.erase(it);
    }

    // add a path for any that matches the first letter of the word

    for (int i = 0; i < cubieCnt; i++)
    {
        // find first char in cube matching word[0]
        if (loadedCube[i] == word[0])
        {
            Path temp;
            temp.push_back(i);
            paths.push_back(temp);
        }
    }

    if (paths.size() == 0)
    {
        return false;
    }
    else
    {
        return followWordPaths();
    }
}

bool Cube::followWordPaths()
{
    // for each letter in word
    size_t wordSize = word.size();

    for (size_t i = 1; i < wordSize; i++)
    {
        // paths could expand from iteration to iteration, so important to loop
        // based on size of vector at start of loop

        unsigned int pathSize = paths.size();
        for (unsigned int p = 0; p < pathSize; p++ )
        {
            addPaths(p, word[i]);
        }

        // remove paths that didn't get added to in for loop (didn't "make the cut")
        removePathsShorterThan(i+1);
    }

    // if we make it here and there are any paths remaining, that means we found
    // the word!
    if (paths.size() > 0)
         return true;

    return false;
}

bool Cube::addPaths(unsigned int p, char c)
{
    // add any cubies that the last cubie in the path says we can get to and
    // that match character c

    bool firstTime = true;

    const TouchList& touchList = cubies[paths[p].back()].getTouchList();

    TouchList::const_iterator it = touchList.begin();

    // go through the list of all cubies that the one at the end of our path
    // touches
    for(; it != touchList.end(); ++it)
    {
        if (getPathPosition(p, (*it)) == -1)
        {
            // the cubie is not already on our path (a single cubie can only be
            // used once on a given path)

            if (loadedCube[(*it)] == c)
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

    return (!firstTime);  // will return true if we added to atleast one word
}

void Cube::removePathsShorterThan(unsigned int length)
{
    for (vector<Path>::iterator it = paths.begin() ; it != paths.end(); )
    {
        if ((*it).size() < length)
            it = paths.erase(it);
        else
            ++it;
    }
}

int Cube::getPathPosition(unsigned int p, int cubie)
{
    Path::size_type pSize = paths[p].size();
    for (Path::size_type i = 0; i < pSize; i++)
    {
        if (paths[p][i] == cubie)
            return i;
    }

    return -1;  // returns -1 if not found
}

void Cube::initCubbies(int plane)
{
    // a note about how this works
    // a single "plane" is made up of 16 cubies in a 4x4 grid
    // the overall cube is then 4 planes stacked on top of each other
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

    int arr0[] = {1, 4, 5};
    vector<int> v0(arr0, arr0 +3);
    cubies[0 + (plane * 16)].init(0 + (plane * 16), v0);

    int arr1[] = {0, 2,  4,  5,  6};
    vector<int> v1(arr1, arr1 +5);
    cubies[1 + (plane * 16)].init(1 + (plane * 16), v1);

    int arr2[] = {1,  3,  5,  6,  7};
    vector<int> v2(arr2, arr2 +5);
    cubies[2 + (plane * 16)].init(2 + (plane * 16), v2);

    int arr3[] = {2,  6,  7};
    vector<int> v3(arr3, arr3 +3);
    cubies[3 + (plane * 16)].init(3 + (plane * 16), v3);

    int arr4[] = {0,  1,  5,  8,  9};
    vector<int> v4(arr4, arr4 +5);
    cubies[4 + (plane * 16)].init(4 + (plane * 16), v4);

    int arr5[] = {0,  1,  2,  4,  6,  8,  9, 10};
    vector<int> v5(arr5, arr5 +8);
    cubies[5 + (plane * 16)].init(5 + (plane * 16), v5);

    int arr6[] = {1,  2,  3,  5,  7,  9, 10, 11};
    vector<int> v6(arr6, arr6 +8);
    cubies[6 + (plane * 16)].init(6 + (plane * 16), v6);

    int arr7[] = {2,  3,  6, 10, 11};
    vector<int> v7(arr7, arr7 +5);
    cubies[7 + (plane * 16)].init(7 + (plane * 16), v7);

    int arr8[] = {4,  5, 9, 12, 13};
    vector<int> v8(arr8, arr8 +5);
    cubies[8 + (plane * 16)].init(8 + (plane * 16), v8);

    int arr9[] = {4,  5,  6,  8, 10, 12, 13, 14};
    vector<int> v9(arr9, arr9 +8);
    cubies[9 + (plane * 16)].init(9 + (plane * 16), v9);

    int arr10[] = {5,  6,  7,  9, 11, 13, 14, 15};
    vector<int> v10(arr10, arr10 +8);
    cubies[10 + (plane * 16)].init(10 + (plane * 16), v10);

    int arr11[] = {6,  7, 10, 14, 15};
    vector<int> v11(arr11, arr11 +5);
    cubies[11 + (plane * 16)].init(11 + (plane * 16), v11);

    int arr12[] = {8,  9, 13};
    vector<int> v12(arr12, arr12 +3);
    cubies[12 + (plane * 16)].init(12 + (plane * 16), v12);

    int arr13[] = {8,  9, 10, 12, 14};
    vector<int> v13(arr13, arr13 +5);
    cubies[13 + (plane * 16)].init(13 + (plane * 16), v13);

    int arr14[] = {9, 10, 11, 13, 15};
    vector<int> v14(arr14, arr14 +5);
    cubies[14 + (plane * 16)].init(14 + (plane * 16), v14);

    int arr15[] = {10, 11, 14};
    vector<int> v15(arr15, arr15 +3);
    cubies[15 + (plane * 16)].init(15 + (plane * 16), v15);
}

