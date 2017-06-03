#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "window_manager.h"
#include "player.h"

typedef struct Game Game;
struct Game {
    bool running;
    Window_manager* wm;
    Player* player;
    SDL_Event e;
};

static Game* Game_new();
static void Game_clean(Game* g);
static int init(Game* g);
static void Game_loop(Game* g);
static void eventHandler(Game *g);
static void draw(Game *g);

static Game* Game_new()
{
    Game* g = NULL;

    g = (Game *) malloc(sizeof(Game));
    init(g);
    return g;
}

static void Game_clean(Game* g)
{
    if(g == NULL)
        return;

    Player_clear(g->player);
    WM_clean(g->wm);
}

static int init(Game* g)
{
    g->wm = WM_new();
    assert(g->wm != NULL);

    if(g->wm == NULL)
    {
        printf("SDL_Error");
        return -1;
    }

    SDL_Renderer* r = WM_get_renderer(g->wm);
    g->player = Player_new(r);
    g->running = true;
    return 0;
}

static void Game_loop(Game* g)
{
    while(g->running)
    {
        eventHandler(g);
        draw(g);
    }
}

static void eventHandler(Game *g)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
                g->running = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        g->running = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                g->running = false;
                break;
            default:
                break;
        }
    }

    const Uint8 *k_state = SDL_GetKeyboardState(NULL);
    Player_update(g->player, k_state);

}

static void draw(Game *g)
{
    SDL_SetRenderDrawColor( WM_get_renderer(g->wm), 255, 255, 255, 255 );
    SDL_RenderClear( WM_get_renderer(g->wm) );
    Player_draw(g->player);
}

int main()
{
    Game* g = NULL;
    g = Game_new();

    Game_loop(g);

    Game_clean(g);

    return 0;
}
