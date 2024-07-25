#include "util/util.hpp"

std::string util_generateid() {
	const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = sizeof(charset) - 1;

    // Random number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, max_index);

    std::string randomString;
    for (int i = 0; i < 5; ++i) {
        randomString += charset[distribution(generator)];
    }

    return randomString;
}