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

	PointNr& get_PointNR(int number);
	std::list<PointNr>& get_PointNr_list();

	bool add(PointNr& P);
	bool del(int number);

	bool read_from_file_system(std::string file_name);

	size_t size();
private:

  std::string m_list_name;

  std::list<PointNr> m_point_nr_list;

  PointNr m_default_point_nr;
};

#endif /* POINT_NR_LIST_H_ */
