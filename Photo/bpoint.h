#ifndef __BPOINT_h
#define __BPOINT_h

#include <iostream>


#include "cam.h"
#include "..//Basics//point.h"

//#include "straight_line.h"

using namespace std;

class BPoint:public Point //->hier wird die Klasse Punkt direkt in Klasse Bpunkt mit 
                          //eingebunden, so als wrde man alles aus Punkt nochmal 
						  //komplett in Bpunkt schreiben, somit sind alle Funktionen
						  //und Variablen aus Punkt auch direkt in Bpunkt verfgbar
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
		  return (*this);
	}
	BPoint(const BPoint &A)
	{
	 (*this)=A;
	}
	
	Cam&   get_Cam    () { return *m_Cam; /*Cam C; C=*m_Cam; return C;*/}
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

private:

    //Hilfsfunktionen
	bool PixKooInBildKoo();
	bool Verzeichnungskorrektur(double& vx,double& vy);
    bool TransInObjKoo();
    
	//Hauptfunktionen
	bool BildpunktkorrekturVonPixInBildKoo();
	bool PixelkorrekturVonBildInPixKoo();

	//Variablen
	Cam    *m_Cam;          //Kamera des Bildpunktes
	double m_m,m_n;         //Pixelkoordinaten
	
	double m_xkorr,m_ykorr; //korrigierte Bildkoordinaten (m_z nur fr interne Berechnungen)
	
	//:Point (Ableitung der Klasse) ->
	// X,Y,Z //fr Bildkoordinaten->(nur fr interne Berechnungen m_z=-c) und Objektkoordinaten (Rckrechnung ObjKooInBKoo)      
  
	bool m_isOK;
};




#endif
