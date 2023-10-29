#include <iostream>
#include <fstream>
#include "lib/TSVParser.h"
#include "lib/Sandpile.h"

void PrintInitialValues(PointWithValue* initial_values, std::size_t initial_size) {
  for (std::size_t i = 0; i < initial_size; ++i) {
    std::cout << initial_values[i].x << " " << initial_values[i].y << " " << initial_values[i].value << '\n';
  }
}

int main() {
  std::ifstream file("../test.tsv");

  ParsedTSV parsed_tsv = ParseTSV(file);
  Sandpile sp(parsed_tsv.points, parsed_tsv.size, parsed_tsv.absolute_values);
  uint64_t counter = 0;

  while (sp.Iterate()) {
    ++counter;
    // todo output to file every n-th iteration
    sp.PrintCurrentState();
    std::cout << "\n";
  }

  return 0;
}
