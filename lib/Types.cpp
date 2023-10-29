#include "Types.h"

bool Point::operator==(const Point& value) const {
  return x == value.x && y == value.y;
}
