#include <stdio.h>
#include <time.h>
#include "main.h"
#include "status.h"

#define GRAVITY 0.35f

void loadGame(GameState * game)
{
	SDL_Surface *surface = NULL;

//Load images and create rendering textures from them
	surface = IMG_Load("images/rocket_fire.png");
	if (surface == NULL) {
		printf("Cannot find imag.png");
		SDL_Quit();
		exit(1);
	}

	game->star = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);

	for (int i = 1; i <= 29; i++) {
		char str[128];
		sprintf(str, "%s%d%s", "images/heroe/ryu", i, ".png");
		surface = IMG_Load(str);
		if (surface == NULL) {
			printf("no hay image en %s", str);
			SDL_Quit();
			exit(1);
		}
		game->manFrames[i - 1] =
		    SDL_CreateTextureFromSurface(game->renderer, surface);
		SDL_FreeSurface(surface);
	}

	surface = IMG_Load("images/landing_area.png");
	if (surface == NULL) {
		printf("no hay image");
		SDL_Quit();
		exit(1);
	}
	game->brick = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);

//Load fonts
	game->font = TTF_OpenFont("fonts/Hack-Regular.ttf", 48);
	if (!game->font) {
		printf("Cannot find font file!\n\n");
		SDL_Quit();
		exit(1);
	}

	game->label = NULL;

	game->man.x = 320;
	game->man.y = 240;
	game->man.dx = 0;
	game->man.dy = 0;
	game->man.onLedge = 0;
	game->statusState = STATUS_STATE_LIVES;

	init_status_lives(game);

//Init stars
	for (int i = 0; i < 100; i++) {
		game->stars[i].x = 640;
		game->stars[i].y = 480;
	}

//Init ledges
	for (int i = 0; i < 100; i++) {
		game->ledges[i].w = 127;
		game->ledges[i].h = 40;
		game->ledges[i].x = i * 127;
		game->ledges[i].y = 400;
	}
	game->ledges[99].x = 350;
	game->ledges[99].y = 200;

	game->ledges[98].x = 350;
	game->ledges[98].y = 350;

	game->scrollX = 0;
	game->time = 0;
}

void process(GameState * game)
{
//Add time
	game->time++;

	if (game->time > 120) {
		shutdown_status_lives(game);
		game->statusState = STATUS_STATE_GAME;
	}

	if (game->statusState == STATUS_STATE_GAME) {
//Man movement
		Man *man = &game->man;
		man->x += man->dx;
		man->y += man->dy;

		if (man->dx != 0 && man->onLedge && !man->slowingDown) {
			if (game->time % 8 == 0) {
				if (man->animFrame == 0) {
					man->animFrame = 1;
				} else {
					man->animFrame = 0;
				}
			}
		}

		man->dy += GRAVITY;

		game->scrollX = -man->x + 320;
	}
}

void collisionDetect(GameState * game)
{
//Check for collision with any ledges (brick blocks)
	for (int i = 0; i < 100; i++) {
		float mw = 17, mh = 31;
		float mx = game->man.x, my = game->man.y;
		float bx = game->ledges[i].x, by = game->ledges[i].y, bw =
		    game->ledges[i].w, bh = game->ledges[i].h;

		if (my + mh > by && my < by + bh) {
//Rubbing against right edge
			if (mx < bx + bw && mx + mw > bx + bw
			    && game->man.dx < 0) {
//correct x
				game->man.x = bx + bw;
				mx = bx + bw;
				game->man.dx = 0;
			}
//Rubbing against left edge
			if (mx + mw > bx && mx < bx && game->man.dx > 0) {
//correct x
				game->man.x = bx - mw;
				mx = bx - mw;
				game->man.dx = 0;
			}
		}

		if (mx + mw / 2 > bx && mx + mw / 2 < bx + bw) {
//are we bumping our head?
			if (my < by + bh && my > by && game->man.dy < 0) {
//correct y
				game->man.y = by + bh;
				my = by + bh;

//bumped our head, stop any jump velocity
				game->man.dy = 0;
			}
		}
		if (mx + mw > bx && mx < bx + bw) {
//are we landing on the ledge
			if (my + mh > by && my < by && game->man.dy > 0) {
//correct y
				game->man.y = by - mh;

//landed on this ledge, stop any jump velocity
				game->man.dy = 0;
				game->man.onLedge = 1;
			}
		}
	}
}

int processEvent(SDL_Window * window, GameState * game)
{
	int done = 0;;
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT_CLOSE:
			if (window) {
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				done = 1;
				break;
			case SDLK_UP:
				if (game->man.onLedge) {
					game->man.dy = -8;
					game->man.onLedge = 0;
				}
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			done = 1;
			break;
		default:
			break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_RIGHT]) {
		game->man.dx += 0.5;
		if (game->man.dx > 6) {
			game->man.dx = 6;
		}
	} else if (state[SDL_SCANCODE_LEFT]) {
		game->man.dx -= 0.5;
		if (game->man.dx < -6) {
			game->man.dx = -6;
		}
	} else {
		game->man.dx *= 0.8f;
		if (fabsf(game->man.dx) < 0.1f) {
			game->man.dx = 0;
		}
	}
	if (state[SDL_SCANCODE_UP]) {
		game->man.dy -= 0.2f;
	}

	return done;
}

void doRender(SDL_Renderer * renderer, GameState * game)
{
	if (game->statusState == STATUS_STATE_LIVES) {
		draw_status_lives(game);
	} else if (game->statusState == STATUS_STATE_GAME) {
//Set the drawing color to blue
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

//Clear the screen (to blue)
		SDL_RenderClear(renderer);

//Set the drawing color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		for (int i = 0; i < 100; i++) {
			SDL_Rect ledgeRect =
			    { game->scrollX + game->ledges[i].x,
				game->ledges[i].y,
				game->ledges[i].w,
				game->ledges[i].h
			};
			SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
		}

//Draw a rectangle at man's position
		SDL_Rect rect =
		    { game->scrollX + game->man.x, game->man.y, 17, 31 };
		SDL_RenderCopyEx(renderer, game->manFrames[0], NULL, &rect, 0,
				 NULL, 0);

//Draw the star image
		SDL_Rect starRect = { 50, 50, 17, 32 };
		SDL_RenderCopy(renderer, game->star, NULL, &starRect);

		for (int i = 0; i < 100; i++) {
			SDL_Rect starRect = { game->stars[i].x,
				game->stars[i].y,
				64,
				64
			};
			SDL_RenderCopy(renderer, game->star, NULL, &starRect);
		}

//We are done drawing, "present" or show to the screen what we've draw
	}
	SDL_RenderPresent(renderer);
}

int main()
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	GameState game;

	SDL_Init(SDL_INIT_VIDEO);

	//srandom((int)time(NULL));

//Create an application window with the following settings:
	window = SDL_CreateWindow("Game window",
				  SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	renderer = SDL_CreateRenderer(window,
				      -1,
				      SDL_RENDERER_ACCELERATED |
				      SDL_RENDERER_PRESENTVSYNC);

	game.renderer = renderer;

//Initialize font system
	TTF_Init();

	loadGame(&game);

//The windows is open: enter program loop (see SDL_PollEvent)
	int done = 0;
//Event loop
	while (!done) {
//Check for events
		done = processEvent(window, &game);

		process(&game);
		collisionDetect(&game);

//Render display
		doRender(renderer, &game);
	}

//Shutdown game and unload all memory
	SDL_DestroyTexture(game.star);
	SDL_DestroyTexture(game.manFrames[0]);
	SDL_DestroyTexture(game.manFrames[1]);
	SDL_DestroyTexture(game.brick);
	if (game.label != NULL)
		SDL_DestroyTexture(game.label);

//Close and destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(game.font);
	TTF_Quit();

//Clean up
	SDL_Quit();
	return 0;
}
