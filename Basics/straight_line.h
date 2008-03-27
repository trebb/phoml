#ifndef __STRAIGHT_LINE_h
#define __STRAIGHT_LINE_h

#include <iostream>

#include "point.h"

using namespace std;

class Gerade
{
public:
 Gerade(Point P1,Point P2);
 Gerade(const Gerade& G);
 ~Gerade();

 Gerade& operator=(const Gerade& G);

 Point get_O() { return m_p1; }
    
 Point get_R() const { Point P;
                      P.set_X(m_p2.get_X()-m_p1.get_X());
					  P.set_Y(m_p2.get_Y()-m_p1.get_Y());
					  P.set_Z(m_p2.get_Z()-m_p1.get_Z());
					  P=P.DivS(P.Betrag());
					  return P;
 }
	
	double AbstandGP      (Point& P);
	Point  LotFussP       (Point& P);
	double SchnittWinkelGG(Gerade& G);
	Point  Schnitt        (Gerade &G);

private:

  Point m_p1; //GeradenPunkt 1
  Point m_p2; //GeradenPunkt 2

};




#endif
