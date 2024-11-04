#ifndef LAB2_SEM3_ENHANCEDSELECTIONSORTWIDGET_H
#define LAB2_SEM3_ENHANCEDSELECTIONSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>

class EnhancedSelectionSortWidget : public QWidget {
public:
    EnhancedSelectionSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 100; ++i) {
            array.push_back(rand() % 500 + 10);
        }

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &EnhancedSelectionSortWidget::nextStep);

        // Стартуем таймер
        timer->start(50);

        // Фиксируем начальное время
        startTime = QTime::currentTime();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::white); // Очищаем фон

        int width = rect().width() / array.size();
        for (size_t i = 0; i < array.size(); ++i) {
            if (i == minIndex) {
                painter.setBrush(Qt::red); // Подсвечиваем минимальный элемент
            } else if (sorted && i <= sortedIndex) {
                painter.setBrush(Qt::green); // Закрашиваем отсортированные элементы
            } else {
                painter.setBrush(Qt::blue); // Обычный цвет
            }
            painter.drawRect(i * width, rect().height() - array[i], width - 2, array[i]);
        }
    }

private slots:
    void nextStep() {
        if (sorted) {
            sortedIndex++;
            if (sortedIndex >= array.size()) {
                timer->stop();
            }
            update();
            return;
        }

        // Усовершенствованная сортировка выбором
        if (currentPass < array.size() - 1) {
            minIndex = currentPass;
            for (int j = currentPass + 1; j < array.size(); ++j) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            std::swap(array[currentPass], array[minIndex]);
            currentPass++;
        } else {
            sorted = true;
            sortedIndex = 0;
            timer->stop();
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));
            timer->start(20); // Перезапуск таймера для закрашивания
        }

        update();
    }

private:
    std::vector<int> array; // Массив для сортировки
    int currentPass = 0;    // Текущий проход
    int minIndex = -1;      // Индекс минимального элемента
    bool sorted = false;    // Флаг завершения сортировки
    int sortedIndex = 0;    // Индекс для закрашивания зеленым цветом

    QTimer *timer;          // Таймер для анимации
    QTime startTime;        // Время начала сортировки
};

#endif //LAB2_SEM3_ENHANCEDSELECTIONSORTWIDGET_H
