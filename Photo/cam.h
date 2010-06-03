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
	
	
	double get_pix_row() const {return m_pix_row;}
    double get_pix_col() const {return m_pix_col;}
	double get_pix_size() const {return m_pix_size;}

    Point  get_O()  const {return m_O;}
	double get_OX() const {return m_O.get_X();}
    double get_OY() const {return m_O.get_Y();}
	double get_OZ() const {return m_O.get_Z();}
    
	double get_rotX() const {return m_rotX;}
    double get_rotY() const {return m_rotY;}
	double get_rotZ() const {return m_rotZ;}
	
	double get_c()  const {return m_c;}
    double get_xh() const {return m_xh;}
	double get_yh() const {return m_yh;}

	double get_A1() const {return m_A1;}
	double get_A2() const {return m_A2;}
	double get_A3() const {return m_A3;}
	double get_B1() const {return m_B1;}
	double get_B2() const {return m_B2;}
	double get_C1() const {return m_C1;}
	double get_C2() const {return m_C2;}

	double get_r0() const {return m_r0;}
	
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

ostream& operator<<(ostream& s,const Cam& C);


#endif
