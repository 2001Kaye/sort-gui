#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

struct Student {
    int id;
    QString name;
    double score;

    Student(int _id = 0, const QString& _name = "", double _score = 0.0)
        : id(_id), name(_name), score(_score) {}
};

enum class CompareKey {
    ID,
    NAME,
    SCORE
};

#endif // STUDENT_H
