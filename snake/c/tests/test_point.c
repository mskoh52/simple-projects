#include "../point.h"
#include <assert.h>
#include <stdio.h>

int main() {
  Point zero = point(0, 0);
  Point x = point(1, 0);
  Point y = point(0, 1);
  Point z = point(1, 1);
  Point u = point(-1, 0);
  Point v = point(0, -1);
  Point w = point(-1, -1);
  Point a = point(300, 0);
  Point b = point(0, 40001);
  Point c = point(83, -199);

  assert(eq(zero, zero));
  assert(eq(x, x));
  assert(eq(y, y));
  assert(eq(z, z));
  assert(eq(u, u));
  assert(eq(v, v));
  assert(eq(w, w));
  assert(eq(a, a));
  assert(eq(b, b));
  assert(eq(c, c));

  assert(eq(zero, point(0, 0)));
  assert(eq(x, point(1, 0)));
  assert(eq(y, point(0, 1)));
  assert(eq(z, point(1, 1)));
  assert(eq(u, point(-1, 0)));
  assert(eq(v, point(0, -1)));
  assert(eq(w, point(-1, -1)));
  assert(eq(a, point(300, 0)));
  assert(eq(b, point(0, 40001)));
  assert(eq(c, point(83, -199)));

  // _ + zero = _
  assert(eq(add(zero, zero), zero));
  assert(eq(add(zero, x), x));
  assert(eq(add(zero, y), y));
  assert(eq(add(zero, z), z));
  assert(eq(add(zero, u), u));
  assert(eq(add(zero, v), v));
  assert(eq(add(zero, w), w));
  assert(eq(add(zero, a), a));
  assert(eq(add(zero, b), b));
  assert(eq(add(zero, c), c));

  assert(eq(add(x, x), point(2, 0)));
  assert(eq(add(x, y), point(1, 1)));
  assert(eq(add(z, z), point(2, 2)));

  // _ * zero = zero
  assert(eq(mul(zero, zero), zero));
  assert(eq(mul(zero, x), zero));
  assert(eq(mul(zero, y), zero));
  assert(eq(mul(zero, z), zero));
  assert(eq(mul(zero, u), zero));
  assert(eq(mul(zero, v), zero));
  assert(eq(mul(zero, w), zero));
  assert(eq(mul(zero, a), zero));
  assert(eq(mul(zero, b), zero));
  assert(eq(mul(zero, c), zero));

  // _ * z = _
  assert(eq(mul(z, x), x));
  assert(eq(mul(z, y), y));
  assert(eq(mul(z, z), z));
  assert(eq(mul(z, u), u));
  assert(eq(mul(z, v), v));
  assert(eq(mul(z, w), w));
  assert(eq(mul(z, a), a));
  assert(eq(mul(z, b), b));
  assert(eq(mul(z, c), c));

  assert(eq(mul(x, x), point(1, 0)));
  assert(eq(mul(x, point(2, 2)), point(2, 0)));
  assert(eq(mul(x, y), point(0, 0)));

  printf("PASSED!\n");
  return 0;
}
