#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include <vector>
#include <chrono>
#include "student.h"

class SortAlgorithm {
public:
    virtual ~SortAlgorithm() = default;
    virtual void sort(std::vector<Student>& students, CompareKey key) = 0;
    virtual QString getName() const = 0;

    // 정렬 수행 및 시간 측정
    std::chrono::microseconds execute(std::vector<Student>& students, CompareKey key) {
        auto start = std::chrono::high_resolution_clock::now();
        sort(students, key);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }

protected:
    // 비교 함수들
    bool isGreater(const Student& a, const Student& b, CompareKey key) const {
        switch (key) {
        case CompareKey::ID: return a.id > b.id;
        case CompareKey::NAME: return a.name > b.name;
        case CompareKey::SCORE: return a.score > b.score;
        default: return false;
        }
    }

    bool isLessEqual(const Student& a, const Student& b, CompareKey key) const {
        switch (key) {
        case CompareKey::ID: return a.id <= b.id;
        case CompareKey::NAME: return a.name <= b.name;
        case CompareKey::SCORE: return a.score <= b.score;
        default: return false;
        }
    }
};

#endif // SORT_ALGORITHM_H
