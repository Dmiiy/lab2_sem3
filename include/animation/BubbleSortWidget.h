
#ifndef LAB2_SEM3_BUBBLESORTWIDGET_H
#define LAB2_SEM3_BUBBLESORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <QTime>
class BubbleSortWidget : public QWidget {

public:
    BubbleSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 50; ++i) {
            array.push_back(rand() % 500 + 10);
        }

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &BubbleSortWidget::nextStep);

        // Стартуем таймер
        timer->start(20);

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
            } else if (i == currentIndex || i == currentIndex + 1) {
                // Подсвечиваем сравниваемые элементы
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

        // Выполняем один шаг сортировки пузырьком
        if (array[currentIndex] > array[currentIndex + 1]) {
            std::swap(array[currentIndex], array[currentIndex + 1]);
        }

        currentIndex++;

        // Проверяем завершение прохода
        if (currentIndex >= array.size() - pass - 1) {
            currentIndex = 0;
            pass++;
        }

        // Проверяем завершение сортировки
        if (pass >= array.size() - 1) {
            sorted = true;
            sortedIndex = 0;

            // Останавливаем таймер сортировки и выводим время выполнения
            timer->stop();
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));

            timer->start(20);  // Перезапускаем таймер для закрашивания
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

private:
    std::vector<int> array;  // Массив для сортировки
    int currentIndex = 0;    // Текущий индекс для сравнения
    int pass = 0;            // Количество завершенных проходов
    bool sorted = false;     // Флаг завершения сортировки
    int sortedIndex = 0;     // Индекс для закрашивания зеленым цветом

    QTimer *timer;           // Таймер для анимации
    QTime startTime;         // Время начала сортировки
};
#endif //LAB2_SEM3_BUBBLESORTWIDGET_H
