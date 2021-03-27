#include "list.h"
#include <stdlib.h>

List *newList(Point elem) {
  List *list = malloc(sizeof(List));
  list->car = elem;
  list->cdr = NULL;
  return list;
}

Point getCar(List *list) { return list->car; }

List *getCdr(List *list) { return list->cdr; }

List *setCar(List *list, Point elem) {
  list->car = elem;
  return list;
}

List *setCdr(List *list, List *cdr) {
  list->cdr = cdr;
  return list;
}

List *cons(List *list, Point elem) {
  if (getCdr(list) == NULL) {
    List *cdr = newList(elem);
    setCdr(list, cdr);
  } else {
    cons(getCdr(list), elem);
  }
  return list;
}

int len(List *const list) {
  int length = 0;
  List *const *pList = &list;
  while (*pList != NULL) {
    ++length;
    List *next = getCdr(*pList);
    pList = &next;
  }
  return length;
}
