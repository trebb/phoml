#ifndef __FORWARD_INTERSECTION_h
#define __FORWARD_INTERSECTION_h

#include <vector> 
#include "..//Basics//point.h"
#include "..//Basics//straight_line.h"
#include "cam.h"
#include "bpoint.h"


#include "bpoint.h"

class Vorwaertsschnitt
{
public:
	Vorwaertsschnitt(vector<BPoint> &BP);
	~Vorwaertsschnitt(){}

	Point get_Schnittpunkt(){ return m_schnittpunkt;}
    bool  get_is_error()    { return m_is_error;    }

private:
    // interne Funktionen
	double Zaehler_x(Cam K, Point OP_0, Matrix& R);
    double Zaehler_y(Cam K, Point OP_0, Matrix& R);
    double Nenner(Cam K, Point OP_0, Matrix& R);
    double dxdX(Cam K, double Zx, double N, Matrix& R);
    double dxdY(Cam K, double Zx, double N, Matrix& R);
    double dxdZ(Cam K, double Zx, double N, Matrix& R);
	double dydX(Cam K, double Zy, double N, Matrix& R);
    double dydY(Cam K, double Zy, double N, Matrix& R);
	double dydZ(Cam K, double Zy, double N, Matrix& R);
	double lx(Cam K, Point OP_0, double BP_x, Matrix& R);
	double ly(Cam K, Point OP_0, double BP_y, Matrix& R);
	double x(Cam K, Point OP_0, Matrix& R);
	double y(Cam K, Point OP_0, Matrix& R);

	//berechneter Schnittpunkt
    Point m_schnittpunkt;
	bool  m_is_error;
};



#endif
