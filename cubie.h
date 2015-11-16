#ifndef CUBIE_H
#define CUBIE_H

#include <vector>

typedef std::vector<int> TouchList;

class Cubie
{

public:
    Cubie();

    void init(int cubie, std::vector<int>& simpleList);

    const TouchList& getTouchList();

private:
    void addPlane(int plane, const std::vector<int>& simpleList);

    TouchList touchList;
};

#endif // CUBIE_H
