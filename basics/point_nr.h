#ifndef __POINT_NR_H_
#define __POINT_NR_H_

#include "point.h"



class PointNr : public Point
{
private:
   int m_PktNr;
   
public:
	PointNr();
	PointNr(int pkt,double x,double y,double z);
	PointNr(int pkt,Point P);
	virtual ~PointNr();
	
	PointNr& operator= (const PointNr &P);
	PointNr& operator= (const Point &P);
	
	bool operator< (PointNr &P);
	bool operator== (PointNr &P);
	bool operator== (int pkt_nr);

	// Umwandlung "CPoint_nR  >>-->  Point"
    operator Point () const;
      
   int  get_PktNr() const;
   void set_PktNr(int pkt_nr);


};

inline ostream& operator<<(ostream& s,PointNr &A)
{
   int precision=5;       //Nachkommastellen   
   int vorkommastellen=8; //Minus zhlt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

   s<<setfill(' ')<<setw(precision+1)
	<<A.get_PktNr()
    <<" ("
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<A.get_X()
	<<","
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<A.get_Y()
	<<","
	<<setfill(' ')<<setw(precision+vorkommastellen+1)
	<<A.get_Z()
	<<") ";

return s;
};

#endif /*CPOINT_NR_H_*/
