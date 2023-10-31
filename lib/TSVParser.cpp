#include "TSVParser.h"
#include <limits>

std::size_t GetLinesCount(std::ifstream& file) {
  char _[64];
  std::size_t size = 0;
  while (file.getline(_, 64)) {
    ++size;
  }

  file.clear();
  file.seekg(0);

  return size;
}

//void Normalize(PointWithValue* points, OffsetValues offset_values, std::size_t lines_count) {
//  for (int i = 0; i < lines_count; ++i) {
//    points[i].x -= offset_values.x;
//    points[i].y -= offset_values.y;
//  }
//}

ParsedTSV ParseTSV(std::ifstream& file) {
  char line[64];
  std::size_t lines_count = GetLinesCount(file);
  PointWithValue* points = new PointWithValue[lines_count];
  std::size_t idx = 0;

  AbsoluteValues absolute_values;

  while (file.getline(line, 64)) {
    int16_t idx_x;
    int16_t idx_y;

    PointWithValue point{};

    sscanf(line, "%hd %hd %lu", &idx_x, &idx_y, &point.value);

    point.x = idx_x + std::numeric_limits<int16_t>::max() + 1;
    point.y = idx_y + std::numeric_limits<int16_t>::max() + 1;

    bool is_repeated = false;
    for (std::size_t i = 0; i < idx; ++i) {
      if (points[i].x == point.x && points[i].y == point.y) {
        is_repeated = true;
      }
    }

    if (is_repeated) {
      continue;
    }

    absolute_values.max_x = std::max(point.x, absolute_values.max_x);
    absolute_values.max_y = std::max(point.y, absolute_values.max_y);
    absolute_values.min_x = std::min(point.x, absolute_values.min_x);
    absolute_values.min_y = std::min(point.y, absolute_values.min_y);

    points[idx] = point;
    ++idx;
  }

  OffsetValues offset_values;
  offset_values.y = absolute_values.min_y;
  offset_values.x = absolute_values.min_x;

  Size array_dimensions{static_cast<uint16_t>(absolute_values.max_x - absolute_values.min_x + 1),
                        static_cast<uint16_t>(absolute_values.max_y - absolute_values.min_y + 1)};

  //  Normalize(points, offset_values, idx);
  return ParsedTSV{points, absolute_values, offset_values, array_dimensions, idx};
}
