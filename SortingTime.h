#ifndef LAB2_SEM3_SORTINGTIME_H
#define LAB2_SEM3_SORTINGTIME_H

#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QElapsedTimer>
#include <QLabel>
#include <QLineEdit>
#include <QRandomGenerator>
#include "sorting/BubbleSort.h"
#include "sorting/QuickSorter.h"
#include "sorting/CountingSort.h"
#include "sorting/HeapSort.h"
#include "sorting/SelectionSort.h"
#include "sorting/ShakerSort.h"
#include "sorting/ShellSort.h"
#include "sorting/MergeSort.h"
#include "sorting/InsertionSort.h"
#include "sorting/BinaryInsertionSort.h"
#include "sorting/BatcherSort.h"

class SortingTime : public QMainWindow {
//Q_OBJECT

public:
    SortingTime(QWidget *parent = nullptr) : QMainWindow(parent) {
        auto *mainWidget = new QWidget;
        auto *layout = new QVBoxLayout(mainWidget);

        // Поля для ввода размера массива и диапазона значений
        sizeInput = new QLineEdit;
        minInput = new QLineEdit;
        maxInput = new QLineEdit;

        layout->addWidget(new QLabel("Размер массива:"));
        layout->addWidget(sizeInput);
        layout->addWidget(new QLabel("Минимальное значение:"));
        layout->addWidget(minInput);
        layout->addWidget(new QLabel("Максимальное значение:"));
        layout->addWidget(maxInput);

        // Кнопка для запуска сортировки
        auto *runButton = new QPushButton("Запустить сортировки");
        layout->addWidget(runButton);

        // Таблица для отображения результатов
        resultTable = new QTableWidget;
        resultTable->setColumnCount(2);
        resultTable->setHorizontalHeaderLabels({"Сортировка", "Время (мс)"});
        layout->addWidget(resultTable);

        connect(runButton, &QPushButton::clicked, this, &SortingTime::runSortingTests);

        setCentralWidget(mainWidget);
    }

private slots:
    void runSortingTests() {
        int size = sizeInput->text().toInt();
        int min = minInput->text().toInt();
        int max = maxInput->text().toInt();

        // Создаем ArraySequence с случайными значениями
        ArraySequence<int> array;
        for (int i = 0; i < size; ++i) {
            int randomValue = QRandomGenerator::global()->bounded(min, max + 1);
            array.append(randomValue);
        }

        // Запускаем сортировки и замеряем время
        runSingleSort<BubbleSorter<int>>("Bubble Sort", array);
        runSingleSort<QuickSorter<int>>("Quick Sort", array);
        runSingleSort<CountingSorter<int>>("Counting Sort", array);
        runSingleSort<HeapSorter<int>>("Heap Sort", array);
        runSingleSort<SelectionSorter<int>>("Selection Sort", array);
        runSingleSort<ShakerSorter<int>>("Shaker Sort", array);
        runSingleSort<ShellSorter<int>>("Shell Sort", array);
        runSingleSort<MergeSorter<int>>("Merge Sort", array);
        runSingleSort<InsertionSorter<int>>("Insertion Sort", array);
        runSingleSort<BinaryInsertionSorter<int>>("Binary Insertion Sort", array);
        runSingleSort<BatcherSorter<int>>("Batcher Sort", array);

    }

    template <typename SorterType>
    void runSingleSort(const QString &sortName, const ArraySequence<int> &array) {
        ArraySequence<int> copy = array;  // Создаем копию массива

        QElapsedTimer timer;
        timer.start();

        SorterType sorter;
        sorter.sort(&copy);

        int elapsed = timer.elapsed();
        addResult(sortName, elapsed);
    }

    void addResult(const QString &sortName, int time) {
        int rowCount = resultTable->rowCount();
        resultTable->insertRow(rowCount);
        resultTable->setItem(rowCount, 0, new QTableWidgetItem(sortName));
        resultTable->setItem(rowCount, 1, new QTableWidgetItem(QString::number(time)));
    }

private:
    QLineEdit *sizeInput;
    QLineEdit *minInput;
    QLineEdit *maxInput;
    QTableWidget *resultTable;
};
#endif //LAB2_SEM3_SORTINGTIME_H
