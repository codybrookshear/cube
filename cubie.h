#ifndef CUBIE_H
#define CUBIE_H

#include <vector>

class Cubie
{

public:
    Cubie();

    void init(int cubie, std::vector<int>& simpleList);

    const std::vector<int>& getTouchList();

private:
    void addPlane(int plane, const std::vector<int>& simpleList);

    std::vector<int> touchList;
};

#endif // CUBIE_H
