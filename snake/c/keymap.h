#ifndef __KEYMAP_H_
#define __KEYMAP_H_

#include "actions.h"
#include "state.h"

static const key_action KEY_ACTIONS[5] = {&escape, &moveNorth, &moveWest,
                                          &moveSouth, &moveEast};

void handleEvents(SDL_Event *e, State *state, bool *quit);
void _dispatchKey(SDL_Keycode kc, State *state);

#endif // __KEYMAP_H_
