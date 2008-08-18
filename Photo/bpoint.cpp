#include "bpoint.h"

#include <cmath>
#include "..//Basics//Matrix//matrix.h"
#include "..//Basics//rot_matrix.h"
#include "..//Basics//straight_line.h"

//###################################################################################
// Rechnung von Bildkoordinaten in Objektkoordinaten
//###################################################################################
bool BPoint::PixKooInBildKoo()
{
 //von Pixelkoordinaten in Bildkoordinaten unkorrigiert
 m_x = ( m_m - m_Cam->get_pix_row()/2 + 0.5 )*m_Cam->get_pix_size();
 m_y = ( m_Cam->get_pix_col()/2 - m_n + 0.5 )*m_Cam->get_pix_size();
 m_z = -fabs(m_Cam->get_c());//

return true;
}

//###################################################################################
bool BPoint::Verzeichnungskorrektur(double& vx,double& vy)
{
/**/
 
 //Berechnung der Radial-symetrischen Verzeichnung
 double rB =sqrt(m_x*m_x+m_y*m_y); //Bildradius,Abstand vom Bildhauptpunkt

 double dx_rad = m_x * (  m_Cam->get_A1()*(pow(rB,2.0)-pow(m_Cam->get_r0(),2.0))
	                    + m_Cam->get_A2()*(pow(rB,4.0)-pow(m_Cam->get_r0(),4.0))
				        + m_Cam->get_A3()*(pow(rB,6.0)-pow(m_Cam->get_r0(),6.0)));
 double dy_rad = m_y * (  m_Cam->get_A1()*(pow(rB,2.0)-pow(m_Cam->get_r0(),2.0))
	                    + m_Cam->get_A2()*(pow(rB,4.0)-pow(m_Cam->get_r0(),4.0))
				        + m_Cam->get_A3()*(pow(rB,6.0)-pow(m_Cam->get_r0(),6.0)));

  //Berechnung der Radial-asymetrischen und tangentialen Verzeichnung
 double dx_tan = m_Cam->get_B1() * ( rB*rB + 2.0*m_x*m_x ) + 2.0*m_Cam->get_B2()*m_x*m_y;
 double dy_tan = m_Cam->get_B2() * ( rB*rB + 2.0*m_y*m_y ) + 2.0*m_Cam->get_B1()*m_x*m_y;

 //Berechnung Affinitt und Scherung
 double dx_aff = m_Cam->get_C1()*m_x + m_Cam->get_C2()*m_y;
 double dy_aff = 0;

 //Addieren der Verzeichnungen
 vx = dx_rad + dx_tan + dx_aff;
 vy = dy_rad + dy_tan + dy_aff;

return true;
}

//###################################################################################
bool BPoint::TransInObjKoo()
{
 //Transformation in den Objektraum
 Rot M(m_Cam->get_rotX(),m_Cam->get_rotY(),m_Cam->get_rotZ());
 Matrix R;
 R=M;//.get_Matrix();
 
 Matrix x(3,1,Null);
 x(0,0)=m_x;
 x(1,0)=m_y;
 x(2,0)=m_z;
 
 Matrix X0(3,1,Null);
 X0(0,0)=m_Cam->get_OX();
 X0(1,0)=m_Cam->get_OY();
 X0(2,0)=m_Cam->get_OZ();
 
 Matrix X;
 Matrix Ri;
 Ri=R.MatMult(x);
 X=X0.MatAdd(Ri);
 
 m_x=X(0,0);
 m_y=X(1,0);
 m_z=X(2,0);

return true;
}

//###################################################################################
bool BPoint::BildpunktkorrekturVonPixInBildKoo()
{
 double vx,vy;
 
 //Umrechnen von PixelKoordinaten in Bildkoordinaten (m_z=-Kamerakonstante)
 PixKooInBildKoo();
 
 //Anbringen der Bildhauptpunktlage 
 //double xh=m_Cam->get_xh();
 //double yh=m_Cam->get_yh();
 
 m_x -= m_Cam->get_xh();
 m_y -= m_Cam->get_yh();

 //Berechnen der Verzeichnungskorrektur
 Verzeichnungskorrektur(vx,vy);

 //Anbringen der Verzeichnung
 m_x -= vx;
 m_y -= vy;

 //speichern der korrigierten Bildkoordinaten
 m_xkorr = m_x;
 m_ykorr = m_y;

 //Transformieren ins Objektkoordinatensystem
 TransInObjKoo();
 
return true;
}




//###################################################################################
// Rechnung von Objektkoordinaten in Bildkoordinaten
//###################################################################################
bool BPoint::PixelkorrekturVonBildInPixKoo()
{
 //Rcktransformation von Objektkoordinaten in Bildkoordinaten
 Matrix X(3,1,Null);
 X(0,0)=m_x;
 X(1,0)=m_y;
 X(2,0)=m_z;

 Matrix X0(3,1,Null);
 X0(0,0)=m_Cam->get_OX();
 X0(1,0)=m_Cam->get_OY();
 X0(2,0)=m_Cam->get_OZ();
 
 Rot M(m_Cam->get_rotX(),m_Cam->get_rotY(),m_Cam->get_rotZ());
 Matrix R;
 R=M.get_Matrix().MatTrans();

 Matrix t;
 t=X.MatSub(X0);

 Matrix x;
 x=R.MatMult(t);

 m_x=(m_Cam->get_c())/x(2,0)*x(0,0);
 m_y=(m_Cam->get_c())/x(2,0)*x(1,0);

 //speichern der korrigierten Bildkoordinaten
 m_xkorr = m_x;
 m_ykorr = m_y;
 
 int i=0;
 double xt=m_x,yt=m_y,dx=100000,dy=1000000;
 
 double vx,vy;
 
 while( fabs(dx) > 0.00000000001 && fabs(dy) > 0.00000000001 )
 //while( fabs(dx) > 0.000001 && fabs(dy) > 0.000001 )
 {
   
   Verzeichnungskorrektur(vx,vy); 
   m_x=(m_Cam->get_c())/x(2,0)*x(0,0)+vx;
   m_y=(m_Cam->get_c())/x(2,0)*x(1,0)+vy;
   dx=m_x-xt;
   dy=m_y-yt;
   xt=m_x;
   yt=m_y;
   ++i;
   if(i>10000)
   {
       m_isOK=false;
	   break;
   }
 }

 //Anbringen der Hauptpunktverschiebung
 m_x+=m_Cam->get_xh();
 m_y+=m_Cam->get_yh();

 //von Bildkoordinaten in Pixelkoordinaten unkorrigiert	
 m_m =         m_x/m_Cam->get_pix_size() + m_Cam->get_pix_row()/2 - 0.5  ;
 m_n =(-1.0)*( m_y/m_Cam->get_pix_size() - m_Cam->get_pix_col()/2 - 0.5 );

 //Rckschreiben der Objektkoordinaten
 m_x=X(0,0);
 m_y=X(1,0);
 m_z=X(2,0);

return true;
}




//###################################################################################
// Eingabe / Ausgaberoutinen
//###################################################################################
void  BPoint::set_mnPixKoo (double m,double n) //Eingabe (m,n) des Bildpunktes in [pix]
{
 m_m=m;
 m_n=n;
 m_x=m_y=m_z    =-111111.1;
 BildpunktkorrekturVonPixInBildKoo();
}

//###################################################################################
void  BPoint::set_xyBKoo(double x,double y)
{
 m_m =         x/m_Cam->get_pix_size() + m_Cam->get_pix_row()/2 - 0.5  ;
 m_n =(-1.0)*( y/m_Cam->get_pix_size() - m_Cam->get_pix_col()/2 - 0.5 );

 BildpunktkorrekturVonPixInBildKoo();
}

//###################################################################################
void  BPoint::set_XYZObjKoo(double X,double Y,double Z) //Eingabe (x,y,z) des Objektpunktes in [mm]
{
 m_x=X;
 m_y=Y;
 m_z=Z;
 m_m=m_n=-1.0;
 PixelkorrekturVonBildInPixKoo();
}

//###################################################################################
Point BPoint::get_xyBKoo()
{
 Point P;
 P.set_X( ( m_m - m_Cam->get_pix_row()/2 + 0.5 )*m_Cam->get_pix_size() );
 P.set_Y( ( m_Cam->get_pix_col()/2 - m_n + 0.5 )*m_Cam->get_pix_size() );
 return P;
}


//###################################################################################
//Kernlinie
//###################################################################################
BPoint BPoint::get_KernlinenPunkt( Cam &C, double s )
{

 Gerade G( (*this).get_Cam().get_O() , (*this).get_Point() );
 Point PK = G.get_O().Add( G.get_R().MultS( s ) );

 BPoint BPKern(C,PK.get_X(),PK.get_Y(),PK.get_Z());

return BPKern;
}
