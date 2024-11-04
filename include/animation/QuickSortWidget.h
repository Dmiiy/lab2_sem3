#ifndef LAB2_SEM3_QUICKSORTWIDGET_H
#define LAB2_SEM3_QUICKSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>
#include <stack>

class QuickSortWidget : public QWidget {
public:
    QuickSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 100; ++i) {
            array.push_back(rand() % 500 + 10);
        }

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &QuickSortWidget::nextStep);

        // Стартуем таймер
        timer->start(50);

        // Инициализация параметров для Quick Sort
        leftStack.push(0);
        rightStack.push(array.size() - 1);
        quickSortStep = true;

        // Фиксируем начальное время
        startTime = QTime::currentTime();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

        // Очищаем фон
        painter.fillRect(rect(), Qt::white);

        // Рисуем элементы массива как вертикальные столбцы
        int width = rect().width() / array.size();
        for (size_t i = 0; i < array.size(); ++i) {
            if (sorted && i <= sortedIndex) {
                // Закрашиваем элементы в зелёный, если они отсортированы
                painter.setBrush(Qt::green);
            } else if (i == leftPointer || i == rightPointer || i == pivotIndex) {
                // Подсвечиваем текущие элементы
                painter.setBrush(Qt::red);
            } else {
                painter.setBrush(Qt::blue);
            }

            // Рисуем столбец
            painter.drawRect(i * width, rect().height() - array[i], width - 2, array[i]);
        }
    }

private slots:
    void nextStep() {
        if (sorted) {
            // После завершения сортировки проверяем массив
            sortedIndex++;
            if (sortedIndex >= array.size()) {
                timer->stop();
            }
            update();
            return;
        }

        // Реализация шагов для алгоритма Quick Sort
        if (quickSortStep) {
            if (!leftStack.empty()) {
                int left = leftStack.top();
                int right = rightStack.top();
                leftStack.pop();
                rightStack.pop();

                // Находим опорный элемент и разделяем массив
                pivotIndex = partition(left, right);

                // Добавляем подмассивы в стек для дальнейшей сортировки
                if (pivotIndex - 1 > left) {
                    leftStack.push(left);
                    rightStack.push(pivotIndex - 1);
                }
                if (pivotIndex + 1 < right) {
                    leftStack.push(pivotIndex + 1);
                    rightStack.push(right);
                }
            } else {
                sorted = true;
                sortedIndex = 0;
                timer->stop();

                int elapsed = startTime.msecsTo(QTime::currentTime());
                setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));
                timer->start(20);  // Перезапускаем таймер для закрашивания
            }
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

    int partition(int left, int right) {
        pivotIndex = right;
        int pivotValue = array[pivotIndex];
        int storeIndex = left;
        for (int i = left; i < right; ++i) {
            if (array[i] < pivotValue) {
                std::swap(array[i], array[storeIndex]);
                storeIndex++;
            }
        }
        std::swap(array[storeIndex], array[right]);
        return storeIndex;
    }

private:
    std::vector<int> array;   // Массив для сортировки
    int leftPointer = 0;      // Левый указатель для текущего разделения
    int rightPointer = 0;     // Правый указатель для текущего разделения
    int pivotIndex = -1;      // Индекс опорного элемента
    bool sorted = false;      // Флаг завершения сортировки
    int sortedIndex = 0;      // Индекс для закрашивания зеленым цветом

    QTimer *timer;            // Таймер для анимации
    QTime startTime;          // Время начала сортировки

    // Стек для реализации неполной рекурсии в Quick Sort
    std::stack<int> leftStack;
    std::stack<int> rightStack;
    bool quickSortStep;
};

#endif // LAB2_SEM3_QUICKSORTWIDGET_H
