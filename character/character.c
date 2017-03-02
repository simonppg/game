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
    c->rect.w = 10;
    c->rect.h = 10;

    c->renderer = r;
}

void Character_draw(const Character *c)
{
    if(c == NULL)
        return;

    const SDL_Rect *rect = NULL;
    rect = &c->rect;
    SDL_SetRenderDrawColor(c->renderer,
            (Uint8) 255,
            (Uint8) 0,
            (Uint8) 0,
            (Uint8) 255);
    SDL_RenderDrawRect(c->renderer, rect);
}
