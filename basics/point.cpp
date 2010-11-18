#include "point.h"

#include <cmath>

#include "rot_matrix.h"


double Point::Quad()
{
 /*        double d =     ( (*this).m_x*(*this).m_x
		                 +(*this).m_y*(*this).m_y
				         +(*this).m_z*(*this).m_z
				        );
  return d;
 */
  return ( (*this).m_x*(*this).m_x
          +(*this).m_y*(*this).m_y
          +(*this).m_z*(*this).m_z
         );
}

Point  Point::Quad_separate()
{
  return Point ( (*this).m_x*(*this).m_x ,
                 (*this).m_y*(*this).m_y ,
                 (*this).m_z*(*this).m_z
             );
}

Point  Point::Sqrt_separate    ()
{
    return Point (  sqrt((*this).m_x) ,
                    sqrt((*this).m_y) ,
                    sqrt((*this).m_z)
                 );
}

double Point::Betrag()
{
  /*       double d =  sqrt( (*this).m_x*(*this).m_x
		                  +(*this).m_y*(*this).m_y
				          +(*this).m_z*(*this).m_z
				         );
  return d;
  */
  return sqrt( (*this).m_x*(*this).m_x
          +(*this).m_y*(*this).m_y
          +(*this).m_z*(*this).m_z
         );
}
Point Point::Norm()
{/*
 Point n=(*this).DivS( (*this).Betrag() );

 return n;
 */
 return (*this).DivS( (*this).Betrag() );
}
double Point::Abstand(const Point &B)
{/*
         double d = sqrt( (B.m_x-(*this).m_x)*(B.m_x-(*this).m_x)
		                 +(B.m_y-(*this).m_y)*(B.m_y-(*this).m_y)
				         +(B.m_z-(*this).m_z)*(B.m_z-(*this).m_z)
				        );
  return d;
  */
  return sqrt( (B.m_x-(*this).m_x)*(B.m_x-(*this).m_x)
          +(B.m_y-(*this).m_y)*(B.m_y-(*this).m_y)
          +(B.m_z-(*this).m_z)*(B.m_z-(*this).m_z)
         );
} 
Point Point::Add(const Point &B)
{
	 //Point Koo;
	 
	 //Koo.set_X((*this).m_x+B.m_x);
	 //Koo.set_Y((*this).m_y+B.m_y);
	 //Koo.set_Z((*this).m_z+B.m_z);
        
  //return Koo;
  return Point( (*this).m_x + B.m_x  ,
                (*this).m_y + B.m_y  ,
                (*this).m_z + B.m_z  ,
                 sqrt((*this).m_dx*(*this).m_dx + B.m_dx*B.m_dx),
                 sqrt((*this).m_dy*(*this).m_dy + B.m_dy*B.m_dy),
                 sqrt((*this).m_dz*(*this).m_dz + B.m_dz*B.m_dz)
  );
}
Point Point::Subt(const Point &B)
{
	 //Point Koo();
	 
	 //Koo.set_X((*this).m_x-B.m_x);
	 //Koo.set_Y((*this).m_y-B.m_y);
	 //Koo.set_Z((*this).m_z-B.m_z);
        
  //return Koo;
    return Point( (*this).m_x-B.m_x  ,
                  (*this).m_y-B.m_y  ,
                  (*this).m_z-B.m_z  ,
                  sqrt((*this).m_dx*(*this).m_dx + B.m_dx*B.m_dx),
                  sqrt((*this).m_dy*(*this).m_dy + B.m_dy*B.m_dy),
                  sqrt((*this).m_dz*(*this).m_dz + B.m_dz*B.m_dz)
    );
}
double Point::Mult(const Point &B)
{/*
	 double d = (*this).m_x*B.m_x + (*this).m_y*B.m_y + (*this).m_z*B.m_z ;
	
  return d;
  */
    return (*this).m_x*B.m_x + (*this).m_y*B.m_y + (*this).m_z*B.m_z ;
}
Point Point::MultS(const double t )
{/*
     Point Koo;
	 
	 Koo.set_X((*this).m_x*t);
	 Koo.set_Y((*this).m_y*t);
	 Koo.set_Z((*this).m_z*t);
        
  return Koo;
  */
  return Point( (*this).m_x*t , (*this).m_y*t , (*this).m_z*t , (*this).m_dx , (*this).m_dy ,(*this).m_dz );
}
Point Point::DivS( double t )
{/*
     Point Koo;
	 
	 Koo.set_X((*this).m_x/t);
	 Koo.set_Y((*this).m_y/t);
	 Koo.set_Z((*this).m_z/t);
        
 return Koo;
 */
 return Point( (*this).m_x/t  ,  (*this).m_y/t  ,  (*this).m_z/t , (*this).m_dx , (*this).m_dy ,(*this).m_dz );
}
Point Point::SpatP(const Point &B)
{/*
	 Point Koo;
	 
	 Koo.set_X( (*this).m_y*B.m_z - (*this).m_z*B.m_y);
	 Koo.set_Y( (*this).m_z*B.m_x - (*this).m_x*B.m_z);
	 Koo.set_Z( (*this).m_x*B.m_y - (*this).m_y*B.m_x);
	
  return Koo;
  */
  return Point( (*this).m_y*B.m_z - (*this).m_z*B.m_y  ,
                (*this).m_z*B.m_x - (*this).m_x*B.m_z  ,
                (*this).m_x*B.m_y - (*this).m_y*B.m_x  ,
                sqrt((*this).m_dx*(*this).m_dx/(*this).m_x + B.m_dx*B.m_dx/B.m_x),
                sqrt((*this).m_dy*(*this).m_dy/(*this).m_y + B.m_dy*B.m_dy/B.m_y),
                sqrt((*this).m_dz*(*this).m_dz/(*this).m_z + B.m_dz*B.m_dz/B.m_z)
  );
}
Point Point::Rotation( Point& X0, Matrix& R)
{
     //Punkttransformation
	 Matrix x(3,1,Null);
	 x(0,0)=(*this).m_x;
	 x(1,0)=(*this).m_y;
	 x(2,0)=(*this).m_z;
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.m_x;
	 X0_(1,0)=X0.m_y;
	 X0_(2,0)=X0.m_z;
 
	 Matrix X;
	 Matrix Ri=R.MatMult(x);
	 X=X0_.MatAdd(Ri);
 
	 Point PRt(X(0,0),X(1,0),X(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).m_dx;
	 dx(1,0)=(*this).m_dy;
	 dx(2,0)=(*this).m_dz;
 
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
	 x(0,0)=(*this).m_x;
	 x(1,0)=(*this).m_y;
	 x(2,0)=(*this).m_z;
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.m_x;
	 X0_(1,0)=X0.m_y;
	 X0_(2,0)=X0.m_z;
 
	 Matrix X;
	 Matrix Ri=R.MatMultSkalar(m).MatMult(x);
	 X=X0_.MatAdd(Ri);
 
	 Point PRt(X(0,0),X(1,0),X(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).m_dx;
	 dx(1,0)=(*this).m_dy;
	 dx(2,0)=(*this).m_dz;
 
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
	 x(0,0)=(*this).m_x;
	 x(1,0)=(*this).m_y;
	 x(2,0)=(*this).m_z;
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.m_x;
	 X0_(1,0)=X0.m_y;
	 X0_(2,0)=X0.m_z;
 
	 Matrix X =x.MatSub(X0_);
	 Matrix Ri=R.MatInvert().MatMult(X);
	 //Matrix Ri=R.MatTrans().MatMult(X);
	 Point PRt(Ri(0,0),Ri(1,0),Ri(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).m_dx;
	 dx(1,0)=(*this).m_dy;
	 dx(2,0)=(*this).m_dz;
 
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
	 x(0,0)=(*this).m_x;
	 x(1,0)=(*this).m_y;
	 x(2,0)=(*this).m_z;
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.m_x;
	 X0_(1,0)=X0.m_y;
	 X0_(2,0)=X0.m_z;
 
	 double m_inv=1.0/m;

	 Matrix X =x.MatSub(X0_);
	 Matrix Ri=R.MatInvert().MatMultSkalar(m_inv).MatMult(X);
	 Point PRt(Ri(0,0),Ri(1,0),Ri(2,0));

	 //Fehlertransformation
	 Matrix dx(3,1,Null);
	 dx(0,0)=(*this).m_dx;
	 dx(1,0)=(*this).m_dy;
	 dx(2,0)=(*this).m_dz;
 
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
	 x(0,0)=(*this).m_x;
	 x(1,0)=(*this).m_y;
	 x(2,0)=(*this).m_z;
 
	 Matrix X0_(3,1,Null);
	 X0_(0,0)=X0.m_x;
	 X0_(1,0)=X0.m_y;
	 X0_(2,0)=X0.m_z;
 
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

Point Point::Rotation_with_std( Point& X0, Rotation_matrix& R)
{
         //point transformation
         Matrix x(3,1,Null);
         x(0,0)=(*this).m_x;
         x(1,0)=(*this).m_y;
         x(2,0)=(*this).m_z;

         Matrix X0_(3,1,Null);
         X0_(0,0)=X0.m_x;
         X0_(1,0)=X0.m_y;
         X0_(2,0)=X0.m_z;

         Matrix X;
         Matrix Ri=R.get_Matrix().MatMult(x);
         X=X0_.MatAdd(Ri);

         Point PRt(X(0,0),X(1,0),X(2,0));

         //formula point rotation for deviation
         // Y = X0 + R*X

         // Yx = 1*X0x + 0*X0y + 0*X0z + 1*r11Xx + 1*r12Xy + 1*r13Xz + 0*r21Xx + 0*r22Xy + 0*r23Xz + 0*r31Xx + 0*r32Xy + 0*r33Xz
         // Yy = 0*X0x + 1*X0y + 0*X0z + 0*r11Xx + 0*r12Xy + 0*r13Xz + 1*r21Xx + 1*r22Xy + 1*r23Xz + 0*r31Xx + 0*r32Xy + 0*r33Xz
         // Yz = 0*X0x + 0*X0y + 1*X0z + 0*r11Xx + 0*r12Xy + 0*r13Xz + 0*r21Xx + 0*r22Xy + 0*r23Xz + 1*r31Xx + 1*r32Xy + 1*r33Xz


         //standard deviation for derivative X0 -> derivative line by line  ( (dYx/dX0x) , (dYy/dX0y) , (dYz/dX0z) )
         Point dYdX0 = X0.get_dXYZ();


         //standard deviation for derivative Xx (*this) -> derivative ( (dYx/dXx) , (dYy/dXx) , (dYz/dXx) )
         Matrix M_mask_dYdXx(3,1,Null); M_mask_dYdXx(0,0)=1.0;
         Matrix M_dYdXx = R.get_Matrix().MatMult(M_mask_dYdXx);

         Point dYdXx(M_dYdXx(0,0),M_dYdXx(1,0),M_dYdXx(2,0));
         dYdXx = dYdXx.MultS( (*this).m_dx );


         //standard deviation for derivative Xy (*this) -> derivative ( (dYx/dXy) , (dYy/dXy) , (dYz/dXy) )
         Matrix M_mask_dYdXy(3,1,Null); M_mask_dYdXy(1,0)=1.0;
         Matrix M_dYdXy = R.get_Matrix().MatMult(M_mask_dYdXy);

         Point dYdXy(M_dYdXy(0,0),M_dYdXy(1,0),M_dYdXy(2,0));
         dYdXy = dYdXy.MultS( (*this).m_dy );


         //standard deviation for derivative Xz (*this) -> derivative ( (dYx/dXz) , (dYy/dXz) , (dYz/dXz) )
         Matrix M_mask_dYdXz(3,1,Null); M_mask_dYdXz(2,0)=1.0;
         Matrix M_dYdXz = R.get_Matrix().MatMult(M_mask_dYdXz);

         Point dYdXz(M_dYdXz(0,0),M_dYdXz(1,0),M_dYdXz(2,0));
         dYdXz = dYdXz.MultS( (*this).m_dz );


         //standard deviation for rotation
         double drotX,drotY,drotZ;
         R.get_rotation_angle_std(R.get_rotation_matrix_type(),drotX,drotY,drotZ);


         //standard deviation for derivative rotx (*this) -> derivative ( (dYx/drotx) , (dYy/drotx) , (dYz/drotx) )
         Matrix R_drotx = R.get_differentiate_matrix(Rotation_matrix::rotx);
         Matrix x_drotx = R_drotx.MatMult(x);

         Point dYdrotx(x_drotx(0,0),x_drotx(1,0),x_drotx(2,0));
         dYdrotx = dYdrotx.MultS(drotX);


         //standard deviation for derivative roty (*this) -> derivative ( (dYx/droty) , (dYy/droty) , (dYz/droty) )
         Matrix R_droty = R.get_differentiate_matrix(Rotation_matrix::roty);
         Matrix x_droty = R_droty.MatMult(x);

         Point dYdroty(x_droty(0,0),x_droty(1,0),x_droty(2,0));
         dYdroty = dYdroty.MultS(drotY);


         //standard deviation for derivative rotz (*this) -> derivative ( (dYx/drotz) , (dYy/drotz) , (dYz/drotz) )
         Matrix R_drotz = R.get_differentiate_matrix(Rotation_matrix::rotz);
         Matrix x_drotz = R_drotz.MatMult(x);

         Point dYdrotz(x_drotz(0,0),x_drotz(1,0),x_drotz(2,0));
         dYdrotz = dYdrotz.MultS(drotZ);



         //sum derivative for the standard deviation
            Point dY_d_all;
            dY_d_all = (      dYdX0.Quad_separate()
                         .Add(dYdXx.Quad_separate())
                         .Add(dYdXy.Quad_separate())
                         .Add(dYdXz.Quad_separate())
                         .Add(dYdrotx.Quad_separate())
                         .Add(dYdroty.Quad_separate())
                         .Add(dYdrotz.Quad_separate())
                        ).Sqrt_separate() ;
/*
            cout <<endl <<"Hin";
            cout <<endl <<"standard deviation X0 translation :"<<X0.get_dXYZ();
            cout <<endl <<"standard deviation (*this)        :"<<(*this).get_dXYZ();
            cout <<endl <<"standard deviation rotx,roty,rotz :   "<<drotX<<" "<<drotY<<" "<<drotZ;
            cout <<endl <<"standard deviations calc for each";
            cout <<endl <<"dYdX0                             : "<<dYdX0;
            cout <<endl <<"dYdXx                             : "<<dYdXx;
            cout <<endl <<"dYdXy                             : "<<dYdXy;
            cout <<endl <<"dYdXz                             : "<<dYdXz;
            cout <<endl <<"dYdrotx                           : "<<dYdrotx;
            cout <<endl <<"dYdroty                           : "<<dYdroty;
            cout <<endl <<"dYdrotz                           : "<<dYdrotz;
            cout <<endl <<"standard deviation transformation : "<<dY_d_all;
            cout <<endl;
*/
 return PRt.set_dXYZ(dY_d_all);
}

Point Point::RotationRueck_with_std( Point& X0, Rotation_matrix& R)
{
       //Punkttransformation
       Matrix x(3,1,Null);
       x(0,0)=(*this).m_x;
       x(1,0)=(*this).m_y;
       x(2,0)=(*this).m_z;

       Matrix X0_(3,1,Null);
       X0_(0,0)=X0.m_x;
       X0_(1,0)=X0.m_y;
       X0_(2,0)=X0.m_z;

       Rotation_matrix R_inv = R; //copy ::math or ::geod
       R_inv = R.get_Matrix().MatInvert();//set new rotation matrix

       Matrix X =x.MatSub(X0_);
       Matrix Ri=R_inv.get_Matrix().MatMult(X);
       //Matrix Ri=R_inv.MatTrans().MatMult(X);
       Point PRt(Ri(0,0),Ri(1,0),Ri(2,0));


       //formula point rotation for deviation
       // Y = Ri( X - X0 )

       // Yx = 1*r11(Xx-X0x) + 1*r12(Xy-X0y) + 1*r13(Yz-X0z) + 0*r21(Xx-X0x) + 0*r22(Xy-X0y) + 0*r23(Yz-X0z) + 0*r31(Xx-X0x) + 0*r32(Xy-X0y) + 0*r33(Yz-X0z)
       // Xy = 0*r11(Xx-X0x) + 0*r12(Xy-X0y) + 0*r13(Yz-X0z) + 1*r21(Xx-X0x) + 1*r22(Xy-X0y) + 1*r23(Yz-X0z) + 0*r31(Xx-X0x) + 0*r32(Xy-X0y) + 0*r33(Yz-X0z)
       // Yz = 0*r11(Xx-X0x) + 0*r12(Xy-X0y) + 0*r13(Yz-X0z) + 0*r21(Xx-X0x) + 0*r22(Xy-X0y) + 0*r23(Yz-X0z) + 1*r31(Xx-X0x) + 1*r32(Xy-X0y) + 1*r33(Yz-X0z)


       //standard deviation for derivative X0 -> derivative line by line  ( (dYx/dX0x) , (dYy/dX0y) , (dYz/dX0z) )
       Matrix M_mask_dYdX0x(3,1,Null); M_mask_dYdX0x(0,0)=1.0;
       Point dYdX0x = R_inv.get_Matrix().MatMult(M_mask_dYdX0x);
       dYdX0x = dYdX0x.MultS( X0.get_dX() );

       Matrix M_mask_dYdX0y(3,1,Null); M_mask_dYdX0y(0,0)=1.0;
       Point dYdX0y = R_inv.get_Matrix().MatMult(M_mask_dYdX0y);
       dYdX0y = dYdX0y.MultS( X0.get_dY() );

       Matrix M_mask_dYdX0z(3,1,Null); M_mask_dYdX0z(0,0)=1.0;
       Point dYdX0z = R_inv.get_Matrix().MatMult(M_mask_dYdX0z);
       dYdX0z = dYdX0z.MultS( X0.get_dZ() );


       //standard deviation for derivative Xx (*this) -> derivative ( (dYx/dXx) , (dYy/dXx) , (dYz/dXx) )
       Matrix M_mask_dYdXx(3,1,Null); M_mask_dYdXx(0,0)=1.0;
       Matrix M_dYdXx = R_inv.get_Matrix().MatMult(M_mask_dYdXx);

       Point dYdXx(M_dYdXx(0,0),M_dYdXx(1,0),M_dYdXx(2,0));
       dYdXx = (dYdXx.MultS( (*this).m_dx ));


       //standard deviation for derivative Xy (*this) -> derivative ( (dYx/dXy) , (dYy/dXy) , (dYz/dXy) )
       Matrix M_mask_dYdXy(3,1,Null); M_mask_dYdXy(1,0)=1.0;
       Matrix M_dYdXy = R_inv.get_Matrix().MatMult(M_mask_dYdXy);

       Point dYdXy(M_dYdXy(0,0),M_dYdXy(1,0),M_dYdXy(2,0));
       dYdXy = dYdXy.MultS( (*this).m_dy );


       //standard deviation for derivative Xz (*this) -> derivative ( (dYx/dXz) , (dYy/dXz) , (dYz/dXz) )
       Matrix M_mask_dYdXz(3,1,Null); M_mask_dYdXz(2,0)=1.0;
       Matrix M_dYdXz = R_inv.get_Matrix().MatMult(M_mask_dYdXz);

       Point dYdXz(M_dYdXz(0,0),M_dYdXz(1,0),M_dYdXz(2,0));
       dYdXz = dYdXz.MultS( (*this).m_dz );


       //standard deviation for rotation
       double drotX,drotY,drotZ;
       R_inv.get_rotation_angle_std(R_inv.get_rotation_matrix_type(),drotX,drotY,drotZ);


       //standard deviation for derivative rotx (*this) -> derivative ( (dYx/drotx) , (dYy/drotx) , (dYz/drotx) )
       Matrix R_drotx = R_inv.get_differentiate_matrix(Rotation_matrix::rotx);
       Matrix x_drotx = R_drotx.MatMult(X);

       Point dYdrotx(x_drotx(0,0),x_drotx(1,0),x_drotx(2,0));
       dYdrotx = dYdrotx.MultS(drotX);


       //standard deviation for derivative roty (*this) -> derivative ( (dYx/droty) , (dYy/droty) , (dYz/droty) )
       Matrix R_droty = R_inv.get_differentiate_matrix(Rotation_matrix::roty);
       Matrix x_droty = R_droty.MatMult(X);

       Point dYdroty(x_droty(0,0),x_droty(1,0),x_droty(2,0));
       dYdroty = dYdroty.MultS(drotY);


       //standard deviation for derivative rotz (*this) -> derivative ( (dYx/drotz) , (dYy/drotz) , (dYz/drotz) )
       Matrix R_drotz = R_inv.get_differentiate_matrix(Rotation_matrix::rotz);
       Matrix x_drotz = R_drotz.MatMult(X);

       Point dYdrotz(x_drotz(0,0),x_drotz(1,0),x_drotz(2,0));
       dYdrotz = dYdrotz.MultS(drotZ);



       //sum derivative for the standard deviation
       Point dY_d_all;
       dY_d_all = (      dYdX0x.Quad_separate()
                    .Add(dYdX0y.Quad_separate())
                    .Add(dYdX0z.Quad_separate())
                    .Add(dYdXx.Quad_separate())
                    .Add(dYdXy.Quad_separate())
                    .Add(dYdXz.Quad_separate())
                    .Add(dYdrotx.Quad_separate())
                    .Add(dYdroty.Quad_separate())
                    .Add(dYdrotz.Quad_separate())
                   ).Sqrt_separate() ;
/*
       cout <<endl <<"Rück";
       cout <<endl <<"standard deviation X0 translation :"<<X0.get_dXYZ();
       cout <<endl <<"standard deviation (*this)        :"<<(*this).get_dXYZ();
       cout <<endl <<"standard deviation rotx,roty,rotz :    "<<drotX<<" "<<drotY<<" "<<drotZ;
       cout <<endl <<"standard deviations calc for each";
       cout <<endl <<"dYdX0x                            : "<<dYdX0x;
       cout <<endl <<"dYdX0y                            : "<<dYdX0y;
       cout <<endl <<"dYdX0z                            : "<<dYdX0z;
       cout <<endl <<"dYdXx                             : "<<dYdXx;
       cout <<endl <<"dYdXy                             : "<<dYdXy;
       cout <<endl <<"dYdXz                             : "<<dYdXz;
       cout <<endl <<"dYdrotx                           : "<<dYdrotx;
       cout <<endl <<"dYdroty                           : "<<dYdroty;
       cout <<endl <<"dYdrotz                           : "<<dYdrotz;
       cout <<endl <<"standard deviation transformation : "<<dY_d_all;
       cout <<endl;

*/

 return PRt.set_dXYZ(dY_d_all);
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
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.get_dX()
    <<","
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.get_dY()
    <<","
    <<setfill(' ')<<setw(precision+vorkommastellen+1)
    <<A.get_dZ()
    <<") ";

return s;
};
