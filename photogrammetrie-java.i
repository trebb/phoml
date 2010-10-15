%module photo
%{
#include "basics/point.h"
#include "photo/bpoint.h"
#include "photo/cam.h"
#include "photo/forward_intersection.h"
#include "boresight_alignment/cam_bore.h"
#include <vector>
#include "wrapper_for_java/Vorwaertsschnitt_java.h"
#include "wrapper_for_java/CBPointList.h"
#include "wrapper_for_java/mainwrapperjava.h"
#include "internal_control/CPhotogrammetrieTest.h"
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

class CCam_bore:public Cam
{
public:
	CCam_bore();
	virtual ~CCam_bore();
	CCam_bore(
				        double pix_row, double pix_col, double pix_size,
						double OX, double OY, double OZ,
					    double rotX, double rotY, double rotZ,
					    double c, double xh, double yh, 
						double A1, double A2, double A3,
						double B1, double B2, double C1,
						double C2, double r0,
						double B_dx, double B_dy, double B_dz,
						double B_ddx, double B_ddy, double B_ddz,
						double B_rotx, double B_roty, double B_rotz,
						double B_drotx, double B_droty, double B_drotz
		);
	
	CCam_bore(const CCam_bore &C);
	//CCam_bore& operator=(const CCam_bore &C);
	//CCam_bore& operator=(Cam &C);
	
	// convertion of "CCam_bore  >>-->  Cam"
	//operator Cam () const;
	
	//get funktions
	Point  get_B()   {Point P(m_B_dx,m_B_dy,m_B_dz); P.set_dX(m_B_ddx); P.set_dY(m_B_ddy);P.set_dZ(m_B_ddz);return P;}
	double get_B_dx(){return m_B_dx;}
	double get_B_dy(){return m_B_dy;}
	double get_B_dz(){return m_B_dz;}
	
	double get_B_ddx(){return m_B_ddx;}
	double get_B_ddy(){return m_B_ddy;}
	double get_B_ddz(){return m_B_ddz;}
	
	double get_B_rotx(){return m_B_rotx;}
	double get_B_roty(){return m_B_roty;}
	double get_B_rotz(){return m_B_rotz;}
	
	double get_B_drotx(){return m_B_drotx;}
	double get_B_droty(){return m_B_droty;}
	double get_B_drotz(){return m_B_drotz;}
		
	//set funktions
	void set_B_dx(double B_dx){m_B_dx=B_dx;}
	void set_B_dy(double B_dy){m_B_dy=B_dy;}
	void set_B_dz(double B_dz){m_B_dz=B_dz;}
	
	void set_B_ddx(double B_ddx){m_B_ddx=B_ddx;}
	void set_B_ddy(double B_ddy){m_B_ddy=B_ddy;}
	void set_B_ddz(double B_ddz){m_B_ddz=B_ddz;}
	
	void set_B_rotx(double B_rotx){m_B_rotx=B_rotx;}
	void set_B_roty(double B_roty){m_B_roty=B_roty;}
	void set_B_rotz(double B_rotz){m_B_rotz=B_rotz;}
	
	void set_B_drotx(double B_drotx){m_B_drotx=B_drotx;}
	void set_B_droty(double B_droty){m_B_droty=B_droty;}
	void set_B_drotz(double B_drotz){m_B_drotz=B_drotz;}
		
	int 		get_channels				(){return m_channels;}
	
	//overwrite of Cam funktions
	bool read_from_ini(const char *datname);
	bool  write_in_ini(const char *datname);
	
private:
	//[GENERAL]
	std::string m_camera_name;
	int         m_channels;
	std::string m_camera_serial_number;
	
	//[OBJECTIV]
	std::string m_objectiv_name;
	//focal length in [mm]
	//this is not c!!! This is the value from the manufacturer!!
	std::string m_focal_length;
	std::string m_objectiv_serial_number;
	
	//[INNER_ORIENTATION]
	std::string m_calib_inner_date;
	std::string m_calib_inner_person;
	std::string m_calib_inner_comments;

	//[OUTER_ORIENTATION]
	std::string m_calib_outer_date;
	std::string m_calib_outer_person;
	std::string m_calib_outer_comments;
	
	//[BORESIDE_ALIGNEMENT]
	std::string m_calib_boreside_date;
	std::string m_calib_boreside_person;
	std::string m_calib_boreside_comments;
	
	// tranlation [mm]
	double m_B_dx;
	double m_B_dy;
	double m_B_dz;
	
	//standart deviation translation
	double m_B_ddx;
	double m_B_ddy;
	double m_B_ddz;
	
	// rotation [rad]
	double m_B_rotx;
	double m_B_roty;
	double m_B_rotz;
	
	//standart deviation rotation
	double m_B_drotx;
	double m_B_droty;
	double m_B_drotz;
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

class CMainWrapperJava
{
public:
	CMainWrapperJava();
	virtual ~CMainWrapperJava();

	//divide into two steps local and global (utm) functions
	
	//local funktions (camera coordinate system) (in [m])
	
	//forwart intersection
	//put 2 or more BPoints into the list with differend Cameras
	//and get a 3D Point back
	Point get_3D_Point_local(CBPointList BPlist);
	
	//put a 3D Point into the funktion and get a BPoint from the camera back
	//then you can visualisation the 3D Point in the picture
	BPoint get_BPoint_from_local_3D_Point(Point P_local,CCam_bore cam);
	
	
	//global funktions (boreside in [m]) in UTM coordinates if the Car position also in UTM, angels [roll,pitch,heading] in old degree 
	//(applanix like: roll pitch in mathematic direction and heading in geodetic direction ;-))
	
	//put the local 3D Point from get_3D_Point_local(), the camera_calibration
	// cam_bore and the car position (Esting,Northing,ellHieght,roll,pitch,heading) inside
	// and get the UTM coordinate of the local Point
	Point get_3D_Point_global(Point P_local_in_m,CCam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading);
	Point get_3D_Point_global_wMC(Point P_local_in_m,CCam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading,double latitude,double longitude);

	//put a global 3D Point Point(Easting,Northing,eHeight), the camera_calibration
	// cam_bore and the car position (Esting,Northing,ellHieght,roll,pitch,heading) inside
	// and get the local 3D coordinates of the global Point
	Point get_3D_Point_local(Point P_global_E_N_eH_in_m,CCam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading);
	Point get_3D_Point_local_wMC(Point P_global_E_N_eH_in_m,CCam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading,double latitude,double longitude);

};

class CPhotogrammetrieTest
{
public:
	CPhotogrammetrieTest();
	virtual ~CPhotogrammetrieTest();
	
	bool check();
	
};
