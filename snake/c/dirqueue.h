#ifndef __DIRQUEUE_H_
#define __DIRQUEUE_H_

#include "point.h"

typedef struct DirQ {
  Point fst;
  Point snd;
  int len;
} DirQ;

DirQ *newDirQ();
void append(DirQ *q, Point p);
Point pop(DirQ *q);

#endif // __DIRQUEUE_H_
