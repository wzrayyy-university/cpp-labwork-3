#include "ArgumentParser.h"

#include <cstring>
#include <stdexcept>
#include <string>

#include "ErrorMessage.h"

int CompareStrings(const char* lhs, const char* rhs) {
  for (int idx = 0; lhs[idx] != '\0' && rhs[idx] != '\0'; ++idx) {
    if (lhs[idx] != rhs[idx]) {
      return idx;
    }
  }
  return 0;
}

bool StartsWith(const char* str, const Argument& arg) {
  return CompareStrings(str, arg.short_name) == 0 || CompareStrings(str, arg.full_name) == 0;
}

std::size_t GetValueIndex(const char* str, const Argument arg) {
  if (CompareStrings(str, arg.full_name) == 0) {
    return strlen(arg.full_name);
  } else if (CompareStrings(str, arg.short_name) == 0) {
    return strlen(arg.short_name);
  }
  return 0;
}

uint64_t GetNumber(char** argv, int& i, const Argument& arg) {
  std::size_t value_idx = GetValueIndex(argv[i], arg);
  char* tmp_number = nullptr;
  if (argv[i][value_idx] == '\0') {
    tmp_number = argv[++i];
  } else if (argv[i][value_idx] == '=') {
    tmp_number = argv[i] + value_idx;
  } else {
    ErrorMessage(ErrorCodes::kWrongArgument, argv[i], argv[0]);
  }
  try {
    return std::stoull(tmp_number);
  } catch (std::invalid_argument& e) {
    ErrorMessage(ErrorCodes::kWrongArgument, argv[i], argv[0]);
  }
  exit(1);
};

char* GetString(char** argv, int& i, const Argument& arg) {
  std::size_t value_idx = GetValueIndex(argv[i], arg);
  if (argv[i][value_idx] == '\0') {
    return argv[++i];
  } else if (argv[i][value_idx] == '=') {
    return argv[i] + value_idx;
  } else {
    ErrorMessage(ErrorCodes::kWrongArgument, argv[i], argv[0]);
  }
  exit(1);
}

Config ArgumentParser::ParseArguments(const int argc, char** argv) {
  Config config;
  bool is_filename_set = false;
  bool is_output_set = false;

  for (int i = 1; i < argc; ++i) {
    if (StartsWith(argv[i], Arguments::kHelp)) {
      PrintHelpMessage(false, argv[0]);
    } else if (StartsWith(argv[i], Arguments::kFreq)) {
      config.freq = GetNumber(argv, i, Arguments::kFreq);
    } else if (StartsWith(argv[i], Arguments::kMaxIter)) {
      config.max_iter = GetNumber(argv, i, Arguments::kMaxIter);
    } else if (StartsWith(argv[i], Arguments::kInputFilename)) {
      config.input_filename = GetString(argv, i, Arguments::kInputFilename);
      is_filename_set = true;
    } else if (StartsWith(argv[i], Arguments::kOutputFilename)) {
      config.output_filename = GetString(argv, i, Arguments::kOutputFilename);
      is_output_set = true;
    } else {
      ErrorMessage(ErrorCodes::kWrongArgument, argv[i], argv[0]);
    }
  }
  if (!is_filename_set || !is_output_set) {
    ErrorMessage(ErrorCodes::kFilenameMissing, reinterpret_cast<char*>('\0'), argv[0]);
  }
  return config;
}