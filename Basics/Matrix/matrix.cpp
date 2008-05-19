#include "matrix.h"

#include <cstdlib>
#include <cmath>

double SIGN(double &a,double &b){ return ( (b)<0 ? -fabs(a) : fabs(a) ); }

//#############################################################################
// 1. Konstruktur (Referenz auf ein Matrix-Feld)
Matrix::Matrix()
{ 
  isPEmpty = true;
  //cout<<endl<<"Reference Konstruktor";
};
//#############################################################################
// 2. Konstruktor (vollwertig)
Matrix::Matrix( int zeilen , int spalten , eMatDef MatDef) 
{
 mat = new structMat;
 create(zeilen,spalten);
 fill(MatDef);
 //cout<<endl<<"erw. Konstruktor";
}
//#############################################################################
// 2. "Kopier"Konstruktor (Kopiert nicht!! setzt nur Referenzen!)
// zum Kopieren Bitte "MatrixFunktionen::MatCopy" verwenden!!!
Matrix::Matrix(const Matrix &A )
{
 (*this)=A;	
 /*
 (*this).mat=A.mat;
 isPEmpty=A.isEmpty();
 A.isPEmpty=true;
 A.~Matrix();
 */  
 //cout<<endl<<"CopyKonstruktor";
}
//#############################################################################
//DeKonstruktor (löscht alle noch verbleibenden Matrix-Felder)
Matrix::~Matrix()
{
 del();
 //cout<<endl<<"DeKonstruktor ";
}
//#############################################################################
//= Operator
Matrix& Matrix::operator= (const Matrix &A)
{
 if(!isPEmpty ) 
  (*this).del();

  (*this).create(A.getRow() , A.getCol() , Empty );

  int j=0;
    while( j != (*this).getRow() )
    {
	 int i=0;
     while( i != (*this).getCol() )
	 {
      (*this)(j,i)=A(j,i);
	  ++i;
     }
	 ++j;
    }
 
/*
	 mat=A.mat;
	 isPEmpty=A.isEmpty();
	 //A.isPEmpty=true;
	 A.~Matrix();
	 //cout<<endl<<"=operator Ende";
*/

 return (*this);
}
//#############################################################################
bool Matrix::operator==( const Matrix& B) const
{
 assert( !(*this).isEmpty() );
 assert( !      B.isEmpty() );
 assert( (*this).getRow()  ==  B.getRow()  ); 
 assert( (*this).getCol()  ==  B.getCol()  );

 int kontrol=0;

 int j=0;
    while( j != B.getRow() )
    {
	 int i=0;
     while( i != B.getCol() )
	 {
	  if((*this)(j,i)!=B(j,i))
	    ++kontrol;
	  
	  ++i;
     }
	 ++j;
    }
 if(kontrol)
	 return false;

return true;
}
//#############################################################################
//Abgleichen ob 2 Matrizen "gleich" sind
bool Matrix::NearEqual( const Matrix& B, double &threshold) const
{
 assert( !(*this).isEmpty() );
 assert( !      B.isEmpty() );
 assert( (*this).getRow()  ==  B.getRow()  ); 
 assert( (*this).getCol()  ==  B.getCol()  );

 //double threshold = 9.99999e-8;

 int kontrol=0;

 int j=0;
    while( j != B.getRow() )
    {
	 int i=0;
     while( i != B.getCol() )
	 {
	  double diff=fabs((*this)(j,i)-B(j,i));
      if(diff>threshold)
	    ++kontrol;
	  
	  ++i;
     }
	 ++j;
    }
 if(kontrol)
	 return false;

return true;
}
//#############################################################################
// Matrix Zugriff über ()
double& Matrix::operator() (int zeile,int spalte)
{
 assert( zeile < mat->m_zeilen && spalte < mat->m_spalten);
 return mat->m_matrix[zeile][spalte];
} 
//#############################################################################
// Matrix Zugriff über ()
const double& Matrix::operator() (int zeile,int spalte) const
{  
 assert(zeile<mat->m_zeilen && spalte<mat->m_spalten);
 return mat->m_matrix[zeile][spalte];
}
//#############################################################################
//gleichwertig mit Konstruktor 2
void Matrix::create(int zeilen,int spalten, eMatDef MatDef)
{
 (*this).del();
 mat = new structMat;
 create(zeilen,spalten);
 fill(MatDef);
}
//#############################################################################
//Speicherplatz für Matrix-Feld beschaffen
void Matrix::create(int &zeilen,int &spalten)
{
 assert(zeilen>0);
 assert(spalten>0);
 
 if(zeilen>0)
 if(spalten>0)
 {	
	 mat->m_zeilen=zeilen;
	 mat->m_spalten=spalten;
		
	 mat->m_matrix = new double*[mat->m_zeilen];
	 int s=0;
	 while(s!=mat->m_zeilen)
	 {
	  mat->m_matrix[s] = new double[mat->m_spalten];
	  ++s; 
	 }
	 isPEmpty=false;
 }
  
 assert(*mat->m_matrix );//**mat->m_matrix &&
}
//#############################################################################
//Matrix füllen
void Matrix::fill(eMatDef MatDef)
{
 //Erstellen einer EinheitsMatrix (HauptDiagonale = 1 ,Rest = 0)
 if(MatDef==Einh)
 {
   int j=0;
   while(j!=mat->m_zeilen)
   {
	int i=0;
	while(i!=mat->m_spalten)
    {
       if(j==i)
		mat->m_matrix[j][i]=1;
	   else
        mat->m_matrix[j][i]=0;
	 ++i;
    }
	++j;
   }
   
 }
 //Marix mit Nullenfllen
 if(MatDef==Null)
 {
   int j=0;
   while(j!=mat->m_zeilen)
   {
	int i=0;
    while(i!=mat->m_spalten)
    {
     mat->m_matrix[j][i]=0;
	 ++i;
    }
	++j;
   }   
  
 }
 //Matrix leer lassen
 //if(MatDef==Empty)

}
//#############################################################################
//Matrix-Feld löschen
void Matrix::del()
{
 if(isPEmpty==false)
 {
	  int i=0;
	  while(i!=mat->m_zeilen)
	  {
	   delete [] mat->m_matrix[i];
	   ++i;
	  }
	  delete [] mat->m_matrix;
      
	  isPEmpty=true;
	  delete mat;
	  mat=NULL;
	  //cout<<endl<<"Matrix gelscht";
 }

}
//#############################################################################
// Matrix Kopieren (tiefe Kopie)
Matrix Matrix::MatCopy() const
{
    assert( !(*this).isEmpty() );
  
	Matrix Z( (*this).getRow() , (*this).getCol() , Empty );
    
	int j=0;
    while( j != Z.getRow() )
    {
	 int i=0;
     while( i != Z.getCol() )
	 {
      Z(j,i)=(*this)(j,i);
	  ++i;
     }
	 ++j;
    }
   return Z;
}
//#############################################################################
// zwei Matrizen addieren
Matrix Matrix::MatAdd(const Matrix &B )
{
   assert(!(*this).isEmpty() && !B.isEmpty() );
   assert( (*this).getRow()  ==  B.getRow()  ); 
   assert( (*this).getCol()  ==  B.getCol()  );
   
    Matrix Z( (*this).getRow() , (*this).getCol() , Empty );
    	
    int j=0;
    while( j != Z.getRow() )
    {
	 int i=0;
     while( i != Z.getCol() )
	 {
      Z(j,i)=(*this)(j,i)+B(j,i);
	  ++i;
     }
	 ++j;
    }
   return Z;
}
//#############################################################################
Matrix Matrix::MatSub(const Matrix &B )
{   // zwei Matrizen subtraieren
   assert(!(*this).isEmpty() && !B.isEmpty() );
   assert( (*this).getRow()  ==  B.getRow()  ); 
   assert( (*this).getCol()  ==  B.getCol()  );
   
    Matrix Z( (*this).getRow() , (*this).getCol() , Empty );
    	
    int j=0;
    while( j != Z.getRow() )
    {
	 int i=0;
     while( i != Z.getCol() )
	 {
      Z(j,i)=(*this)(j,i)-B(j,i);
	  ++i;
     }
	 ++j;
    }
   return Z;
}
//#############################################################################
// Matrix Transponieren 
Matrix Matrix::MatTrans() const
{
  assert( !(*this).isEmpty() );

  Matrix Z( (*this).getCol() , (*this).getRow() ,  Empty );
  
  int j=0;
    while( j != (*this).getRow() )
    {
	 int i=0;
     while( i != (*this).getCol() )
	 {
      Z(i,j)=(*this)(j,i);
	  ++i;
     }
	 ++j;
    }
  return Z;
} 
//#############################################################################
// Matizen multiplizieren
Matrix Matrix::MatMult(const Matrix &B )
{
   assert(!(*this).isEmpty() && !B.isEmpty() );
   assert( (*this).getCol()  ==  B.getRow()  );
     
   Matrix Z( (*this).getRow() , B.getCol() , Empty );
   int i=0,j=0,k=0;

    j=0;
    while( j != Z.getRow() )
    {
		 i=0;
		 while( i != Z.getCol() )
		 {
			 Z(j,i)=0.0;

			  k=0;
			  while( k != (*this).getCol() )
			  {
			   Z(j,i)+=(*this)(j,k)*B(k,i);
			   ++k;
			  }
		  ++i;
		 }
	 ++j;
    }
  return Z; 
} 
//#############################################################################
// Matrix multipliziert mit Skalar
Matrix Matrix::MatMultSkalar(const double &b )
{
   assert(!(*this).isEmpty() );
      
    Matrix Z( (*this).getRow() , (*this).getCol() , Empty );
    	
    int j=0;
    while( j != Z.getRow() )
    {
	 int i=0;
     while( i != Z.getCol() )
	 {
      Z(j,i)=(*this)(j,i)*b;
	  ++i;
     }
	 ++j;
    }
   return Z;
}
//#############################################################################
//interne Funktion zu Matrix invertieren
int Matrix::MatLu( Matrix &A, Matrix &D)
{
 	int n=A.getCol();
 
	int	i=0;
	while( i != n )
	{
	 D(i,0)=static_cast<double>(i);
	 ++i;
	}
	
	int r=0, max, tmp;
	double	temp, temp1;

	int m=0;
	while( m != n )
	{
		 // Pivoelement suchen ---
		 max=m;
		 temp=0.0;
		 i=m;
		 while( i != n)
		 {
		  temp1 = fabs(  A( static_cast<int>(D(i,0)) , m )  );
		  if (temp1 > temp)
		  {
		   temp = temp1;
		   max = i;
		  }
		  ++i;
		 }

		 //Zeilentausch
		 if(m != max)
		 {
		  r++;
		  tmp =( static_cast<int>(D(m,0)) );
		  D(m,0)=D(max,0);
		  D(max,0)=tmp;
		 }

		 //singulr!!
		 if( A( static_cast<int>(D(m,0)) , m )==0.0 )
			return(-1);

	     //for(i=m+1;i<n;i++)
		 int j;
		 i=m+1;
		 while( i != n )
		 {
			 A( static_cast<int>(D(i,0)) ,m) = A( static_cast<int>(D(i,0)) ,m) / A( static_cast<int>(D(m,0)) ,m);
			  j=m+1;
			  //for(j=m+1; j<n; j++)
			  while( j != n )
			  {
			   A( static_cast<int>(D(i,0)) ,j)-= A( static_cast<int>(D(i,0)) ,m) * A( static_cast<int>(D(m,0)) ,j);
			   ++j;
			  }
		  ++i;
		 }
	 ++m;
	}
return r;
}
//#############################################################################
//interne Funktion zu Matrix invertieren
Matrix& Matrix::MatRuecksub(Matrix &A,Matrix &B,Matrix &C,Matrix &D,int &x)
{
	int n=A.getCol();
    
	int t=0;
	int i;
	while( t != n)
	{
		i=t+1;
		while( i != n)
		{
		 B( static_cast<int>(D(i,0)) ,0)-= A( static_cast<int>(D(i,0)) ,t) * B( static_cast<int>(D(t,0)) ,0);
		 ++i;
        }
	 ++t;
	}
    C(n-1,x) = B( static_cast<int>(D(n-1,0)) ,0  ) / A( static_cast<int>(D(n-1,0)) ,n-1);

	double	sum;

	t=n-2;
	while( t != -1 )
	{
	     sum = 0.0;		 
		 i=t+1;
		 while( i != n )
		 {
          sum+=A( static_cast<int>(D(t,0)) ,i) * C(i,x);
		  ++i;
		 }
         C(t,x) = ( B( static_cast<int>(D(t,0)) ,0) - sum ) / A( static_cast<int>(D(t,0)) ,t);
	 --t;
	}
return C;
}
//#############################################################################
//Matrix invertieren
Matrix Matrix::MatInvert() 
{
 	Matrix A = (*this).MatCopy();
	int n = A.getCol();

	Matrix B(n,1,Empty);
	Matrix C(n,n,Empty);
	Matrix D(n,1,Empty);

	//Test singulre Matrix
	if(MatLu(A,D)==-1)
	{	assert( "singulre Matrix" );
	    cout<<endl<<"singulre Matrix! Programmabbruch";
	    exit(1);
	}
	int i=0;
	while( i != n )
	{
	 B.fill(Null);
	 B(i,0)=1.0;
	 MatRuecksub(A,B,C,D,i);
	 ++i;
	}

 return C; 
}
//#############################################################################
//Determinante einer Matrix berechnen
double Matrix::MatDet()
{
	double result;
    double vorz[2] = {1.0, -1.0};

	int n = (*this).getRow();
	Matrix A = (*this).MatCopy();
	Matrix P( n, 1, Empty);
 
	int i = MatLu(A, P);
	if(i==-1)
	{//singulre Matrix
	 result = 0.0;
	}
	else
	{
	 result = 1.0;
	  int j=0;
	  while(j != n)
	  {
       result *= A( static_cast<int>(P(j,0)) ,j);
	   ++j;
	  }
	 result *= vorz[i%2];
	}
 return result;
}
//#############################################################################
// EigenVektoren-Berechnung (pro Spalte ein Eigenvektor)
Matrix Matrix::MatEigVek()
{
 Matrix Eigenwerte;
 Matrix A=(*this).MatEigVek(Eigenwerte);
 return A;
}
//#############################################################################
// EigenVektoren-Berechnung (pro Spalte ein Eigenvektor)
Matrix Matrix::MatEigVek( Matrix &Eigenwerte )
{
 Matrix A = (*this).MatCopy();
 Matrix d(A.getCol(),1,Empty);
 Matrix e(A.getCol(),1,Empty);
 int n = A.getCol()-1;
 
//#########
//Teil 1 
 
 int l,k,j,i,m,iter;
 double scale,hh,h,g,f,s,r,p,dd,c,b;

 for(i=n;i>=1;i--)
 {
   l=i-1;
   h=scale=0.0;
   
   if(l>0)
   {
		for(k=0;k<=l;k++)
		{ scale += fabs(A(i,k));	
		}//END for(k=1;k<=1;k++)

		if(scale==0.0)
		{ e(i,0)=A(i,l);
		}
		else
		{
			 for(k=0;k<=l;k++)
			 { A(i,k) /= scale;
			   h += A(i,k)*A(i,k);
			 }

			 f=A(i,l);
			 g = (f >= 0.0 ? -sqrt(h) : sqrt(h));
			 e(i,0)=scale*g;
			 h -= f*g;
			 A(i,l)=f-g;
			 f=0.0;

			 for(j=0;j<=l;j++)
			 { A(j,i)=A(i,j)/h;
			   g=0.0;

				  for(k=0;k<=j;k++)
				  { g += A(j,k)*A(i,k);
				  }
				  for(k=j+1;k<=l;k++)
				  { g += A(k,j)*A(i,k);
				  }
			  e(j,0)=g/h;
			  f += e(j,0)*A(i,j);
			 }//END for(j=1;j<=l;j++)

			 hh=f/(h+h);

			 for(j=0;j<=l;j++)
			 { f=A(i,j);
			   e(j,0)=g=e(j,0)-hh*f;
			  
			   for(k=0;k<=j;k++)
			   { A(j,k) -= (f*e(k,0)+g*A(i,k));
			   }
			 }
		}   
   }
   else
   { e(i,0)=A(i,l);
   }
  d(i,0)=h;
 }//END for(i=n;i>=2;i--)

 d(0,0)=0.0;
 e(0,0)=0.0;

 for(i=0;i<=n;i++)
 { l=i-1;

   if( d(i,0) )
   {
	   for(j=0;j<=l;j++)
	   { g=0.0;
			for(k=0;k<=l;k++)
			{ g += A(i,k)*A(k,j);
			}
			for(k=0;k<=l;k++)
			{ A(k,j) -= g*A(k,i);
			}
	   }
   }
  
  d(i,0)=A(i,i);
  A(i,i)=1.0;
  for(j=0;j<=l;j++)
  { A(j,i)=A(i,j)=0.0;
  }
 }

 //########
 //Teil 2

 for(i=1;i<=n;i++)
 { e(i-1,0)=e(i,0);
 }
 e(n,0)=0.0;
 
 for(l=0;l<=n;l++)
 {	iter=0;
	do
	{
	   for(m=l;m<=n-1;m++)
	   { dd=fabs(d(m,0))+fabs(d(m+1,0));
		 
	     if((double)(fabs(e(m,0))+dd) == dd)
		 { break;
		 }
	   }

	   if(m!=l)
	   {
	    if(iter++ == 30) 
		{ cerr<<"Eigenwertberechnung unsicher -> ber 30 Iterationen!!!";   
		}
		
        g=( d(l+1,0) - d(l,0) ) / (2.0*e(l,0));
        r=sqrt((g*g)+1.0); 
		g= d(m,0) - d(l,0) + e(l,0) / (g+SIGN(r,g));
        s=c=1.0;
        p=0.0;

		for(i=m-1;i>=l;i--)
		{ f=s*e(i,0);
		  b=c*e(i,0);
          //##################################################
		  //B## alt ##
		   if(fabs(f) >= fabs(g))
		   { c=g/f;
			 r=sqrt((c*c)+1.0);
			 e(i+1,0)=f*r;
			 c *= (s=1.0/r);
		   }
		   else
		   { s=f/g;
			 r=sqrt((s*s)+1.0);
			 e(i+1,0)=g*r;
			 s *= (c=1.0/r);
		   }
		 //E## alt ##
		 /*//B## neu ###
    	    e(i+1,0)=(r=sqrt((f*f)+(g*g)));;
			
			if (r == 0.0) 
			{ d(i+1,0) -= p;
			  e(m,0)=0.0;
			  break;
			}
			s=f/r;
			c=g/r;
		 *///E## neu ### 
		//################################################################
		   g=d(i+1,0)-p;
		   r=(d(i,0)-g)*s+2.0*c*b;
		   p=s*r;
		   d(i+1,0)=g+p;
		   g=c*r-b;

		   for(k=0;k<=n;k++)
		   { f=A(k,i+1);
             A(k,i+1) =s*A(k,i) +c*f;
             A(k,i)   =c*A(k,i) -s*f;
		   }
		}
       //E## neu ###
       //if (r == 0.0 && i >= l) continue;
       d(l,0) -= p;
	   e(l,0)=g;
	   e(m,0)=0.0;
	   }
	}
	while(m != l);
 }
//########
//Teil 3  (nach Greöße sortieren)
 
 i=0;
 while(i!=(n))
 {
  k=i;
  p=d(i,0);
   
   for(j=i+1;j<=n;j++) 
   {
	if( d(j,0) <=p )
	{ k=j;
	  p=d(j,0);
	}
   }
   if( k!=i )
   { d(k,0)=d(i,0);
	 d(i,0)=p;

     for(j=0;j<=n;j++)	  		  
	 { p=A(j,i);
	   A(j,i)=A(j,k);
	   A(j,k)=p;		   
	 }		
   }    
   
  ++i;
 }

 Eigenwerte=d;
 return A;
}
//#############################################################################
//#############################################################################
//Anzeigen der Matrix auf dem Bildschrim 
void Matrix::MatShow()
{
  assert( !(*this).isEmpty() );

  if(!(*this).isEmpty())
  {
  cout.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
  cout.setf(ios::right, ios::adjustfield);
  cout.precision(5);

      cout<<endl;
	  for(int i=0;i<(*this).getRow();++i)
	  {
	   cout<<endl;
	   for(int j=0;j<(*this).getCol();++j)
		cout<<(*this)(i,j)<<" ";  
	  }
  } 
}

ostream& operator<<(ostream& s,const Matrix& A)
{
  assert( !A.isEmpty() );

  if(!A.isEmpty())
  {
   int precision=5;       //Nachkommastellen   
   int vorkommastellen=2; //Minus zählt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

      s<<endl;
	  for(int i=0;i<A.getRow();++i)
	  {
	   s<<endl;
	   for(int j=0;j<A.getCol();++j)
		s<<setfill(' ')<<setw(precision+vorkommastellen+1)<<A(i,j)<<" ";  
	  }
  } 
  return s;
}
