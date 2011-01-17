/*
 * basics_exception.h
 *
 *  Created on: 28.12.2010
 *      Author: steffen
 */

#ifndef BASICS_EXCEPTION_H_
#define BASICS_EXCEPTION_H_

#include <iostream>
#include <string>
#include <exception>

class Basics_exception: public std::exception
{
public:
    Basics_exception();
     ~Basics_exception() throw();

   Basics_exception&    operator () (std::string err, std::string info);
   virtual const char*  what() const throw();
   virtual const char*  info() const throw();


private:
  std::string m_error;
  std::string m_default;
  std::string m_info;
};

static Basics_exception b_ex;

#endif /* BASICS_EXCEPTION_H_ */
