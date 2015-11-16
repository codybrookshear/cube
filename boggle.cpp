#include "boggle.h"
#include <iostream>

using namespace std;

Boggle::Boggle(char *cubeFile, char *wordFile)
    : cubies()
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
    const vector<int>& list = cubies[c].getTouchList();

    for (vector<int>::const_iterator it = list.begin() ; it != list.end(); ++it)
        cout << *it << ", ";

    cout << endl;
}

bool Boggle::findWord(string &word, string &loadedCube)
{
    // add a path for any that matches the first letter of the word

    for (int i = 0; i < cubieCnt; i++)
    {
        // find first char in cube matching word[0]
        if (loadedCube[i] == word[0])
        {
            std::vector<int> temp;
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
        return followWordPaths(word, loadedCube);
    }
}

bool Boggle::followWordPaths(string &word, string &loadedCube)
{
    // for each letter in word
    for (int i = 0; i < word.size(); i++)
    {
        for (vector<Path>::iterator p = paths.begin() ; p != paths.end(); ++p)
        {
            cout << "last: " << (*p).back();
        }
        cout << endl;
    }

    // TODO clear all paths out
    return false;
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

