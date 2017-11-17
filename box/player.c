#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "player.h"
#include "utils.h"

struct Player 
{
    SDL_Rect rect;
    SDL_Renderer *renderer;
    Vector *position;
};

static void init(Player * c, SDL_Renderer* r);
static void update_position(Player *c, const Uint8 *k_state);
static void move_to_left(Player *c);
static void move_to_right(Player *c);

Player *Player_new(SDL_Renderer* r)
{
    Player * c = NULL;

    c = (Player *) malloc(sizeof(Player ));

    if(c != NULL)
        init(c, r);
    return c;
}

void Player_clear(Player *c)
{
    if(c != NULL)
    {
        Vector_clear(c->position);
        free(c);
    }
}

static void init(Player * c, SDL_Renderer* r)
{
    if(c == NULL)
        return;

    c->rect.x = 0;
    c->rect.y = 0;
    c->rect.w = 50;
    c->rect.h = 50;

    c->renderer = r;
    c->position = Vector_new(0, 0);
}

void Player_draw(const Player *c)
{
    if(c == NULL)
        return;

    SDL_SetRenderDrawColor( c->renderer, 0, 0, 255, 255 );

    SDL_RenderFillRect( c->renderer, &c->rect );

    SDL_RenderPresent(c->renderer);
}

/*
 * Player : update all the properties of the Player , like position,
 * size, speed, etc...
 */
void Player_update(Player *c, const Uint8 *k_state)
{
    update_position(c, k_state);
    c->rect.x = Vector_get_x(c->position);
    c->rect.y = Vector_get_y(c->position);
}

static void update_position(Player *c, const Uint8 *k_state)
{
    if(k_state[SDL_SCANCODE_LEFT]) {
            move_to_left(c);
    } else if(k_state[SDL_SCANCODE_RIGHT]) {
            move_to_right(c);
    }
}

static void move_to_left(Player *c)
{
    Vector_update(c->position,
            Vector_get_x(c->position) - 1,
            Vector_get_y(c->position));

}

static void move_to_right(Player *c)
{
    Vector_update(c->position,
            Vector_get_x(c->position) + 1,
            Vector_get_y(c->position));

}
