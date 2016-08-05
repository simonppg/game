#include "main.h"

void init_status_lives(GameState * game)
{
	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Game", white);
	game->labelW = tmp->w;
	game->labelH = tmp->h;
	game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
	SDL_FreeSurface(tmp);
}

void draw_status_lives(GameState * game)
{
	SDL_Renderer *renderer = game->renderer;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear the screen
	SDL_RenderClear(renderer);

	//Set the drawing color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect textRect =
	    { 320, 240 - game->labelH, game->labelW, game->labelH };
	SDL_RenderCopy(renderer, game->label, NULL, &textRect);
}

void shutdown_status_lives(GameState * game)
{
	SDL_DestroyTexture(game->label);
	game->label = NULL;
}
