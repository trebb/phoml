#ifndef __POINT_NR_H_
#define __POINT_NR_H_

#include "point.h"



class Point_nr : public Point
{
private:
   int m_PktNr;
   
public:
	Point_nr();
	Point_nr(int pkt,double x,double y,double z);
	Point_nr(int pkt,double x,double y,double z,double dx,double dy,double dz);
	Point_nr(int pkt,Point P);
	virtual ~Point_nr();
	
	Point_nr& operator= (const Point_nr &P);
	Point_nr& operator= (const Point &P);
	
	bool operator< (Point_nr &P);
	bool operator== (Point_nr &P);
	bool operator== (int pkt_nr);

	// Umwandlung "CPoint_nR  >>-->  Point"
    operator Point () const;
      
   int  get_PktNr() const;
   void set_PktNr(int pkt_nr);


};

ostream& operator<<(ostream& s,const Point_nr &A);
istream& operator>>(istream& s,Point_nr &A);

#endif /*CPOINT_NR_H_*/
