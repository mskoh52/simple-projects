#include "dirqueue.h"
#include <stdlib.h>

DirQ *newDirQ() {
  DirQ *ret = malloc(sizeof(DirQ));
  ret->fst = point(0, 0);
  ret->snd = point(0, 0);
  return ret;
}

void append(DirQ *q, Point p) {
  if (q->len == 0) {
    q->fst = p;
    q->len = 1;
    return;
  } else if (q->len == 1) {
    q->snd = p;
  } else {
    q->fst = q->snd;
    q->snd = p;
  }
  q->len = 2;
}

Point pop(DirQ *q) {
  if (q->len == 0)
    return point(0, 0);

  Point p = q->fst;
  q->fst = q->snd;
  --q->len;
  return p;
}
