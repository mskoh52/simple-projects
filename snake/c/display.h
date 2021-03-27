#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "state.h"
#include <SDL2/SDL.h>

void draw(const State *state, SDL_Renderer *renderer, int w, int h);

#endif // __DISPLAY_H_
