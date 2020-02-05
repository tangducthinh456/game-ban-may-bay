#include "AmoObject.h"

AmoObject::AmoObject()
{
	m_x_val = 0;
	m_is_move = false;
	m_rect.x = 0;
	m_rect.y = 0;
	m_amo_type = NONE; 
}

AmoObject::~AmoObject()
{

}

void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
	m_rect.x += m_x_val;
	if (m_rect.x > x_border) m_is_move = false;
}

void AmoObject::HandleMoveRightToLeft()
{
	m_rect.x -= m_x_val;
	if (m_rect.x < 0)
	{
		m_is_move = false;
	}
}

