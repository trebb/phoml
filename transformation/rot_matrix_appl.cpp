#include "rot_matrix_appl.h"

#include <cmath>

#include "..//Basics//fix_values.h"

//constructor I
Rot_appl::Rot_appl(double rotX,double rotY,double rotZ)
{
	 isError=false;
	 
	 m_R.create(3,3,Null);

///* [z][y][x] -> geodetic rotation
	    	 //first row
	    	 m_R(0,0) = cos(rotY) * cos(rotZ) ;
	         m_R(0,1) = sin(rotX) * sin(rotY) * cos(rotZ) - cos(rotX) * sin(rotZ) ;
	         m_R(0,2) = cos(rotX) * sin(rotY) * cos(rotZ) + sin(rotX) * sin(rotZ) ;

	         //second row
	         m_R(1,0) = cos(rotY) * sin(rotZ);
	         m_R(1,1) = cos(rotX) * cos(rotZ) + sin(rotX) * sin(rotY) * sin(rotZ) ;
	         m_R(1,2) = cos(rotX) * sin(rotY) * sin(rotZ) - sin(rotX) * cos(rotZ) ;

	         //last row
	         m_R(2,0) =-sin(rotY) ;
	         m_R(2,1) = sin(rotX) * cos(rotY) ;
	         m_R(2,2) = cos(rotX) * cos(rotY) ;

//*/
}
//constructor II
Rot_appl::Rot_appl(const Matrix& R)
{
 isError=false;	
 (*this).m_R=R.MatCopy();
}
//copy constructor
Rot_appl::Rot_appl(const Rot_appl& R)
{
 (*this)=R;
}
//deconstructor    
Rot_appl::~Rot_appl()
{
 //R.~Matrix();
}

Rot_appl& Rot_appl::operator=(const Rot_appl& R)
{
 (*this).m_R=R.m_R;
 return (*this);
}

Rot_appl& Rot_appl::operator=(const Matrix& R)
{
 m_R=R.MatCopy();
 return (*this);
}
/*
Rot::operator Matrix () const
{
 return m_R.MatCopy();
}
*/
Rot_appl::operator Matrix& ()
{
 return m_R;
}

Matrix Rot_appl::get_Matrix()
{
	return m_R.MatCopy(); 
}

//ein Vielfaches von einem Winkel reduzieren
double Rot_appl::clamp(double& wert, double min, double max)
{
   while(wert < min)
   {
       wert += (max-min);
   }
   while(wert > max)
   {
       wert -= (max-min);
   }
   return wert;
} 

bool Rot_appl::get_RotWinkel(double& Omega,double& Phi,double& Kappa)
{
 if(m_R.getCol()==3 && m_R.getRow()==3)
 {
 	   double r11 =m_R(0,0); 
	   double r12 =m_R(0,1);
	   double r13 =m_R(0,2);
	   double r21 =m_R(1,0); 
	   double r22 =m_R(1,1);
	   double r23 =m_R(1,2);
	   double r31 =m_R(2,0); 
	   double r32 =m_R(2,1); 
	   double r33 =m_R(2,2); 

	   double threshold = pow(9.99999,-13);
       if(fabs(r11)<threshold) r11=0.0;
	   if(fabs(r21)<threshold) r21=0.0;
	   if(fabs(r31)<threshold) r31=0.0;
	   if(fabs(r12)<threshold) r12=0.0;
	   if(fabs(r22)<threshold) r22=0.0;
	   if(fabs(r32)<threshold) r32=0.0;
	   if(fabs(r13)<threshold) r13=0.0;
	   if(fabs(r23)<threshold) r23=0.0;
	   if(fabs(r33)<threshold) r33=0.0;
  	   
	   if(r32||r33)
	   {
		Omega = atan2(r32,r33);
	   }

	   if(r32||r33||r31)
	   {
		  Phi = atan2(-r31,sqrt(r32*r32+r33*r33));
	   }
	   else if(r31)
	   {
		  Phi = -asin(r31);
	   }
	   
	   if(r21||r11)
	   {
	    Kappa = atan2(r21,r11);
	   }

	   Omega = clamp(Omega, -PI, PI);
	   Phi   = clamp(Phi  , -PI, PI);
	   Kappa = clamp(Kappa, 0, 2*PI);

	   Rot_appl Rt(Omega,Phi,Kappa);
	   if(Rt.get_Matrix().NearEqual(m_R,threshold))
	   {
	    //cout<<"passt";
		   return true;
	   }
	   else
	   {
	       cout<<endl<<"Rot_appl passt nicht!";
	       isError=true;
           errorstring="calculation fails!!";
		   return false;
	   }
	   
 }
 else
 {
  isError=true;
  errorstring="No rotation matrix available!!";
  return false;
 }

}
