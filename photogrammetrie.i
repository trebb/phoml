%module photo
%{
#include "Basics/point.h"
#include "Photo/bpoint.h"
#include "Photo/cam.h"
#include "Photo/forward_intersection.h"
#include "wrapper_for_java/Vorwaertsschnitt_java.h"
#include "wrapper_for_java/CBPointList.h"
#include <vector>
%}

class Point
{
public:	
	
	Point(){m_x=m_y=m_z=0.0;m_dx=m_dy=m_dz=0.0;}
	Point(double x,double y,double z):m_x(x),m_y(y),m_z(z){m_dx=m_dy=m_dz=0.0;}
   ~Point(){}

	 double get_X()  const{ return m_x; }
	 double get_Y()  const{ return m_y; }
	 double get_Z()  const{ return m_z; }
	 double get_dX() const{ return m_dx; }
	 double get_dY() const{ return m_dy; }
	 double get_dZ() const{ return m_dz; }

	 Point get_dXYZ() const{Point dP(m_dx,m_dy,m_dz); return dP;}
	
	Point(Point const &A)  //das ist ein Copy-Konstruktor, eigentlich dasselbe
	{                      //wie die darber stehende Funktion: Point& operator=....
	 (*this)=A;
	}

	void set_X (double x) { m_x=x;  }
	void set_Y (double y) { m_y=y;  }
	void set_Z (double z) { m_z=z;  }
	void set_dX (double x) { m_dx=x;  }
	void set_dY (double y) { m_dy=y;  }
	void set_dZ (double z) { m_dz=z;  }

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
 Point  Rotation(Point& X0,Matrix& R);
 Point  RotationRueck(Point& X0,Matrix& R);
};

class BPoint:public Point 
{
public:

	//Konstruktor 0 (Eingabe der Kamera)
    BPoint(Cam &C):m_Cam(&C)
	{m_m=m_n        =-1.0;
     m_xkorr=m_ykorr=-111111.1;
	 m_x=m_y=m_z    =-111111.1;
	};
	//Konstruktor I (Eingabe der Pixel(m,n))
	BPoint(Cam &C,double m,double n):m_Cam(&C),m_m(m),m_n(n)
	{m_x=m_y=m_z    =-111111.1;
	 BildpunktkorrekturVonPixInBildKoo();
	};
    //Konstruktor II (Rckprojektion in die Kamera, Eingabe Objektkoordinaten(X,Y,Z) in [mm] )
    BPoint(Cam &C,double x,double y,double z):Point(x,y,z),m_Cam(&C)
	{m_m=m_n=-1.0;
	 PixelkorrekturVonBildInPixKoo();
	}; 

    void  set_mnPixKoo (double m,double n); //Eingabe (m,n) des Bildpunktes in [pix]
    void  set_xyBKoo   (double x,double y); //Eingabe (x,y) der unkorrigierten Bildpunkte in [mm]
    void  set_XYZObjKoo(double X,double Y,double Z); //Eingabe (x,y,z) des Objektpunktes in [mm]

	BPoint(const BPoint &A)
	{
	 (*this)=A;
	}
	
	Cam   get_Cam    () { Cam C; C=*m_Cam; return C;}
	Cam&  get_Cam_Ref() { return *m_Cam;}
	
	double get_m() const{ return m_m; }
	double get_n() const{ return m_n; }

	//Achtung!! Dieser Objektpunkt kann irgendwo auf dem Strahl Kamerahauptpunkt und gesuchtem Objektpunkt liegen!!
	//Bei der Rckrechnung vom Objektraum in Bildkoordinaten ist diese Koordinate zu setzen!
	double get_X() const {return m_x; }
    double get_Y() const {return m_y; }
    double get_Z() const {return m_z; }
		
	Point get_Point()     { Point P(m_x,m_y,m_z);         return P;} // Ausgabe im Objektkoordinatensystem (fr interne Berechnungen oder Rckrechnung ObjKoo In BKoo)
	Point get_xyBKooKorr(){ Point P(m_xkorr,m_ykorr,0.0); return P;} // Ausgabe Bildpunkt   korrigiert x,y (z=0)
    Point get_xyBKoo();                                              // Ausgabe Bildpunkt unkorrigiert x,y (z=0)


	BPoint get_KernlinenPunkt( Cam &C, double s ); //Cam &C ist die Kamera in der der Kernlinien Punkt gesucht wird
	                                               // s ist die Entfernung von Kamerahauptpunkt in den Objektraum
};

class Cam
{
public:
	Cam();
	
	Cam(double pix_row,double pix_col,double pix_size,
		double OX,  double OY,  double OZ,
	    double rotX,double rotY,double rotZ,
	    double c,   double xh,  double yh, 
		double A1,  double A2,  double A3,
		double B1,  double B2, double C1,
		double C2, double r0);
		
	~Cam();
 
	Cam(const Cam &C);
	
	
	double get_pix_row(){return m_pix_row;}
    double get_pix_col(){return m_pix_col;}
	double get_pix_size(){return m_pix_size;}

    Point  get_O() {return m_O;}
	double get_OX(){return m_O.get_X();}
    double get_OY(){return m_O.get_Y();}
	double get_OZ(){return m_O.get_Z();}
    
	double get_rotX(){return m_rotX;}
    double get_rotY(){return m_rotY;}
	double get_rotZ(){return m_rotZ;}
	
	double get_c() {return m_c;}
    double get_xh(){return m_xh;}
	double get_yh(){return m_yh;}

	double get_A1(){return m_A1;}
	double get_A2(){return m_A2;}
	double get_A3(){return m_A3;}
	double get_B1(){return m_B1;}
	double get_B2(){return m_B2;}
	double get_C1(){return m_C1;}
	double get_C2(){return m_C2;}

	double get_r0(){return m_r0;}
	
	//verfügbare set_ Funktionen um die Ausrichtung der Kamera im Raum zu gewährleisten  
	void set_rotX(double rotX) {m_rotX = rotX;}
    void set_rotY(double rotY) {m_rotY = rotY;}
	void set_rotZ(double rotZ) {m_rotZ = rotZ;}

    void set_O(Point P) {m_O = P;}

	Matrix TransInRellativeOrientierung( Cam &C_l, Cam &C_r, Cam &C_l_rell ,Cam &C_r_rell);

	bool read_from_ini(const char *datname);
	bool write_in_ini(const char *datname);         
};

class CBPointList
{
public:
	CBPointList();
	virtual ~CBPointList();
	void addBPoint(BPoint bp);
	int size();
	void clearBPointList();
	vector <BPoint> m_BPoint_List; 
};

class Vorwaertsschnitt_java
{
public:
	Vorwaertsschnitt_java();
	Point calc_vorwaertsschnitt(CBPointList blist); 
	virtual ~Vorwaertsschnitt_java();
	
};


