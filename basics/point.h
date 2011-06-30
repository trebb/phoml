#ifndef __POINT_h
#define __POINT_h

#include <iostream>

#include "matrix//matrix.h"
#include "rotation_matrix.h"

using namespace std;

class Point
{
public:	
	
	Point(){m_x=m_y=m_z=0.0;m_dx=m_dy=m_dz=0.0;}
	Point(double x,double y,double z):m_x(x),m_y(y),m_z(z),m_dx(0.0),m_dy(0.0),m_dz(0.0){}
	Point(double x,double y,double z,double dx,double dy,double dz):m_x(x),m_y(y),m_z(z),m_dx(dx),m_dy(dy),m_dz(dz){}

    ~Point(){}

	bool operator==( const Point& t) const { return m_x == t.m_x &&
													m_y == t.m_y &&
												    m_z == t.m_z;
	}
	bool operator!=( const Point& t) const { return !(m_x == t.m_x &&
													  m_y == t.m_y &&
													  m_z == t.m_z );
	}
	bool operator<( const Point& t) const { return m_x < t.m_x;

	}


	Point& operator= (const Point &A)
	{     (*this).m_x  = A.m_x;
		  (*this).m_y  = A.m_y;
		  (*this).m_z  = A.m_z;
		  (*this).m_dx = A.m_dx;
		  (*this).m_dy = A.m_dy;
		  (*this).m_dz = A.m_dz;
/*old steffen 08.nov.2010
		  (*this).set_X( A.get_X() );
		  (*this).set_Y( A.get_Y() );
		  (*this).set_Z( A.get_Z() );
		  (*this).set_dX( A.get_dX() );
		  (*this).set_dY( A.get_dY() );
		  (*this).set_dZ( A.get_dZ() );
*/
		  return (*this);
	}
	Point(Point const &A)
	{
	 (*this)=A;
	}

	// conversion of "Point  >>-->  Matrix(3,1,...)"
	operator Matrix () const
	{
	    Matrix P(3,1,Null);
	    P(0,0)=m_x;P(1,0)=m_y;P(2,0)=m_z;
	    return P.MatCopy();
	}

	Point& operator= (const Matrix &A)
	{
	       assert( !A.isEmpty() );
	       assert( A.getRow() == 3  );
	       assert( A.getCol() == 1  );

	     (*this).m_x = A(0,0);
         (*this).m_y = A(1,0);
         (*this).m_z = A(2,0);

         return (*this);
	}

	Point(Matrix const &A)
	{
	  (*this)=A;
	}


    double get_X()  const{ return m_x; }
    double get_Y()  const{ return m_y; }
    double get_Z()  const{ return m_z; }
    double get_dX() const{ return m_dx; }
    double get_dY() const{ return m_dy; }
    double get_dZ() const{ return m_dz; }

	void set_X (double x) { m_x=x;  }
	void set_Y (double y) { m_y=y;  }
	void set_Z (double z) { m_z=z;  }
	void set_dX (double x) { m_dx=x;  }
	void set_dY (double y) { m_dy=y;  }
	void set_dZ (double z) { m_dz=z;  }

    Point get_dXYZ() const{Point dP(m_dx,m_dy,m_dz); return dP;}
    Point set_dXYZ(Point dP) { m_dx=dP.m_x; m_dy=dP.m_y; m_dz=dP.m_z; return (*this);}


protected:                 //private
	double m_x,m_y,m_z;    //Koordinate
	double m_dx,m_dy,m_dz; //Standardabweichung


public:
 
 double Quad    ();
 Point  Quad_separate    ();
 Point  Sqrt_separate    ();
 double Betrag  ();
 Point  Norm    ();
 double Abstand (const Point &B);
 
 Point  Add     (const Point &B);
 Point  Subt    (const Point &B);
 double Mult    (const Point &B);
 Point  MultS   (const double t);
 Point  DivS    (double t);
 Point  SpatP   (const Point &B);
 
 Point  Rotation( Point& X0, Matrix& R);
 Point  Rotation( Point& X0, Matrix& R, double& m);
 
 Point  RotationRueck( Point& X0, Matrix& R);
 Point  RotationRueck( Point& X0, Matrix& R, double& m);
 Point  RotationRueck( Point& X0, Matrix& R, double& mx, double& my, double& mz);
 
 Point  Rotation_with_std( Point& X0, Rotation_matrix& R);
 Point  RotationRueck_with_std( Point& X0, Rotation_matrix& R);

};

ostream& operator<<(ostream& s,const Point& A);
istream& operator>>(istream& s,Point &A);

#endif



