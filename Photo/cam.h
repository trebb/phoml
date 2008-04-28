#ifndef __CAM_h
#define __CAM_h

#include <iostream>

#include "..//Basics//point.h"

using namespace std;

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
 
	Cam& operator=(const Cam &C);
	
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
	
protected:
	    //Hilfsfunktion
	    double clamp(double& wert, double min, double max);

        //Pixelgroesse
        double m_pix_size;
        //Sensorgroesse Row=Breite Col=Hoehe
        double m_pix_row;
        double m_pix_col;
	    
		Point m_O;

		//double Omega, Phi, Kappa;
		double m_rotX, m_rotY, m_rotZ;//Rotationswinkel
		double m_c;                   //Kamerakonstante 
		double m_xh, m_yh;            //Bildhauptpunkt
		double m_A1, m_A2, m_A3, m_B1, m_B2, m_C1, m_C2; //Verzeichnungsparameter
		double m_r0;   

            
};




#endif
