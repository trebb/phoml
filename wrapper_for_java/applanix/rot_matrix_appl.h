#ifndef __ROT_MATRIX_APPL_h
#define __ROT_MATRIX_APPL_h

#include <iostream>


#include "..//..//Basics//Matrix//matrix.h"

using namespace std;

class Rot_appl
{
public:
	Rot_appl(double rotX,double rotY,double rotZ);
	Rot_appl(const Matrix& R);
	Rot_appl(const Rot_appl& R);
    ~Rot_appl();
    
    Rot_appl& operator=(const Rot_appl& R);
    Rot_appl& operator=(const Matrix& R);
    
    //Konvertierungs operator für class Matrix
    //operator Matrix () const;
    operator Matrix& ();
	
	//Matrix R;
	Matrix get_Matrix();
	
	bool get_RotWinkel(double& Omega,double& Phi,double& Kappa);
	
	const string get_errorstring();
	
private:
    //help funktion
    double clamp(double& wert, double min, double max);

    bool isError;
    Matrix m_R;
    
    string errorstring;
};

#endif
