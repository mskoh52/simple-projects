#include "display.h"
#include "keymap.h"
#include "point.h"
#include "state.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int WIDTH = 600;
int HEIGHT = 600;

void renderText(State *state, TTF_Font *font, SDL_Surface *surface,
                SDL_Renderer *renderer) {
  SDL_Color red = {0xFF, 0, 0};
  SDL_Color green = {0, 0xFF, 0};
}

int main() {
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return 1;
  }

  TTF_Init();

  SDL_Window *window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                                        SDL_WINDOW_SHOWN);
  if (!window)
    return 1;

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
    return 1;

  SDL_Color red = {255, 0, 0, 255};
  SDL_Color green = {0, 255, 0, 255};
  SDL_Color gray = {128, 128, 128, 255};
  TTF_Font *font =
      TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 36);
  TTF_Font *font2 =
      TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);

  State *state = NULL;
  int tick = 0;
  SDL_Event e;

  bool quit = false;
  char scorebuffer[1024];
  while (!quit) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Surface *surface = TTF_RenderText_Solid(font, "GAME OVER", red);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textureRect = {WIDTH / 2 - surface->w / 2,
                            HEIGHT / 2 - surface->h - 10, surface->w,
                            surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textureRect);

    if (state) {
      sprintf(scorebuffer, "score: %d", len(state->snakeBits));
    } else {
      strcpy(scorebuffer, " ");
    }
    SDL_Surface *surface2 = TTF_RenderText_Solid(font, scorebuffer, green);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Rect textureRect2 = {WIDTH / 2 - surface2->w / 2, HEIGHT / 2 + 10,
                             surface2->w, surface2->h};
    SDL_RenderCopy(renderer, texture2, NULL, &textureRect2);

    SDL_Surface *surface3 = TTF_RenderText_Solid(
        font2, "press any key to play, escape to quit", gray);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_Rect textureRect3 = {WIDTH / 2 - surface3->w / 2,
                             HEIGHT / 2 + surface2->h + surface3->h + 10,
                             surface3->w, surface3->h};
    SDL_RenderCopy(renderer, texture3, NULL, &textureRect3);

    SDL_RenderPresent(renderer);

    SDL_WaitEvent(&e);
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.sym == SDLK_ESCAPE) {
        quit = true;
      } else {
        state = initState(point(50, 50));
        state->dead = false;
      }
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface2);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface3);
    SDL_DestroyTexture(texture3);

    while (state && !state->dead) {
      if (tick == 0) {
        draw(state, renderer, WIDTH, HEIGHT);
        updateState(state);
      }
      handleEvents(&e, state, &quit);
      tick = (tick + 1) % 50;
      SDL_Delay(1);
    }
    SDL_Delay(1);
  }

  TTF_CloseFont(font);
  TTF_CloseFont(font2);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
