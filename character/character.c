#include <stdlib.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "character.h"

struct Character
{
    SDL_Rect rect;
    SDL_Renderer* renderer;
};

static void init(Character* c, SDL_Renderer* r);

Character* Character_new(SDL_Renderer* r)
{
    Character* c = NULL;

    c = (Character *) malloc(sizeof(Character));

    if(c != NULL)
        init(c, r);
    return c;
}

static void init(Character* c, SDL_Renderer* r)
{
    if(c == NULL)
        return;

    c->rect.x = 0;
    c->rect.y = 0;
    c->rect.w = 100;
    c->rect.h = 100;

    c->renderer = r;
}

void Character_draw(const Character *c)
{
    if(c == NULL)
        return;

    //SDL_SetRenderDrawColor( c->renderer, 255, 0, 0, 255 );

    //SDL_RenderClear( c->renderer );

    SDL_SetRenderDrawColor( c->renderer, 0, 0, 255, 255 );

    SDL_RenderFillRect( c->renderer, &c->rect );

    SDL_RenderPresent(c->renderer);
}
