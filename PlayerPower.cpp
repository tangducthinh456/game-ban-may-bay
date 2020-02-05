#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
	
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& x_pos)
{
	if (m_number < 5)
	{
		m_number++;
		m_pos_list.push_back(x_pos);
	}
}

void PlayerPower::Render(SDL_Surface* des)
{
	if (m_number + 1 == m_pos_list.size())
	{
		for (int i = 0; i < m_pos_list.size(); i++)
		{
			m_rect.x = m_pos_list.at(i);
			Show(des);
		}
	}
}

void PlayerPower::Init()
{
	LoadImg("images/heart.png");
	m_number = -1;
	
	if (m_pos_list.size() > 0)
	{
		m_pos_list.clear();
	}
	AddPos(-50);
	AddPos(20);
	AddPos(60);
	AddPos(100);
	
}

void PlayerPower::Decrease()
{
	m_number--;
	m_pos_list.pop_back();
}
