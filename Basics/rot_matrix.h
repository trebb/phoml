#ifndef __ROT_MATRIX_h
#define __ROT_MATRIX_h

#include <iostream>


#include "Matrix//matrix.h"

using namespace std;

class Rot
{
public:
	Rot(double rotX,double rotY,double rotZ);
	Rot(const Matrix& R);
	Rot(const Rot& R);
    ~Rot();
    
    Rot& operator=(const Rot& R);
    //Konvertierungs operator für class Matrix
    operator Matrix () const;
	
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
