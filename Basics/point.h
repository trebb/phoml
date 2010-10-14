#ifndef __POINT_h
#define __POINT_h

#include <iostream>

#include "Matrix//matrix.h"

using namespace std;

class Point
{
public:	
	
	Point(){m_x=m_y=m_z=0.0;m_dx=m_dy=m_dz=0.0;}
	Point(double x,double y,double z):m_x(x),m_y(y),m_z(z){m_dx=m_dy=m_dz=0.0;}
	Point(double x,double y,double z,double dx,double dy,double dz):m_x(x),m_y(y),m_z(z),m_dx(dx),m_dy(dy),m_dz(dz){}

    ~Point(){}

	 double get_X()  const{ return m_x; }
	 double get_Y()  const{ return m_y; }
	 double get_Z()  const{ return m_z; }
	 double get_dX() const{ return m_dx; }
	 double get_dY() const{ return m_dy; }
	 double get_dZ() const{ return m_dz; }

	 Point get_dXYZ() const{Point dP(m_dx,m_dy,m_dz); return dP;}


	bool operator==( const Point& t) const { return get_X() == t.get_X() &&
													get_Y() == t.get_Y() &&
												    get_Z() == t.get_Z();
	}
	bool operator!=( const Point& t) const { return !(get_X() == t.get_X() &&
													  get_Y() == t.get_Y() &&
													  get_Z() == t.get_Z() );
	}


	Point& operator= (const Point &A)
	{     (*this).set_X( A.get_X() );
		  (*this).set_Y( A.get_Y() );
		  (*this).set_Z( A.get_Z() );
		  (*this).set_dX( A.get_dX() );
		  (*this).set_dY( A.get_dY() );
		  (*this).set_dZ( A.get_dZ() );
		  return (*this);
	}
	Point(Point const &A)
	{
	 (*this)=A;
	}

	void set_X (double x) { m_x=x;  }
	void set_Y (double y) { m_y=y;  }
	void set_Z (double z) { m_z=z;  }
	void set_dX (double x) { m_dx=x;  }
	void set_dY (double y) { m_dy=y;  }
	void set_dZ (double z) { m_dz=z;  }


protected:                 //private
	double m_x,m_y,m_z;    //Koordinate
	double m_dx,m_dy,m_dz; //Standardabweichung


public:
 
 double Quad    ();
 double Betrag  ();
 Point  Norm    ();
 double Abstand (const Point &B);
 
 Point  Add     (const Point &B);
 Point  Subt    (const Point &B);
 double Mult    (const Point &B);
 Point  MultS   (const double t);
 Point  DivS    (const double t);
 Point  SpatP   (const Point &B);
 
 Point  Rotation( Point& X0, Matrix& R);
 Point  Rotation( Point& X0, Matrix& R, double& m);
 
 Point  RotationRueck( Point& X0, Matrix& R);
 Point  RotationRueck( Point& X0, Matrix& R, double& m);
 Point  RotationRueck( Point& X0, Matrix& R, double& mx, double& my, double& mz);
 


};

ostream& operator<<(ostream& s,const Point& A);

#endif



