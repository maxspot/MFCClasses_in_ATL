#pragma once

class CPoint2D
{
public:
					CPoint2D();
					CPoint2D( double dX, double dY);
					~CPoint2D();

public:
	double			m_dX;			///< Coordinata X
	double			m_dY;			///< Coordinata X
};

#define vect_CPoint2D std::vector<CPoint2D>
