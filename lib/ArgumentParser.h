#pragma once

#include <cstdint>
#include <limits>

struct Argument {
  const char* short_name;
  const char* full_name;
};

struct Arguments {
  static constexpr Argument kHelp = {"-h", "--help"};
  static constexpr Argument kInputFilename = {"-i", "--input_filename"};
  static constexpr Argument kOutputFilename = {"-o", "--output_filename"};
  static constexpr Argument kMaxIter = {"-m", "--max-iter"};
  static constexpr Argument kFreq = {"-f", "--freq"};
};

struct Config {
  char* input_filename{};
  char* output_filename{};
  uint64_t max_iter = std::numeric_limits<uint64_t>::max();
  uint64_t freq = 0;
};

class ArgumentParser {
 public:
  static Config ParseArguments(const int argc, char** argv);
};