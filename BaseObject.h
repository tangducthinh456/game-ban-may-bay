
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);
	bool LoadImg(std::string file_name);

	void SetRect(const int &x, const int &y) { m_rect.x = x, m_rect.y = y; };
	SDL_Rect GetRect() const { return m_rect; };
	SDL_Surface* GetObject() { return m_p_object; };
	 

protected:
	SDL_Rect m_rect;
	SDL_Surface* m_p_object;

};



#endif BASE_OBJECT_H
