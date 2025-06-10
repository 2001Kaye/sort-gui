#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <chrono>
#include "algorithms/insertion_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/merge_sort.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onSortBtnClicked();
    void onResetBtnClicked();
    void onShuffleBtnClicked();
    void onPivotComboChanged(int index);

private:
    Ui::MainWindow *ui;
    std::vector<Student> students;
    std::vector<Student> originalStudents;
    InsertionSort insertionSort;
    QuickSort quickSort;
    MergeSort mergeSort;

    void loadDummyData();
    void updateTable();
    void log(const QString& msg);
    CompareKey getCurrentSortKey() const;
};
#endif // MAINWINDOW_H
