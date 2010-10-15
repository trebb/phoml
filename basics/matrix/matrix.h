#ifndef __MATRIX_h
#define __MATRIX_h

#include <iostream>
#include <cassert>
#include <iomanip> //for setfill() and setw()
using namespace std;

enum eMatDef { Null , Einh , Empty };

struct structMat
{
 int m_zeilen;
 int m_spalten;
 double **m_matrix; 
};

class Matrix
{
public:
    
	Matrix();
	Matrix( int zeilen , int spalten , eMatDef MatDef);
	Matrix(const Matrix& A );
	~Matrix();

	Matrix& operator= ( const Matrix &A);

	bool operator==( const Matrix& T) const;
	bool NearEqual( const Matrix& B, double &threshold) const;
	
	double a;
    double& operator() (int zeile,int spalte);
    const double& operator() (int zeile,int spalte) const;

    //Matrix operator+( Matrix &A ) { return (*this).MatAdd(A);  }
	//Matrix operator-( Matrix &A ) { return (*this).MatSub(A);  }
	//Matrix operator!()            { return (*this).MatTrans();}
    //Matrix operator*( Matrix &A ) { return (*this).MatMult(A); }
	//Matrix operator*( double &d ) { return (*this).MatMultSkalar(d); }
	//Matrix operator^(int i)       { return (*this).MatInvert();}
    //double operator&()            { return (*this).MatDet();}
    //Matrix operator~()            { return (*this).MatEigVek();}
	
    const int &getCol() const {return mat->m_spalten;}
    const int &getRow() const {return mat->m_zeilen; }
 
	const bool &isEmpty() const {return isPEmpty;}	
	
    void create(int zeilen,int spalten, eMatDef MatDef);

	void del();
    
    void fill(eMatDef MatDef);

public:
	Matrix MatCopy() const;	                         // Matrix Kopieren (tiefe Kopie)
    Matrix MatAdd(const Matrix &A );                      // zwei Matrizen addieren
	Matrix MatSub(const Matrix &A );                      // zwei Matrizen subtraieren
    Matrix MatTrans() const;                               // Matrix Transponieren 
    Matrix MatMult(const Matrix &A );                     // Matizen multiplizieren
    Matrix MatMultSkalar(const double &b );               // Matrix multipliziert mit Skalar
    Matrix MatInvert();                              // Matrix invertieren
    double MatDet();                                 // Determinanten-Berechnung
	Matrix MatEigVek();                              // EigenVektoren-Berechnung (pro Spalte ein Eigenvektor) (Eigenvektoren sind aufsteigend sortiert )
    Matrix MatEigVek( Matrix &Eingenwerte );         // EigenVektoren-Berechnung (pro Spalte ein Eigenvektor) mit ausgabe der Eigenwerte
    void MatShow();                                  //Anzeigen der Matrix auf dem Bildschrim 

private:
	//private Hilfsfunktion -> auf keinen Fall public setzten und außerhalb der Klasse verwenden!!
    void create(int &zeilen,int &spalten);
    
    //interne Rechenfunktionen für Matrixinveertierung
    int MatLu( Matrix &A, Matrix &D);
    Matrix& MatRuecksub(Matrix &A,Matrix &B,Matrix &C,Matrix &D,int &x);
    
    //Grundstruktur
	structMat *mat;
	bool isPEmpty;      //Gibt an ob Pointer auf structMat gesetzt wurde	
};


//help funktions

ostream& operator<<(ostream& s,const Matrix& A);


#endif //Matrix_h
