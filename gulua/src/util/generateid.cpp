#include "util/util.hpp"

std::string util_generateid() {
    // Random number generator
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd; // Seed for the random number engine
    std::mt19937 generator(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string randomString;
    for (int i = 0; i < 5; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}