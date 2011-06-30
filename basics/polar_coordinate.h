/*
 * polar_coordinate.h
 *
 *  Created on: 25.01.2011
 *      Author: steffen
 */

#ifndef POLAR_COORDINATE_H_
#define POLAR_COORDINATE_H_

#include <iostream>
#include "fix_values.h"
#include "point.h"

class Polar_coordinate
{
public:
    Polar_coordinate();
    Polar_coordinate(double alpha,double distance); //2D
    Polar_coordinate(double alpha,double distance,double alpha_std,double distance_std); //2D
    Polar_coordinate(double alpha,double beta,double distance); //3D
    Polar_coordinate(double alpha,double beta,double distance,double alpha_std,double beta_std,double distance_std); //3D
    Polar_coordinate(Point P);
    virtual ~Polar_coordinate();

    Polar_coordinate& operator = (const Polar_coordinate& P);

    //convert operator
    operator Point () const;
    Polar_coordinate& operator = (const Point& P);

    double get_alpha() const;
    double get_beta() const;
    double get_distance() const;

    void set_alpha(double alpha);
    void set_beta(double beta);
    void set_distance(double distance);

    friend ostream& operator<<(ostream& s,const Polar_coordinate& A);
private:
    void convert_polar_to_cartesian(Point& cart) const;
    void convert_cartesian_to_polar(const Point& cart);

    enum dim{_2D_,_3D_};
    dim m_dim;

    double m_alpha;
    double m_beta;
    double m_distance;
    double m_alpha_std;
    double m_beta_std;
    double m_distance_std;
};

ostream& operator<<(ostream& s,const Polar_coordinate& A);

#endif /* POLAR_COORDINATE_H_ */
