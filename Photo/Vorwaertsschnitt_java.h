#ifndef VORWAERTSSCHNITT_JAVA_H_
#define VORWAERTSSCHNITT_JAVA_H_
#include "CBPointList.h"
#include "forward_intersection.h"

class Vorwaertsschnitt_java
{
public:
	Vorwaertsschnitt_java();
	Point calc_vorwaertsschnitt(CBPointList blist); 
	virtual ~Vorwaertsschnitt_java();
};

#endif /*VORWAERTSSCHNITT_JAVA_H_*/
