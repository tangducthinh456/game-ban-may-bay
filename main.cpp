#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "PlayerPower.h"
#include "textShow.h"
#include <windows.h>



	
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "fail!";
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		std::cout << "Init screen fail!" << std::endl;
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Init audio fail!" << std::endl;
		return false;
	}

	//Read file wav audio
	g_sound_bullet[0] = Mix_LoadWAV("sound/laser.wav");
	g_sound_bullet[1] = Mix_LoadWAV("sound/sphere.wav");
	g_sound_exp[0] = Mix_LoadWAV("sound/exp_threat.wav");
	g_sound_exp[1] = Mix_LoadWAV("sound/exp_main.wav");
	g_sound_background = Mix_LoadWAV("sound/runnow.wav");
	g_sound_heart = Mix_LoadWAV("Taunt019.wav");

	if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL || g_sound_background == NULL)
	{
		std::cout << "Load file audio fail !" << std::endl;
		return false;
	}

	// init font type
	TTF_Init();
	g_font = TTF_OpenFont("fast99_3.ttf", 20);
	if (g_font == NULL)
	{
		std::cout << "Can't load file.ttf !\n";
		return false;
	}

	return true;
}


int main(int argc, char* argv[])
{
	
	
	if (Init() == false)
	{
		std::cout << "Init fail!" << std::endl;
		return 0;
	}

	//make sound background
	Mix_PlayChannel(-1, g_sound_background, 0);

Enter:;

	
	
	std::vector<std::string> background_name(7, "");

	background_name[0] = "images/background.png";
	background_name[1] = "images/backgroundCastle.png";
	background_name[2] = "images/backgroundColorDesert.png";
	background_name[3] = "images/backgroundColorFall.png";
	background_name[4] = "images/backgroundColorForest.png";
	background_name[5] = "images/backgroundColorGrass.png";
	background_name[6] = "images/bg4800.png";

	int bkgn_x = 0;
	bool is_run = true;
	bool is_quit = false;
	std::string m_time_game;

	int threat_count = 0;
	// initialize window, audio, font type

	// blit surface with background

	for (int i = 0; i < 7; i++)
	{
		g_bkground[i] = SDLCommonFunc::LoadImage(background_name[i]);
	}


	if (g_bkground == NULL)
	{
		std::cout << " loadimage background fail! " << std::endl;
		return 0;
	}

	//Make player power
	PlayerPower	player_power;


	//init text time game
	TextObject time_game;
	time_game.SetColor(TextObject::RED_TEXT);

	//init text score game
	TextObject score_game;
	score_game.SetColor(TextObject::RED_TEXT);

	//init heart for more life
	BaseObject* heart = new BaseObject;
	heart->LoadImg("images/heart.png");
	heart->SetRect(1300, 700);

	//init game over
	TextObject game_over;
	game_over.SetColor(TextObject::RED_TEXT);

	//Init level text
	TextObject text_level;
	text_level.SetColor(TextObject::RED_TEXT);

	//init text when change level
	TextObject change_level;
	change_level.SetColor(TextObject::RED_TEXT);

	//Make main
	MainObject* main_object = new MainObject;
	main_object->SetRect(100, 200);

	// Make 2 player
	MainObject* main2 = new MainObject;
	main2->SetRect(-100, -200);

	bool ret = main_object->LoadImg("images/plane_fly2.png");
	bool ret2 = main2->LoadImg("images/plane_fly.png");
	if (!ret || !ret2)
	{
		std::cout << "Init ret fail " << std::endl;
		return 0;
	}

	// Init explosion object for main object
	ExplosionObject exp_main[2];
	exp_main[0].setClip();
	exp_main[1].setClip();
	ret = exp_main[0].LoadImg("images/exp_main.png");
	ret2 = exp_main[1].LoadImg("images/exp_main.png");
	if (!ret || !ret2)
	{
		std::cout << "Can't load explosion images for main object !";
		return 0;
	}

	//Make threat

	ThreatObject* p_threats = new ThreatObject[10];

	for (int t = 0; t < 10; t++)
	{
		ThreatObject* p_threat = (p_threats + t);

		if (p_threat)
		{
			ret = p_threat->LoadImg("images/UFO.png");
			if (!ret)
			{
				std::cout << "fail loading UFO!" << std::endl;
				return 0;
			}

			srand(time(NULL));
			int rand_y = rand() * t % 400;
			if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}

			p_threat->SetRect(SCREEN_WIDTH + t * DISTANCE_THREAT, rand_y);
			p_threat->Set_x_val(SPEED_THREAT);

			AmoObject* p_amo = new AmoObject();

			p_threat->InitAmo(p_amo);
		}

	}

	// Init explosion object for threat object
	ExplosionObject exp_threat;
	exp_threat.setClip();
	ret = exp_threat.LoadImg("images/exp.png");
	if (!ret)
	{
		std::cout << "Can't load explosion images for threat object !";

	}


	player_power.Init();

	int score = 0;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font);

	if (ret_menu == 1) main2->SetRect(100, 200);

	if (ret_menu == 4) is_quit = true;
	else if (ret_menu == 2)
	{
		int ret_tutorial = SDLCommonFunc::showTutorial(g_screen, g_font);
		if (ret_tutorial == 1) goto Enter;
	}
	else if (ret_menu == 3)
	{
		int ret_highscore = SDLCommonFunc::showHighScore(g_screen, g_font);
		if (ret_highscore == 1) goto Enter;
	}
	else if (ret_menu == 0 || ret_menu == 1)
	{
		
		score = 0;
		level = 1;
		// game start
		while (!is_quit)
		{

			while (SDL_PollEvent(&g_event))
			{

				if (g_event.type == SDL_QUIT)
				{
					is_quit = true;
					break;
				}


				main_object->HandleInputAction(g_event, g_sound_bullet);
				if (ret_menu == 1)
				{
					main2->HandleInputActionPlayerTwo(g_event, g_sound_bullet);
				}
			}


			//apply background 

			if (level == 7)
			{
				if (is_run == true)
				{
					bkgn_x -= 2;

					if (bkgn_x <= -(BACKGROUND_WIDTH - SCREEN_WIDTH))
					{
						is_run = false;
					}
					SDLCommonFunc::ApplySurface(g_bkground[6], g_screen, bkgn_x, 0);
					//show level change
					std::string str_level = "Level 7";
					str_level += " : Start!";
					change_level.SetText(str_level);
					if (bkgn_x <= -300) change_level.SetRect(1300, 700);
					else change_level.SetRect(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 5);
					change_level.CreateGameText(g_font, g_screen);
				}
				else
				{
					SDLCommonFunc::ApplySurface(g_bkground[6], g_screen, bkgn_x, 0);
				}

			}
			else
			{
				if (level == 4) change_level.SetColor(TextObject::WHITE_TEXT);
				else change_level.SetColor(TextObject::RED_TEXT);
				bkgn_x -= 2;
				SDLCommonFunc::ApplySurface(g_bkground[level - 1], g_screen, bkgn_x, 0);

				//show level change
				std::string str_level = "Level ";
				str_level += std::to_string(level);
				str_level += " : Start!";
				change_level.SetText(str_level);
				if (bkgn_x <= -300) change_level.SetRect(1300, 700);
				else change_level.SetRect(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 5);
				change_level.CreateGameText(g_font, g_screen);

				if (bkgn_x == -(BACKGROUND_WIDTH - SCREEN_WIDTH))
				{
					bkgn_x = 0;
					level++;
				}
			}





			player_power.Render(g_screen);


			//Impliment main object
			main_object->HandleMove();
			main_object->Show(g_screen);
			main_object->MakeAmo(g_screen);

			if (ret_menu == 1)
			{
				main2->HandleMove();
				main2->Show(g_screen);
				main2->MakeAmo(g_screen);
			}





			//Impliment threat object
			NUM_THREATS = level + ret_menu * 2 + 1;

			for (int tt = 0; tt < NUM_THREATS; tt++)
			{
				ThreatObject* p_threat = (p_threats + tt);
				if (p_threat)
				{
					if (level == 1 || level == 2 || level == 3) p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
					else if (level == 4)
					{
						if (tt % 5 != 2) p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
						else p_threat->HandleMoveUFO(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					else if (level == 5)
					{
						if (tt % 5 == 1 || tt % 5 == 3) p_threat->HandleMoveUFO(SCREEN_WIDTH, SCREEN_HEIGHT);
						else p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					else if (level == 6)
					{
						if (tt % 5 == 0 || tt % 5 == 2 | tt % 5 == 4) p_threat->HandleMoveUFO(SCREEN_WIDTH, SCREEN_HEIGHT);
						else p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					else if (level == 7) p_threat->HandleMoveUFO(SCREEN_WIDTH, SCREEN_HEIGHT);

					p_threat->Show(g_screen);
					p_threat->Set_x_val(SPEED_THREAT);
					p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

					//check collision amo of threat and main object

					bool is_col1 = false;
					bool is_col2 = false;
					std::vector <AmoObject*> threat_amo_list = p_threat->GetAmoList();
					for (int im = 0; im < threat_amo_list.size(); im++)
					{
						AmoObject* p_amo = threat_amo_list.at(im);
						if (p_amo)
						{
							is_col1 = SDLCommonFunc::checkCollision(p_amo->GetRect(), main_object->GetRect());
							is_col2 = SDLCommonFunc::checkCollision(p_amo->GetRect(), main2->GetRect());
							if (is_col1 || is_col2)
							{
								p_threat->ResetAmo(p_amo);
								break;
							}
						}
					}


					//check collision main and threat
					bool is_col = SDLCommonFunc::checkCollision(main_object->GetRect(), p_threat->GetRect());

					bool is_col_ = false;

					if (ret_menu == 1)
					{
						is_col_ = SDLCommonFunc::checkCollision(main2->GetRect(), p_threat->GetRect());
					}


					// check the death of main object
					if (is_col || is_col1 || is_col2 || is_col_)
					{
						player_power.Decrease();

						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = main_object->GetRect().x + main_object->GetRect().w * 0.5 - EX_WIDTH * 0.5;
							int y_pos = main_object->GetRect().y + main_object->GetRect().h * 0.5 - EX_HEIGHT * 0.5;

							int x_pos_2 = main2->GetRect().x + main_object->GetRect().w * 0.5 - EX_WIDTH * 0.5;
							int y_pos_2 = main2->GetRect().y + main_object->GetRect().h * 0.5 - EX_HEIGHT * 0.5;


							exp_main[0].setFrame(ex);
							exp_main[0].SetRect(x_pos, y_pos);
							if (ret_menu == 1)
							{
								exp_main[1].setFrame(ex);
								exp_main[1].SetRect(x_pos_2, y_pos_2);
								exp_main[1].showEX(g_screen);
							}

							Mix_PlayChannel(-1, g_sound_exp[0], 0);
							Mix_PlayChannel(-1, g_sound_exp[1], 0);

							exp_main[0].showEX(g_screen);

							SDL_Delay(50);

							// Update screen
							if (SDL_Flip(g_screen) == -1)
							{
								return 0;
							}
						}

						main_object->SetRect(100, 400);
						if (ret_menu == 1) main2->SetRect(100, 420);

						p_threat->Reset(SCREEN_WIDTH + tt * 400);
					}

					


					// check collision amo of main object and threats
					std::vector <AmoObject*> amo_list = main_object->GetAmoList();
					for (int im = 0; im < amo_list.size(); im++)
					{
						AmoObject* p_amo = amo_list.at(im);
						if (p_amo != NULL)
						{
							bool ret_col = SDLCommonFunc::checkCollision(p_amo->GetRect(), p_threat->GetRect());
							if (ret_col)
							{
								threat_count++;
								if (tt % 2 == 0) score += 10;
								else score += 20;

								for (int ex = 0; ex < 4; ex++)
								{
									int x_pos = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - EX_WIDTH * 0.5;
									int y_pos = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - EX_HEIGHT * 0.5;

									exp_threat.setFrame(ex);
									exp_threat.SetRect(x_pos, y_pos);
									Mix_PlayChannel(-1, g_sound_exp[0], 0);
									exp_threat.showEX(g_screen);
									SDL_Delay(10);
									// Update screen
									if (SDL_Flip(g_screen) == -1)
									{
										return 0;
									}
								}
								if (threat_count % 15 == 0) heart->SetRect(p_threat->GetRect().x, p_threat->GetRect().y);
								p_threat->Reset(SCREEN_WIDTH + tt * 400);
								main_object->RemoveAmo(im);

							}

						}
					}


					if (ret_menu == 1)
					{
						std::vector <AmoObject*> amo_list_2 = main2->GetAmoList();
						for (int im = 0; im < amo_list_2.size(); im++)
						{
							AmoObject* p_amo = amo_list_2.at(im);
							if (p_amo != NULL)
							{
								bool ret_col = SDLCommonFunc::checkCollision(p_amo->GetRect(), p_threat->GetRect());
								if (ret_col)
								{
									threat_count++;
									if (tt % 2 == 0) score += 10;
									else score += 20;

									for (int ex = 0; ex < 4; ex++)
									{
										int x_pos = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - EX_WIDTH * 0.5;
										int y_pos = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - EX_HEIGHT * 0.5;

										exp_threat.setFrame(ex);
										exp_threat.SetRect(x_pos, y_pos);
										Mix_PlayChannel(-1, g_sound_exp[0], 0);
										exp_threat.showEX(g_screen);
										SDL_Delay(10);
										// Update screen
										if (SDL_Flip(g_screen) == -1)
										{
											return 0;
										}
									}
									if (threat_count % 15 == 0) heart->SetRect(p_threat->GetRect().x, p_threat->GetRect().y);
									p_threat->Reset(SCREEN_WIDTH + tt * 400);
									main_object->RemoveAmo(im);

								}

							}
						}
					}

					if (player_power.GetNumber() == 0)
					{
						//SDLCommonFunc::highScore();
						main_object->SetRect(-100, -100);
						main2->SetRect(-100, -100);
						//Show game over
						std::string str_over = "Game Over!";
						game_over.SetText(str_over);
						game_over.SetRect(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 5);
						game_over.CreateGameText(g_font, g_screen);
						delete[] p_threats;
						delete heart;
						delete main_object;
						delete main2;

						SDL_Flip(g_screen);
						SDL_Delay(3000);

						// handle high score
						std::ifstream filein("text/HighScore.txt");
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
						int x = score;
						for (int i = 0; i < 5; i++)
						{
							if (highscore[i] < x)
							{
								mark = i;
							}
						}

						for (int i = 0; i < mark; i++)
						{
							highscore[i] = highscore[i + 1];
						}

						highscore[mark] = score;


						std::ofstream fileout("text/HighScore.txt");

						if (!fileout) std::cout << "can't open file out!";
						fileout.clear();
						for (int i = 4; i >= 0; i--)
						{

							fileout << highscore[i] << std::endl;
						}
						fileout.close();
						

						
						goto Enter;
					}

				}

			}
			//show image heart 
			heart->Show(g_screen);

			// check collision between main and heart object
			if (SDLCommonFunc::checkCollision(main_object->GetRect(), heart->GetRect()) || SDLCommonFunc::checkCollision(main2->GetRect(), heart->GetRect()))
			{
				Mix_PlayChannel(-1, g_sound_heart, 0);
				player_power.AddPos(20 + 40 * player_power.GetNumber());
				heart->SetRect(1500, 800);
			}


			//show level
			std::string str_level = "Level ";
			str_level += std::to_string(level);
			text_level.SetText(str_level);
			text_level.SetRect(20, SCREEN_HEIGHT - 30);
			text_level.CreateGameText(g_font, g_screen);


			//Show time for game
			std::string str_time = "Time : ";
			Uint32 time_val = SDL_GetTicks() / 1000;
			time_game.SetRect(SCREEN_WIDTH - 200, 10);
			std::string str_val;
			// if gameover stop time
			if (player_power.GetNumber() != 0)
			{
				str_val = std::to_string(time_val);
				m_time_game = str_val;
			}
			else
			{
				str_val = m_time_game;
			}
			str_time += str_val;
			time_game.SetText(str_time);
			time_game.CreateGameText(g_font, g_screen);




			//show mark to screen
			
			std::string strMark("Score : " + std::to_string(score));
			score_game.SetText(strMark);
			score_game.CreateGameText(g_font, g_screen);

			// Update screen
			if (SDL_Flip(g_screen) == -1)
			{
				return 0;
			}

		}

		
		//delete[] p_threats;
		//delete heart;
		SDLCommonFunc::CleanUp();
		SDL_Quit();
	}


	return 1;
}