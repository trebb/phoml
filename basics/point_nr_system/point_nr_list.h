/*
 * point_nr_list.h
 *
 *  Created on: 15.11.2009
 *      Author: steffen
 */

#ifndef POINT_NR_LIST_H_
#define POINT_NR_LIST_H_

#include <iostream>
#include <string>
#include <list>

#include "..//point_nr.h"

class CPoint_nr_list
{
public:
	CPoint_nr_list(std::string list_name);
	virtual ~CPoint_nr_list();

	const std::string& get_name();
	void rename_list(std::string list_name);

	Point_nr& get_PointNR(int number);
	std::list<Point_nr>& get_PointNr_list();
	std::list<Point>& get_Point_list();

	bool add(Point_nr& P);
	bool del(int number);

	bool read_from_file_system(std::string file_name);

	size_t size();
private:

  std::string m_list_name;

  std::list<Point_nr> m_point_nr_list;

  //empty list -> only for output the list<Point> format
  std::list<Point> m_point_list;

  Point_nr m_default_point_nr;
};

#endif /* POINT_NR_LIST_H_ */
