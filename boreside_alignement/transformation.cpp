#include "transformation.h"

#include <cmath>
#include <vector>

//#include "Basics//point.h"
#include "..//Basics//fix_values.h"
#include "..//Basics//rot_matrix.h"

//#######################################################################################
// Initialisierung
void Transformation::init()
{
 m_Rot.create(3,3,Null);
 m_m=1.0;
}




//#######################################################################################
// Konstructor -> Input: zwei gleich sortierte Punktlisten KooSys1 und KooSys2 (Pos 1 Liste 1 -> P1 in Sys1 und Pos 1 Liste 2 -> P1 in Sys2)
Transformation::Transformation(list<Point> &KooSys1L,list<Point> &KooSys2L,list<Point> &KooSys1Lreject,list<Point> &KooSys2Lreject)
{
 init(); 

 //Beide Listen mssen die gleiche Punktnzahl haben und min vier Punkte enthalten!!
 if(KooSys1L.size()==KooSys2L.size()&&KooSys1L.size()>3)
 {

	 //Reduzierung beider Listen auf den Schwerpunkt (sollte sich einfacher berechnen lassen die 3D Helmert)

	
	//exakte Lsung mit 4 Punkten 
	if(KooSys1L.size()==4 && KooSys2L.size()==4)
	{
		 //Nherung fr Helmerttransformation ber 4Punkte in beiden KoordinatenSystemen
		 Matrix Rotout;
		 Point X0(0.0,0.0,0.0);
		 double m=1.0;

		 bool ok = Naeherung_4Punkte(KooSys1L,KooSys2L,Rotout,X0,m);

		 if(ok)
		 {
		  m_Rot = Rotout;
		  m_T   = X0;
		  m_m   = m;
		 }
	}
	else
	{

		 //Nherung fr Helmerttransformation ber 4Punkte in beiden KoordinatenSystemen
		 Matrix Rotout;
		 Point X0(0.0,0.0,0.0);
		 double m=0.0;

		 list<Point> KooSys1L4,KooSys2L4;

		 Punkte_aus_Liste(4,KooSys1L,KooSys1L4,KooSys2L,KooSys2L4);
		 
		 bool ok = Naeherung_4Punkte(KooSys1L4,KooSys2L4,Rotout,X0,m);

		 if(ok)
		 {
		   m_Rot = Rotout.MatCopy(); // wichtig bei nur operator= ist Rotout leer!!!
		   m_T   = X0;
		   m_m   = m;
		 
		   cout<<endl<<"Nherung Helmert OK!";


		       //Helmerttransformation
		   
		       bool ok=Helmerttransformation2(KooSys1L,KooSys2L,KooSys1Lreject,KooSys2Lreject,Rotout,X0,m);
			   if(ok)
			   {   
				   m_Rot = Rotout;
				   m_T   = X0;
				   m_m   = m;
			   }
			   else
			   {
			    cout<<endl<<"Fehler in der Helmerttransformation!";
			   }

			   
		

		  /**/
		 }
	} // END else



	

	  


 } //END if(KooSys1L.size()==KooSys2L.size()&&KooSys1L.size()>3)

}




//#######################################################################################
//Näherung (exakte Lsung) über 4 Punkte
bool Transformation::Naeherung_4Punkte(list<Point> &KooSys1L, list<Point> &KooSys2L, Matrix &Rotout, Point &T , double &m)
{
 if(KooSys1L.size()==4 && KooSys2L.size()==4)
 {
  //4 unabhngige Punkte werden bentigt

  //Lsen des Gleichungssytems x=Ry+T  ->Punkt x-KooSys1  ->Punkt y-KooSys2  -> R-Rotationsmatrix(3x3) (3Punkte-9Unbekannte)
  //alle x-Werte (xx)*Ay^(-1)=R11-13(und Tx)
  //alle y-Werte (xy)*Ay^(-1)=R21-23(und Ty)
  //alle z-Werte (xz)*Ay^(-1)=R31-33(und Tz)

  //fllen der xx-xy-xz-Vektoren mit den Punkten von KooSys1
  Matrix xx(4,1,Empty);
  Matrix xy(4,1,Empty);
  Matrix xz(4,1,Empty);
  
  list<Point>::iterator iKooSys2L    = KooSys2L.begin();//red

      int j=0;
	  while(iKooSys2L!=KooSys2L.end())//red
	  {
	   xx(j,0)=iKooSys2L->get_X();//red
	   xy(j,0)=iKooSys2L->get_Y();//red
	   xz(j,0)=iKooSys2L->get_Z();//red
	   ++iKooSys2L;//red
	   ++j;
	  }

	  //xx.MatShow();
	  //xy.MatShow();
	  //xz.MatShow();

  //fllen der A-Matrix mit den Punkten KooSys2
  Matrix Ay(4,4,Empty);
  list<Point>::iterator iKooSys1L    = KooSys1L.begin();

      int i=0;
	  while(iKooSys1L!=KooSys1L.end())
	  {
	   Ay(i,0)=iKooSys1L->get_X();
	   Ay(i,1)=iKooSys1L->get_Y();
	   Ay(i,2)=iKooSys1L->get_Z();
	   Ay(i,3)=1;
	   ++iKooSys1L;
	   ++i;
	  }

	  //cout<<endl<<"Ay:"<<endl;
	  //Ay.MatShow();

	  Matrix AyInv=Ay.MatInvert();

	  //Ay.MatShow();
  
	  Matrix R1113,R2123,R3133;

	  R1113=AyInv.MatMult(xx);
	  R2123=AyInv.MatMult(xy);
	  R3133=AyInv.MatMult(xz);
  
	  //R1113.MatShow(R1113);
	  //R2123.MatShow(R2123);
	  //R3133.MatShow(R3133);
  
	  //zusammensetzen der Lsungsvektoren
	  //Rotationsmatrix
	  Rotout.create(3,3,Null);
	  Rotout(0,0)=R1113(0,0);
	  Rotout(0,1)=R1113(1,0);
	  Rotout(0,2)=R1113(2,0);
	  Rotout(1,0)=R2123(0,0);
	  Rotout(1,1)=R2123(1,0);
	  Rotout(1,2)=R2123(2,0);
	  Rotout(2,0)=R3133(0,0);
	  Rotout(2,1)=R3133(1,0);
	  Rotout(2,2)=R3133(2,0);
	  //Translationsvektor
	  Point Transl(R1113(3,0),R2123(3,0),R3133(3,0));
	  T=Transl;

	
      Point nx(Rotout(0,0),Rotout(1,0),Rotout(2,0));
	  Point ny(Rotout(0,1),Rotout(1,1),Rotout(2,1));
	  Point nz(Rotout(0,2),Rotout(1,2),Rotout(2,2));
 
	  
	  Point nx_new=nx.Norm();
	  Point nz_new=(nx_new.SpatP(ny.Norm()));
	  //Point nz_new2=ny.SpatP(nx);
	  Point ny_new=nz_new.SpatP(nx_new);

	  nx_new=nx_new.Norm();
	  ny_new=ny_new.Norm();
	  nz_new=nz_new.Norm();
	  
      
	  Rotout(0,0)=nx_new.get_X();
	  Rotout(1,0)=nx_new.get_Y();
	  Rotout(2,0)=nx_new.get_Z();
	  Rotout(0,1)=ny_new.get_X();
	  Rotout(1,1)=ny_new.get_Y();
	  Rotout(2,1)=ny_new.get_Z();
	  Rotout(0,2)=nz_new.get_X();
	  Rotout(1,2)=nz_new.get_Y();
	  Rotout(2,2)=nz_new.get_Z();
/**/	  

	  //anbringen des mittleren Mastabs an die Translation
	  double bnxyz=(nx.Betrag()+ny.Betrag()+nz.Betrag())/3;
	  //T=T.DivS(bnxyz);

	  //Ausgabe des Mastabs
	  m = bnxyz;

	  m_mx=nx.Betrag();
	  m_my=ny.Betrag();
	  m_mz=nz.Betrag();
	  T.set_X(T.get_X()/m_mx);
	  T.set_Y(T.get_Y()/m_my);
	  T.set_Z(T.get_Z()/m_mz);

	  //Ausgabe des mittleren Mastabs
	  m =(m_mx+m_my+m_mz)/3;

	  
	         
	         //Testausgabe
		     double o1,p1,k1;
	         //(*this).get_RotWinkel(Rotout,o1,p1,k1);
	         Rot TempRot(Rotout);
	         TempRot.get_RotWinkel(o1,p1,k1);
	         cout<<endl<<endl<<"o: "<<o1/PI*180.0<<"  p: "<<p1/PI*180.0<<"  k: "<<k1/PI*180.0;
	         cout<<endl<<"Transl.:"<<T;
			 cout<<endl<<"m     .:"<<m;
			 cout<<endl<<Rotout;
	  
 return true;
}
else
 return false;

}

//#######################################################################################
//Helmerttransformation
bool Transformation::Helmerttransformation2(list<Point> &KooSys1L,list<Point> &KooSys2L,list<Point> &KooSys1Lreject,list<Point> &KooSys2Lreject, Matrix &Rotm, Point &T , double &m)
{
 /*
 Ausgangsgleichung
 X2=X0+m*R*X1

 v = Verbesserung
 Rotation nur fr sehr kleine Winkel -> Vereinfachung der Rotationsmatrix
 I=Einheitsmatrix
          1 0 0          0    kappa  -beta
 I+dR = ( 1 1 1 ) + ( -kappa    0    omega  )
          0 0 1         beta -omega    0

 Ersetzen von m durch (1+m)

 X2 + v =X0+(1+m)*(I+dR)*X1

 ausmultipliziert und umgeformt

 v = X0 + m*X1 + dR*X1 + m*dR*X1 - ( X2 - X1 )

 Term  "m*dR*X1" fllt weg da er nahe Null ist

 v = X0 + m*X1 + dR*X1 - ( X2 - X1 )


 ordentlich aufgeschrieben in Matrix - Form ( jeder 3D Punkt ergibt 3 Gleichungen vx,vy,vz) -> min 3 Punkte -> 9 Parameter -> 7 werden gebraucht

 v = A*p-l
  
       1 0 0  X1x   0  -X1z  X1y 
 A = ( 0 1 0  X1y  X1z   0  -X1x )
       0 0 1  X1z -X1y  X1x   0 

 p = ( X0x , X0y , X0z , m , omega , phi , kappa )T

       X2x - X1x
 l = ( X2y - X1y )
       X2z - X1z

 */

 if(KooSys1L.size()==KooSys2L.size()&&KooSys1L.size()>2)
 {


   bool recalc=true; // Neuberechnung der Helmerttransformatin duch Ausschlu eines groben Ausreiers

   while(recalc!=false)
   {
   
	     recalc=false;

         //Anzahl der Punkte die in die Rechnung einflieen -> jeder Punkt liefert 3 Gleichungen
         int MSize=3*KooSys1L.size();

		 Matrix A(MSize,7,Empty);
		 Matrix P(MSize,MSize,Einh);
		 Matrix l(MSize,1,Empty);
		 Matrix x;

	 int count=0;
	 int countEnd=1;
	 while(count!=countEnd)
	 {

		     //Testausgabe
		     double o1,p1,k1;
	         //(*this).get_RotWinkel(Rotm,o1,p1,k1);
	         Rot TempRot(Rotm);
	         TempRot.get_RotWinkel(o1,p1,k1);
	         cout<<endl<<endl<<"o: "<<o1/PI*180.0<<"  p: "<<p1/PI*180.0<<"  k: "<<k1/PI*180.0;
	         cout<<endl<<"Transl.:"<<T;
			 cout<<endl<<"m     .:"<<m;
		

		 //Mit den Nherungen die Punktliste KooSys2 in KooSys1 transformieren
		 list<Point> KooSys1toSys2L(KooSys1L);
		  
		 list<Point>::iterator iKooSys1toSys2L =KooSys1toSys2L.begin();
		 while(iKooSys1toSys2L!=KooSys1toSys2L.end())
		 {
		  *iKooSys1toSys2L=iKooSys1toSys2L->Rotation(T,Rotm,m);
		  //cout<<endl<<*iKooSys2toSys1L;
		  ++iKooSys1toSys2L;
		 }
	
         Point schwerpSys1 = (*this).Schwerpunkt(KooSys1toSys2L);
		 Point schwerpSys2 = (*this).Schwerpunkt(KooSys2L);
		 Point SchwDiff=schwerpSys1.Subt(schwerpSys2);

		 //Iteratoren
		 list<Point>::const_iterator iKooSys2L       = KooSys2L.begin(); 
							         iKooSys1toSys2L = KooSys1toSys2L.begin();



			 //fllen der A Matrix
			 int i=0;
			 while(i!=MSize)
			 {
				//Fllen Zeilenweise
				//erste Zeile
				A(i,0)= 1.0;
				A(i,1)= 0.0;
				A(i,2)= 0.0;
				A(i,3)= iKooSys2L->get_X();//+
				A(i,4)= 0.0;
				A(i,5)=-iKooSys2L->get_Z();//-
				A(i,6)= iKooSys2L->get_Y();//+
				//zweite Zeile
				A(i+1,0)= 0.0;
				A(i+1,1)= 1.0;
				A(i+1,2)= 0.0;
				A(i+1,3)= iKooSys2L->get_Y();//+
				A(i+1,4)= iKooSys2L->get_Z();//+
				A(i+1,5)= 0.0;
				A(i+1,6)=-iKooSys2L->get_X();//-
				//dritte Zeile
				A(i+2,0)= 0.0;
				A(i+2,1)= 0.0;
				A(i+2,2)= 1.0;
				A(i+2,3)= iKooSys2L->get_Z();//+
				A(i+2,4)=-iKooSys2L->get_Y();//-
				A(i+2,5)= iKooSys2L->get_X();//+
				A(i+2,6)= 0.0;

				 //fllen der l Matrix
				l(i,0)  =(-1.0)*(iKooSys1toSys2L->get_X()-iKooSys2L->get_X());
				l(i+1,0)=(-1.0)*(iKooSys1toSys2L->get_Y()-iKooSys2L->get_Y());
				l(i+2,0)=(-1.0)*(iKooSys1toSys2L->get_Z()-iKooSys2L->get_Z());

			 ++iKooSys2L;
			 ++iKooSys1toSys2L;
			 i+=3;
			 }
	 	 
	    

		 //A.MatShow();
		 //l.MatShow();
		 //P.MatShow();

		 Matrix N;
		 N=A.MatTrans().MatMult(P).MatMult(A);
		 //N.MatShow();
		 Matrix AT=A.MatTrans();
		 
		 x=N.MatInvert().MatMult(AT).MatMult(P).MatMult(l);
		 x.MatShow();


              // setzen der neuen Transformationsparameter
			 m+=x(3,0);//*0.01;//*0.45
		  	 

			 T.set_X(T.get_X()+x(0,0));//*0.45);//*0.45 //-
			 T.set_Y(T.get_Y()+x(1,0));//*0.45);//*0.45 //-
			 T.set_Z(T.get_Z()+x(2,0));//*0.45);//*0.45 //+

			 

			 double omega,phi,kappa;
			 //(*this).get_RotWinkel(Rotm,omega,phi,kappa);
			 Rot TempRot1(Rotm);
	         TempRot1.get_RotWinkel(omega,phi,kappa);

			 //if( fabs(x(3,0))<0.001 && fabs(x(2,0))<0.1 && fabs(x(1,0))<0.1 && fabs(x(0,0))<0.1)
			 //{
			  omega-=x(4,0);//+//*0.1
			  phi  -=x(5,0);//+//*0.1
			  kappa-=x(6,0);//-//*0.1
			 //}

			 if( fabs(x(0,0))<0.00001 && fabs(x(1,0))<0.00001 && fabs(x(2,0))<0.00001 &&
				 fabs(x(3,0))<0.0000001 && fabs(x(4,0))<0.00000001 && fabs(x(5,0))<0.00000001 && fabs(x(6,0))<0.00000001)
				 --countEnd;

			 Rot R(omega,phi,kappa);
			 Rotm=R.get_Matrix();

			 
			 //fr spezial Falle die nicht wollen
			 // alle daten werden um 20 weiter gedreht
			 // hier nur abbruch der Routiene
			 if(count>100000)
				 return false;

             

	  ++count;
	  ++countEnd;
	  }
      
	  //Testausgabe
		     double o1,p1,k1;
	         //(*this).get_RotWinkel(Rotm,o1,p1,k1);
	         Rot TempRot(Rotm);
	         TempRot.get_RotWinkel(o1,p1,k1);
	         cout<<endl<<endl<<"o: "<<o1/PI*180.0<<"  p: "<<p1/PI*180.0<<"  k: "<<k1/PI*180.0;
	         cout<<endl<<"Transl.:"<<T;
			 cout<<endl<<"m     .:"<<m;

	  cout<<endl<<"Anzahl der Iterationen:"<<count;



		 //grobe Fehler rausschmeien -> Data-Snooping nach Baarda 1968
		 //NVi=vi/mvi
		 //mvi=m0*Wurzel(Qvv) -> in diesem Fall mvi=m0/Wurzel(Pi);
		 //0   < NVi < 2,5 keingrober Fehler
		 //2,5 < NVi < 4,0 grober Fehler mglich
		 //4,0 < NVi       grober Fehler sehr warscheinlich


		 //Berechnung der Verbesserungen
		 Matrix v;
		 v=A.MatMult(x).MatSub(l);
		 
		 cout<<endl<<endl<<"v: ";
		 v.MatShow();


		 //mittler Fehler m0
		 Matrix m0_2; //m0^2*(n-u)
		 m0_2=v.MatTrans().MatMult(P).MatMult(v);
		 double m0 = sqrt( m0_2(0,0)/(MSize-7));
	     
		 cout<<endl<<endl<<"m0: "<<m0;


			 // suchen des Grten Wertes in den Verbesserungen
			 double max=0;
			 int pos=-1;
			 double temp;
			 double qmittel=0;

			 for(int i=0;i!=v.getRow();i++)
			 {
			  temp=fabs(v(i,0))*P(i,i);
			  qmittel+=temp*temp;
			  if( temp > max )
			  {
			   max=temp;
			   pos=i;
			  }
		 
		     }//END for(int i=0;i==v.getRow();i++)


		 // Durchschnittswert der Verbesserungen
		 //Anzahl der enthaltenen Punkte
		 int anzahlinP=0;
		 for(int k=0;k!=P.getRow();k++)
		 {
		  anzahlinP+=static_cast<int>(P(k,k));
		 }

		 qmittel=sqrt( qmittel / anzahlinP );

		 
		 
		 // Endscheidung ob die Helmerttransformation noch mal gerechnet wird mit Ausschlu des "groben Fehlers"
	     double NVi=0.0;

		 if(pos>-1)
		  NVi=fabs(v(pos,0))/m0;

		 if(NVi>3.0)
			 recalc=true;

         double NVeigen=0.0;
		 
		 if(pos>-1)
		  NVeigen=fabs(v(pos,0))/qmittel;
	     
		 if(NVeigen>2.2)
			 recalc=true;

		 if(anzahlinP==9)
			 recalc=false; //fr den Fall das nur noch 4 Punkte enthalten sind

		 if(recalc)
		 {
		      //anpassen der Punktliste -> Punkt aus der Punktliste lschen
			  int pktpos=pos/3;
			  cout<<endl<<"Fehlerpos: "<<pos;
              
              list<Point>::iterator iKooSys1L =KooSys1L.begin();
			  list<Point>::iterator iKooSys2L =KooSys2L.begin();
			
			     int i=0;
				 while(iKooSys1L!=KooSys1L.end())
				 {
					 bool add=false; //kontrolle ob Iterator schon ein weiter gesetz wurde

					   if(pktpos==i)
					   {
						 KooSys1Lreject.push_back(*iKooSys1L);
						 KooSys1L.erase(iKooSys1L++);

						 KooSys2Lreject.push_back(*iKooSys2L);
						 KooSys2L.erase(iKooSys2L++);

						 add=true;
					   }

				   if(!add)
	               {
			        ++iKooSys1L;
				    ++iKooSys2L;
				   }
				   ++i;
				 }

			  //Neuberechnung der Nherung falls die Nherung ber einen Ausreier bestimm wurde
			  if(anzahlinP>9)
			  {
			   list<Point> KooSys1L4,KooSys2L4;

		       Punkte_aus_Liste(4,KooSys1L,KooSys1L4,KooSys2L,KooSys2L4);
		 
		       bool ok = Naeherung_4Punkte(KooSys1L4,KooSys2L4,Rotm,T,m);
		        if(!ok)
		        {cout<<"Fehler in der Näherung";return false;
		        }
			  }
			  
			  
		 }
		 else
		 {
		  // setzen der neuen Transformationsparameter
           			
			 T.set_X(T.get_X()+x(0,0));//-
			 T.set_Y(T.get_Y()+x(1,0));//+
			 T.set_Z(T.get_Z()+x(2,0));//-

	     	 double omega,phi,kappa;
			 //(*this).get_RotWinkel(Rotm,omega,phi,kappa);
			 Rot TempRot(Rotm);
	         TempRot.get_RotWinkel(omega,phi,kappa);
			 omega-=x(4,0);// /2.0;
			 phi  -=x(5,0);// /2.0;
			 kappa-=x(6,0);// kappa-=... /2.0;
			 
			 Rot R(omega,phi,kappa);
			 Rotm=R.get_Matrix();
			 
			 //Ende
			 cout<<endl<<"Ende Helmert...";
			 return true;
		 }

   }//END while(recalc)
 
 }//END if(KooSys1L.size()==KooSys2L.size()&&KooSys1L.size()>2)

 
return false;
}

//#######################################################################################
//Schwerpunkt
Point Transformation::Schwerpunkt(list<Point> PointL)
{
      //Schwerpunktberechnung
	  double sum_x=0,sum_y=0,sum_z=0;
	 
	  list<Point>::const_iterator iPointL = PointL.begin();

	  while(iPointL!=PointL.end())
	  {
	   sum_x+=iPointL->get_X();
	   sum_y+=iPointL->get_Y();
	   sum_z+=iPointL->get_Z();
	   ++iPointL;
	  }
	
	  Point Koo_Schw;
	  Koo_Schw.set_X(sum_x/PointL.size());
	  Koo_Schw.set_Y(sum_y/PointL.size());
	  Koo_Schw.set_Z(sum_z/PointL.size());
	  //END

return Koo_Schw;
}
/*
//#######################################################################################
//ein Vielfaches von einem Winkel reduzieren
double Transformation::clamp(double& wert, double min, double max)
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


//#######################################################################################
bool Transformation::get_RotWinkel(Matrix& MRot,double& Omega,double& Phi,double& Kappa)
{
 	   double r11 =MRot(0,0); 
	   double r21 =MRot(1,0); 
	   double r31 =MRot(2,0); 
	   double r12 =MRot(0,1); 
	   double r22 =MRot(1,1); 
	   double r32 =MRot(2,1); 
	   double r13 =MRot(0,2); 
	   double r23 =MRot(1,2); 
	   double r33 =MRot(2,2); 

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
*/     
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
/*
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
	   if(Rt.get_Matrix().NearEqual(MRot,threshold))
	   {
	    //cout<<"passt";
		   return true;
	   }
	   else
	   {
	    //cout<<"passt nicht!";
		   return false;
	   }

}
*/
//#######################################################################################
bool Transformation::Punkte_aus_Liste(int Anzahl,list<Point> &KooSys1OrgL, list<Point> &KooSys1OutL, list<Point> &KooSys2OrgL, list<Point> &KooSys2OutL)
{
 if(KooSys1OrgL.size()==KooSys2OrgL.size() && static_cast<int>(KooSys1OrgL.size())>=abs(Anzahl))
 {

	 int Punkte=abs(Anzahl);

	 vector<int> Zufallsliste(Punkte,-1);

	 int j=0;
	 while(j!=Punkte)
	 {
	    
		//Zufallszahl (ohne doppeltes Vorkommen)
		int Zufall=-1;
		bool doppelt=false;
		while(doppelt!=true)
		{
			 doppelt=true;
			 Zufall = rand()%(KooSys1OrgL.size());//
			 
			 for(size_t i=0;i!=Zufallsliste.size();i++)
			 {
			  if(Zufallsliste[i]==Zufall)
				 doppelt=false;
			  else
			  {
			   if(i+1==Zufallsliste.size())
				Zufallsliste[j]=Zufall; 
			  }
			 }
		}

		//Iterator
		list<Point>::const_iterator iKooSys1OrgL =KooSys1OrgL.begin(); 
		list<Point>::const_iterator iKooSys2OrgL =KooSys2OrgL.begin(); 
		
		list<Point>::iterator iKooSys1OutL =KooSys1OutL.begin(); 
		list<Point>::iterator iKooSys2OutL =KooSys2OutL.begin();
		
		    
		int i=0;
		while(iKooSys1OrgL!=KooSys1OrgL.end())
		{
		 //bool add=false; //kontrolle ob Iterator schon ein weiter gesetz wurde

			   if(Zufall==i)
			   {
				KooSys1OutL.push_back(*iKooSys1OrgL);
				KooSys2OutL.push_back(*iKooSys2OrgL);
			   }

		 ++i;
		 ++iKooSys1OrgL;
		 ++iKooSys2OrgL; 
		}

	  ++j;
	 }
  //Kontrolle ob alle in einer Ebene liegen (fehlt noch!!)


 }		
 else return false;

return true;
}
