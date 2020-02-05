#include "ThreatsObject.h"
#include <math.h>

ThreatObject::ThreatObject()
{
	m_rect.x = SCREEN_WIDTH;
	m_rect.y = SCREEN_HEIGHT * 0.5;
	m_rect.w = THREAT_WIDTH;
	m_rect.h = THREAT_HEIGHT;
	
	m_x_val = 0;
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
	if (p_amo != NULL)
	{
		bool ret = p_amo->LoadImg("images/sphere.png");
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(m_rect.x, m_rect.y + m_rect.h * 0.5);
			p_amo->setRectX(8);
			m_p_amo_list.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < m_p_amo_list.size(); i++)
	{
		AmoObject* p_amo = m_p_amo_list.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(m_rect.x, m_rect.y + m_rect.h * 0.5);
			}
		}
	}

}

ThreatObject::~ThreatObject()
{
	;
}

void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	m_rect.x -= m_x_val;
	
	if (m_rect.x < 0)
	{
		m_rect.x = x_border;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = (int)SCREEN_HEIGHT * 0.3;
		}
		m_rect.y = rand_y;
 	}
	
}


void ThreatObject::HandleMoveUFO(const int& x_border, const int& y_border)
{
	m_rect.x -= m_x_val;

	if (m_rect.x < 0)
	{
		m_rect.x = x_border;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = (int)SCREEN_HEIGHT * 0.3;
		}
		m_rect.y = rand_y;
	}
	m_rect.y += (int)5 * sin(double(SCREEN_WIDTH - m_rect.x) / 300 * PI);
}




void ThreatObject::Reset(const int& xborder)
{
	m_rect.x = xborder;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = (int)SCREEN_HEIGHT * 0.3;
	}
	m_rect.y = rand_y;
	

}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(m_rect.x, m_rect.y + (int)m_rect.h * 0.5);
}