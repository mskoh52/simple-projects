#ifndef __POINT_H_
#define __POINT_H_

#include <stdbool.h>

typedef struct Point {
  int x;
  int y;
} Point;

Point point(int x, int y);

Point add(Point a, Point b);
Point mul(Point a, Point b);
bool eq(Point a, Point b);

#endif // __POINT_H_
