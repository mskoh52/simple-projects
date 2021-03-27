#ifndef __STATE_H_
#define __STATE_H_

#include "dirqueue.h"
#include "list.h"
#include "point.h"
#include <stdbool.h>

typedef struct State {
  bool dead;
  Point currentDirection;
  DirQ *direction;
  Point apple;
  Point *futureSnakeBit;
  List *snakeBits;
  Point worldSize;
} State;

State *initState(Point worldSize);
void updateState(State *state);

#endif // __STATE_H_
