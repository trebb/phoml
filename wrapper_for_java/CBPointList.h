#ifndef CBPOINTLIST_H_
#define CBPOINTLIST_H_
#include "../photo/bpoint.h"
#include <vector>

class CBPointList
{
public:
	CBPointList();
	~CBPointList();
	void addBPoint(BPoint bp);
	int size();
	void clearBPointList();
	vector<BPoint> m_BPoint_List;
};


#endif /*CBPOINTLIST_H_*/
