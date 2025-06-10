#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "sort_algorithm.h"

class InsertionSort : public SortAlgorithm {
public:
    void sort(std::vector<Student>& students, CompareKey key)
    {
        for (int i = 1; i < students.size(); i++) {
            Student key_student = students[i];
            int j = i - 1;

            while (j >= 0 && isGreater(students[j], key_student, key)) {
                students[j + 1] = students[j];
                j--;
            }
            students[j + 1] = key_student;
        }
    }

    QString getName() const override {
        return QString::fromLocal8Bit("삽입 정렬");
    }
};

#endif // INSERTION_SORT_H
