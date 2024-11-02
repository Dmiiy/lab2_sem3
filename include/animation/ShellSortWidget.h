#ifndef LAB2_SEM3_SHELLSORTWIDGET_H
#define LAB2_SEM3_SHELLSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>

class ShellSortWidget : public QWidget {
public:
    ShellSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 50; ++i) {
            array.push_back(rand() % 500 + 50);
        }

        // Задаем начальный интервал (половина длины массива)
        gap = array.size() / 2;

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &ShellSortWidget::nextStep);

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
            } else if (i == currentIndex || i == currentIndex - gap) {
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

        // Выполняем один шаг Shell Sort
        if (gap > 0) {
            if (currentIndex >= gap) {
                // Сравниваем элементы на расстоянии `gap`
                if (array[currentIndex] < array[currentIndex - gap]) {
                    std::swap(array[currentIndex], array[currentIndex - gap]);
                    currentIndex -= gap;  // Перемещаемся назад для вставки в отсортированную часть
                } else {
                    // Переходим к следующему элементу
                    currentIndex++;
                }
            } else {
                // Завершаем текущий проход для данного интервала
                gap /= 2;  // Уменьшаем интервал
                currentIndex = gap;  // Начинаем с нового интервала
            }
        } else {
            // Завершение сортировки
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
    int gap;                 // Текущий интервал для Shell Sort
    bool sorted = false;     // Флаг завершения сортировки
    int sortedIndex = 0;     // Индекс для закрашивания зеленым цветом

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};

#endif // LAB2_SEM3_SHELLSORTWIDGET_H
