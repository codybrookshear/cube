#ifndef CUBIE_H
#define CUBIE_H

#include <vector>

typedef std::vector<int> TouchList;

/*! stores information about a cubie element in a Cube*/
class Cubie
{

public:
    /*! basic, empty constructor*/
    Cubie();

    /*! initializes the cubie's touchList
     *  \param cubie        The "number" of the cubie (index in cubies array)
     *  \param simpleList   List of other cubies this one "touches" i.e. the
     *                      paths that can be traversed to from this cubie, in
     *                      terms of cubies 0-15 (plane centric), but we declare 64
     *                      cubies total.
     *                      The list only provides the cubies touched as if the cubie
     *                      appeared on the first plane. We have to calculate which
     *                      plane "cubie" actually belongs to, then extrapolate what all
     *                      cubies actually can be tocuhed by cubie parameter passed in.
     */
    void init(int cubie, std::vector<int>& simpleList);

    /*! provides access the cubie's touch list
     *  \returns    A constant reference to the cubie's touch list
     */
    const TouchList& getTouchList();

private:
    /*! helper method to initialize a touch list
     *  \param plane        The plane number to be initialized (0-3)
     *  \param simpleList   A vector of integers that is complete for the single
     *                      plane only
     */
    void addPlane(int plane, const std::vector<int>& simpleList);

    /*! a vector of integers (positions in the cube of other cubies that can be
     *  reached by this one.
     */
    TouchList touchList;
};

#endif // CUBIE_H
