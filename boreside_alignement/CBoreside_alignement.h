#ifndef CBORESIDE_ALIGNEMENT_H_
#define CBORESIDE_ALIGNEMENT_H_

#include <iostream>
#include <string>
#include <list>

#include "..//Basics//point.h"
#include "..//Basics//point_nr.h"


using namespace std;

class CBoreside_alignement
{
public:
	//CBoreside_alignement(string &KooDat1,string &KooDat2);
	CBoreside_alignement();
	virtual ~CBoreside_alignement();
	
	bool calc_3D_Helmert_transformation(string &KooDat1,string &KooDat2);
	
	bool calc_boreside_transformation(string &KooDat1,string &KooDat2);
		
	
private:
//internal funktions
    bool read_KooDat(string &KooDat1,list<CPoint_Nr> &KooList);
    bool merge_list(list<CPoint_Nr> &KooList1,list<CPoint_Nr> &KooList2);
    bool convert_list(list<CPoint_Nr> &InputList,list<Point> &OutputList);
    
    void KooL_anzeigen(list<CPoint_Nr> &KooList);
    void KooL_anzeigen(list<Point> &KooList);
    

//variables
    list<CPoint_Nr> m_KooList1;
    list<CPoint_Nr> m_KooList2;
    
//controll
	bool m_is_ok;
	string m_error_string;
};

#endif /*CBORESIDE_ALIGNEMENT_H_*/
