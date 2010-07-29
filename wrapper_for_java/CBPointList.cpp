#include "CBPointList.h"

CBPointList::CBPointList()
{
	
}

CBPointList::~CBPointList()
{
}
void CBPointList::addBPoint(BPoint bp)
{
	m_BPoint_List.push_back(bp);
}
int CBPointList::size()
{
	return static_cast<int>(m_BPoint_List.size());
}
void CBPointList::clearBPointList()
{
	m_BPoint_List.clear();
}
