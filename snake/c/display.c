#include "display.h"
#include "list.h"

SDL_Rect grid2px(Point p, Point worldSize, Point gridSize) {
  int w = gridSize.x / worldSize.x;
  int h = gridSize.y / worldSize.y;

  return (SDL_Rect){p.x * w, p.y * h, w, h};
}

void draw(const State *state, SDL_Renderer *renderer, int w, int h) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);

  // draw the apple
  SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);
  SDL_Rect fillRect = grid2px(state->apple, state->worldSize, point(w, h));
  SDL_RenderFillRect(renderer, &fillRect);

  // draw the snake
  SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);

  List *const *pSnakeBits = &state->snakeBits;
  while (*pSnakeBits != NULL) {
    SDL_Rect fillRect =
        grid2px(getCar(*pSnakeBits), state->worldSize, point(w, h));
    SDL_RenderFillRect(renderer, &fillRect);
    List *next = getCdr(*pSnakeBits);
    pSnakeBits = &next;
  }

  SDL_RenderPresent(renderer);
}
