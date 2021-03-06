#include "cam.h"

#include <fstream>
#include <sstream>
#include <cmath>

#include "..//basics//fix_values.h"
#include "..//basics//rotation_matrix.h"
//#include "..//basics//rot_matrix.h"//old!

//#######################################################################################
//ein Vielfaches von einem Winkel reduzieren
double Cam::clamp(double& wert, double min, double max)
{
   while(wert < min)
   {
       wert += (max-min);
   }
   while(wert > max)
   {
       wert -= (max-min);
   }
   return(wert);
} 

Cam::Cam()
{
		m_pix_size=m_pix_row=m_pix_col=
		m_OX=m_OY=m_OZ=
		m_dOX=m_dOY=m_dOZ=
		m_rotX=m_rotY=m_rotZ=
		m_drotX=m_drotY=m_drotZ=
		m_c=m_xh=m_yh=
		m_A1=m_A2=m_A3=
		m_B1=m_B2=
		m_C1=m_C2=
		m_r0=0.0;
		  //m_OX=m_OY=m_OZ=
}
/*
Cam::Cam(double pix_row,double pix_col,double pix_size,
		double OX,  double OY,  double OZ,
	    double rotX,double rotY,double rotZ,
	    double c,   double xh,  double yh, 
		double A1,  double A2,  double A3,
		double B1,  double B2, double C1,
		double C2, double r0):m_pix_size(pix_size),m_pix_row(pix_row),m_pix_col(pix_col),
		m_OX(OX),m_OY(OY),m_OZ(OZ),m_rotX(rotX),m_rotY(rotY),m_rotZ(rotZ),
		m_c(c),m_xh(xh),m_yh(yh),m_A1(A1),m_A2(A2),m_A3(A3),m_B1(B1),m_B2(B2),m_C1(C1),m_C2(C2),m_r0(r0)
{

}
*/
Cam::Cam(double pix_row,double pix_col,double pix_size,
        double OX,  double OY,  double OZ,
        double dOX,  double dOY,  double dOZ,
        double rotX,double rotY,double rotZ,
        double drotX,double drotY,double drotZ,
        double c,   double xh,  double yh,
        double A1,  double A2,  double A3,
        double B1,  double B2, double C1,
        double C2, double r0):m_pix_size(pix_size),m_pix_row(pix_row),m_pix_col(pix_col),
        m_OX(OX),m_OY(OY),m_OZ(OZ),
        m_dOX(dOX),m_dOY(dOY),m_dOZ(dOZ),
        m_rotX(rotX),m_rotY(rotY),m_rotZ(rotZ),
        m_drotX(drotX),m_drotY(drotY),m_drotZ(drotZ),
        m_c(c),m_xh(xh),m_yh(yh),m_A1(A1),m_A2(A2),m_A3(A3),m_B1(B1),m_B2(B2),m_C1(C1),m_C2(C2),m_r0(r0)
{

}
				   
Cam::~Cam()
{
}

Cam& Cam::operator=(const Cam &C)
{		  
	 (*this).m_pix_row = C.m_pix_row;
	 (*this).m_pix_col = C.m_pix_col;
	 (*this).m_pix_size= C.m_pix_size;
	 (*this).m_OX      = C.m_OX;
	 (*this).m_OY      = C.m_OY;
	 (*this).m_OZ      = C.m_OZ;
	 (*this).m_dOX      = C.m_dOX;
	 (*this).m_dOY      = C.m_dOY;
	 (*this).m_dOZ      = C.m_dOZ;
     (*this).m_rotX = C.m_rotX;
	 (*this).m_rotY = C.m_rotY;
	 (*this).m_rotZ = C.m_rotZ;
	 (*this).m_drotX = C.m_drotX;
	 (*this).m_drotY = C.m_drotY;
	 (*this).m_drotZ = C.m_drotZ;
	 (*this).m_c    = C.m_c;
	 (*this).m_xh   = C.m_xh;
	 (*this).m_yh   = C.m_yh;
	 (*this).m_A1   = C.m_A1;
	 (*this).m_A2   = C.m_A2;
	 (*this).m_A3   = C.m_A3;
	 (*this).m_B1   = C.m_B1;
	 (*this).m_B2   = C.m_B2;
	 (*this).m_C1   = C.m_C1;
	 (*this).m_C2   = C.m_C2;
	 (*this).m_r0   = C.m_r0;

 return (*this);
}

Cam::Cam(const Cam &C)
{
		(*this)=C;
}
//#######################################################################################
//Bestimmung der relativen Orientierung zweier Kameras
Matrix Cam::TransInRellativeOrientierung( Cam &C_l, Cam &C_r, Cam &C_l_rell ,Cam &C_r_rell)
{
 //#############
 //Kamera links

	
	 // Rotationsmatrix von Kamera links (in Objektkoordinaten)
	 Rotation_matrix R1_(Rotation_matrix::math,C_l.get_rotX(),C_l.get_rotY(),C_l.get_rotZ());
	 Matrix R1=R1_.get_Matrix();
	 //R1.MatShow(R1);
 
	 //fr die Transformation von Objektkoordinaten ins Koordinatensystem Kamera 1
	 Matrix RotInKooC_l;
	 RotInKooC_l=R1.MatTrans();

 
 //########################
 // Setzen der Kamera links
 C_l_rell = C_l; //bertragen der Kalib.werte
 
 Point O_l(0.0,0.0,0.0);
 //C_l_rell.m_O = O_l;
 C_l_rell.set_O( O_l );
 
  //Rotationswinkel
 C_l_rell.m_rotX = 0.0;
 C_l_rell.m_rotY = 0.0;
 C_l_rell.m_rotZ = 0.0;



 //#############
 //Kamera rechts
 
	
     // Rotationsmatrix von Kamera rechts (in Objektkoordinaten)
     Rotation_matrix R2_(Rotation_matrix::math,C_r.get_rotX(),C_r.get_rotY(),C_r.get_rotZ());
	 Matrix R2=R2_.get_Matrix();
	 //R2.MatShow(R2);


 //########################
 //Setzen der Kamera rechts
 C_r_rell=C_r; //bertragen der Kalib.werte


     //#######################################################################
	 // transformieren des Hauptpunktes Kamera 2 in KooSystem Kamera 1
	 // RT*(O_r-O_l) = Hauptpunkt Kamera 2 neu (im Koordinatensystem Kamera 1)
	 Matrix O_Rd(3,1,Null);
	 O_Rd(0,0)=C_r.get_O().get_X() - C_l.get_O().get_X();
	 O_Rd(1,0)=C_r.get_O().get_Y() - C_l.get_O().get_Y();
	 O_Rd(2,0)=C_r.get_O().get_Z() - C_l.get_O().get_Z();
 
	 Matrix O_R=RotInKooC_l.MatMult( O_Rd );
	 Point O_r(O_R(0,0),O_R(1,0),O_R(2,0));

 // setzen des Neuen Bildhauptpunktes im KooSystem Kamera 1
 //C_r_rell.m_O=O_r;
 C_r_rell.set_O(O_r);
 

	 //#######################################################################
     //berechnen der Rotationswinkel von Cam_r zu Cam_l
	 Matrix Rotw;
	 Rotw=RotInKooC_l.MatMult(R2);
	 //Rotw.MatShow(Rotw);

	   double o,p,k;
	   double r11,r12,r13,r21,r22,r23,r31,r32,r33;

	   r11 =Rotw(0,0); 
	   r21 =Rotw(1,0); 
	   r31 =Rotw(2,0); 
	   r12 =Rotw(0,1); 
	   r22 =Rotw(1,1); 
	   r32 =Rotw(2,1); 
	   r13 =Rotw(0,2); 
	   r23 =Rotw(1,2); 
	   r33 =Rotw(2,2); 
//neu
	   double threshold = 9.99999e-14;
       if(fabs(r11)<threshold) r11=0.0;
	   if(fabs(r21)<threshold) r21=0.0;
	   if(fabs(r31)<threshold) r31=0.0;
	   if(fabs(r12)<threshold) r12=0.0;
	   if(fabs(r22)<threshold) r22=0.0;
	   if(fabs(r32)<threshold) r32=0.0;
	   if(fabs(r13)<threshold) r13=0.0;
	   if(fabs(r23)<threshold) r23=0.0;
	   if(fabs(r33)<threshold) r33=0.0;
//END neu
	   p = asin (r13);
//alt
/*	   C = cos(p);

	   if(fabs(p)>0.0005)
	   {
		   trx_ =  r33 / C;
		   try_ = -r23 / C;
		   o    =  atan2(try_, trx_);

		   trx_ =  r11 / C;
		   try_ = -r12 / C;
		   k    =  atan2(try_, trx_);
	   }
	   else
	   {
		   o    =  0.0;
		   trx_ =  r22;
		   try_ =  r21;
		   k    =  atan2(try_, trx_);
	   }
	   */
//END alt
//neu
	   if(r23||r33)
	    o = atan2(-r23,r33);
	   else
	    o = atan2(-r22,r32);
	   
	     //Testrechnung
	       //double Omega1 = atan2(-r23,r33);
	       //double Omega2 = atan2(-r22,r32);
	   
	   if(r12||r11)
        k = atan2(-r12,r11);
	   else
	    k = atan2(-r22,r21);

	     //Testrechnung
	       //double Kappa1 = atan2(-r12,r11);
	       //double Kappa2 = atan2(-r22,r21);

	   if(fabs(r13-1.0) < threshold || fabs(r13+1.0) < threshold)
	   {
	    o = atan2(r32,r22);
		k = 0.0;
	   }
    //END neu
	   o = clamp(o, -PI, PI);
	   p = clamp(p, -PI, PI);
	   k = clamp(k, -PI, PI);

	   //Testausgabe
	   //Rot R3_(o,p,k);
	   //Matrix R3=R3_.R;
	   //R2.MatShow(R3);

 //setzen der neuen Rotationswinkel Kamera 2
 C_r_rell.m_rotX = o;
 C_r_rell.m_rotY = p;
 C_r_rell.m_rotZ = k;


return R1;
}








//#######################################################################################
//Ausleseroutine
bool Cam::read_from_ini(const char *datname)
{
ifstream SET_TXT;  //ifstream und ofstream dienen dazu Dateien fr eine Eingabe bzw.
                   //Ausgabe zu oeffnen
 SET_TXT.open(datname); //->zur Erklrung: die beiden Befehle ifstream .... und Set_TXT.open....
                        //knnen auch zu einem Befehl zusammengefasst werden:
                        //ifstream SET_TXT(datname); hier steckt indirekt der open Befehl drin
                        //ist wie ein Konstruktor
 if(!SET_TXT) { return false; }
  
 string hilf;
 int j=0;
   

               char s_0_1[]="SensorBreitePix=";

			   char s_0_2[]="SensorHoehePix=";
				
			   char s_0_3[]="Pixelgroesse=";
 
               char s_0_9[]="c=";
               
			   char s_1_0[]="xh=";
			  
			   char s_1_1[]="yh=";
               
			   char s_2_1[]="a1=";
			    
			   char s_2_2[]="a2=";
               
			   char s_2_3[]="a3=";

			   char s_3_1[]="b1=";

			   char s_3_2[]="b2=";

			   char s_4_1[]="c1=";
		       
			   char s_4_2[]="c2=";

			   char s_5_1[]="r0=";

			   char s_6_1[]="dx=";

			   char s_6_2[]="dy=";

			   char s_6_3[]="dz=";

			   char s_7_1[]="rotx=";

			   char s_7_2[]="roty=";

			   char s_7_3[]="rotz=";

 int count=0;
	
 while(getline(SET_TXT,hilf))
 {					
			if(hilf.length()>0 )
			if(hilf.at(j)!='\r')
            if(hilf.at(j)!='\n')
            if(hilf.at(j)!='#' )
            if(hilf.at(j)!='[' )
            if(hilf.at(j)!=' ' )
            if(hilf.length()>1 ) //one character is nothing
            if(hilf.at(j)!='/' && hilf.at(j+1)!='/')
			 {                  		   
				  size_t find_0_1=0;
              	      find_0_1=hilf.find(s_0_1)+1;  //find ist ein vordefinierter Befehl in der Klasse string!
              
					  if(find_0_1)
					  {hilf.erase(0,(find_0_1-2)+sizeof(s_0_1));  //erase heisst lschen auch in Klasse string vordefiniert!
					   stringstream stream; stream<<hilf.c_str(); //c_str() ein Befehl in der Klasse string, schiebe den Rest von hilfe in 
					                                              //stream, welches als stringstream deklariert wurden, nur hier kann man reinkopieren ....
					   hilf.erase(); 	   stream>>m_pix_row;
					   ++count;
					  }
              

				  size_t find_0_2=0;
					  find_0_2=hilf.find(s_0_2)+1;
				  
					  if(find_0_2)
					  {hilf.erase(0,(find_0_2-2)+sizeof(s_0_2));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_pix_col;
					   ++count;
					  }
					  

				  size_t find_0_3=0;
					  find_0_3=hilf.find(s_0_3)+1;
				  
					  if(find_0_3)
					  {hilf.erase(0,(find_0_3-2)+sizeof(s_0_3));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_pix_size;
					   ++count;
					  }
			
				
				  size_t find_0_9=0;
					  find_0_9=hilf.find(s_0_9)+1;
				  
					  if(find_0_9)
					  {hilf.erase(0,(find_0_9-2)+sizeof(s_0_9));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_c;
					   m_c=-fabs(m_c);
					   ++count;
					  }


				  size_t find_1_0=0;
              	      find_1_0=hilf.find(s_1_0)+1;
              
					  if(find_1_0)
					  {hilf.erase(0,(find_1_0-2)+sizeof(s_1_0));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_xh;
					   ++count;
					  }
              

				  size_t find_1_1=0;
					  find_1_1=hilf.find(s_1_1)+1;
				  
					  if(find_1_1)
					  {hilf.erase(0,(find_1_1-2)+sizeof(s_1_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_yh;
					   ++count;
					  }          
					  
				  size_t find_2_1=0;
					  find_2_1=hilf.find(s_2_1)+1;
				  
					  if(find_2_1)
					  {hilf.erase(0,(find_2_1-2)+sizeof(s_2_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_A1;
					   ++count;
					  }              


				  size_t find_2_2=0;
					  find_2_2=hilf.find(s_2_2)+1;
				  
					  if(find_2_2)
					  {hilf.erase(0,(find_2_2-2)+sizeof(s_2_2));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_A2;
					   ++count;
					  } 

					  
				  size_t find_2_3=0;
					  find_2_3=hilf.find(s_2_3)+1;
				  
					  if(find_2_3)
					  {hilf.erase(0,(find_2_3-2)+sizeof(s_2_3));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_A3;
					   ++count;
					  } 


				 size_t find_3_1=0;
					  find_3_1=hilf.find(s_3_1)+1;
				  
					  if(find_3_1)
					  {hilf.erase(0,(find_3_1-2)+sizeof(s_3_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_B1;
					   ++count;
					  }              


				  size_t find_3_2=0;
					  find_3_2=hilf.find(s_3_2)+1;
				  
					  if(find_3_2)
					  {hilf.erase(0,(find_3_2-2)+sizeof(s_3_2));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_B2;
					   ++count;
					  } 


				  size_t find_4_1=0;
					  find_4_1=hilf.find(s_4_1)+1;
				  
					  if(find_4_1)
					  {hilf.erase(0,(find_4_1-2)+sizeof(s_4_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_C1;
					   ++count;
					  }              


				  size_t find_4_2=0;
					  find_4_2=hilf.find(s_4_2)+1;
				  
					  if(find_4_2)
					  {hilf.erase(0,(find_4_2-2)+sizeof(s_4_2));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_C2;
					   ++count;
					  }
					  

				  size_t find_5_1=0;
					  find_5_1=hilf.find(s_5_1)+1;
				  
					  if(find_5_1)
					  {hilf.erase(0,(find_5_1-2)+sizeof(s_5_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_r0;
					   ++count;
					  }


				  size_t find_6_1=0;
					  find_6_1=hilf.find(s_6_1)+1;
				  
					  if(find_6_1)
					  {hilf.erase(0,(find_6_1-2)+sizeof(s_6_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); stream>>m_OX;
					   ++count;
					  }              


				  size_t find_6_2=0;
					  find_6_2=hilf.find(s_6_2)+1;
				  
					  if(find_6_2)
					  {hilf.erase(0,(find_6_2-2)+sizeof(s_6_2));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); stream>>m_OY;
					   ++count;
					  } 

					  
				  size_t find_6_3=0;
					  find_6_3=hilf.find(s_6_3)+1;
				  
					  if(find_6_3)
					  {hilf.erase(0,(find_6_3-2)+sizeof(s_6_3));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); stream>>m_OZ;
					   ++count;
					  } 


				  size_t find_7_1=0;
					  find_7_1=hilf.find(s_7_1)+1;
				  
					  if(find_7_1)
					  {hilf.erase(0,(find_7_1-2)+sizeof(s_7_1));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_rotX;
					   ++count;
					  }              


				  size_t find_7_2=0;
					  find_7_2=hilf.find(s_7_2)+1;
				  
					  if(find_7_2)
					  {hilf.erase(0,(find_7_2-2)+sizeof(s_7_2));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_rotY;
					   ++count;
					  } 

					  
				  size_t find_7_3=0;
					  find_7_3=hilf.find(s_7_3)+1;
				  
					  if(find_7_3)
					  {hilf.erase(0,(find_7_3-2)+sizeof(s_7_3));
					   stringstream stream; stream<<hilf.c_str();
					   hilf.erase(); 	   stream>>m_rotZ;
					   ++count;
					  } 

				  
						
			}
 }

 SET_TXT.close();
 SET_TXT.clear();

 if(count != 20)
 {
  cout<<endl<<"CAM -> Fail to read the old style calibration file!! "<<datname<<flush;
  return false;
 }
 cout<<endl<<"CAM -> OK -> reading the old style calibration file "<<datname<<flush;
 //cout<<endl<<(*this);
 return true;
}

bool Cam::write_in_ini(const char *datname)
{
 ofstream SET_TXT;  
 
 SET_TXT.open(datname); 
 if(!SET_TXT) { return false; }
 else
 {
  string hilf;
  //int j=0;
  
  SET_TXT.precision(10);
  SET_TXT.setf(ios::left,ios::showpoint);
  SET_TXT.setf(ios::showbase);


  SET_TXT<<"// in Pixel"<<endl;
  SET_TXT<<"SensorBreitePix="<<m_pix_row<<endl;
  SET_TXT<<"SensorHoehePix="<<m_pix_col<<endl<<endl;

  SET_TXT<<"// Pixelgroee in [mm]"<<endl;
  SET_TXT<<"Pixelgroesse="<<m_pix_size<<endl<<endl;

  SET_TXT<<"// KameraKonstante in [mm]"<<endl;
  SET_TXT<<"c= "<<m_c<<endl<<endl;

  SET_TXT<<"// Werte der inneren Orientierung"<<endl;
  SET_TXT<<"// Hauptpunkt [mm]"<<endl;
  SET_TXT<<"xh="<<m_xh<<endl;
  SET_TXT<<"yh="<<m_yh<<endl<<endl;

  SET_TXT<<"// Verzeichnungsparameter Radialsymmetrik"<<endl,
  SET_TXT<<"a1="<<m_A1<<endl;
  SET_TXT<<"a2="<<m_A2<<endl;
  SET_TXT<<"a3="<<m_A3<<endl<<endl;

  SET_TXT<<"// asymmterische und tangentiale Verzeichnung"<<endl;
  SET_TXT<<"b1="<<m_B1<<endl;
  SET_TXT<<"b2="<<m_B2<<endl<<endl;

  SET_TXT<<"// Affinitt und Scherung"<<endl;
  SET_TXT<<"c1="<<m_C1<<endl;
  SET_TXT<<"c2="<<m_C2<<endl<<endl;

  SET_TXT<<"// r0-Parameter"<<endl;
  SET_TXT<<"r0="<<m_r0<<endl<<endl;

  SET_TXT<<"// äußere Orientierung [?]"<<endl;
  SET_TXT<<"dx= "<<m_OX<<endl;
  SET_TXT<<"dy= "<<m_OY<<endl;
  SET_TXT<<"dz= "<<m_OZ<<endl<<endl;

  SET_TXT<<"// in [rad]"<<endl;
  SET_TXT<<"rotx="<<m_rotX<<endl;
  SET_TXT<<"roty="<<m_rotY<<endl;
  SET_TXT<<"rotz="<<m_rotZ<<endl<<endl;

  SET_TXT.close();
  SET_TXT.clear();
 }

return true;
}

ostream& operator<<(ostream& s,const Cam& C)
{
	  s.precision(10);
	  s.setf(ios::left,ios::showpoint);
	  s.setf(ios::showbase);

	  s<<"//in Pixel"<<endl;
	  s<<"SensorBreitePix="<<C.get_pix_row()<<endl;
	  s<<"SensorHoehePix="<<C.get_pix_col()<<endl<<endl;

	  s<<"//Pixelgroee in [mm]"<<endl;
	  s<<"Pixelgroesse="<<C.get_pix_size()<<endl<<endl;

	  s<<"//KameraKonstante in [mm]"<<endl;
	  s<<"c= "<<C.get_c()<<endl<<endl;

	  s<<"// Werte der inneren Orientierung"<<endl;
	  s<<"// Hauptpunkt [mm]"<<endl;
	  s<<"xh="<<C.get_xh()<<endl;
	  s<<"yh="<<C.get_yh()<<endl<<endl;

	  s<<"// Verzeichnungsparameter Radialsymmetrik"<<endl,
	  s<<"a1="<<C.get_A1()<<endl;
	  s<<"a2="<<C.get_A2()<<endl;
	  s<<"a3="<<C.get_A3()<<endl<<endl;

	  s<<"// asymmterische und tangentiale Verzeichnung"<<endl;
	  s<<"b1="<<C.get_B1()<<endl;
	  s<<"b2="<<C.get_B2()<<endl<<endl;

	  s<<"// Affinitt und Scherung"<<endl;
	  s<<"c1="<<C.get_C1()<<endl;
	  s<<"c2="<<C.get_C2()<<endl<<endl;

	  s<<"// r0-Parameter"<<endl;
	  s<<"r0="<<C.get_r0()<<endl<<endl;

	  s<<"//äußere Orientierung [mm]"<<endl;

	  s<<"dx= "<<C.get_O().get_X()<<endl;
	  s<<"dy= "<<C.get_O().get_Y()<<endl;
	  s<<"dz= "<<C.get_O().get_Z()<<endl<<endl;

	  s<<"// in [rad]"<<endl;
	  s<<"rotx="<<C.get_rotX()<<endl;
	  s<<"roty="<<C.get_rotY()<<endl;
	  s<<"rotz="<<C.get_rotZ()<<endl<<endl;

 return s;
}
