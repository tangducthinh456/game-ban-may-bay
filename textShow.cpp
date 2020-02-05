#include "textShow.h"

TextObject::TextObject()
{
	m_rect.x = 500;
	m_rect.y = 10;
	m_text_color.r = 255;
	m_text_color.g = 0;
	m_text_color.b = 0;

}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int& type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0};
		m_text_color = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255};
		m_text_color = color;
	}
	else
	{
		SDL_Color color = { 0, 0, 0};
		m_text_color = color;
	}
}

void TextObject::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
	m_p_object = TTF_RenderText_Solid(font, m_text.c_str(), m_text_color);
	Show(des);
}