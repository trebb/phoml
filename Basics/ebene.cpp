#include "ebene.h"
#include "Matrix//matrix.h"

Ebene::Ebene(Point N,double D)
{
 m_n=N.Norm();
 m_d=D;
}

Ebene::Ebene(list<Point> &KooL)
{
  	if(KooL.size()>3)
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

	  Point KooEv;
	  KooEv.set_X(Ev(0,0));
	  KooEv.set_Y(Ev(1,0));
	  KooEv.set_Z(Ev(2,0));
	  
	  m_n=KooEv;
	  m_d=KooEv.Mult(Koo_Schw)*(-1);
	}
}

Ebene::Ebene(const Ebene& E )
{
	(*this)=E;
}

Ebene::~Ebene()
{
}

Point Ebene::get_N() const 
{
 return m_n; 
}
    
double Ebene::get_D() const
{ 
 return m_d; 
}

Gerade Ebene::Schnitt(Ebene &E)
{
 
  if( (*this).get_N() == E.get_N() || (*this).get_N() == E.get_N().MultS(-1.0) )
  {
   Point  P0(0.0,0.0,0.0);
   Gerade G(P0,P0);
   
   return G;
  }
  else
  {	  
      
   Point n1;
   n1=(*this).get_N();

   Point n2;
   n2=E.get_N();

   Point n3;
   n3=n1.SpatP(n2);

   //A
   Matrix matA(3,3,Null);

   matA(0,0)=n1.get_X();
   matA(0,1)=n1.get_Y();
   matA(0,2)=n1.get_Z();

   matA(1,0)=n2.get_X();
   matA(1,1)=n2.get_Y();
   matA(1,2)=n2.get_Z();

   matA(2,0)=n3.get_X();
   matA(2,1)=n3.get_Y();
   matA(2,2)=n3.get_Z();

   double D = matA.MatDet();
	   if(D==0)
	   {
		   Point  P0(0.0,0.0,0.0);
           Gerade G(P0,P0);
   
        return G;
	   }

   //b
   Matrix matD(3,1,Null);

   matD(0,0)=(-1)*(*this).get_D();
   matD(1,0)=(-1)*E.get_D();
   matD(2,0)=0.0;

   //x
   Matrix matX;

   matX=matA.MatInvert().MatMult(matD);
   
   //Radiusvektor
   Point  P1(matX(0,0),matX(1,0),matX(2,0));
   Point  P2=P1.Add(n3);
   
   Gerade G(P1,P2);
   
   return G;
  }

}

Point Ebene::Durchstoss(Gerade &G)
{
 Point P=G.get_O().Add( 
	            G.get_R().MultS(
	                            ( (*this).get_D()-(*this).get_N().Mult(G.get_O()) ) /
	                            ( (*this).get_N().Mult(G.get_R())                )
							   )
			         );

return P;
}
