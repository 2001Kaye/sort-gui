#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "sort_algorithm.h"

class MergeSort : public SortAlgorithm {
public:
    void sort(std::vector<Student>& students, CompareKey key) override {
        if (!students.empty()) {
            std::vector<Student> temp(students.size());
            mergeSort(students, temp, 0, students.size() - 1, key);
        }
    }

    QString getName() const override {
        return QString::fromLocal8Bit("병합 정렬");
    }

private:
    void merge(std::vector<Student>& arr, std::vector<Student>& temp, int left, int middle, int right, CompareKey key) {
        int i = left;
        int j = middle + 1;
        int k = left;

        while (i <= middle && j <= right) {
            if (isLessEqual(arr[i], arr[j], key)) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= middle) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (int idx = left; idx <= right; idx++) {
            arr[idx] = temp[idx];
        }
    }

    void mergeSort(std::vector<Student>& arr, std::vector<Student>& temp, int left, int right, CompareKey key) {
        if (left < right) {
            int middle = left + (right - left) / 2;
            mergeSort(arr, temp, left, middle, key);
            mergeSort(arr, temp, middle + 1, right, key);
            merge(arr, temp, left, middle, right, key);
        }
    }
};

#endif // MERGE_SORT_H
