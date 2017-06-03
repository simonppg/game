#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct Player Player;

Player *Player_new(SDL_Renderer* r);
void Player_draw(const Player *c);
void Player_clear(Player *c);
void Player_update(Player *c, const Uint8 *k_state);

#endif
