#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef struct Character Character;

Character* Character_new(SDL_Renderer* r);
void Character_draw(const Character *c);
void Character_update(Character *c, const Uint8 *k_state);

#endif
