#include "boggle.h"
#include <iostream>
#include <algorithm>

using namespace std;

Boggle::Boggle(char *cubeFile, char *wordFile)
    : cubies(), loadedCube(), word()
{
    for (int plane = 0; plane < 4; plane++)
    {
        initCubbies(plane);
    }
}

void Boggle::printTouchLists()
{
    for (int c = 0; c < cubieCnt; c++)
    {
        printTouchList(c);
    }

    cout << endl;
}

void Boggle::printTouchList(int c)
{
    cout << c << ": ";
    const TouchList& list = cubies[c].getTouchList();

    for (TouchList::const_iterator it = list.begin() ; it != list.end(); ++it)
        cout << *it << ", ";

    cout << endl;
}

void Boggle::printPaths()
{
    for (vector<Path>::iterator it = paths.begin() ; it != paths.end(); ++it)
    {
        cout << "Path ";

        for (int i = 0; i < (*it).size(); i++)
        {
            cout << (*it)[i] << "(" << word[i] << "), ";
        }
        cout << endl;
    }
}

void Boggle::setLoadedCube(string &cube)
{
    loadedCube = cube;
}

void Boggle::setWord(string &word)
{
    this->word = word;
}

bool Boggle::findWord()
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

bool Boggle::followWordPaths()
{
    // for each letter in word
    int wordSize = word.size();

    for (int i = 1; i < wordSize; i++)
    {
        for (vector<Path>::iterator it = paths.begin() ; it != paths.end(); ++it)
        {
            if ((*it).size() == i)
            {
                // paths could have expanded on us in a previous iteration,
                // so only call addPaths if current path size is as expected

                addPaths((*it), word[i]);
            }
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

bool Boggle::addPaths(Path &p, char c)
{
    // add any cubies that the last cubie in the path says we can get to and
    // that match character c

    bool firstTime = true;

    const TouchList& touchList = cubies[p.back()].getTouchList();

    TouchList::const_iterator it = touchList.begin();

    // go through the list of all cubies that the one at the end of our path
    // touches
    for(; it != touchList.end(); ++it)
    {
        if ( std::find(p.begin(), p.end(), (*it)) == p.end() )
        {
            // the cubie is not already on our path (a single cubie can only be
            // used once on a given path)

            if (loadedCube[(*it)] == c)
            {
                // this path made the cut! it touches the next req'd char

                if (firstTime)
                {
                    // first match, so just add cubie to our existing path
                    p.push_back(*it);
                    firstTime = false;
                }
                else
                {
                    // we already found one path and added to it. in this case,
                    // we duplicate the existing path and change the last element
                    // and then add it to paths.
                    Path newPath(p);
                    newPath[newPath.size()-1] = (*it);
                    paths.push_back(newPath);
                }
            }
        }
    }

    return (!firstTime);  // will return true if we added to atleast one word
}

void Boggle::removePathsShorterThan(int length)
{
    for (vector<Path>::iterator it = paths.begin() ; it != paths.end(); )
    {
        if ((*it).size() < length)
            it = paths.erase(it);
        else
            ++it;
    }
}

void Boggle::initCubbies(int plane)
{
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

