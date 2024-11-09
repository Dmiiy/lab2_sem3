#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QRandomGenerator>
#include <QComboBox>
#include "SortingTime.h"
#include "animation/BubbleSortWidget.h"
#include "animation/CountingSortWidget.h"
#include "animation/HeapSortWidget.h"
#include "animation/QuickSortWidget.h"
#include "animation/SelectionSortWidget.h"
#include "animation/ShakerSortWidget.h"
#include "animation/MergeSortWidget.h"
#include "animation/InsertionSortWidget.h"
#include "animation/BinaryInsertionSortWidget.h"
#include "SortingStudents.h"
#include "animation/EnhancedSelectionSortWidget.h"
#include "sequence/Statistics.h"
#include "FileSorting.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Сортировка массива");
        resize(800, 800);

        QWidget *mainWidget = new QWidget;
        auto *mainLayout = new QVBoxLayout(mainWidget);

        QGroupBox *manualInputBox = new QGroupBox("Ручной ввод массива");
        auto *manualLayout = new QVBoxLayout(manualInputBox);
        inputSequence = new QLineEdit;
        QPushButton *validateButton = new QPushButton("Проверить и отсортировать");


        // Выпадающее меню для выбора сортировки
        sortMethodComboBoxForGeneration = new QComboBox();
        sortMethodComboBoxForGeneration->addItems({
                                             "Bubble Sort",
                                             "Quick Sort",
                                             "Counting Sort",
                                             "Heap Sort",
                                             "Selection Sort",
                                             "Shaker Sort",
                                             "Shell Sort",
                                             "Merge Sort",
                                             "Insertion Sort",
                                             "Binary Insertion Sort",
                                             "Batcher Sort",
                                             "Enhanced Selection Sort",
                                             "Tree Sort"
                                     });

        // Добавляем новый QComboBox для выбора порядка сортировки
        sortOrderComboBoxForGeneration = new QComboBox();
        sortOrderComboBoxForGeneration->addItems({"По возрастанию", "По убыванию"});
        // Выпадающее меню для выбора сортировки
        sortMethodComboBoxForManual = new QComboBox();
        sortMethodComboBoxForManual->addItems({
                                                          "Bubble Sort",
                                                          "Quick Sort",
                                                          "Counting Sort",
                                                          "Heap Sort",
                                                          "Selection Sort",
                                                          "Shaker Sort",
                                                          "Shell Sort",
                                                          "Merge Sort",
                                                          "Insertion Sort",
                                                          "Binary Insertion Sort",
                                                          "Batcher Sort",
                                                          "Enhanced Selection Sort",
                                                          "Tree Sort"
                                                  });

        // Добавляем новый QComboBox для выбора порядка сортировки
        sortOrderComboBoxForManual = new QComboBox();
        sortOrderComboBoxForManual->addItems({"По возрастанию", "По убыванию"});
        manualLayout->addWidget(new QLabel("Введите элементы массива через пробел:"));
        manualLayout->addWidget(inputSequence);
        manualLayout->addWidget(new QLabel("Выберите метод сортировки:"));
        manualLayout->addWidget(sortMethodComboBoxForManual);
        manualLayout->addWidget(new QLabel("Выберите порядок сортировки:"));
        manualLayout->addWidget(sortOrderComboBoxForManual);
        manualLayout->addWidget(validateButton);

        // Группа для генерации массива
        QGroupBox *generateArrayBox = new QGroupBox("Генерация массива");
        auto *generateLayout = new QVBoxLayout(generateArrayBox);
        arraySizeInput = new QLineEdit;
        minValueInput = new QLineEdit;
        maxValueInput = new QLineEdit;
        QPushButton *generateButton = new QPushButton("Сгенерировать и отсортировать");

        generateLayout->addWidget(new QLabel("Размер массива:"));
        generateLayout->addWidget(arraySizeInput);
        generateLayout->addWidget(new QLabel("Минимальное значение:"));
        generateLayout->addWidget(minValueInput);
        generateLayout->addWidget(new QLabel("Максимальное значение:"));
        generateLayout->addWidget(maxValueInput);
        generateLayout->addWidget(new QLabel("Выберите метод сортировки:"));
        generateLayout->addWidget(sortMethodComboBoxForGeneration);
        generateLayout->addWidget(new QLabel("Выберите порядок сортировки:"));
        generateLayout->addWidget(sortOrderComboBoxForGeneration);
        generateLayout->addWidget(generateButton);

        // Поле для вывода информации
        outputDisplay = new QTextEdit;
        outputDisplay->setReadOnly(true);

        // Кнопки для запуска анимаций сортировок
        QGroupBox *animationButtonsBox = new QGroupBox("Анимации сортировок");
        auto *animationLayout = new QHBoxLayout(animationButtonsBox);

        // Инициализация кнопок сортировок
        bubbleSortButton = new QPushButton("Bubble Sort");
        quickSortButton = new QPushButton("Quick Sort");
        countingSortButton = new QPushButton("Counting Sort");
        heapSortButton = new QPushButton("Heap Sort");
        selectionSortButton = new QPushButton("Selection Sort");
        shakerSortButton = new QPushButton("Shaker Sort");
        mergeSortButton = new QPushButton("Merge Sort");
        insertionSortButton = new QPushButton("Insertion Sort");
        binaryInsertionSortButton = new QPushButton("Binary Insertion Sort");
        enhancedSelectionSortButton = new QPushButton("Enhanced Selection Sort");


        // Добавляем кнопки на компоновку
        animationLayout->addWidget(bubbleSortButton);
        animationLayout->addWidget(quickSortButton);
        animationLayout->addWidget(countingSortButton);
        animationLayout->addWidget(heapSortButton);
        animationLayout->addWidget(selectionSortButton);
        animationLayout->addWidget(shakerSortButton);
        animationLayout->addWidget(mergeSortButton);
        animationLayout->addWidget(insertionSortButton);
        animationLayout->addWidget(binaryInsertionSortButton);
        animationLayout->addWidget(enhancedSelectionSortButton);

        // Кнопка для перехода к замеру времени
        QPushButton *openSortingTimeButton = new QPushButton("Замер времени сортировок");
        QPushButton *openSortingStudentsButton = new QPushButton("Сортировка для студентов");
        QPushButton *fileSortButton = new QPushButton("Сортировка из файлов");

        // Компоновка основных элементов
        mainLayout->addWidget(manualInputBox);
        mainLayout->addWidget(generateArrayBox);
        mainLayout->addWidget(outputDisplay);
        mainLayout->addWidget(animationButtonsBox);
        mainLayout->addWidget(openSortingTimeButton);
        mainLayout->addWidget(openSortingStudentsButton);
        mainLayout->addWidget(fileSortButton);

        setCentralWidget(mainWidget);

        // Подключение сигналов и слотов
        connect(validateButton, &QPushButton::clicked, this, &MainWindow::onValidateAndSort);
        connect(generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateAndSort);
        connect(bubbleSortButton, &QPushButton::clicked, this, &MainWindow::onShowBubbleSortAnimation);
        connect(quickSortButton, &QPushButton::clicked, this, &MainWindow::onShowQuickSortAnimation);
        connect(countingSortButton, &QPushButton::clicked, this, &MainWindow::onShowCountingSortAnimation);
        connect(heapSortButton, &QPushButton::clicked, this, &MainWindow::onShowHeapSortAnimation);
        connect(selectionSortButton, &QPushButton::clicked, this, &MainWindow::onShowSelectionSortAnimation);
        connect(shakerSortButton, &QPushButton::clicked, this, &MainWindow::onShowShakerSortAnimation);
        connect(mergeSortButton, &QPushButton::clicked, this, &MainWindow::onShowMergeSortAnimation);
        connect(insertionSortButton, &QPushButton::clicked, this, &MainWindow::onShowInsertionSortAnimation);
        connect(binaryInsertionSortButton, &QPushButton::clicked, this, &MainWindow::onShowBinaryInsertionSortAnimation);
        connect(enhancedSelectionSortButton, &QPushButton::clicked, this, &MainWindow::onShowEnhancedSelectionSortAnimation);
        connect(openSortingTimeButton, &QPushButton::clicked, this, &MainWindow::onOpenSortingTime);
        connect(openSortingStudentsButton, &QPushButton::clicked, this, &MainWindow::onOpenSortingStudents);
        connect(fileSortButton, &QPushButton::clicked, this, &MainWindow::onOpenFileSorting);


    }

private slots:
    void onValidateAndSort() {
        QString input = inputSequence->text();
        QStringList numbers = input.split(" ", Qt::SkipEmptyParts);
        ArraySequence<int> array;
        outputDisplay->clear();
        outputDisplay->append("Исходный массив: " );
        for (const QString &number : numbers) {
            bool ok;
            int value = number.toInt(&ok);
            if (ok) {
                array.append(value);
                outputDisplay->append(QString::number(value) + " ");
            } else {
                outputDisplay->append("Некорректный ввод. Пожалуйста, введите целые числа.");
                return;
            }
        }

        // Определяем порядок сортировки
        bool ascendingOrder = sortOrderComboBoxForManual->currentText() == "По возрастанию";


        // Получаем выбранный метод сортировки
        QString selectedSortMethod = sortMethodComboBoxForManual->currentText();
        if (selectedSortMethod == "Bubble Sort") {
            BubbleSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Quick Sort") {
            QuickSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Counting Sort") {
            CountingSorter<int, int> sorter(ascendingOrder ? ascending : descending, intExtractor);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Heap Sort") {
            HeapSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Selection Sort") {
            SelectionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Shaker Sort") {
            ShakerSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Shell Sort") {
            ShellSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Merge Sort") {
            MergeSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Insertion Sort") {
            InsertionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Binary Insertion Sort") {
            BinaryInsertionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Batcher Sort") {
            BatcherSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Tree Sort") {
            TreeSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Enhanced Selection Sort") {
            EnhancedSelectionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        displayArray(array, "Отсортированный массив:");

        outputDisplay->append("Статистические показатели: ");

        int mean= Statistics<int>::mean(array);
        int median = Statistics<int>::median(array);
        int meanSquare = Statistics<int>::meanSquare(array);
        int standardDeviation = Statistics<int>::standardDeviation(array);

        outputDisplay->append("Среднее значение: " + QString::number(mean));
        outputDisplay->append("Медиана: " + QString::number(median));
        outputDisplay->append("Среднеквадратичное значение: " + QString::number(meanSquare));
        outputDisplay->append("Стандартное отклонение: " + QString::number(standardDeviation));
    }

    void onGenerateAndSort() {
        bool ok;
        int size = arraySizeInput->text().toInt(&ok);
        if (!ok || size <= 0) {
            outputDisplay->append("Некорректный размер массива.");
            return;
        }

        int minValue = minValueInput->text().toInt(&ok);
        if (!ok) {
            outputDisplay->append("Некорректное минимальное значение.");
            return;
        }

        int maxValue = maxValueInput->text().toInt(&ok);
        if (!ok) {
            outputDisplay->append("Некорректное максимальное значение.");
            return;
        }
        outputDisplay->clear();
        outputDisplay->append("Исходный массив: " );

        ArraySequence<int> array;
        for (int i = 0; i < size; ++i) {
            int value = QRandomGenerator::global()->bounded(minValue, maxValue + 1);
            array.append(value);
            outputDisplay->append(QString::number(value) + " ");
        }

        // Определяем порядок сортировки
        bool ascendingOrder = sortOrderComboBoxForGeneration->currentText() == "По возрастанию";

        // Получаем выбранный метод сортировки
        QString selectedSortMethod = sortMethodComboBoxForGeneration->currentText();

        if (selectedSortMethod == "Bubble Sort") {
            BubbleSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Quick Sort") {
            QuickSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Counting Sort") {
            CountingSorter<int, int> sorter(ascendingOrder ? ascending : descending, intExtractor);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Heap Sort") {
            HeapSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Selection Sort") {
            SelectionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Shaker Sort") {
            ShakerSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Shell Sort") {
            ShellSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Merge Sort") {
            MergeSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Insertion Sort") {
            InsertionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Binary Insertion Sort") {
            BinaryInsertionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Batcher Sort") {
            BatcherSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Tree Sort") {
            TreeSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }
        if (selectedSortMethod == "Enhanced Selection Sort") {
            EnhancedSelectionSorter<int> sorter(ascendingOrder ? ascending : descending);
            sorter.sort(&array);
        }


        displayArray(array, "Отсортированный массив:");
        outputDisplay->append("Статистические показатели: ");

        int mean= Statistics<int>::mean(array);
        int median = Statistics<int>::median(array);
        int meanSquare = Statistics<int>::meanSquare(array);
        int standardDeviation = Statistics<int>::standardDeviation(array);

        outputDisplay->append("Среднее значение: " + QString::number(mean));
        outputDisplay->append("Медиана: " + QString::number(median));
        outputDisplay->append("Среднеквадратичное значение: " + QString::number(meanSquare));
        outputDisplay->append("Стандартное отклонение: " + QString::number(standardDeviation));
    }

    void displayArray(const ArraySequence<int>& array, const QString& message) {
        //outputDisplay->clear();
        outputDisplay->append(message);
        for (int i = 0; i < array.getLength(); ++i) {
            int number = array[i];
            outputDisplay->append(QString::number(number));
        }
    }

        void onShowBubbleSortAnimation() {
        BubbleSortWidget *bubbleSortWidget = new BubbleSortWidget();
        bubbleSortWidget->show();
    }

    void onShowQuickSortAnimation() {
        QuickSortWidget *quickSortWidget = new QuickSortWidget();
        quickSortWidget->show();
    }

    void onShowCountingSortAnimation() {
        CountingSortWidget *countingSortWidget = new CountingSortWidget();
        countingSortWidget->show();
    }

    void onShowHeapSortAnimation() {
        HeapSortWidget *heapSortWidget = new HeapSortWidget();
        heapSortWidget->show();
    }

    void onShowSelectionSortAnimation() {
        SelectionSortWidget *selectionSortWidget = new SelectionSortWidget();
        selectionSortWidget->show();
    }

    void onShowShakerSortAnimation() {
        ShakerSortWidget *shakerSortWidget = new ShakerSortWidget();
        shakerSortWidget->show();
    }



    void onShowMergeSortAnimation() {
        MergeSortWidget *mergeSortWidget = new MergeSortWidget();
        mergeSortWidget->show();
    }

    void onShowInsertionSortAnimation() {
        InsertionSortWidget *insertionSortWidget = new InsertionSortWidget();
        insertionSortWidget->show();
    }

    void onShowBinaryInsertionSortAnimation() {
        BinaryInsertionSortWidget *binaryInsertionSortWidget = new BinaryInsertionSortWidget();
        binaryInsertionSortWidget->show();
    }



    void onShowEnhancedSelectionSortAnimation() {
        EnhancedSelectionSortWidget *enhancedSelectionSortWidget = new EnhancedSelectionSortWidget();
        enhancedSelectionSortWidget->show();
    }

    void onOpenSortingTime() {
        SortingTime *sortingTimeWindow = new SortingTime();
        sortingTimeWindow->show();
    }

    void onOpenSortingStudents() {
        SortingStudents *sortingStudentsWindow = new SortingStudents();
        sortingStudentsWindow->show();
    }
    void onOpenFileSorting() {
        FileSorting *fileSortingWindow = new FileSorting();
        fileSortingWindow->show();
    }

private:
    QLineEdit *inputSequence;
    QLineEdit *arraySizeInput;
    QLineEdit *minValueInput;
    QLineEdit *maxValueInput;
    QComboBox *sortMethodComboBoxForGeneration;
    QComboBox *sortOrderComboBoxForGeneration;
    QComboBox *sortMethodComboBoxForManual;
    QComboBox *sortOrderComboBoxForManual;
    QTextEdit *outputDisplay;

    QPushButton *bubbleSortButton;
    QPushButton *quickSortButton;
    QPushButton *countingSortButton;
    QPushButton *heapSortButton;
    QPushButton *selectionSortButton;
    QPushButton *shakerSortButton;
    QPushButton *shellSortButton;
    QPushButton *mergeSortButton;
    QPushButton *insertionSortButton;
    QPushButton *binaryInsertionSortButton;
    QPushButton *treeSortButton;
    QPushButton *enhancedSelectionSortButton;
};

#endif // MAINWINDOW_H


