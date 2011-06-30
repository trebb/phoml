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

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define DEBUG_LOCATION " [" __FILE__ " : " TOSTRING(__LINE__) "] "

class Basics_exception: public std::exception
{
public:
    Basics_exception();
     ~Basics_exception() throw();

   Basics_exception&    operator () (std::string err, const char* DEBUG_POS, std::string info);
   virtual const char*  what() const throw();
   virtual const char*  info() const throw();


private:
  std::string m_error;
  std::string m_default;
  std::string m_info;
};

typedef Basics_exception Exception_tool ;

static Basics_exception b_ex;
static Basics_exception CMD_EX; // only for CMD tools!!
static Basics_exception EX_t;
static Basics_exception EX;


/* Example for try and catch
 *


try{



    //code...or some thing else

    // throw EX("what",DEBUG_LOCATION,"location -> info ");

     *
     * throw EX("Couldn't open connection to ....",DEBUG_LOCATION,"wrapper::wrapper() -> open connection to ... -> error");
     *



}
catch(Exception_tool ex){
    cout << endl
         << ex.info()
         << endl
         <<"  -> catch at: " << DEBUG_LOCATION
         //<< endl
         //<<"  -> throw resume"
         <<flush;
    //throw ex;
}
catch(exception EX) { cout << endl << EX.what() <<flush;
}


 *
 */

#endif /* BASICS_EXCEPTION_H_ */
