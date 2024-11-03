#ifndef LAB2_SEM3_BINARYINSERTIONSORTWIDGET_H
#define LAB2_SEM3_BINARYINSERTIONSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>


class BinaryInsertionSortWidget : public QWidget {
public:
    BinaryInsertionSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 50; ++i) {
            array.push_back(rand() % 500 + 50);  // Случайные числа в диапазоне от 50 до 550
        }

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &BinaryInsertionSortWidget::nextStep);

        // Стартуем таймер
        timer->start(100);

        // Фиксируем начальное время
        startTime = QTime::currentTime();

        // Начинаем сортировку
        currentIndex = 1;
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

        // Очищаем фон
        painter.fillRect(rect(), Qt::white);

        // Рисуем элементы массива как вертикальные столбцы
        int width = rect().width() / array.size();
        for (size_t i = 0; i < array.size(); ++i) {
            if (sorted && i < sortedIndex) {
                // Закрашиваем элементы в зелёный, если они отсортированы
                painter.setBrush(Qt::green);
            } else if (i == currentIndex || i == insertIndex) {
                // Подсвечиваем текущий элемент и место вставки
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
                timer->stop();  // Останавливаем таймер после полной проверки
            }
            update();
            return;
        }

        // Выполняем один шаг бинарной вставочной сортировки
        if (currentIndex < array.size()) {
            int key = array[currentIndex];
            int insertPos = binarySearch(array, key, 0, currentIndex - 1);

            // Вставка элемента на нужную позицию
            array.insert(array.begin() + insertPos, key);
            array.erase(array.begin() + currentIndex + 1);

            // Обновляем индексы
            currentIndex++;
            insertIndex = insertPos; // Сохраняем индекс для подсветки
        }

        // Проверяем завершение сортировки
        if (currentIndex >= array.size()) {
            sorted = true;
            sortedIndex = 0;

            // Останавливаем таймер сортировки и выводим время выполнения
            timer->stop();
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));
            timer->start(50);  // Перезапускаем таймер для закрашивания
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

private:
    int binarySearch(const std::vector<int>& arr, int key, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] > key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low; // Вставляем в позицию low
    }

    std::vector<int> array;  // Массив для сортировки
    int currentIndex = 0;    // Индекс текущего элемента
    int insertIndex = -1;    // Индекс для вставки
    bool sorted = false;     // Флаг завершения сортировки
    int sortedIndex = 0;     // Индекс для закрашивания зеленым цветом

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};

#endif // LAB2_SEM3_BINARYINSERTIONSORTWIDGET_H
