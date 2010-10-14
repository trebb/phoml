#include "point.h"

#include <cmath>

#include "rot_matrix.h"


double Point::Quad()
{
         double d =     ( (*this).get_X()*(*this).get_X() 
		                 +(*this).get_Y()*(*this).get_Y()
				         +(*this).get_Z()*(*this).get_Z()
				        );
  return d;
}
double Point::Betrag()
{
         double d =  sqrt( (*this).get_X()*(*this).get_X() 
		                  +(*this).get_Y()*(*this).get_Y()
				          +(*this).get_Z()*(*this).get_Z()
				         );
  return d;
}
Point Point::Norm()
{
 Point n=(*this).DivS( (*this).Betrag() );

 return n;
}
double Point::Abstand(const Point &B)
{
         double d = sqrt( (B.get_X()-(*this).get_X())*(B.get_X()-(*this).get_X()) 
		                 +(B.get_Y()-(*this).get_Y())*(B.get_Y()-(*this).get_Y())
				         +(B.get_Z()-(*this).get_Z())*(B.get_Z()-(*this).get_Z())
				        );
  return d;
} 
Point Point::Add(const Point &B)
{
	 Point Koo;
	 
	 Koo.set_X((*this).get_X()+B.get_X());
	 Koo.set_Y((*this).get_Y()+B.get_Y());
	 Koo.set_Z((*this).get_Z()+B.get_Z());
        
  return Koo;
}
Point Point::Subt(const Point &B)
{
	 Point Koo;
	 
	 Koo.set_X((*this).get_X()-B.get_X());
	 Koo.set_Y((*this).get_Y()-B.get_Y());
	 Koo.set_Z((*this).get_Z()-B.get_Z());
        
  return Koo;
}
double Point::Mult(const Point &B)
{
	 double d = (*this).get_X()*B.get_X() + (*this).get_Y()*B.get_Y() + (*this).get_Z()*B.get_Z() ;
	
  return d;
}
Point Point::MultS(const double t )
{
     Point Koo;
	 
	 Koo.set_X((*this).get_X()*t);
	 Koo.set_Y((*this).get_Y()*t);
	 Koo.set_Z((*this).get_Z()*t);
        
  return Koo;
}
Point Point::DivS(const double t )
{
     Point Koo;
	 
	 Koo.set_X((*this).get_X()/t);
	 Koo.set_Y((*this).get_Y()/t);
	 Koo.set_Z((*this).get_Z()/t);
        
 return Koo;
}
Point Point::SpatP(const Point &B)
{
	 Point Koo;
	 
	 Koo.set_X( (*this).get_Y()*B.get_Z() - (*this).get_Z()*B.get_Y());
	 Koo.set_Y( (*this).get_Z()*B.get_X() - (*this).get_X()*B.get_Z());
	 Koo.set_Z( (*this).get_X()*B.get_Y() - (*this).get_Y()*B.get_X());
	
  return Koo;
}
Point Point::Rotation( Point& X0, Matrix& R)
{
     //Punkttransformation
	 Matrix x(3,1,Null);
	 x(0,0)=(*this).get_X();
	 x(1,0)=(*this).get_Y();
	 x(2,0)=(*this).get_Z();
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.get_X();
	 X0_(1,0)=X0.get_Y();
	 X0_(2,0)=X0.get_Z();
 
	 Matrix X;
	 Matrix Ri=R.MatMult(x);
	 X=X0_.MatAdd(Ri);
 
	 Point PRt(X(0,0),X(1,0),X(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).get_dX();
	 dx(1,0)=(*this).get_dY();
	 dx(2,0)=(*this).get_dZ();
 
	 Matrix dX=R.MatMult(dx);
	  
     PRt.set_dX(dX(0,0));
	 PRt.set_dY(dX(1,0));
	 PRt.set_dZ(dX(2,0));

return PRt;
}

Point Point::Rotation( Point& X0, Matrix& R, double& m)
{
     //Punkttransformation
	 Matrix x(3,1,Null);
	 x(0,0)=(*this).get_X();
	 x(1,0)=(*this).get_Y();
	 x(2,0)=(*this).get_Z();
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.get_X();
	 X0_(1,0)=X0.get_Y();
	 X0_(2,0)=X0.get_Z();
 
	 Matrix X;
	 Matrix Ri=R.MatMultSkalar(m).MatMult(x);
	 X=X0_.MatAdd(Ri);
 
	 Point PRt(X(0,0),X(1,0),X(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).get_dX();
	 dx(1,0)=(*this).get_dY();
	 dx(2,0)=(*this).get_dZ();
 
	 Matrix dX=R.MatMultSkalar(m).MatMult(dx);
	  
     PRt.set_dX(dX(0,0));
	 PRt.set_dY(dX(1,0));
	 PRt.set_dZ(dX(2,0));

return PRt;
}


Point Point::RotationRueck( Point& X0, Matrix& R)
{
     //Punkttransformation
	 Matrix x(3,1,Null);
	 x(0,0)=(*this).get_X();
	 x(1,0)=(*this).get_Y();
	 x(2,0)=(*this).get_Z();
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.get_X();
	 X0_(1,0)=X0.get_Y();
	 X0_(2,0)=X0.get_Z();
 
	 Matrix X =x.MatSub(X0_);
	 Matrix Ri=R.MatInvert().MatMult(X);
	 //Matrix Ri=R.MatTrans().MatMult(X);
	 Point PRt(Ri(0,0),Ri(1,0),Ri(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).get_dX();
	 dx(1,0)=(*this).get_dY();
	 dx(2,0)=(*this).get_dZ();
 
	 Matrix dX=R.MatInvert().MatMult(dx);
	 //Matrix dX=R.MatTrans().MatMult(dx);
	  
     PRt.set_dX(dX(0,0));
	 PRt.set_dY(dX(1,0));
	 PRt.set_dZ(dX(2,0));

return PRt;
}

Point Point::RotationRueck( Point& X0, Matrix& R, double& m)
{
     //Punkttransformation
	 Matrix x(3,1,Null);
	 x(0,0)=(*this).get_X();
	 x(1,0)=(*this).get_Y();
	 x(2,0)=(*this).get_Z();
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.get_X();
	 X0_(1,0)=X0.get_Y();
	 X0_(2,0)=X0.get_Z();
 
	 double m_inv=1.0/m;

	 Matrix X =x.MatSub(X0_);
	 Matrix Ri=R.MatInvert().MatMultSkalar(m_inv).MatMult(X);
	 Point PRt(Ri(0,0),Ri(1,0),Ri(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).get_dX();
	 dx(1,0)=(*this).get_dY();
	 dx(2,0)=(*this).get_dZ();
 
	 Matrix dX=R.MatInvert().MatMultSkalar(m_inv).MatMult(dx);
	  
     PRt.set_dX(dX(0,0));
	 PRt.set_dY(dX(1,0));
	 PRt.set_dZ(dX(2,0));

return PRt;
}

Point Point::RotationRueck( Point& X0, Matrix& R, double& mx, double& my, double& mz)
{
     //Punkttransformation
	 Matrix x(3,1,Null);
	 x(0,0)=(*this).get_X();
	 x(1,0)=(*this).get_Y();
	 x(2,0)=(*this).get_Z();
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.get_X();
	 X0_(1,0)=X0.get_Y();
	 X0_(2,0)=X0.get_Z();
 
	 Matrix X =x.MatSub(X0_);
	 Matrix Ri=R.MatInvert().MatMult(X);
	 Point PRt(Ri(0,0)*mx,Ri(1,0)*my,Ri(2,0)*mz);

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).get_dX();
	 dx(1,0)=(*this).get_dY();
	 dx(2,0)=(*this).get_dZ();
 
	 Matrix dX=R.MatInvert().MatMult(dx);
	  
     PRt.set_dX(dX(0,0)*mx);
	 PRt.set_dY(dX(1,0)*mx);
	 PRt.set_dZ(dX(2,0)*mx);

return PRt;
}

ostream& operator<<(ostream& s,const Point& A)
{
   int precision=5;       //Nachkommastellen   
   int vorkommastellen=8; //Minus zählt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

   s<<" ("
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<A.get_X()
	<<","
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<A.get_Y()
	<<","
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<A.get_Z()
	<<") "
	<<"std("
	<<setfill(' ')<<setw(precision+1)
    <<A.get_dX()
    <<","
    <<setfill(' ')<<setw(precision+1)
    <<A.get_dY()
    <<","
    <<setfill(' ')<<setw(precision+1)
    <<A.get_dZ()
    <<") ";

return s;
};
