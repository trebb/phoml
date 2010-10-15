/*
 * point_nr_list.cpp
 *
 *  Created on: 15.11.2009
 *      Author: steffen
 */

#include "point_nr_list.h"

#include <sstream>
#include <fstream>

CPoint_nr_list::CPoint_nr_list(std::string list_name)
{
	m_list_name = list_name;
}

CPoint_nr_list::~CPoint_nr_list()
{

}

void CPoint_nr_list::rename_list(std::string list_name)
{
	m_list_name = list_name;
}

PointNr& CPoint_nr_list::get_PointNR(int number)
{
	std::list<PointNr>::iterator iP = m_point_nr_list.begin();

    while(iP!=m_point_nr_list.end())
	  {
	   if(number==iP->get_PktNr())
	   {
		 return *iP;
	   }
	   ++iP;
	  }

return m_default_point_nr;
}

std::list<PointNr>& CPoint_nr_list::get_PointNr_list()
{
 return m_point_nr_list;
}

std::list<Point>& CPoint_nr_list::get_Point_list()
{
	std::list<PointNr>::iterator iP = m_point_nr_list.begin();

	      while(iP!=m_point_nr_list.end())
		  {
	    	  m_point_list.push_back(*iP);
		   ++iP;
		  }

 return m_point_list;
}

bool CPoint_nr_list::add(PointNr& P)
{
   size_t so = m_point_nr_list.size();
	m_point_nr_list.push_back(P);
   if( (so+1) == m_point_nr_list.size())
    return true;
    else return false;
}

bool CPoint_nr_list::del(int number)
{
	std::list<PointNr>::iterator iP = m_point_nr_list.begin();
    bool is_del=false;

    while(iP!=m_point_nr_list.end())
	  {
	   if(number==iP->get_PktNr())
	   {
		 if(iP==m_point_nr_list.begin())
			 m_point_nr_list.erase(iP++);
		 else
			 m_point_nr_list.erase(iP--);

		 is_del=true;
	   }
	   ++iP;
	  }

	  if(is_del)
		  return true;

return false;
}


bool CPoint_nr_list::read_from_file_system(std::string file_name)
{
	//read
	 std::ifstream DAT_TXT;
	 DAT_TXT.open(file_name.c_str());
	 if(!DAT_TXT) { return false; }

	 string hilf;

	 int pkt=0;
	 double x=0.0,y=0.0,z=0.0;

	 PointNr T(0,0.0,0.0,0.0);

	 while(getline(DAT_TXT,hilf))
	 {
				if(hilf.length()>0 )
				if(hilf.at(0)!='#' )
				{
				 std::stringstream stream;
				 stream<<hilf.c_str();
				 hilf.erase();
				 stream>>pkt>>x>>y>>z;

				 T.set_PktNr(pkt);
				 T.set_X(x);
				 T.set_Y(y);
				 T.set_Z(z);

				 m_point_nr_list.push_back(T);
				}
	 }
	 DAT_TXT.close();
	 DAT_TXT.clear();

return true;
}

size_t CPoint_nr_list::size()
{
	return m_point_nr_list.size();
}

