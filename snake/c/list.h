#ifndef __LIST_H_
#define __LIST_H_

#include "point.h"

typedef struct List {
  Point car;
  struct List *cdr;
} List;

List *newList(Point elem);
Point getCar(List *list);
List *getCdr(List *list);
List *setCar(List *list, Point elem);
List *setCdr(List *list, List *cdr);
List *cons(List *list, Point elem);
int len(List *const list);

#endif // __LIST_H_
