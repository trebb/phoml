/*
 * basics_exception.cpp
 *
 *  Created on: 28.12.2010
 *      Author: steffen
 */

#include "basics_exception.h"


Basics_exception::Basics_exception() : m_default("!!! basics_exception error !!! : ")
{

}

Basics_exception::~Basics_exception() throw()
{

}

Basics_exception& Basics_exception::operator () (std::string err, std::string info)
{
    m_error = err;
    m_info = m_default +info + "  -> error type: "+m_error;
  return (*this);
}

const char* Basics_exception::what() const throw()
{
      return m_error.c_str();
}

const char* Basics_exception::info() const throw()
{
       return m_info.c_str();
}
