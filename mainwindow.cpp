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

    // �޺��ڽ� �ʱ�ȭ
    ui->sortKeyCombo->addItem(toKor("�й�"), static_cast<int>(CompareKey::ID));
    ui->sortKeyCombo->addItem(toKor("�̸�"), static_cast<int>(CompareKey::NAME));
    ui->sortKeyCombo->addItem(toKor("����"), static_cast<int>(CompareKey::SCORE));

    ui->pivotCombo->addItem(toKor("ù��°"), static_cast<int>(QuickSort::FIRST));
    ui->pivotCombo->addItem(toKor("�߰�"), static_cast<int>(QuickSort::MIDDLE));
    ui->pivotCombo->addItem(toKor("������"), static_cast<int>(QuickSort::LAST));
    ui->pivotCombo->addItem(toKor("����"), static_cast<int>(QuickSort::RANDOM));

    // ���̺� ����
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({toKor("�й�"), toKor("�̸�"), toKor("����")});

    // �ñ׳� ����
    connect(ui->sortBtn, &QPushButton::clicked, this, &MainWindow::onSortBtnClicked);
    connect(ui->resetBtn, &QPushButton::clicked, this, &MainWindow::onResetBtnClicked);
    connect(ui->shuffleBtn, &QPushButton::clicked, this, &MainWindow::onShuffleBtnClicked);
    connect(ui->pivotCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onPivotComboChanged);

    // ������ �ε� �� ���̺� ������Ʈ
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

    // 5000���� ���� ������ ����
    for (int i = 0; i < 5000; i++) {
        Student student(
            1000 + i,
            toKor("�л�") + QString::number(i),
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

    // �� ���� �˰��� ���� ���纻 ����
    std::vector<Student> insertionData = students;
    std::vector<Student> quickData = students;
    std::vector<Student> mergeData = students;

    // ���� ���� ���� �� �ð� ����
    auto insertionTime = insertionSort.execute(insertionData, compKey);

    // �� ���� ���� �� �ð� ����
    auto quickTime = quickSort.execute(quickData, compKey);

    // ���� ���� ���� �� �ð� ����
    auto mergeTime = mergeSort.execute(mergeData, compKey);

    // �α� ���
    log(toKor("- ���� ����: ") + keyName);
    log(toKor("- ���� ����: %1 ��s").arg(insertionTime.count()));
    log(toKor("- �� ����(%1): %2 ��s").arg(ui->pivotCombo->currentText()).arg(quickTime.count()));
    log(toKor("- ���� ����: %1 ��s").arg(mergeTime.count()));

    // ���ĵ� �����ͷ� ���̺� ������Ʈ (���� ���� ���� ���� ��� ���)
    students = mergeData;
    updateTable();
}

void MainWindow::onResetBtnClicked() {
    students = originalStudents;
    updateTable();
    log(toKor("�����Ͱ� �ʱ� ���·� �缳���Ǿ����ϴ�."));
}

void MainWindow::onShuffleBtnClicked() {
    RandomUtil::shuffle(students.begin(), students.end());
    updateTable();
    log(toKor("�����Ͱ� �������� �������ϴ�."));
}

void MainWindow::onPivotComboChanged(int index) {
    quickSort.setPivotType(static_cast<QuickSort::PivotType>(index));
}
