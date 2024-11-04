#ifndef LAB2_SEM3_COUNTINGSORTWIDGET_H
#define LAB2_SEM3_COUNTINGSORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QTime>

class CountingSortWidget : public QWidget {
public:
    CountingSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 100; ++i) {
            array.push_back(rand() % 500 + 10);
        }

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &CountingSortWidget::nextStep);

        // Стартуем таймер
        timer->start(10);

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
            if (sorted) {
                // Закрашиваем все элементы в зелёный, если сортировка завершена
                painter.setBrush(Qt::green);
                // Рисуем столбец отсортированного массива
                painter.drawRect(i * width, rect().height() - sortedArray[i] * 5, width - 2, sortedArray[i] * 5);
            } else if (i == currentIndex) {
                // Подсвечиваем текущий элемент
                painter.setBrush(Qt::red);
                painter.drawRect(i * width, rect().height() - array[i] * 5, width - 2, array[i] * 5);
            } else {
                painter.setBrush(Qt::blue);
                painter.drawRect(i * width, rect().height() - array[i] * 5, width - 2, array[i] * 5);
            }
        }
    }

private slots:
    void nextStep() {
        if (sorted) {
            // Если сортировка завершена, просто обновляем виджет
            update();
            return;
        }

        if (step == 0) {
            // Первый шаг: находим максимальный элемент
            maxElement = *max_element(array.begin(), array.end());
            count.assign(maxElement + 1, 0);
            step++;
        } else if (step == 1) {
            // Второй шаг: заполняем массив подсчета
            if (currentIndex < array.size()) {
                count[array[currentIndex]]++;
                currentIndex++;
            } else {
                currentIndex = 0;
                step++;
            }
        } else if (step == 2) {
            // Третий шаг: восстанавливаем отсортированный массив
            if (currentIndex <= maxElement) {
                while (count[currentIndex] > 0) {
                    sortedArray.push_back(currentIndex);
                    count[currentIndex]--;
                }
                currentIndex++;
            } else {
                // Завершаем сортировку
                sorted = true;
                timer->stop();
                int elapsed = startTime.msecsTo(QTime::currentTime());
                setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));
            }
        }

        // Обновляем виджет (вызываем paintEvent)
        update();
    }

private:
    std::vector<int> array;        // Массив для сортировки
    std::vector<int> count;        // Массив для подсчета
    std::vector<int> sortedArray;   // Массив для хранения отсортированных элементов
    int maxElement;                // Максимальный элемент массива
    int currentIndex = 0;          // Индекс для текущей операции
    int step = 0;                  // Шаги алгоритма
    bool sorted = false;           // Флаг завершения сортировки

    QTimer *timer;                 // Таймер для анимации
    QTime startTime;               // Время начала сортировки
};

#endif // LAB2_SEM3_COUNTINGSORTWIDGET_H
