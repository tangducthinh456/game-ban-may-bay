#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

#include "AmoObject.h"




class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();


	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleInputActionPlayerTwo(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list) { m_p_amo_list = amo_list; }
	std::vector<AmoObject*> GetAmoList() const { return m_p_amo_list; }

	void MakeAmo(SDL_Surface* des);

	void RemoveAmo(const int& idx);
private:
	int m_x_val;
	int m_y_val;
	std::vector<AmoObject*> m_p_amo_list;

};







#endif MAIN_OBJECT_H_
