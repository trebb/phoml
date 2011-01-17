/*
 * forward_intersection_bore.h
 *
 *  Created on: 19.11.2010
 *      Author: steffen
 */

#ifndef FORWARD_INTERSECTION_BORE_H_
#define FORWARD_INTERSECTION_BORE_H_

#include <iostream>
#include <vector>

#include "..//photo/forward_intersection.h"
#include "bpoint_bore.h"

class Forward_intersection_bore// : public std::vector<BPoint_bore>
{
public:
    Forward_intersection_bore(std::vector<BPoint_bore> &bpl);
    virtual ~Forward_intersection_bore();

    void calc();

    Point_nr get_intersection_point() const { return m_intersection_point; }
    bool  get_is_error()           const { return m_is_error; }

private:

    //list
    std::vector<BPoint_bore>    *m_bpoint_bore_list_intern;

    Point_nr m_intersection_point;

    bool  m_is_error;

    //class for using command //for_each(inters.begin(),inters.end(),print<CBpoint_pmn>());
    template <class T> class set_Point
    {
     public:
     void operator() (const T& elem) { cout << elem << endl; }
    };
};

#endif /* FORWARD_INTERSECTION_BORE_H_ */
