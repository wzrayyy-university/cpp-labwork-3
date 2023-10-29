#ifndef TSV_PARSER_H_
#define TSV_PARSER_H_

#include <fstream>
#include "Types.h"

ParsedTSV ParseTSV(std::ifstream& file);

#endif // TSV_PARSER_H_