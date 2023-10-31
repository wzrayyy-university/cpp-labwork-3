#include "Stack.h"

void Stack::Add(Point point) {
  StackMember* member = new StackMember{point, first};

  first = member;
  ++size;
}

Point Stack::Get() {
  Point point = first->point;
  StackMember* next = first->next;
  --size;
  delete first;

  first = next;

  return point;
}

std::size_t Stack::Count() const {
  return size;
}

bool Stack::IsEmpty() const {
  return size == 0;
}