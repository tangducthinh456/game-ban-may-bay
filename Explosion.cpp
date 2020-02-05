// #include "BaseObject.h"
#include "Explosion.h"

ExplosionObject::ExplosionObject()
{
	m_frame = 0;
}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::setClip()
{
	m_clip[0].x = 0;
	m_clip[0].y = 0;
	m_clip[0].w = EX_WIDTH;
	m_clip[0].h = EX_HEIGHT;

	m_clip[1].x = EX_WIDTH;
	m_clip[1].y = 0;
	m_clip[1].w = EX_WIDTH;
	m_clip[1].h = EX_HEIGHT;

	m_clip[2].x = EX_WIDTH * 2;
	m_clip[2].y = 0;
	m_clip[2].w = EX_WIDTH;
	m_clip[2].h = EX_HEIGHT;

	m_clip[3].x = EX_WIDTH * 3;
	m_clip[3].y = 0;
	m_clip[3].w = EX_WIDTH;
	m_clip[3].h = EX_HEIGHT;
}

void ExplosionObject::showEX(SDL_Surface* des)
{
	if (m_frame >= 4)
	{
		m_frame = 0;
	}

	SDLCommonFunc::ApplySurfaceClip(this->m_p_object, des, &m_clip[m_frame], m_rect.x, m_rect.y);
}

