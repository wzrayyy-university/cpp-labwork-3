#include "ErrorMessage.h"

#include <iostream>

void PrintHelpMessage(bool is_error, const char* filepath) {
  const char options_text[] = "Options:\n"
                              "\t-i, --input_filename=FILENAME\t\tSet input_filename filename.\n"
                              "\t-o, --output_filename\t\tPath to output_filename directory.\n"
                              "\t-m --max-iter=N\tMax amount of iterations to do.\n"
                              "\t-f --freq=N\tImage output_filename frequency\n";
  if (is_error) {
    std::cerr << "\"Usage:\\n\"\n";
    std::cerr << "\t " << filepath << " [OPTIONS] [FILE]\n\n";
    std::cerr << options_text;
  } else {
    std::cout << "\"Usage:\\n\"\n";
    std::cout << "\t " << filepath << " [OPTIONS] [FILE]\n\n";
    std::cout << options_text;
  }
};

void ErrorMessage(ErrorCodes error_code, char* argument, const char* filepath) {
  switch (error_code) {
  case ErrorCodes::kFilenameMissing: {
    std::cerr << "ARGUMENT ERROR: Missing filename" << std::endl;
    break;
  }
  case ErrorCodes::kFileUnavailable: {
    std::cerr << "ERROR: Unable to open " << argument << std::endl;
    break;
  }
  case ErrorCodes::kWrongArgument: {
    std::cerr << "ARGUMENT ERROR: " << argument << " doesn't exist" << std::endl;
    break;
  }
  }
  PrintHelpMessage(true, filepath);
  exit(EXIT_FAILURE);
};
