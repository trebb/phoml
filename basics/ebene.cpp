#include "ebene.h"

#include <fstream>
#include <sstream>

#include "matrix//matrix.h"


Ebene::Ebene()
{
 (*this).m_n = Point(0.0,0.0,1.0);
 (*this).m_p = 0.0;
}

Ebene::Ebene(Point N,double D)
{
 m_n=N.Norm();
 m_p=D;
}

Ebene::Ebene(double nx,double ny,double nz,double D)
{
 (*this).m_n = Point(nx,ny,nz).Norm();
 (*this).m_p = D;
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
	  
	  //test
	  //double d;
	  
	  m_n=KooEv;
	  //m_p=KooEv.Mult(Koo_Schw)*(-1.0);
	  m_p=KooEv.Mult(Koo_Schw)*(1.0);//change problems

	}
}

Ebene::Ebene(const Ebene& E )
{
	(*this)=E;
}

Ebene::~Ebene()
{
}

Ebene& Ebene::operator= (const Ebene &E)
{
	 (*this).m_n=E.m_n;
	 (*this).m_p=E.m_p;
  return (*this);
}

bool Ebene::operator== (const Ebene &E)
{
	return ((*this).m_n==E.get_N() && (*this).m_p==E.get_D());
}

Point Ebene::get_N() const 
{
 return m_n; 
}
    
double Ebene::get_D() const
{ 
 return m_p; 
}

double Ebene::Abstand(const Point &P)
{
 return m_n.Mult(P)-m_p;
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
 //Point P=G.get_O().Add( 
//	            G.get_R().MultS(
//	                            ( (*this).get_D()-(*this).get_N().Mult(G.get_O()) ) /
//	                            ( (*this).get_N().Mult(G.get_R())                )
//							   )
//			         );
 //pimp 11.05.2009
 Point GO = G.get_O();
 Point GR = G.get_R();
 
 Point P=GO.Add( 
 	            GR.MultS(
 	                            ( (*this).m_p-(*this).m_n.Mult(GO) ) /
 	                            ( (*this).m_n.Mult(GR)                )
 							   )
 			         );
 

return P;
}

Point Ebene::LotFussP       (Point &P)
{
 Gerade G(P,P.Add((*this).m_n));

 Point PL;
 PL = (*this).Durchstoss(G);

 return PL;
}

Ebene Ebene::Rotation(Point& X0, Matrix& R)
{
 //steps for point generate
 Point Px_d(0.0,10.0,10.0);
 Point Py_d(10.0,0.0,10.0);
 Point Pz_d(10.0,10.0,0.0);
 Point Px(10000.0,10000.0,10000.0),Py(10000.0,10000.0,10000.0),Pz(10000.0,10000.0,10000.0);

 //point generate
 std::list<Point> pl;
 int c=0;
 while(c!=100)
 {
  Px = Px.Add(Px_d);
  Py = Py.Add(Py_d);
  Pz = Pz.Add(Pz_d);

  //add to the point vector
  pl.push_back(Px);
  pl.push_back(Py);
  pl.push_back(Pz);

  pl.push_back(Px.MultS(-1.0));
  pl.push_back(Py.MultS(-1.0));
  pl.push_back(Pz.MultS(-1.0));

  ++c;
 }

 //transform the points on to the plain

 std::list<Point>::iterator ipl = pl.begin();
 while(ipl!=pl.end())
 {
  *ipl=(*this).LotFussP(*ipl).Rotation(X0,R);
  ++ipl;
 }

 //calc the average plane
 Ebene E(pl);

  return E;
}

Ebene Ebene::RotationRueck(Point& X0, Matrix& R)
{
	 //steps for point generate
	 Point Px_d(0.0,10.0,10.0);
	 Point Py_d(10.0,0.0,10.0);
	 Point Pz_d(10.0,10.0,0.0);
	 Point Px(10000.0,10000.0,10000.0),Py(10000.0,10000.0,10000.0),Pz(10000.0,10000.0,10000.0);

	 //point generate
	 std::list<Point> pl;
	 int c=0;
	 while(c!=10)
	 {
	  Px = Px.Add(Px_d);
	  Py = Py.Add(Py_d);
	  Pz = Pz.Add(Pz_d);

	  //add to the point vector (+ and - values)
	  pl.push_back(Px);
	  pl.push_back(Py);
	  pl.push_back(Pz);

	  pl.push_back(Px.MultS(-1.0));
	  pl.push_back(Py.MultS(-1.0));
	  pl.push_back(Pz.MultS(-1.0));

	  ++c;
	 }

	 //transform the points on to the plain and rotate into the new coordinate system
	 std::list<Point>::iterator ipl = pl.begin();
	 while(ipl!=pl.end())
	 {
		 *ipl=(*this).LotFussP(*ipl).RotationRueck(X0,R);
		 ++ipl;
	 }

	 //calc the average plane
	 Ebene E(pl);
     //cout<<endl<<E;
	 return E;
}

bool Ebene::write(std::string &filename)
{
	ofstream SET_TXT(filename.c_str(),ios_base::out);  
		 
	 //SET_TXT.open(datname); 
	 if(!SET_TXT) { return false; }
	 else
	 {  
		SET_TXT.precision(10);
		SET_TXT.setf(ios::left,ios::showpoint);
		SET_TXT.setf(ios::showbase);
		
		SET_TXT<<std::endl<<"# comment:";
		SET_TXT<<std::endl<<"[PLANE]";
		SET_TXT<<std::endl<<""				<<(*this).m_n.get_X();
		SET_TXT<<std::endl<<""				<<(*this).m_n.get_Y();
		SET_TXT<<std::endl<<""				<<(*this).m_n.get_Z();
		SET_TXT<<std::endl<<""				<<(*this).m_p;
		
	  SET_TXT.close();
	  SET_TXT.clear();
	 }
		
	 return true;
}

bool Ebene::read(std::string &filename)
{
	std::ifstream SET_TXT;  
	SET_TXT.open(filename.c_str(),ios_base::in); 
	 if(!SET_TXT) { return false; }
	
	 std::string hilf;
	 
	 //####line offset of the input file
	 //int lineoffset=m_start_line;
	 //int count=0;
	 //while(count++!=lineoffset)
	 //	 getline(SET_TXT,hilf);
	 //####
	 
	 
	 double nx=0,ny=0,nz=0,d=0;
	 
	 int line=0;
	 int j=0;
	  while(getline(SET_TXT,hilf))
	  {					
		  if(hilf.length()>0 )
		  if(hilf.at(j)!='#' )
		  if(hilf.at(j)!='/' && hilf.at(j+1)!='/')
		  if(hilf.at(j)!='[')
		  {
	 				  //####
	 				  //ersetzen der ; durch " "
	 				  //std::string search((*this).m_separator);
	 				  //std::string replace(" ");
	 				
	 				  //size_t pos = hilf.find(search);
	 				  //while(pos!=std::string::npos)
	 				  //{
	 			     //	hilf.replace(hilf.find(search),1,replace);	
	 			   	  //  pos = hilf.find(search,pos+replace.length());
	 				  //}
	 				  //#####
	 				  
	 			 std::stringstream stream; stream<<hilf.c_str();
	 			 if(line==0)
	 			    stream>>nx;
	 			 if(line==1)
	 			    stream>>ny;
	 			 if(line==2)
	 			   stream>>nz;
	 			 if(line==3)
	 			   stream>>d;
	 	 ++line;			 
	 	}
	  		
	  }
	  SET_TXT.close();
	  SET_TXT.clear();
   
	  m_n.set_X(nx);
	  m_n.set_Y(ny);
	  m_n.set_Z(nz);
	  m_p=d;
	  
 return true;
}

