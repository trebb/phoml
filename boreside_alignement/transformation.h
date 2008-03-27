#ifndef __TRANSFORMATION_h
#define __TRANSFORMATION_h

#include <iostream>
#include <list>

#include "..//Basics//point.h"
#include "..//Basics//Matrix//matrix.h"


class Transformation
{
public:
 Transformation(list<Point> &KooSys1L,list<Point> &KooSys2L,list<Point> &KooSys1Lreject,list<Point> &KooSys2Lreject);
 ~Transformation(){}

 Matrix&  get_Rotation()    { return m_Rot; }
 Point&   get_Translation() { return m_T; }
 double&  get_Massstab()    { return m_m; }
 //double get_MassstabX()   { return m_mx; }
 //double get_MassstabY()   { return m_my; }
 //double get_MassstabZ()   { return m_mz; }

 //static bool get_RotWinkel(Matrix& Rot,double& o,double& p,double& k);

private:

 //Hilfsfunktionen
 void init();
 bool Naeherung_4Punkte     (list<Point> &KooSys1L,list<Point> &KooSys2L, Matrix &Rotout, Point &T , double &m);
 bool Helmerttransformation (list<Point> &KooSys1L,list<Point> &KooSys2L,list<Point> &KooSys1Lreject,list<Point> &KooSys2Lreject, Matrix &Rotout, Point &T , double &m);
 bool Helmerttransformation2(list<Point> &KooSys1L,list<Point> &KooSys2L,list<Point> &KooSys1Lreject,list<Point> &KooSys2Lreject, Matrix &Rotout, Point &T , double &m);
 
 Point Schwerpunkt(list<Point> PointL);
 //static double clamp(double& wert, double min, double max);
 bool Punkte_aus_Liste(int Anzahl,list<Point> &KooSys1InL, list<Point> &KooSys1OutL, list<Point> &KooSys2InL, list<Point> &KooSys2OutL);


 //Variablen	 
 Matrix m_Rot;    //Rotationsmatrix
 Point m_T;       //Translation
 double m_m;      //Mastab
 double m_mx;      //Mastab x
 double m_my;      //Mastab y
 double m_mz;      //Mastab z

 //Reduzierung auf den Schwerpunkt (nur Translation) (1. Schritt fr bessere Nherung der rotation)
 Point m_T_Sys1;
 Point m_T_Sys2;

 //Fr spezialflle die partu nicht wollen werden Alle Daten pauschal um 20 in omega phi kappa weiter gedreht.
 double m_offset_winkel;
 Matrix m_offset_Rot;

};



#endif
