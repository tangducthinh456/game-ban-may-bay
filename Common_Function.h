
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_


#include <windows.h>
#include <SDL.h>
#undef main
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define PI 3.1415926535897

//threat
#define SPEED_THREAT 3
#define THREAT_WIDTH 90
#define THREAT_HEIGHT 33
#define DISTANCE_THREAT 400
const int UNDER_LIMIT_THREAT = 200;

//bullet
#define WIDTH_LASER 35
#define HEIGHT_LASER 5
#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

#define SPEED_LASER 30
#define SPEED_SPHERE 18

//main
#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

//size of background
const int BACKGROUND_WIDTH = 9600;
const int BACKGROUND_HEIGHT = 600;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

static int level = 1;


static int NUM_THREATS;

//static int score = -1;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground[7] = { NULL };
// static SDL_Surface* g_menu_bkground = NULL;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_sound_background;
static Mix_Chunk* g_sound_heart;

static TTF_Font* g_font = NULL;

static SDL_Event g_event;





namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);	
	void CleanUp();
	bool checkCollision(const SDL_Rect& object1, const SDL_Rect&  object2);
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
	int showTutorial(SDL_Surface* des, TTF_Font* font);
	int showHighScore(SDL_Surface* des, TTF_Font* font);
	
}


#endif