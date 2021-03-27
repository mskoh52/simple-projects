#include "../list.h"
#include "../point.h"
#include <assert.h>
#include <stdio.h>

int main() {
  Point p = {1, 1};
  Point p2 = {2, 2};
  Point p3 = {3, 3};

  List *list = newList(p);
  assert(getCdr(list) == NULL);

  cons(list, p2);
  cons(list, p3);

  assert(getCdr(list) != NULL);
  assert(eq(getCar(list), (Point){1, 1}));
  assert(eq(getCar(getCdr(list)), (Point){2, 2}));
  assert(eq(getCar(getCdr(getCdr(list))), (Point){3, 3}));
  assert(getCdr(getCdr(getCdr(list))) == NULL);

  printf("PASSED!\n");
  return 0;
}
