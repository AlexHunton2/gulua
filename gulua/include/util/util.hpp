#ifndef GULUA_UTIL
#define GULUA_UTIL

#include <string>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <random>

/* generateid.cpp */
std::string util_generateid();

/* lowercase.cpp */
void util_lowercase(std::string *s);

/* format.cpp */
std::string util_format(const std::string fmt_str, ...);

#endif