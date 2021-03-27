#ifndef __ACTIONS_H_
#define __ACTIONS_H_

#include "state.h"
#include <SDL2/SDL_events.h>

typedef void (*key_action)(State *);

void moveNorth(State *state);
void moveEast(State *state);
void moveSouth(State *state);
void moveWest(State *state);
void escape(State *state);

#endif // __ACTIONS_H_
