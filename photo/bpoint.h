#ifndef __BPOINT_h
#define __BPOINT_h

#include <iostream>


#include "cam.h"
#include "..//basics//point.h"
#include "..//basics//ebene.h"

using namespace std;

class BPoint:public Point //->hier wird die Klasse Punkt direkt in Klasse Bpunkt mit 
                          //eingebunden, so als wrde man alles aus Punkt nochmal 
						  //komplett in Bpunkt schreiben, somit sind alle Funktionen
						  //und Variablen aus Punkt auch direkt in Bpunkt verfügbar
{
//*************************************************************************************
// Pixelkoordinaten m,n
// *-->m   Pixelkoordinatensystem Ursprung links-oben
// |
// n  y'
//    |
//    *-->x' Bildkoordinatensystem Ursprung Durchstopunkt optische Achse und Bildsensor(ebene)
//
//Bildkoordinatensystem (Rechtshandsystem) x'y'(z) -> -z zeigt in Aufnahmerichtung!!!!
//**************************************************************************************	
public:

	//Konstruktor 0 (Eingabe der Kamera)
    BPoint(Cam &C):m_Cam(&C)
	{m_m=m_n        =-1.0;
     m_xkorr=m_ykorr=-111111.1;
	 m_x=m_y=m_z    =-111111.1;
	 m_change_cam=false;
	 m_iteration_limit=false;
	};

	//Konstruktor I (Eingabe der Pixel(m,n))
	BPoint(Cam &C,double m,double n):m_Cam(&C),m_m(m),m_n(n)
	{m_x=m_y=m_z    =-111111.1;
	 //BildpunktkorrekturVonPixInBildKoo(); //old now in update_internal_data_structur()

	 m_input_type = BPoint::picture;
	 //todo exception handling an check picture coordinates
	 update_internal_data_structur();
	};

    //Konstruktor II (Rückprojektion in die Kamera, Eingabe Objektkoordinaten(X,Y,Z) in [mm] )
    BPoint(Cam &C,double x,double y,double z):Point(x,y,z),m_Cam(&C)
	{m_m=m_n=-1.0;
	 //PixelkorrekturVonBildInPixKoo(); //old now in update_internal_data_structur()

	 m_input_type = BPoint::object;
	 //todo exception handling an check picture coordinates	//steffen
	 update_internal_data_structur();
	}; 

	BPoint(const BPoint &A)
	{
	 (*this)=A;
	}

	BPoint& operator= (const BPoint &A) 
	{     
		  (*this).m_Cam   = A.m_Cam;
		  (*this).m_m     = A.m_m; 
		  (*this).m_n     = A.m_n; 
		  (*this).m_x     = A.m_x;
		  (*this).m_y     = A.m_y;
		  (*this).m_z     = A.m_z;
		  (*this).m_xkorr = A.m_xkorr;
		  (*this).m_ykorr = A.m_ykorr;
		  (*this).m_change_cam      = A.m_change_cam;
		  (*this).m_iteration_limit = A.m_iteration_limit;
		  (*this).m_input_type      = A.m_input_type;
		  return (*this);
	}

	// convertion of "BPoint  >>-->  Point"
	operator Point () const { return Point(m_x,m_y,m_z); };

		//todo set to deprecated steffen 20101013
    Cam&   get_Cam () { m_change_cam=true; return *m_Cam; /*Cam C; C=*m_Cam; return C;*/}
	//Cam&  get_Cam_Ref()  { return *m_Cam;}


    //function for set new values or update camera changes
    bool  set_mnPixKoo (double m,double n); //Eingabe (m,n) des Bildpunktes in [pix]
    bool  set_xyBKoo   (double x,double y); //Eingabe (x,y) der unkorrigierten Bildpunkte in [m]
    bool  set_XYZObjKoo(double X,double Y,double Z); //Eingabe (x,y,z) des Objektpunktes in [m]
    bool  set_XYZObjKoo( const Point &P); //Eingabe (x,y,z) des Objektpunktes in [m]
	
    double get_m() ;//{ return m_m; }
	double get_n() ;//{ return m_n; }

	//set to deprecated steffen 20101013
	//double get_X() const {return m_x; }
    //double get_Y() const {return m_y; }
    //double get_Z() const {return m_z; }
		
	//old steffen 20101013
	//Point get_Point()     { Point P(m_x,m_y,m_z);         return P;} // Ausgabe im Objektkoordinatensystem (fr interne Berechnungen oder Rckrechnung ObjKoo In BKoo)
	//Point get_xyBKooKorr(){ Point P(m_xkorr,m_ykorr,0.0); return P;} // Ausgabe Bildpunkt   korrigiert x,y (z=0)

	//Achtung!! Dieser Objektpunkt kann irgendwo auf dem Strahl Kamerahauptpunkt und gesuchtem Objektpunkt liegen!!
	//Bei der Rckrechnung vom Objektraum in Bildkoordinaten ist diese Koordinate zu setzen!
	//new steffen 20101013
	Point get_Point()       ;//{ return Point(m_x,m_y,m_z);        } // Ausgabe im Objektkoordinatensystem (fr interne Berechnungen oder Rckrechnung ObjKoo In BKoo)
    Point get_xyBKooKorr()  ;//{ return Point(m_xkorr,m_ykorr,0.0);} // Ausgabe Bildpunkt   korrigiert x,y (z=0)
	Point get_xyBKoo() ;                                              // Ausgabe Bildpunkt unkorrigiert x,y (z=0)

	BPoint get_KernlinenPunkt( Cam &C, double s ); //Cam &C ist die Kamera in der der Kernlinien Punkt gesucht wird
	                                               // s ist die Entfernung von Kamerahauptpunkt in den Objektraum
	Point calc_mono_cam_to_plane_intersection(Ebene &E);

	bool get_error_iteration_limit()       const { return m_iteration_limit; }
	bool get_info_change_camera_settings() const { return m_change_cam; }


private:

    //Hilfsfunktionen
	bool PixKooInBildKoo();
	bool Verzeichnungskorrektur(double& vx,double& vy);
    bool TransInObjKoo();
    
	//Hauptfunktionen
    bool BildpunktkorrekturVonPixInBildKoo();
	bool PixelkorrekturVonBildInPixKoo();
	bool update_internal_data_structur(); //includes the PixelkorrekturVonBildInPixKoo() and the BildpunktkorrekturVonPixInBildKoo() function//steffen 20101014

	//Variablen
	Cam    *m_Cam;          //Kamera des Bildpunktes
	double m_m,m_n;         //Pixelkoordinaten
	
	double m_xkorr,m_ykorr; //korrigierte Bildkoordinaten (m_z nur fr interne Berechnungen)
	
	//:Point (Ableitung der Klasse) ->
	// X,Y,Z //fr Bildkoordinaten->(nur fr interne Berechnungen m_z=-c) und Objektkoordinaten (Rckrechnung ObjKooInBKoo)      
  
	bool m_iteration_limit;
	bool m_change_cam;

	//for updating changes on camera
	enum INPUT_TYPE{picture,object};
	INPUT_TYPE m_input_type;
};




#endif
