/*
 * polar_coordinate.cpp
 *
 *  Created on: 25.01.2011
 *      Author: steffen
 */

#include "polar_coordinate.h"

#include <cmath>

Polar_coordinate::Polar_coordinate()
{
    m_alpha=m_beta=m_distance=0.0;
    m_alpha_std=m_beta_std=m_distance_std=0.0;
    m_dim=Polar_coordinate::_3D_;
}

Polar_coordinate::Polar_coordinate(double alpha,double distance)
{
    m_alpha=alpha;
    m_beta=PI/2;
    m_distance=distance;

    m_alpha_std=0.0;
    m_beta_std=0.0;
    m_distance_std=0.0;

    m_dim=Polar_coordinate::_2D_;
}

Polar_coordinate::Polar_coordinate(double alpha,double distance,double alpha_std,double distance_std)
{
     m_alpha=alpha;
     m_beta=PI/2;
     m_distance=distance;

     m_alpha_std=alpha_std;
     m_beta_std=0.0;
     m_distance_std=distance_std;

     m_dim=Polar_coordinate::_2D_;
}

Polar_coordinate::Polar_coordinate(double alpha,double beta,double distance)
{
    m_alpha=alpha;
    m_beta=beta;
    m_distance=distance;

    m_alpha_std=0.0;
    m_beta_std=0.0;
    m_distance_std=0.0;

    m_dim=Polar_coordinate::_3D_;
}

Polar_coordinate::Polar_coordinate(double alpha,double beta,double distance,double alpha_std,double beta_std,double distance_std)
{
    m_alpha=alpha;
    m_beta=beta;
    m_distance=distance;

    m_alpha_std=alpha_std;
    m_beta_std=beta_std;
    m_distance_std=distance_std;

    m_dim=Polar_coordinate::_3D_;
}

Polar_coordinate::Polar_coordinate(Point P)
{
 (*this).convert_cartesian_to_polar( P );
}

Polar_coordinate::~Polar_coordinate()
{
}

Polar_coordinate& Polar_coordinate::operator = (const Polar_coordinate& P)
{
        m_dim=P.m_dim;
        m_alpha=P.m_alpha;
        m_beta=P.m_beta;
        m_distance=P.m_distance;
        m_alpha_std=P.m_alpha_std;
        m_beta_std=P.m_beta_std;
        m_distance_std=P.m_distance_std;

 return (*this);
}

 //convert operator
Polar_coordinate::operator Point () const
{
  Point cart;
  (*this).convert_polar_to_cartesian( cart );
  return cart;
}

//convert from Point to polar coordinates
Polar_coordinate& Polar_coordinate::operator = (const Point& P)
{
 (*this).convert_cartesian_to_polar( P );
 return (*this);
}

double Polar_coordinate::get_alpha() const
{
 return m_alpha;
}

double Polar_coordinate::get_beta() const
{
 return m_beta;
}

double Polar_coordinate::get_distance() const
{
 return m_distance;
}

void Polar_coordinate::set_alpha(double alpha)
{
    m_alpha=alpha;
}

void Polar_coordinate::set_beta(double beta)
{
    m_beta=beta;
}
void Polar_coordinate::set_distance(double distance)
{
    m_distance=distance;
}


void Polar_coordinate::convert_polar_to_cartesian( Point& cart ) const
{
    //if( m_dim == Polar_coordinate::_3D_)
    //{
            //transformation from Cartesian  into polar coordinate system
            cart.set_X( cos(m_alpha) * sin(m_beta) * m_distance );
            cart.set_Y( sin(m_alpha) * sin(m_beta) * m_distance);
            cart.set_Z( cos(m_beta)  * m_distance);

            //standard deviation calculation
            cart.set_dX(
                         sqrt(
                                  pow( -sin( m_alpha ) * sin( m_beta ) * m_distance  * m_alpha_std    ,2)
                                 +pow(  cos( m_alpha ) * cos( m_beta ) * m_distance  * m_beta_std     ,2)
                                 +pow(  cos( m_alpha ) * sin( m_beta )               * m_distance_std ,2)
                         )
            );

            cart.set_dY(
                         sqrt(
                                  pow(  cos( m_alpha ) * sin( m_beta ) * m_distance  * m_alpha_std    ,2)
                                 +pow(  sin( m_alpha ) * cos( m_beta ) * m_distance  * m_beta_std     ,2)
                                 +pow(  sin( m_alpha ) * sin( m_beta )               * m_distance_std ,2)
                         )
            );

            cart.set_dZ(
                         sqrt(
                                 //0.0+
                                  pow(  -sin( m_beta ) * m_distance  * m_beta_std     ,2)
                                 +pow(   cos( m_beta )               * m_distance_std ,2)
                         )
            );

    //}
/*
    if( m_dim == Polar_coordinate::_2D_)
    {
            //transformation from polar into Cartesian coordinate system
            cart.set_X( cos(m_alpha) * m_distance );
            cart.set_Y( sin(m_alpha) * m_distance);
            cart.set_Z( 0.0 );

            //standard deviation calculation

    }

    //else{//?
           //}
*/
}

void Polar_coordinate::convert_cartesian_to_polar(const Point& cart)
{
 double x,y,z;
 double dx,dy,dz;

 x = cart.get_X();
 y = cart.get_Y();
 z = cart.get_Z();

 dx = cart.get_dX();
 dy = cart.get_dY();
 dz = cart.get_dZ();

 m_alpha    = atan2( y ,x );
 m_beta     = atan2( sqrt( x*x + y*y ) , z );
 m_distance = sqrt( x*x + y*y + z*z );


 m_alpha_std    = sqrt(
                          pow( -y/(x*x+y*y) * dx  ,2)
                         +pow(  x/(x*x+y*y) * dy  ,2)
                         //+ (0.0)
                  );

 m_beta_std     = sqrt(
                          pow( x*z / ( sqrt(x*x+y*y) * (x*x + y*y + z*z) )  * dx  ,2)
                         +pow( y*z / ( sqrt(x*x+y*y) * (x*x + y*y + z*z) )  * dy  ,2)
                         +pow(-sqrt(x*x+y*y) / (x*x + y*y + z*z)            * dz  ,2)
                 );

 m_distance_std = sqrt(
                          pow( x/sqrt(x*x + y*y + z*z) * dx  ,2)
                         +pow( y/sqrt(x*x + y*y + z*z) * dy  ,2)
                         +pow( z/sqrt(x*x + y*y + z*z) * dz  ,2)
                  );



}

ostream& operator<<(ostream& s,const Polar_coordinate& A)
{
   int precision=5;       //Nachkommastellen
   int vorkommastellen=8; //Minus zählt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

    s<<" ( alpha: "
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.m_alpha
    <<", beta: "
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.m_beta
    <<", distance :"
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.m_distance
    <<") "
    <<"std("
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.m_alpha_std
    <<","
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.m_beta_std
    <<","
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.m_distance_std
    <<") ";

return s;
}
