#ifndef EXPLOSION_H_
#define EXPLOSION_H_
#include "BaseObject.h"

const int EX_WIDTH = 165;
const int EX_HEIGHT= 165;

class ExplosionObject : public BaseObject
{
private:
	int m_frame;
	SDL_Rect m_clip[4];

public:
	ExplosionObject();
	~ExplosionObject();
	void setClip();
	void setFrame(const int& fr) { m_frame = fr; }
	void showEX(SDL_Surface* des);
};

#endif EXPLOSION_H_
