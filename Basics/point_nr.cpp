#include "point_nr.h"



PointNr::PointNr()
{
}

PointNr::PointNr(int pkt,double x,double y,double z):Point(x,y,z),m_PktNr(pkt)
{
}

PointNr::PointNr(int pkt,Point P):Point(P),m_PktNr(pkt)
{
}

PointNr::~PointNr()
{
}

PointNr& PointNr::operator= (const PointNr &P)
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

PointNr& PointNr::operator= (const Point &P)
{
			  (*this).set_X( P.get_X() );
			  (*this).set_Y( P.get_Y() );
			  (*this).set_Z( P.get_Z() );
			  (*this).set_dX( P.get_dX() );
			  (*this).set_dY( P.get_dY() );
			  (*this).set_dZ( P.get_dZ() );
			  return (*this);
}

bool PointNr::operator< (PointNr &P)
{
 return (*this).get_PktNr()<P.get_PktNr();
}

bool PointNr::operator== (PointNr &P)
{
 return (*this).get_PktNr()==P.get_PktNr();	
}

bool PointNr::operator== (int pkt_nr)
{
 return (*this).get_PktNr()==pkt_nr;		
}

PointNr::operator Point () const
{
 return Point(m_x,m_y,m_z);
}

int PointNr::get_PktNr() const
{
 return m_PktNr;
}
   
void PointNr::set_PktNr(int pkt_nr)
{
 m_PktNr=pkt_nr;
}
