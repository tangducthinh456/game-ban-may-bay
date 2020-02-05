#include "Common_Function.h"
#include "textShow.h"

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;

	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);

		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}

	return optimize_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
	return offset;
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}


void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground[level - 1]);
}

bool SDLCommonFunc::checkCollision(const SDL_Rect& object1, const SDL_Rect&  object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

bool SDLCommonFunc::checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y +rect.h)
	{
		return true;
	}
	else return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
	SDL_Surface* menu_bkground = LoadImage("images/backgroundmenu.png");

	if (menu_bkground == NULL)
	{
		std::cout << "can't load menu back ground!" << std::endl;
		return 1;
	}
		const int NumMenuItem = 5;
		SDL_Rect pos_arr[NumMenuItem];
		pos_arr[0].x = 200;
		pos_arr[0].y = 100;

		pos_arr[1].x = 200;
		pos_arr[1].y = 200;

		pos_arr[2].x = 200;
		pos_arr[2].y = 300;

		pos_arr[3].x = 200;
		pos_arr[3].y = 400;

		pos_arr[4].x = 200;
		pos_arr[4].y = 500;

		TextObject text_menu[NumMenuItem]; 
		text_menu[0].SetText("1.One player");
		text_menu[0].SetColor(TextObject::RED_TEXT);
		text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

		text_menu[1].SetText("2.Two player");
		text_menu[1].SetColor(TextObject::RED_TEXT);
		text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

		text_menu[2].SetText("3.How to play");
		text_menu[2].SetColor(TextObject::RED_TEXT);
		text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

		text_menu[3].SetText("4.High score");
		text_menu[3].SetColor(TextObject::RED_TEXT);
		text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

		text_menu[4].SetText("5.Exit");
		text_menu[4].SetColor(TextObject::RED_TEXT);
		text_menu[4].SetRect(pos_arr[4].x, pos_arr[4].y);


		bool selected[NumMenuItem] = {1, 1, 1, 1, 1};
		int xm = 0, ym = 0;
		SDL_Event m_event;
		while (true)
		{

			SDLCommonFunc::ApplySurface(menu_bkground, des, 0, 0);
			for (int i = 0; i < NumMenuItem; i++)
			{
				text_menu[i].CreateGameText(font, des);
			}

			while (SDL_PollEvent(&m_event))
			{
				switch (m_event.type)
				{
				case  SDL_QUIT:
					return 1;
					break;
				case SDL_MOUSEMOTION:
				{
					xm = m_event.motion.x;
					ym = m_event.motion.y;

					for (int i = 0; i < NumMenuItem; i++)
					{
						if (SDLCommonFunc::checkFocusWithRect(xm, ym, text_menu[i].GetRect()))
						{ 
							if (selected[i] == false)
							{
								selected[i] = 1;	
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else
						{
							if (selected[i] == true)
							{
								selected[i] = 0;
								text_menu[i].SetColor(TextObject::BLACK_TEXT);
							}
						}
					}
				}
				break;
				case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;

					for (int i = 0; i < NumMenuItem; i++)
					{
						if (SDLCommonFunc::checkFocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							return i;
						}
					}
				}
				break;
				case SDL_KEYDOWN:
				{
					if (m_event.key.keysym.sym == SDLK_ESCAPE || m_event.key.keysym.sym == SDLK_5)
					{
						return 4;
					}
					else if (m_event.key.keysym.sym == SDLK_1) return 0;
					else if (m_event.key.keysym.sym == SDLK_2) return 1;
					else if (m_event.key.keysym.sym == SDLK_3) return 2;
					else if (m_event.key.keysym.sym == SDLK_4) return 3;

				}
				break;
				default:
					break;
				}
			}
			SDL_Flip(des);
		}
	return 4;
}

int SDLCommonFunc::showTutorial(SDL_Surface* des, TTF_Font* font)
{
	SDL_Surface* tutorial_bkground;
	tutorial_bkground = LoadImage("images/backgroundtutorial.png");

	if (tutorial_bkground == NULL)
	{
		std::cout << "can't load tutorial !" << std::endl;
		return 0;
	}

	

	SDL_Event event;

	
	while (true)
	{
		SDLCommonFunc::ApplySurface(tutorial_bkground, des, 0, 0);


		

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return 0;
				
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE) return 1;
			default:
				break;
			}
		}
		SDL_Flip(des);
	}

}
/*
void SDLCommonFunc::highScore()
{
	std::ifstream filein("HighScore.txt");
	if (!filein) std::cout << "can't open file in!";

	int highscore[5] = { 0 };
	int mark = 0;

	for (int i = 0; i < 5; i++)
	{
		filein >> highscore[i];
		filein.ignore();
	}
	std::sort(highscore, highscore + 5);

	
	filein.close();
	
	for (int i = 0; i < 5; i++)
	{
		if (highscore[i] < x)
		{
			mark = i;
		}
	}
	
	for (int i = 0; i < mark ; i++)
	{
		highscore[i] = highscore[i + 1];
	}

	highscore[mark] = score;
	

	std::ofstream fileout("HighScore.txt");
	
	if (!fileout) std::cout << "can't open file out!";
	fileout.clear();
		for (int i = 4; i >= 0; i--)
		{
			
			fileout << highscore[i] << std::endl;
		}
	
		
		fileout.close();
		std::cout << score << " ";

	return;
}
*/
int SDLCommonFunc::showHighScore(SDL_Surface* des, TTF_Font* font)
{
	SDL_Surface* highscore_bkground;
	highscore_bkground = LoadImage("images/backgroundhighscore.png");

	if (highscore_bkground == NULL)
	{
		std::cout << "can't load high score !" << std::endl;
		return 0;
	}

	std::ifstream fileout("text/HighScore.txt");
	int highscore[5];
	for (int i = 0; i < 5; i++) fileout >> highscore[i];
	fileout.close();

	SDL_Rect pos_arr[5];
	pos_arr[0].x = 400;
	pos_arr[0].y = 100;

	pos_arr[1].x = 400;
	pos_arr[1].y = 200;

	pos_arr[2].x = 400;
	pos_arr[2].y = 300;

	pos_arr[3].x = 400;
	pos_arr[3].y = 400;

	pos_arr[4].x = 400;
	pos_arr[4].y = 500;

	TextObject text_highscore[5];
	text_highscore[0].SetText("1. " + std::to_string(highscore[0]));
	text_highscore[0].SetColor(TextObject::RED_TEXT);
	text_highscore[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_highscore[1].SetText("2. " + std::to_string(highscore[1]));
	text_highscore[1].SetColor(TextObject::RED_TEXT);
	text_highscore[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_highscore[2].SetText("3. " + std::to_string(highscore[2]));
	text_highscore[2].SetColor(TextObject::RED_TEXT);
	text_highscore[2].SetRect(pos_arr[2].x, pos_arr[2].y);

	text_highscore[3].SetText("4. " + std::to_string(highscore[3]));
	text_highscore[3].SetColor(TextObject::RED_TEXT);
	text_highscore[3].SetRect(pos_arr[3].x, pos_arr[3].y);

	text_highscore[4].SetText("5. " + std::to_string(highscore[4]));
	text_highscore[4].SetColor(TextObject::RED_TEXT);
	text_highscore[4].SetRect(pos_arr[4].x, pos_arr[4].y);

	SDL_Event event;

	while (true)
	{
		SDLCommonFunc::ApplySurface(highscore_bkground, des, 0, 0);

		for (int i = 0; i < 5; i++)
		{
			text_highscore[i].CreateGameText(font, des);
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return 0;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE) return 1;
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
}