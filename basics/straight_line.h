#ifndef __STRAIGHT_LINE_h
#define __STRAIGHT_LINE_h

#include <iostream>
#include <list>

#include "point.h"

using namespace std;

class Gerade
{
public:
 Gerade();
 Gerade(Point P1,Point P2);
 Gerade(list<Point>& points);
 Gerade(const Gerade& G);
 ~Gerade();

 Gerade& operator=(const Gerade& G);

 enum Eplane{xy,yz,xz};

 //calc_average_plane();
 
 Point get_O() const { return m_p1; }
    
 Point get_R() const { Point P;
                      P.set_X(m_p2.get_X()-m_p1.get_X());
					  P.set_Y(m_p2.get_Y()-m_p1.get_Y());
					  P.set_Z(m_p2.get_Z()-m_p1.get_Z());
					  P=P.DivS(P.Betrag());
					  return P;
 }
 
 void set_O_R(Point &O,Point &n) { m_p1=O;
 								   m_p2 = O.Add(n.MultS(10.0));
 }
	
	double AbstandGP      (Point& P);
	Point  LotFussP       (Point& P);
	double SchnittWinkelGG(Gerade& G);
	Point  Schnitt        (Gerade &G);

private:

  Point m_p1; //GeradenPunkt 1
  Point m_p2; //GeradenPunkt 2

};

ostream& operator<<(ostream& s,const Gerade& G);


#endif
