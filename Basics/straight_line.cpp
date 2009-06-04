#include "straight_line.h"

#include <cmath>
#include "..//Basics//Matrix//matrix.h"
#include "fix_values.h"

Gerade::Gerade()
{
 m_p2.set_Z(1.0);	
}

Gerade::Gerade(Point P1,Point P2)
{
 m_p1=P1;
 m_p2=P2;
}

Gerade::Gerade(list<Point>& KooL)
{
 //ungetestet!!!!!
	if(KooL.size()>2)
	{
	  Point Koo_Schw;
	 
	  //Schwerpunktberechnung
	  double sum_x=0,sum_y=0,sum_z=0;
	 
	  list<Point>::iterator iKooL = KooL.begin();

	  while(iKooL!=KooL.end())
	  {
	   sum_x+=iKooL->get_X();
	   sum_y+=iKooL->get_Y();
	   sum_z+=iKooL->get_Z();
	   ++iKooL;
	  }
	
	  Koo_Schw.set_X(sum_x/KooL.size());
	  Koo_Schw.set_Y(sum_y/KooL.size());
	  Koo_Schw.set_Z(sum_z/KooL.size());
	  //END


	  Matrix A(static_cast<int>(KooL.size()),3,Empty);
	  
	  iKooL = KooL.begin();
	  int i=0;
	  while(iKooL != KooL.end())
	  {
	   A(i,0)=iKooL->get_X() - Koo_Schw.get_X();
	   A(i,1)=iKooL->get_Y() - Koo_Schw.get_Y();
	   A(i,2)=iKooL->get_Z() - Koo_Schw.get_Z();
	  
	   ++i;
	   ++iKooL;
	  }

	  Matrix Q = A.MatTrans().MatMult(A);
	  //Matrix ew;
	  Matrix Ev = Q.MatEigVek();//ew

	  //Point KooEv;
	  //KooEv.set_X(Ev(0,0));
	  //KooEv.set_Y(Ev(1,0));
	  //KooEv.set_Z(Ev(2,0));
	 
	  Point KooEv;
	  KooEv.set_X(Ev(0,2));
	  KooEv.set_Y(Ev(1,2));
	  KooEv.set_Z(Ev(2,2));
	  	  
	  //test
	  //double d;
	  
	  //direction angle
	  
	  (*this).set_O_R(Koo_Schw,KooEv);
	  
	  //m_d=KooEv.Mult(Koo_Schw)*(-1.0);//change problems
	  //m_d=KooEv.Mult(Koo_Schw)*(-1.0);//change problems
	   
	  //m_d = (Point(sum_x/KooL.size(),sum_y/KooL.size(),sum_z/KooL.size()).Mult(KooEv))/KooL.size();
	  //cout<<endl<<"d_alt:"<<m_d<<"d_neu: "<<d<<flush;
	}
	
}

Gerade::Gerade(const Gerade& G)
{
 (*this)=G;
}

Gerade::~Gerade()
{
}
 
Gerade& Gerade::operator=(const Gerade& G)
{
 (*this).m_p1=G.m_p1;
 (*this).m_p2=G.m_p2;
 return (*this);	
}

double Gerade::AbstandGP(Point& P)
{
  //Geradenparamerter berechnen
  double t= (*this).get_R().Mult( P.Subt( (*this).get_O() ) ) / (*this).get_R().Quad();
  //Berechnen Abstandsvektor
  Point Koo1 = (*this).get_O().Subt( P ).Add( (*this).get_R().MultS( t ) );
  //Entfernung von der Geraden
  double d  = Koo1.Betrag();
 
 return d;
}

Point Gerade::LotFussP(Point& P)
{
  //Geradenparamerter berechnen
  double t= (*this).get_R().Mult( P.Subt( (*this).get_O() ) ) / (*this).get_R().Quad();
  //Berechnen Lotfupunkt
  Point LotF;
  LotF = (*this).get_O().Add( (*this).get_R().MultS( t ) );
 
return LotF;
}

double Gerade::SchnittWinkelGG(Gerade& G)
{
  Point G1O;
  G1O=(*this).get_O(); //Ortsvektor
  Point G1R;
  G1R=(*this).get_R(); //Richtungsvektor
  Point G2O;
  G2O=G.get_O(); //Ortsvektor
  Point G2R;
  G2R=G.get_R(); //Richtungsvektor

  double w = acos( ( G1R.Mult(G2R) / ( G1R.Betrag()*G2R.Betrag() ) ) );
  w=w/PI*180;
 
return w;
}

Point Gerade::Schnitt(Gerade &G)
{
  //neuer Ansatz
	  Matrix An(2,2,Null);
	  Matrix xn;
	  Matrix bn(2,1,Null);
      
	  Point G1O;
	  G1O=(*this).get_O(); //Ortsvektor
	  Point G1R;
	  G1R=(*this).get_R(); //Richtungsvektor
	  Point G2O;
	  G2O=G.get_O(); //Ortsvektor
	  Point G2R;
	  G2R=G.get_R(); //Richtungsvektor
	  
	  double x1n= G1R.get_X()*G1R.get_X()+G1R.get_Y()*G1R.get_Y()+G1R.get_Z()*G1R.get_Z();
	  double x2n=-G1R.get_X()*G2R.get_X()-G1R.get_Y()*G2R.get_Y()-G1R.get_Z()*G2R.get_Z();
	  double x3n= G1R.get_X()*G2R.get_X()+G1R.get_Y()*G2R.get_Y()+G1R.get_Z()*G2R.get_Z();
	  double x4n=-G2R.get_X()*G2R.get_X()-G2R.get_Y()*G2R.get_Y()-G2R.get_Z()*G2R.get_Z();

	  An(0,0)=x1n;
	  An(0,1)=x2n;

	  An(1,0)=x3n;
	  An(1,1)=x4n;

	  double b1n=-G1O.get_X()*G1R.get_X()+G2O.get_X()*G1R.get_X()
		         -G1O.get_Y()*G1R.get_Y()+G2O.get_Y()*G1R.get_Y()
				 -G1O.get_Z()*G1R.get_Z()+G2O.get_Z()*G1R.get_Z();

	  double b2n=-G1O.get_X()*G2R.get_X()+G2O.get_X()*G2R.get_X()
		         -G1O.get_Y()*G2R.get_Y()+G2O.get_Y()*G2R.get_Y()
				 -G1O.get_Z()*G2R.get_Z()+G2O.get_Z()*G2R.get_Z();
  
	  bn(0,0)=b1n;
	  bn(1,0)=b2n;

	  xn=An.MatInvert().MatMult( bn );
 
	  Point Sn,S1n,S2n;
	  S1n = (*this).get_O().Add( (*this).get_R().MultS(  xn(0,0) ) );
      S2n =       G.get_O().Add(       G.get_R().MultS(  xn(1,0) ) );

	  Sn.set_X( (S1n.get_X()+S2n.get_X())/2.0);
	  Sn.set_Y( (S1n.get_Y()+S2n.get_Y())/2.0);
	  Sn.set_Z( (S1n.get_Z()+S2n.get_Z())/2.0);

	  Sn.set_dX( (S1n.get_X()-S2n.get_X())/2.0);
	  Sn.set_dY( (S1n.get_Y()-S2n.get_Y())/2.0);
	  Sn.set_dZ( (S1n.get_Z()-S2n.get_Z())/2.0);
	  
  //Gleichnugssystem Ax=b
	  Matrix A(2,2,Null);
	  Matrix x;
	  Matrix b(2,1,Null);
   /*
	  Point G1O;
	  G1O=(*this).getO(); //Ortsvektor
	  Point G1R;
	  G1R=(*this).getR(); //Richtungsvektor
	  Point G2O;
	  G2O=G.getO(); //Ortsvektor
	  Point G2R;
	  G2R=G.getR(); //Richtungsvektor
*/
	  double x1=G1R.get_X();
	  double x2=(-1)*G2R.get_X();
	  double x3=G1R.get_Y();
	  double x4=(-1)*G2R.get_Y();

	  A(0,0)=x1;
	  A(0,1)=x2;

	  A(1,0)=x3;
	  A(1,1)=x4;

	  double b1=G2O.get_X()-G1O.get_X();
	  double b2=G2O.get_Y()-G1O.get_Y();
  
	  b(0,0)=b1;
	  b(1,0)=b2;

	  x=A.MatInvert().MatMult( b );
 
	  Point S,S1,S2;
	  S1 = (*this).get_O().Add( (*this).get_R().MultS(  x(0,0) ) );
      S2 =       G.get_O().Add(       G.get_R().MultS(  x(1,0) ) );

	  S.set_X( (S1.get_X()+S2.get_X())/2.0);
	  S.set_Y( (S1.get_Y()+S2.get_Y())/2.0);
	  S.set_Z( (S1.get_Z()+S2.get_Z())/2.0);

	  S.set_dX( (S1.get_X()-S2.get_X())/2.0);
	  S.set_dY( (S1.get_Y()-S2.get_Y())/2.0);
	  S.set_dZ( (S1.get_Z()-S2.get_Z())/2.0);

 return Sn;
}

ostream& operator<<(ostream& s,const Gerade& G)
{
   int precision=5;       //Nachkommastellen   
   //int vorkommastellen=8; //Minus zhlt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

   s<<"O: ("
	<<G.get_O()
	<<"  R: "
	<<G.get_R()
    <<") ";

return s;
};
