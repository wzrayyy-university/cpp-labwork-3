#include "Sandpile.h"
#include <iostream>

Sandpile::Sandpile(PointWithValue* initial_values,
                   std::size_t initial_values_size,
                   AbsoluteValues absolute_values)
  : absolute_values_(absolute_values),
    initial_values_(initial_values),
    initial_values_size_(initial_values_size) {

  values_ = new uint8_t* [kFieldSize];

  for (uint16_t i = 0; i < kFieldSize; ++i) {
    values_[i] = new uint8_t[kFieldSize];
  }

  for (std::size_t i = 0; i < initial_values_size_; ++i) {
    values_[initial_values_[i].x][initial_values_[i].y] = kInitialFlag;
  }
}

void Sandpile::ResizeToFit(Point point) {
  if (point.x < absolute_values_.min_x) {
    --absolute_values_.min_x;
  }
  if (point.x > absolute_values_.max_x) {
    ++absolute_values_.max_x;
  }
  if (point.y < absolute_values_.min_y) {
    --absolute_values_.min_y;
  }
  if (point.y > absolute_values_.max_y) {
    ++absolute_values_.max_y;
  }
}

uint64_t Sandpile::GetValue(Point point) {
  if (values_[point.x][point.y] == kInitialFlag) {
    for (std::size_t i = 0; i < initial_values_size_; ++i) {
      if (initial_values_[i] == point) {
        return initial_values_[i].value;
      }
    }
  }
  return values_[point.x][point.y];
}

void Sandpile::SetValue(Point point, uint64_t value) {
  if (values_[point.x][point.y] == kInitialFlag) {
    for (std::size_t i = 0; i < initial_values_size_; ++i) {
      if (initial_values_[i] == point) {
        initial_values_[i].value = value;
      }
    }
  } else {
    values_[point.x][point.y] = value;
  }
}

void Sandpile::Scatter(Point point) {
  ScatteredPoints points = {
    Point {static_cast<uint16_t>(point.x + 1), point.y},
    Point {static_cast<uint16_t>(point.x - 1), point.y},
    Point {point.x, static_cast<uint16_t>(point.y - 1)},
    Point {point.x, static_cast<uint16_t>(point.y + 1)},
  };

  SetValue(points.right, GetValue(points.right) + 1);
  ResizeToFit(points.right);
  SetValue(points.left, GetValue(points.left) + 1);
  ResizeToFit(points.left);
  SetValue(points.down, GetValue(points.down) + 1);
  ResizeToFit(points.down);
  SetValue(points.up, GetValue(points.up) + 1);
  ResizeToFit(points.up);
};

bool Sandpile::Iterate() {
  for (uint16_t x = absolute_values_.min_x; x <= absolute_values_.max_x; ++x) {
    for (uint16_t y = absolute_values_.min_y; y <= absolute_values_.max_y; ++y) {
      Point point {x, y};
      if (GetValue(point) >= 4) {
        queue_.Add(point); // todo dynamically manage the queue
      }
    }
  }

  std::size_t unstable_count = queue_.Count();

  while (!queue_.IsEmpty()) {
    Point point = queue_.Get();
    uint64_t value = GetValue(point);

    SetValue(point, value - 4);
    Scatter(point);
  }

  return unstable_count;
//  ResizeParams resize_params = GetResizeParams();
//  if (resize_params.is_required) {
//    ResizeToFit(resize_params);
//  } // todo resize
}

//ResizeParams Sandpile::GetResizeParams() {
//  ResizeParams params;
//
//  for (std::size_t i = 1; i < array_dimensions_.x - 1; ++i) {
//    if (values_[i][0] >= 4) {
//      params.copy_x = 1;
//      params.is_required = true;
//    }
//    if (values_[i][array_dimensions_.y - 1] >= 4) {
//      params.resize_x = 1;
//      params.is_required = true;
//    }
//  }
//
//  for (std::size_t i = 1; i < array_dimensions_.y - 1; ++i) {
//    if (values_[0][i] >= 4) {
//      params.copy_x = 1;
//      params.is_required = true;
//    }
//    if (values_[array_dimensions_.x-1][i] >= 4) {
//      params.resize_x = 1;
//      params.is_required = true;
//    }
//  }
//
//  return params; // fixme THIS DOESN'T WORK PROPERLY, USE JUST FOR TESTING.
//
//void Sandpile::ResizeToFit(ResizeParams params) {
//  uint16_t new_x_size = array_dimensions_.x + params.resize_x + params.copy_x;
//  uint16_t new_y_size = array_dimensions_.y + params.resize_y + params.copy_y;
//
//  uint8_t** tmp = new uint8_t* [new_x_size];
//
//  for (uint8_t i = 0; i < )
//
//  for (uint16_t i = params.copy_x; i < new_x_size - ; ++i) {
//    tmp[i] = new uint8_t[new_y_size];
//    for (uint16_t j = 0; j < new_y_size; ++j) {
//
//    }
//  }
//
//  array_dimensions_.x = new_x_size;
//  array_dimensions_.y = new_y_size;
//
//  values_ = tmp;
//}

void Sandpile::PrintCurrentState() {
  for (uint16_t x = absolute_values_.min_x - 4; x <= absolute_values_.max_x + 4; ++x) {
    for (uint16_t y = absolute_values_.min_y - 4; y <= absolute_values_.max_y + 4; ++y) {
      if (values_[x][y] == 0) {
        std::cout << " 0 ";
      } else {
        std::cout << " " << static_cast<uint16_t>(GetValue(Point{x, y})) << " ";
      }
    }
    std::cout << '\n';
  }
}
