#ifndef LAB2_SEM3_MERGESORTWIDGET_H
#define LAB2_SEM3_MERGESORTWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QTime>

class MergeSortWidget : public QWidget {
public:
    MergeSortWidget(QWidget *parent = nullptr) : QWidget(parent), timer(new QTimer(this)) {
        resize(800, 600);

        // Инициализируем массив случайными значениями
        for (int i = 0; i < 100; ++i) {
            array.push_back(rand() % 500 + 10);
        }

        // Создаем копию массива для работы слияния
        tempArray.resize(array.size());

        // Устанавливаем начальные значения для индексов
        currentStep = 0;
        sorted = false;

        // Соединяем таймер с шагом сортировки
        connect(timer, &QTimer::timeout, this, &MergeSortWidget::nextStep);

        // Стартуем таймер
        timer->start(50);

        // Фиксируем начальное время
        startTime = QTime::currentTime();

        // Начинаем сортировку слиянием
        mergeSort(0, array.size() - 1);
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
            } else if (currentStep < steps.size() &&
                       i >= steps[currentStep].start && i <= steps[currentStep].end) {
                // Подсвечиваем текущие обрабатываемые элементы
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
        if (currentStep < steps.size()) {
            // Выполняем слияние
            auto& step = steps[currentStep]; // Получаем текущий шаг
            merge(step.start, step.mid, step.end);
            currentStep++;
            update();  // Обновляем виджет
        } else {
            // Завершаем сортировку
            sorted = true;
            timer->stop();  // Останавливаем таймер
            int elapsed = startTime.msecsTo(QTime::currentTime());
            setWindowTitle(QString("Сортировка завершена за %1 мс").arg(elapsed));

            // Обновляем для покраски оставшихся элементов в зеленый цвет
            sortedIndex = array.size() - 1; // Индекс последнего элемента
            update();  // Обновляем виджет для финальной покраски
        }
    }

private:
    void mergeSort(int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        steps.push_back({left, mid, right});  // Добавляем шаг слияния
    }

    void merge(int start, int mid, int end) {
        int i = start;     // Начало левой части
        int j = mid + 1;   // Начало правой части
        int k = start;     // Индекс для временного массива

        // Слияние двух подмассивов
        while (i <= mid && j <= end) {
            if (array[i] <= array[j]) {
                tempArray[k++] = array[i++];
            } else {
                tempArray[k++] = array[j++];
            }
        }
        while (i <= mid) tempArray[k++] = array[i++];
        while (j <= end) tempArray[k++] = array[j++];

        // Копируем отсортированные элементы обратно в основной массив
        for (int i = start; i <= end; ++i) {
            array[i] = tempArray[i];
        }
    }

private:
    struct Step {
        int start;
        int mid;
        int end;
    };

    std::vector<int> array;            // Массив для сортировки
    std::vector<int> tempArray;        // Временный массив для хранения промежуточных значений
    std::vector<Step> steps;           // Вектор для хранения шагов слияния
    int currentStep;                   // Текущий шаг сортировки
    bool sorted;                       // Флаг завершения сортировки
    int sortedIndex = 0;               // Индекс для покраски зеленым цветом

    QTimer *timer;                     // Таймер для анимации
    QTime startTime;                   // Время начала сортировки
};

#endif // LAB2_SEM3_MERGESORTWIDGET_H
