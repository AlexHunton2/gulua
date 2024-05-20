#include "util/util.hpp"

void util_lowercase(std::string *src) {
	std::transform(src->begin(), src->end(), src->begin(),
    [](unsigned char c){ return std::tolower(c); });
}