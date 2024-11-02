#ifndef LAB2_SEM3_HEAPSORTWIDGET_H
#define LAB2_SEM3_HEAPSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QTime>

class HeapSortWidget : public QWidget {
public:
    HeapSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 50; ++i) {
            array.push_back(rand() % 500 + 50);
        }

        // Устанавливаем начальные значения
        heapSize = array.size();
        currentIndex = heapSize - 1;
        sorted = false;

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &HeapSortWidget::nextStep);

        // Стартуем таймер
        timer->start(100);

        // Фиксируем начальное время
        startTime = QTime::currentTime();

        // Начинаем сортировку кучей
        buildHeap();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

        // Очищаем фон
        painter.fillRect(rect(), Qt::white);

        // Рисуем элементы массива как вертикальные столбцы
        int width = rect().width() / array.size();
        for (size_t i = 0; i < array.size(); ++i) {
            if (sorted) {
                // Закрашиваем все элементы в зелёный, если сортировка завершена
                painter.setBrush(Qt::green);
            } else if (i == currentIndex) {
                // Подсвечиваем текущий элемент
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
            // Если сортировка завершена, просто обновляем виджет
            update();
            return;
        }

        // Перемещаем корень кучи (максимальный элемент) в конец массива
        if (currentIndex >= 0) {
            std::swap(array[0], array[currentIndex]); // Меняем местами корень и последний элемент
            heapify(0, currentIndex); // Восстанавливаем кучу для уменьшенного массива
            currentIndex--; // Уменьшаем размер обрабатываемой кучи
        } else {
            // После завершения сортировки
            sorted = true; // Завершаем сортировку
            timer->stop();  // Останавливаем таймер сортировки
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

private:
    void buildHeap() {
        // Построение кучи (максимальной кучи)
        for (int i = heapSize / 2 - 1; i >= 0; i--) {
            heapify(i, heapSize);
        }
    }

    void heapify(int root, int size) {
        int largest = root;  // Инициализируем наибольший элемент как корень
        int left = 2 * root + 1; // Левый дочерний элемент
        int right = 2 * root + 2; // Правый дочерний элемент

        // Если левый дочерний элемент больше корня
        if (left < size && array[left] > array[largest]) {
            largest = left;
        }

        // Если правый дочерний элемент больше наибольшего элемента
        if (right < size && array[right] > array[largest]) {
            largest = right;
        }

        // Если наибольший элемент не корень
        if (largest != root) {
            std::swap(array[root], array[largest]); // Меняем местами

            // Рекурсивно кучи для затронутого поддерева
            heapify(largest, size);
        }
    }

private:
    std::vector<int> array;  // Массив для сортировки
    int heapSize;            // Размер кучи
    int currentIndex;        // Индекс для текущей операции
    bool sorted;             // Флаг завершения сортировки

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};

#endif // LAB2_SEM3_HEAPSORTWIDGET_H
