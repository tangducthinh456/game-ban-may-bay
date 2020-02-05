#include "BaseObject.h"


BaseObject::BaseObject()
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_p_object = NULL;
}

BaseObject::~BaseObject()
{
	if (m_p_object != NULL)
	{
		SDL_FreeSurface(m_p_object);
	}
}

bool BaseObject::LoadImg(std::string file_name)
{
	m_p_object = SDLCommonFunc::LoadImage(file_name);
	if (m_p_object == NULL)
	{
		std::cout << "m_p_object fail" << std::endl;
		return false;
	}
	return true;
}

void BaseObject::Show(SDL_Surface* des)
{
	if (m_p_object != NULL)
	{
		m_rect = SDLCommonFunc::ApplySurface(m_p_object, des, m_rect.x, m_rect.y);
	}
}