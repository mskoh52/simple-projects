#include "../state.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  State *state = initState(point(50, 50));

  assert(state->dead);
  assert(eq(state->currentDirection, point(1, 0)));
  assert(eq(state->direction->fst, point(0, 0)));
  assert(eq(state->direction->snd, point(0, 0)));
  assert(state->direction->len == 0);
  assert(state->futureSnakeBit == NULL);
  assert(eq(getCar(state->snakeBits), point(25, 25)));
  assert(eq(getCar(getCdr(state->snakeBits)), point(24, 25)));
  assert(eq(getCar(getCdr(getCdr(state->snakeBits))), point(23, 25)));
  assert(eq(state->worldSize, point(50, 50)));
  assert(state->apple.x >= 0 && state->apple.x < 50);
  assert(state->apple.y >= 0 && state->apple.y < 50);

  state->dead = false;
  state->apple = point(27, 25);

  updateState(state);

  assert(eq(getCar(state->snakeBits), point(26, 25)));
  assert(eq(getCar(getCdr(state->snakeBits)), point(25, 25)));
  assert(eq(getCar(getCdr(getCdr(state->snakeBits))), point(24, 25)));
  assert(state->futureSnakeBit == NULL);

  updateState(state);

  assert(eq(getCar(state->snakeBits), point(27, 25)));
  assert(eq(getCar(getCdr(state->snakeBits)), point(26, 25)));
  assert(eq(getCar(getCdr(getCdr(state->snakeBits))), point(25, 25)));
  assert(eq(*state->futureSnakeBit, point(27, 25)));
  assert(!eq(state->apple, *state->futureSnakeBit));

  append(state->direction, point(0, 1));
  updateState(state);

  assert(eq(getCar(state->snakeBits), point(27, 26)));
  assert(eq(getCar(getCdr(state->snakeBits)), point(27, 25)));
  assert(eq(getCar(getCdr(getCdr(state->snakeBits))), point(26, 25)));
  assert(eq(*state->futureSnakeBit, point(27, 25)));

  updateState(state);

  assert(eq(getCar(state->snakeBits), point(27, 27)));
  assert(eq(getCar(getCdr(state->snakeBits)), point(27, 26)));
  assert(eq(getCar(getCdr(getCdr(state->snakeBits))), point(27, 25)));
  assert(eq(getCar(getCdr(getCdr(getCdr(state->snakeBits)))), point(27, 25)));
  assert(state->futureSnakeBit == NULL);

  printf("PASSED!\n");
  return 0;
}
