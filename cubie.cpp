#include <iostream>
#include "cubie.h"

using namespace std;

Cubie::Cubie()
    : touchList()
{
}

void Cubie::init(int cubie, std::vector<int> &simpleList)
{
    int plane = cubie / 16;

    if (plane == 0)
    {
        // for plane 0, we get what's in list 2x, plane 0 and 1
        addPlane(0, simpleList);
        addPlane(1, simpleList);

        // we can reach square directly underneath us
        touchList.push_back(cubie + 16);
    }
    else if (plane == 1)
    {
        // for plane 1, we get what's in list 3x, plane 0, 1, and 2
        addPlane(0, simpleList);

        // we can reach square directly above us
        touchList.push_back(cubie - 16);

        addPlane(1, simpleList);
        addPlane(2, simpleList);

        // we can reach square directly underneath us
        touchList.push_back(cubie + 16);
    }
    else if (plane == 2)
    {
        // for plane 2, we get what's in list 3x, plane 1, 2, and 3

        addPlane(1, simpleList);

        // we can reach square directly above us
        touchList.push_back(cubie - 16);

        addPlane(2, simpleList);
        addPlane(3, simpleList);

        // we can reach square directly underneath us
        touchList.push_back(cubie + 16);
    }
    else // plane 3
    {
        // for plane 3, we get what's in list 2x, plane 2 and 3
        addPlane(2, simpleList);

        // we can reach square directoy above us
        touchList.push_back(cubie - 16);

        addPlane(3, simpleList);
    }

}

const TouchList &Cubie::getTouchList()
{
    return touchList;
}

void Cubie::addPlane(int plane, const vector<int>& simpleList)
{
    int simpleListSize = simpleList.size();

    for (int s = 0; s < simpleListSize; s++)
    {
        touchList.push_back(simpleList[s] + (16 * plane));
    }
}
