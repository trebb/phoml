#include "Vorwaertsschnitt_java.h"

Vorwaertsschnitt_java::Vorwaertsschnitt_java()
{
}

Vorwaertsschnitt_java::~Vorwaertsschnitt_java()
{
}

Point Vorwaertsschnitt_java::calc_vorwaertsschnitt(CBPointList blist)
{
	Vorwaertsschnitt fw(blist.m_BPoint_List);

	return fw.get_Schnittpunkt();
}

