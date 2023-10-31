#pragma once

#include <cstdint>
#include <limits>

struct Point {
  uint16_t x;
  uint16_t y;
  bool operator==(const Point& value) const;
};

struct PointWithValue : Point {
  uint64_t value;
};

struct ScatteredPoints {
  Point right;
  Point left;
  Point down;
  Point up;
};

struct AbsoluteValues {
  uint16_t max_x = 0;
  uint16_t max_y = 0;
  uint16_t min_x = std::numeric_limits<uint16_t>::max();
  uint16_t min_y = std::numeric_limits<uint16_t>::max();
};

struct OffsetValues {
  uint16_t x = 0;
  uint16_t y = 0;
};

struct Size {
  uint16_t x;
  uint16_t y;
};

struct ParsedTSV {
  PointWithValue* points = nullptr;
  AbsoluteValues absolute_values;
  OffsetValues offset_values;
  Size array_dimensions;
  std::size_t size = 0;
};
