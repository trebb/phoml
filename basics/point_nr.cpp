#include "point_nr.h"



Point_nr::Point_nr()
{
}

Point_nr::Point_nr(int pkt,double x,double y,double z):Point(x,y,z),m_PktNr(pkt)
{
}

Point_nr::Point_nr(int pkt,Point P):Point(P),m_PktNr(pkt)
{
}

Point_nr::~Point_nr()
{
}

Point_nr& Point_nr::operator= (const Point_nr &P)
{
	          (*this).set_PktNr(P.get_PktNr());
	          (*this).set_X( P.get_X() );
			  (*this).set_Y( P.get_Y() );
			  (*this).set_Z( P.get_Z() );
			  (*this).set_dX( P.get_dX() );
			  (*this).set_dY( P.get_dY() );
			  (*this).set_dZ( P.get_dZ() );
			  return (*this);	
}

Point_nr& Point_nr::operator= (const Point &P)
{
			  (*this).set_X( P.get_X() );
			  (*this).set_Y( P.get_Y() );
			  (*this).set_Z( P.get_Z() );
			  (*this).set_dX( P.get_dX() );
			  (*this).set_dY( P.get_dY() );
			  (*this).set_dZ( P.get_dZ() );
			  return (*this);
}

bool Point_nr::operator< (Point_nr &P)
{
 return (*this).get_PktNr()<P.get_PktNr();
}

bool Point_nr::operator== (Point_nr &P)
{
 return (*this).get_PktNr()==P.get_PktNr();	
}

bool Point_nr::operator== (int pkt_nr)
{
 return (*this).get_PktNr()==pkt_nr;		
}

Point_nr::operator Point () const
{
 return Point(m_x,m_y,m_z);
}

int Point_nr::get_PktNr() const
{
 return m_PktNr;
}
   
void Point_nr::set_PktNr(int pkt_nr)
{
 m_PktNr=pkt_nr;
}

ostream& operator<<(ostream& s,const Point_nr &A)
{
   int precision=5;       //Nachkommastellen
   //int vorkommastellen=8; //Minus zählt als Vorkommastelle

   s.setf(ios::fixed|ios::showpoint, ios::floatfield);//<<showpoint<<fixed
   s.setf(ios::right, ios::adjustfield);
   s.precision(precision);

   s<<setfill(' ')<<setw(precision+1)
    <<A.get_PktNr()
    <<static_cast<Point>(A);

return s;
};
