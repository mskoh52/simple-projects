#include "keymap.h"
#include <SDL2/SDL_events.h>

void handleEvents(SDL_Event *e, State *state, bool *quit) {
  while (SDL_PollEvent(e) != 0) {
    if (e->type == SDL_QUIT) {
      *quit = true;
    } else if (e->type == SDL_KEYDOWN) {
      _dispatchKey(e->key.keysym.sym, state);
    }
  }
}

void _dispatchKey(SDL_Keycode kc, State *state) {
  int i;
  switch (kc) {
  case SDLK_ESCAPE:
    i = 0;
    break;
  case SDLK_w:
    i = 1;
    break;
  case SDLK_a:
    i = 2;
    break;
  case SDLK_s:
    i = 3;
    break;
  case SDLK_d:
    i = 4;
    break;
  }
  KEY_ACTIONS[i](state);
}
