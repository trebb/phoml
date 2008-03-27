#include "rot_matrix.h"
#include <cmath>

#include "fix_values.h"

//constructor I
Rot::Rot(double rotX,double rotY,double rotZ)
{
	 isError=false;
	 
	 m_R.create(3,3,Null);
     double Omega = rotX;
     double Phi   = rotY;
     double Kappa = rotZ;

     m_R(0,0) = cos( Phi) * cos( Kappa);
     m_R(1,0) = cos( Omega) * sin( Kappa) + sin( Omega) * sin( Phi) * cos( Kappa);
     m_R(2,0) = sin( Omega) * sin( Kappa) - cos( Omega) * sin( Phi) * cos( Kappa);
			
     m_R(0,1) = - cos( Phi) * sin( Kappa);
     m_R(1,1) = cos( Omega) * cos( Kappa) - sin( Omega) * sin( Phi) * sin( Kappa);
     m_R(2,1) = sin( Omega) * cos( Kappa) + cos( Omega) * sin( Phi) * sin( Kappa);

     m_R(0,2) = sin( Phi);
     m_R(1,2) = - sin( Omega) * cos( Phi);
     m_R(2,2) = cos( Omega) * cos( Phi);

}
//constructor II
Rot::Rot(const Matrix& R)
{
 isError=false;	
 (*this).m_R=R.MatCopy();
}
//copy constructor
Rot::Rot(const Rot& R)
{
 (*this)=R;
}
//deconstructor    
Rot::~Rot()
{
 //R.~Matrix();
}

Rot& Rot::operator=(const Rot& R)
{
 (*this).m_R=R.m_R;
 return (*this);
}

Rot::operator Matrix () const
{
 return m_R.MatCopy();
}

Matrix Rot::get_Matrix()
{
	return (m_R.MatCopy()); 
}

//ein Vielfaches von einem Winkel reduzieren
double Rot::clamp(double& wert, double min, double max)
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

bool Rot::get_RotWinkel(double& Omega,double& Phi,double& Kappa)
{
 if(m_R.getCol()==3 && m_R.getRow()==3)
 {
 	   double r11 =m_R(0,0); 
	   double r21 =m_R(1,0); 
	   double r31 =m_R(2,0); 
	   double r12 =m_R(0,1); 
	   double r22 =m_R(1,1); 
	   double r32 =m_R(2,1); 
	   double r13 =m_R(0,2); 
	   double r23 =m_R(1,2); 
	   double r33 =m_R(2,2); 

	   double threshold = 9.99999e-13;
       if(fabs(r11)<threshold) r11=0.0;
	   if(fabs(r21)<threshold) r21=0.0;
	   if(fabs(r31)<threshold) r31=0.0;
	   if(fabs(r12)<threshold) r12=0.0;
	   if(fabs(r22)<threshold) r22=0.0;
	   if(fabs(r32)<threshold) r32=0.0;
	   if(fabs(r13)<threshold) r13=0.0;
	   if(fabs(r23)<threshold) r23=0.0;
	   if(fabs(r33)<threshold) r33=0.0;
  	   
	   Phi = asin(r13);

       if(r23||r33)
	    Omega = atan2(-r23,r33);
	   else
	    Omega = atan2(-r22,r32);
	   
	     //Testrechnung
	       //double Omega1 = atan2(-r23,r33);
	       //double Omega2 = atan2(-r22,r32);
	   
	   if(r12||r11)
        Kappa = atan2(-r12,r11);
	   else
	    Kappa = atan2(-r22,r21);

	     //Testrechnung
	       //double Kappa1 = atan2(-r12,r11);
	       //double Kappa2 = atan2(-r22,r21);
      
	  /* 
	   if(-threshold < r13-1.0 && r13-1.0 < threshold) //r13==1
	   {
	    //Omega = atan2(r32,r22)/2;
		//Kappa = atan2(r21,r22)/2;
	    Omega = atan2(r32,r22);
		Kappa = 0.0;
	   }
	   if(-threshold < r13+1.0 && r13+1.0 < threshold) //r13==-1
	   {
	    //Omega = atan2(r32,r22)/2;
		//Kappa = atan2(r21,r22)/2;
	    Omega = atan2(r32,r22);
		Kappa = 0.0;
	   }
	   */

	   if(fabs(r13-1.0) < threshold || fabs(r13+1.0) < threshold)
	   {
         if(r32||r22)
		 {
	      Omega = atan2(r32,r22);
		  Kappa = 0.0;
		 }
		 else
		 {
		  Omega = 0.0;
		  Kappa = atan2(r21,r22);
		 }
	   }
	   
	   Omega = clamp(Omega, -PI, PI);
	   Phi   = clamp(Phi  , -PI, PI);
	   Kappa = clamp(Kappa, -PI, PI);

	   Rot Rt(Omega,Phi,Kappa);
	   if(Rt.get_Matrix().NearEqual(m_R,threshold))
	   {
	    //cout<<"passt";
		   return true;
	   }
	   else
	   {
	    //cout<<"passt nicht!";
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
