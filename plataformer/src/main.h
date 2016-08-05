#ifndef _MAIN_H_
#define _MAIN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

typedef struct {
	float x, y;
	float dx, dy;
	short life;
	char *name;
	int onLedge;
	int animFrame, facingLeft, slowingDown;
} Man;

typedef struct {
	int x, y;
} Star;

typedef struct {
	int x, y, w, h;
} Ledge;

typedef struct {
	//Player
	Man man;

	//Star
	Star stars[100];

	//Ledges
	Ledge ledges[100];

	//Images
	SDL_Texture *star;
	SDL_Texture *manFrames[29];
	SDL_Texture *brick;
	SDL_Texture *label;
	int labelW, labelH;

	//Fonts
	TTF_Font *font;

	//Time
	int time;
	int statusState;

	//Renderer
	SDL_Renderer *renderer;
	int scrollX;
} GameState;

//Prototypes 
void doRender(SDL_Renderer * renderer, GameState * game);

#endif
