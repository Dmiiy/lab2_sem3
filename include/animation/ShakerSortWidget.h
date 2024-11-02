#ifndef LAB2_SEM3_SHAKERSORTWIDGET_H
#define LAB2_SEM3_SHAKERSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>

class ShakerSortWidget : public QWidget {
public:
    ShakerSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 50; ++i) {
            array.push_back(rand() % 500 + 50);
        }

        // Устанавливаем правую границу на последний элемент
        rightBoundary = array.size() - 1;

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &ShakerSortWidget::nextStep);

        // Стартуем таймер
        timer->start(0);

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
            } else if (i == currentIndex || i == currentIndex + (leftToRight ? 1 : -1)) {
                // Подсвечиваем текущие сравниваемые элементы
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

        // Выполняем один шаг Shaker Sort
        if (leftToRight) {
            if (currentIndex < rightBoundary) {
                if (array[currentIndex] > array[currentIndex + 1]) {
                    std::swap(array[currentIndex], array[currentIndex + 1]);
                }
                currentIndex++;
            } else {
                rightBoundary--;
                leftToRight = false;  // Меняем направление на противоположное
                currentIndex = rightBoundary;  // Начинаем с правой границы
            }
        } else {
            if (currentIndex > leftBoundary) {
                if (array[currentIndex] < array[currentIndex - 1]) {
                    std::swap(array[currentIndex], array[currentIndex - 1]);
                }
                currentIndex--;
            } else {
                leftBoundary++;
                leftToRight = true;  // Меняем направление на противоположное
                currentIndex = leftBoundary;  // Начинаем с левой границы
            }
        }

        // Проверяем завершение сортировки
        if (leftBoundary >= rightBoundary) {
            sorted = true;
            sortedIndex = 0;  // Для начала закрашивания в зелёный

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
    std::vector<int> array;  // Массив для сортировки
    int currentIndex = 0;    // Текущий индекс для сравнения
    int leftBoundary = 0;    // Левая граница
    int rightBoundary;       // Правая граница
    bool leftToRight = true; // Направление прохода (вправо или влево)
    bool sorted = false;     // Флаг завершения сортировки
    int sortedIndex = 0;     // Индекс для закрашивания зеленым цветом

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};

#endif // LAB2_SEM3_SHAKERSORTWIDGET_H
