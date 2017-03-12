#include <stdlib.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "character.h"
#include "utils.h"

struct Character
{
    SDL_Rect rect;
    SDL_Renderer *renderer;
    Vector *vector;
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
    c->rect.w = 50;
    c->rect.h = 50;

    c->renderer = r;
    c->vector = Vector_new(0, 0);
}

void Character_draw(const Character *c)
{
    if(c == NULL)
        return;

    SDL_SetRenderDrawColor( c->renderer, 0, 0, 255, 255 );

    SDL_RenderFillRect( c->renderer, &c->rect );

    SDL_RenderPresent(c->renderer);
}

/*
 * Character_update: update all the properties of the character, like position,
 * size, speed, etc...
 */
void Character_update(Character *c)
{
    Vector_update(c->vector,
            Vector_get_x(c->vector) + 1,
            Vector_get_y(c->vector) + 1);

    c->rect.x = Vector_get_x(c->vector);
    c->rect.y = Vector_get_y(c->vector);
}
