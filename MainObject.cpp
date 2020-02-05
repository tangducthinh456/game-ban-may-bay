#include "MainObject.h"


MainObject::MainObject()
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = WIDTH_MAIN_OBJECT;
	m_rect.h = HEIGHT_MAIN_OBJECT;
	m_x_val = 0;
	m_y_val = 0;
}
 
MainObject::~MainObject()
{
	;
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			m_y_val -= HEIGHT_MAIN_OBJECT / 15;
			break;
		case SDLK_s:
			m_y_val += HEIGHT_MAIN_OBJECT / 15;
			break;
		case SDLK_d:
			m_x_val += WIDTH_MAIN_OBJECT / 15;
			break;
		case SDLK_a:
			m_x_val -= WIDTH_MAIN_OBJECT / 15;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w: m_y_val += HEIGHT_MAIN_OBJECT / 15; break;
		case SDLK_s: m_y_val -= HEIGHT_MAIN_OBJECT / 15; break;
		case SDLK_a: m_x_val += WIDTH_MAIN_OBJECT / 15; break;
		case SDLK_d: m_x_val -= WIDTH_MAIN_OBJECT / 15; break;
	    
		}

	}

	if (events.type == SDL_KEYDOWN)
	{
		
		if (events.key.keysym.sym == SDLK_g)
		{
			AmoObject* p_amo = new AmoObject;
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("images/laser.png");
			p_amo->set_type(AmoObject::LASER);
			p_amo->setRectX(SPEED_LASER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
			p_amo->SetRect(this->m_rect.x + this->m_rect.w - 20, this->m_rect.y + this->m_rect.h*0.5);
			p_amo->set_is_move(true);
			m_p_amo_list.push_back(p_amo);
		}
		else if (events.key.keysym.sym == SDLK_h)
		{
			AmoObject* p_amo = new AmoObject;
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("images/sphere.png");
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->setRectX(SPEED_SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
			p_amo->SetRect(this->m_rect.x + this->m_rect.w - 20, this->m_rect.y + this->m_rect.h*0.5);
			p_amo->set_is_move(true);
			m_p_amo_list.push_back(p_amo);
		}
		
	}
}



void MainObject::HandleInputActionPlayerTwo(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			m_y_val -= HEIGHT_MAIN_OBJECT / 15;
			break;
		case SDLK_DOWN:
			m_y_val += HEIGHT_MAIN_OBJECT / 15;
			break;
		case SDLK_LEFT:
			m_x_val -= WIDTH_MAIN_OBJECT / 15;
			break;
		case SDLK_RIGHT:
			m_x_val += WIDTH_MAIN_OBJECT / 15;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: m_y_val += HEIGHT_MAIN_OBJECT / 15; break;
		case SDLK_DOWN: m_y_val -= HEIGHT_MAIN_OBJECT / 15; break;
		case SDLK_LEFT: m_x_val += WIDTH_MAIN_OBJECT / 15; break;
		case SDLK_RIGHT: m_x_val -= WIDTH_MAIN_OBJECT / 15; break;

		}

	}
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{

		if (events.button.button == SDL_BUTTON_LEFT)
		{
			AmoObject* p_amo = new AmoObject;
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("images/laser.png");
			p_amo->set_type(AmoObject::LASER);
			p_amo->setRectX(SPEED_LASER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
			p_amo->SetRect(this->m_rect.x + this->m_rect.w - 20, this->m_rect.y + this->m_rect.h*0.5);
			p_amo->set_is_move(true);
			m_p_amo_list.push_back(p_amo);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			AmoObject* p_amo = new AmoObject;
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("images/sphere.png");
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->setRectX(SPEED_SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
			p_amo->SetRect(this->m_rect.x + this->m_rect.w - 20, this->m_rect.y + this->m_rect.h*0.5);
			p_amo->set_is_move(true);
			m_p_amo_list.push_back(p_amo);
		}

	}
	
}



void MainObject::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i < m_p_amo_list.size(); i++)
	{
		
		AmoObject* p_amo = m_p_amo_list.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if (p_amo != NULL)
				{
					m_p_amo_list.erase(m_p_amo_list.begin() + i);
					
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void MainObject::HandleMove()
{
	m_rect.x += m_x_val;
	
	if (m_rect.x < 0 || m_rect.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
	{
		m_rect.x -= m_x_val;
	}

	m_rect.y += m_y_val;

	if (m_rect.y < 0 || m_rect.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
	{
		m_rect.y -= m_y_val;
	}
}

void MainObject::RemoveAmo(const int& idx)
{
	
	for (int i = 0; i < m_p_amo_list.size(); i++)
	{
		if (idx < m_p_amo_list.size())
		{
			AmoObject* p_amo = m_p_amo_list.at(idx);
			m_p_amo_list.erase(m_p_amo_list.begin() + idx);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}

	}
}