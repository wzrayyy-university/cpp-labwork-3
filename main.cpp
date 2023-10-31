#include <iostream>
#include <fstream>
#include "lib/ArgumentParser.h"
#include "lib/TSVParser.h"
#include "lib/Sandpile.h"

void PrintInitialValues(PointWithValue* initial_values, std::size_t initial_size) {
  for (std::size_t i = 0; i < initial_size; ++i) {
    std::cout << initial_values[i].x << " " << initial_values[i].y << " " << initial_values[i].value << '\n';
  }
}

int main( int argc, char** argv ) {
  Config config = ArgumentParser::ParseArguments(argc, argv);
  std::ifstream file(config.input_filename);
  ParsedTSV parsed_tsv = ParseTSV(file);
  Sandpile sp(parsed_tsv.points, parsed_tsv.size, parsed_tsv.absolute_values);
  uint64_t counter = 0;

  while (sp.Iterate() && counter < config.max_iter) {
    ++counter;
    if (config.freq != 0 && counter % config.freq == 0) {
      sp.PrintCurrentState();
      std::cout << counter << std::endl;
      std::cout << "\n";
    }
  }
  sp.PrintCurrentState();
  std::cout << counter << std::endl;
  std::cout << "\n";

  return 0;
}
