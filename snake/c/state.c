#include "state.h"
#include "dirqueue.h"
#include <stdio.h>
#include <stdlib.h>

State *initState(Point worldSize) {
  State *state = malloc(sizeof(State));

  state->dead = true;
  state->currentDirection = point(1, 0);
  state->direction = newDirQ();
  state->apple = point(rand() % worldSize.x, rand() % worldSize.y);

  state->futureSnakeBit = malloc(sizeof(Point));
  state->futureSnakeBit = NULL;

  Point mid = {worldSize.x / 2, worldSize.y / 2};
  List *snakeBits = newList(mid);
  cons(snakeBits, add(mid, point(-1, 0)));
  cons(snakeBits, add(mid, point(-2, 0)));
  state->snakeBits = snakeBits;

  state->worldSize = worldSize;

  return state;
}

void _isDead(State *state) {
  Point head = getCar(state->snakeBits);

  List *next = getCdr(state->snakeBits);
  List *const *pSnakeBits = &next;
  bool collidedWithSelf = false;
  while (*pSnakeBits != NULL && !collidedWithSelf) {
    collidedWithSelf = eq(getCar(*pSnakeBits), head);
    List *next = getCdr(*pSnakeBits);
    pSnakeBits = &next;
  }

  int worldx = state->worldSize.x;
  int worldy = state->worldSize.y;

  if (collidedWithSelf || head.x == worldx || head.y == worldy || head.x < 0 ||
      head.y < 0)
    state->dead = true;
}

Point _validateNextDirection(Point currentDirection, Point maybeNextDirection) {
  return (eq(maybeNextDirection, point(0, 0)) ||
          eq(currentDirection, mul(maybeNextDirection, point(-1, -1))))
             ? currentDirection
             : maybeNextDirection;
}

void updateState(State *state) {
  Point head = getCar(state->snakeBits);
  state->currentDirection =
      _validateNextDirection(state->currentDirection, pop(state->direction));
  List *newHead = newList(add(head, state->currentDirection));

  _isDead(state);

  // drop the last element
  List *const *pSnakeBits = &state->snakeBits;
  while (getCdr(getCdr(*pSnakeBits)) != NULL) {
    List *next = getCdr(*pSnakeBits);
    pSnakeBits = &next;
  }
  setCdr(*pSnakeBits, NULL);
  // reattach to newHead
  setCdr(newHead, state->snakeBits);
  state->snakeBits = newHead;

  // eat the apple
  if (eq(getCar(newHead), state->apple)) {
    if (!state->futureSnakeBit)
      state->futureSnakeBit = malloc(sizeof(Point));
    *state->futureSnakeBit = state->apple;
    state->apple =
        point(rand() % state->worldSize.x, rand() % state->worldSize.y);
  }

  // extend the snake
  if (state->futureSnakeBit &&
      eq(getCar(*pSnakeBits), *state->futureSnakeBit)) {
    setCdr(*pSnakeBits, newList(*state->futureSnakeBit));
    free(state->futureSnakeBit);
    state->futureSnakeBit = NULL;
  }
}
