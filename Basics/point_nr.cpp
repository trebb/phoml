#include "point_nr.h"



CPoint_Nr::CPoint_Nr()
{
}

CPoint_Nr::CPoint_Nr(int pkt,double x,double y,double z):Point(x,y,z),m_PktNr(pkt)
{
}

CPoint_Nr::CPoint_Nr(int pkt,Point P):Point(P),m_PktNr(pkt)
{
}

CPoint_Nr::~CPoint_Nr()
{
}

bool CPoint_Nr::operator< (CPoint_Nr &P)
{
 return (*this).get_PktNr()<P.get_PktNr();
}

CPoint_Nr::operator Point () const
{
 return Point(m_x,m_y,m_z);
}

int CPoint_Nr::get_PktNr()
{
 return m_PktNr;
}
   
void CPoint_Nr::set_PktNr(int pkt_nr)
{
 m_PktNr=pkt_nr;
}
