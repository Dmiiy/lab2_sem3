#ifndef LAB2_SEM3_SELECTIONSORTWIDGET_H
#define LAB2_SEM3_SELECTIONSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>

class SelectionSortWidget : public QWidget {
public:
    SelectionSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 100; ++i) {
            array.push_back(rand() % 500 + 10);  // Случайные числа в диапазоне от 50 до 550
        }

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &SelectionSortWidget::nextStep);

        // Стартуем таймер
        timer->start(0);  // Интервал обновления в миллисекундах (0.1 секунда)

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
            } else if (i == currentIndex || i == minIndex) {
                // Подсвечиваем текущий элемент и минимальный элемент
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

        // Реализация одного шага сортировки выбором
        if (currentIndex < array.size()) {
            if (stepIndex < array.size()) {
                // Находим минимальный элемент в неотсортированной части массива
                if (array[stepIndex] < array[minIndex]) {
                    minIndex = stepIndex;
                }
                stepIndex++;
            } else {
                // Меняем местами найденный минимальный элемент с текущим
                std::swap(array[currentIndex], array[minIndex]);

                // Переходим к следующей позиции
                currentIndex++;
                minIndex = currentIndex;
                stepIndex = currentIndex + 1;
            }
        } else {
            // Установка флага завершения сортировки
            sorted = true;
            sortedIndex = 0;  // Для начала проверки отсортированных элементов

            // Останавливаем таймер сортировки и выводим время выполнения
            timer->stop();
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));

            // Перезапускаем таймер для закрашивания в зелёный
            timer->start(50);
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

private:
    std::vector<int> array;  // Массив для сортировки
    int currentIndex = 0;    // Текущий индекс для сортировки
    int minIndex = 0;        // Индекс минимального элемента
    int stepIndex = 1;       // Внутренний индекс для поиска минимума
    bool sorted = false;     // Флаг завершения сортировки
    int sortedIndex = 0;     // Индекс для закрашивания зеленым цветом

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};

#endif // LAB2_SEM3_SELECTIONSORTWIDGET_H
