#ifndef QUEUE_H_
#define QUEUE_H_

#include "Types.h"

struct StackMember {
  Point point;
  StackMember* next;
};

class Stack {
 private:
  StackMember* first = nullptr;
  std::size_t size = 0;
 public:
  void Add(Point point);
  Point Get();
  std::size_t Count() const;
  bool IsEmpty() const;
};

#endif // QUEUE_H_
