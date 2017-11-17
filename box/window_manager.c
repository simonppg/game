#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "window_manager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct _window_manager {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

static void init(Window_manager *wm);

Window_manager* WM_new()
{
    Window_manager* wm = NULL;

    wm = (Window_manager *) malloc(sizeof(Window_manager));

    if(wm != NULL)
        init(wm);

    return wm;
}

static void init(Window_manager *wm)
{
    SDL_Init(SDL_INIT_VIDEO);

    wm->window = SDL_CreateWindow("Game window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

    wm->renderer = SDL_CreateRenderer(wm->window,
            -1,
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC);
}

void WM_clean(Window_manager* wm)
{
    SDL_DestroyWindow( wm->window );
    SDL_Quit();
}

SDL_Renderer* WM_get_renderer(Window_manager* wm)
{
    return wm->renderer;
}

SDL_Window* WM_get_window(Window_manager* wm)
{
    return wm->window;
}
