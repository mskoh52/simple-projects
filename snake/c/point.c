#include "point.h"

Point point(int x, int y) { return (Point){x, y}; }

Point add(Point a, Point b) { return (Point){a.x + b.x, a.y + b.y}; }
Point mul(Point a, Point b) { return (Point){a.x * b.x, a.y * b.y}; }
bool eq(Point a, Point b) { return ((a.x == b.x) && (a.y == b.y)); }
