#ifndef __EBENE_h
#define __EBENE_h

#include <list>

#include "rot_matrix.h"
#include "point.h"

#include "straight_line.h"

class Ebene
{
public:
 Ebene(Point N,double D);
 Ebene(list<Point> &KooL);
 Ebene(const Ebene& E );
 ~Ebene();

 Ebene& operator= (const Ebene &E)
 {
	 (*this).m_n=E.get_N();
	 (*this).m_d=E.get_D();
  return (*this);
 }
 

 Point  get_N() const;
 double get_D() const;
 
 Gerade Schnitt        (Ebene  &E);
 Point  Durchstoss     (Gerade &G);
	
 //double Abstand        (Point &P);
 //Point  LotFussP       (Point &P);
 //double SchnittWinkel  (Ebene &E);
 //Point  Schnitt        (Ebene &E);

private:

  Point m_n; //Normalenvektor
  double m_d; //Abstand zum Koordinatenursprung

};

inline ostream& operator<<(ostream& s,const Ebene &E)
{
   int precision=5;       //Nachkommastellen   
   int vorkommastellen=8; //Minus zhlt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

   Point P=E.get_N();

   s<<"( n: "
	//<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<P
	<<","
	<<" d:"
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<E.get_D()
	<<") ";

return s;
};

#endif
