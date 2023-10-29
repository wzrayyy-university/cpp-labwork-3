#ifndef SANDPILE_H_
#define SANDPILE_H_

#include <cstdint>
#include "Types.h"
#include "Stack.h"

static const uint8_t kInitialFlag = 0b10000000;
static const uint16_t kFieldSize = std::numeric_limits<uint16_t>::max();

struct SandpileState {
  uint8_t** values;
  std::size_t size;
};

struct ResizeParams {
  bool copy_x = false;
  bool copy_y = false;
  bool resize_x = false;
  bool resize_y = false;
  bool is_required = false;
};

class Sandpile {
 private:
  uint8_t** values_;
  AbsoluteValues absolute_values_;
  OffsetValues offset_values_;
  PointWithValue* initial_values_;
  std::size_t initial_values_size_;
  Stack queue_;

//  ResizeParams GetResizeParams();
  void ResizeToFit(Point point);
  uint64_t GetValue(Point point);
  void SetValue(Point point, uint64_t value);
  void Scatter(Point point);

 public:
  Sandpile(PointWithValue* initial_values,
           std::size_t initial_values_size,
           AbsoluteValues absolute_values);
  bool Iterate();
  void PrintCurrentState();
};

#endif // SANDPILE_H_