#pragma once

#include "inclusioni.h"

#include "Point2D.h"
#include "Object2D.h"

class CObj2D_Polyline : public CObject2D
{
public:
							CObj2D_Polyline();
							~CObj2D_Polyline();

	std::vector<int>		m_aIndex;
	vect_CPoint2D			m_aPnts;

};

