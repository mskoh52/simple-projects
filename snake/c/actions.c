#include "actions.h"
#include "dirqueue.h"
#include "point.h"
#include <stdio.h>

void moveNorth(State *state) {
  printf("north\n");
  append(state->direction, point(0, -1));
};
void moveEast(State *state) {
  printf("east\n");
  append(state->direction, point(1, 0));
}
void moveSouth(State *state) {
  printf("south\n");
  append(state->direction, point(0, 1));
}
void moveWest(State *state) {
  printf("west\n");
  append(state->direction, point(-1, 0));
}
void escape(State *state) {
  printf("escape\n");
  state->dead = true;
}
