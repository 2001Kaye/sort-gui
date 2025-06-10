#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "sort_algorithm.h"
#include <random>

class QuickSort : public SortAlgorithm {
public:
    enum PivotType {
        FIRST = 0,
        MIDDLE = 1,
        LAST = 2,
        RANDOM = 3
    };

    QuickSort(PivotType pivotType = FIRST) : m_pivotType(pivotType) {}

    void sort(std::vector<Student>& students, CompareKey key) override {
        if (!students.empty()) {
            quickSort(students, 0, students.size() - 1, key);
        }
    }

    QString getName() const override {
        QString name = QString::fromLocal8Bit("Äü Á¤·Ä (ÇÇº¿: ");
        switch (m_pivotType) {
        case FIRST: name += QString::fromLocal8Bit("Ã¹¹øÂ°)"); break;
        case MIDDLE: name += QString::fromLocal8Bit("Áß°£)"); break;
        case LAST: name += QString::fromLocal8Bit("¸¶Áö¸·)"); break;
        case RANDOM: name += QString::fromLocal8Bit("·£´ý)"); break;
        }
        return name;
    }

    void setPivotType(PivotType type) {
        m_pivotType = type;
    }

    PivotType getPivotType() const {
        return m_pivotType;
    }

private:
    PivotType m_pivotType;
    std::mt19937 rng{std::random_device{}()};

    int choosePivot(int left, int right) {
        switch (m_pivotType) {
        case FIRST: return left;
        case MIDDLE: return left + (right - left) / 2;
        case LAST: return right;
        case RANDOM: return std::uniform_int_distribution<int>(left, right)(rng);
        default: return left;
        }
    }

    int partition(std::vector<Student>& arr, int left, int right, CompareKey key) {
        int pivotIdx = choosePivot(left, right);
        std::swap(arr[left], arr[pivotIdx]);

        Student pivot = arr[left];
        int low = left + 1;
        int high = right;

        while (low <= high) {
            while (high >= low && isGreater(arr[high], pivot, key)) {
                high--;
            }

            while (low <= high && isLessEqual(arr[low], pivot, key)) {
                low++;
            }

            if (low < high) {
                std::swap(arr[low], arr[high]);
                low++;
                high--;
            }
        }
        std::swap(arr[left], arr[high]);
        return high;
    }

    void quickSort(std::vector<Student>& arr, int left, int right, CompareKey key) {
        if (left < right) {
            int pi = partition(arr, left, right, key);
            quickSort(arr, left, pi - 1, key);
            quickSort(arr, pi + 1, right, key);
        }
    }
};

#endif // QUICK_SORT_H
