#ifndef LAB2_SEM3_INSERTIONSORTWIDGET_H
#define LAB2_SEM3_INSERTIONSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QTime>

class InsertionSortWidget : public QWidget {
public:
    InsertionSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 100; ++i) {
            array.push_back(rand() % 500 + 10);
        }

        currentIndex = 1;  // Начинаем с первого элемента
        sortedIndex = 0;   // Индекс отсортированной части
        sorted = false;    // Изначально массив не отсортирован

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &InsertionSortWidget::nextStep);

        // Стартуем таймер
        timer->start(50);

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
            } else if (i == currentIndex || i == currentIndex - 1) {
                // Подсвечиваем текущий элемент и элемент для вставки
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
            // Если сортировка завершена, просто обновляем индекс для покраски
            sortedIndex++;
            if (sortedIndex >= array.size()) {
                timer->stop();
            }
            update();
            return;
        }

        // Выполняем один шаг сортировки вставками
        int key = array[currentIndex];
        int j = currentIndex - 1;

        // Сдвигаем элементы, которые больше ключа, на одну позицию вперед
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key; // Вставляем ключ на его позицию

        currentIndex++;

        // Проверяем завершение сортировки
        if (currentIndex >= array.size()) {
            sorted = true;
            sortedIndex = 0;  // Для начала проверки отсортированных элементов
            timer->stop();  // Останавливаем таймер сортировки
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));

            timer->start(20);  // Перезапускаем таймер для закрашивания
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

private:
    std::vector<int> array;  // Массив для сортировки
    int currentIndex;        // Текущий индекс для вставки
    bool sorted;             // Флаг завершения сортировки
    int sortedIndex;         // Индекс для закрашивания зеленым цветом

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};

#endif // LAB2_SEM3_INSERTIONSORTWIDGET_H
