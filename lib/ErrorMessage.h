#pragma once

enum class ErrorCodes {
  kFilenameMissing,
  kFileUnavailable,
  kWrongArgument,
};

void PrintHelpMessage(bool is_error, const char* filepath);

void ErrorMessage(ErrorCodes error_code, char* argument, const char* filepath);
