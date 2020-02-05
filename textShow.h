#ifndef TEXT_SHOW_H
#define TEXT_SHOW_H

#include "BaseObject.h"
#include <string>


class TextObject : public BaseObject
{
public:
	enum TextColor
	{
		RED_TEXT = 0,
	    WHITE_TEXT = 1,
		BLACK_TEXT = 2,

	};
	TextObject();
	~TextObject();
	void SetText(const std::string& text) { m_text = text; }
	void SetColor(const int& type);
	void CreateGameText(TTF_Font* font, SDL_Surface* des);

private : 
	std::string m_text;
	SDL_Color m_text_color;

};



#endif TEXT_SHOW_H