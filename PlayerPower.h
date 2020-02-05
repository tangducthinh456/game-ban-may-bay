#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H

#include "Common_Function.h"
#include "BaseObject.h"


class PlayerPower : public BaseObject
{
public :
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) { m_number = num; }
	int GetNumber() { return m_number; }
	void AddPos(const int& x_pos);
	void Render(SDL_Surface* des);
	void Init();
	void Decrease();
private:
	int m_number;
	std::vector<int> m_pos_list;
};






#endif PLAYER_POWER_H