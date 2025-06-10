#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <random>
#include <algorithm>
#include <vector>

class RandomUtil {
public:
    static std::mt19937& getRng() {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        return rng;
    }

    template<typename Iter>
    static void shuffle(Iter begin, Iter end) {
        std::shuffle(begin, end, getRng());
    }

    static double getRandomDouble(double min, double max) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(getRng());
    }

    static int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getRng());
    }
};

#endif // RANDOMUTIL_H
