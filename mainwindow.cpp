#include "mainwindow.h"
#include "ui_mainwindow.h"

// #include "algorithms/insertion_sort.h"
#include "algorithms/quick_sort.h"
#include "algorithms/merge_sort.h"
#include "random_util.h"

#define toKor(str) QString::fromLocal8Bit(str)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 콤보박스 초기화
    ui->sortKeyCombo->addItem(toKor("학번"), static_cast<int>(CompareKey::ID));
    ui->sortKeyCombo->addItem(toKor("이름"), static_cast<int>(CompareKey::NAME));
    ui->sortKeyCombo->addItem(toKor("성적"), static_cast<int>(CompareKey::SCORE));

    ui->pivotCombo->addItem(toKor("첫번째"), static_cast<int>(QuickSort::FIRST));
    ui->pivotCombo->addItem(toKor("중간"), static_cast<int>(QuickSort::MIDDLE));
    ui->pivotCombo->addItem(toKor("마지막"), static_cast<int>(QuickSort::LAST));
    ui->pivotCombo->addItem(toKor("랜덤"), static_cast<int>(QuickSort::RANDOM));

    // 테이블 설정
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({toKor("학번"), toKor("이름"), toKor("성적")});

    // 시그널 연결
    connect(ui->sortBtn, &QPushButton::clicked, this, &MainWindow::onSortBtnClicked);
    connect(ui->resetBtn, &QPushButton::clicked, this, &MainWindow::onResetBtnClicked);
    connect(ui->shuffleBtn, &QPushButton::clicked, this, &MainWindow::onShuffleBtnClicked);
    connect(ui->pivotCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onPivotComboChanged);

    // 데이터 로드 및 테이블 업데이트
    loadDummyData();
    updateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDummyData() {
    students.clear();
    originalStudents.clear();

    // 5000개의 더미 데이터 생성
    for (int i = 0; i < 5000; i++) {
        Student student(
            1000 + i,
            toKor("학생") + QString::number(i),
            std::round(RandomUtil::getRandomDouble(0.0, 4.5) * 100) / 100.0
            );
        originalStudents.push_back(student);
    }

    students = originalStudents;
}

void MainWindow::updateTable() {
    ui->tableWidget->setRowCount(students.size());

    for (size_t i = 0; i < students.size(); i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(students[i].id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(students[i].name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(students[i].score, 'f', 2)));
    }
}

void MainWindow::log(const QString& msg) {
    ui->logEdit->append(msg);
}

CompareKey MainWindow::getCurrentSortKey() const {
    return static_cast<CompareKey>(ui->sortKeyCombo->currentData().toInt());
}

void MainWindow::onSortBtnClicked() {
    CompareKey compKey = getCurrentSortKey();
    QString keyName = ui->sortKeyCombo->currentText();

    // 각 정렬 알고리즘에 대한 복사본 생성
    std::vector<Student> insertionData = students;
    std::vector<Student> quickData = students;
    std::vector<Student> mergeData = students;

    // 삽입 정렬 실행 및 시간 측정
    auto insertionTime = insertionSort.execute(insertionData, compKey);

    // 퀵 정렬 실행 및 시간 측정
    auto quickTime = quickSort.execute(quickData, compKey);

    // 병합 정렬 실행 및 시간 측정
    auto mergeTime = mergeSort.execute(mergeData, compKey);

    // 로그 출력
    log(toKor("- 정렬 기준: ") + keyName);
    log(toKor("- 삽입 정렬: %1 μs").arg(insertionTime.count()));
    log(toKor("- 퀵 정렬(%1): %2 μs").arg(ui->pivotCombo->currentText()).arg(quickTime.count()));
    log(toKor("- 병합 정렬: %1 μs").arg(mergeTime.count()));

    // 정렬된 데이터로 테이블 업데이트 (가장 빠른 병합 정렬 결과 사용)
    students = mergeData;
    updateTable();
}

void MainWindow::onResetBtnClicked() {
    students = originalStudents;
    updateTable();
    log(toKor("데이터가 초기 상태로 재설정되었습니다."));
}

void MainWindow::onShuffleBtnClicked() {
    RandomUtil::shuffle(students.begin(), students.end());
    updateTable();
    log(toKor("데이터가 무작위로 섞였습니다."));
}

void MainWindow::onPivotComboChanged(int index) {
    quickSort.setPivotType(static_cast<QuickSort::PivotType>(index));
}
