#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QStringList>
#include <QElapsedTimer>
#include <QDateTime>
#include "sequence/ArraySequence.h"
#include "sorting/QuickSorter.h"

class SorterWindow : public QWidget {

public:
    SorterWindow(QWidget *parent = nullptr) : QWidget(parent), sequence(new ArraySequence<int>()) {
        // Инициализация компонентов UI
        setWindowTitle("Integer File Sorter");
        setFixedSize(500, 300);

        logEdit = new QTextEdit(this); // Текстовый редактор для логов
        logEdit->setReadOnly(true);
        logEdit->setPlaceholderText("Лог сообщений...");

        loadButton = new QPushButton("Загрузить файл", this);
        sortAscButton = new QPushButton("Сортировать по возрастанию и сохранить", this);
        sortDescButton = new QPushButton("Сортировать по убыванию и сохранить", this);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *buttonLayout = new QHBoxLayout;

        buttonLayout->addWidget(loadButton);
        buttonLayout->addWidget(sortAscButton);
        buttonLayout->addWidget(sortDescButton);

        mainLayout->addLayout(buttonLayout);
        mainLayout->addWidget(logEdit);

        setLayout(mainLayout);

        connect(loadButton, &QPushButton::clicked, this, &SorterWindow::loadFile);
        connect(sortAscButton, &QPushButton::clicked, this, &SorterWindow::sortAndSaveAscending);
        connect(sortDescButton, &QPushButton::clicked, this, &SorterWindow::sortAndSaveDescending);
    }

    ~SorterWindow() override {
        delete sequence;
    }

private slots:
    void loadFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt)");
        if (fileName.isEmpty()) {
            logMessage("Ошибка: файл не выбран.");
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            logMessage("Ошибка: не удалось открыть файл.");
            return;
        }

        // Очищаем последовательность перед загрузкой нового файла
        sequence->clear();

        QTextStream in(&file);
        int value;
        while (!in.atEnd()) {
            QString line = in.readLine();
            bool ok;
            value = line.toInt(&ok);
            if (ok) {
                sequence->append(value);
            }
        }
        file.close();

        logMessage("Файл успешно загружен: " + fileName);
    }

    void sortAndSaveAscending() {
        sortAndSave(true);
    }

    void sortAndSaveDescending() {
        sortAndSave(false);
    }

private:
    QTextEdit *logEdit;
    QPushButton *loadButton;
    QPushButton *sortAscButton;
    QPushButton *sortDescButton;
    ArraySequence<int> *sequence;

    void sortAndSave(bool way) {
        if (sequence->getLength() == 0) {
            logMessage("Ошибка: нет данных для сортировки. Загрузите файл.");
            return;
        }

        // Выбор файла для сохранения
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text Files (*.txt)");
        if (fileName.isEmpty()) {
            logMessage("Ошибка: файл не выбран для сохранения.");
            return;
        }

        // Засекаем время сортировки
        QElapsedTimer timer;


        // Сортировка
        QuickSorter<int> sorter(way ? ascending : descending);
        timer.start();
        sorter.sort(sequence);
        qint64 elapsed = timer.elapsed();  // Время сортировки в миллисекундах

        // Запись в файл
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            logMessage("Ошибка: не удалось сохранить файл.");
            return;
        }

        QTextStream out(&file);
        for (int i = 0; i < sequence->getLength(); ++i) {
            out << QString::number((*sequence)[i]) << "\n";
        }
        file.close();

        // Сообщение о завершении с информацией о времени сортировки
        logMessage(way ? "Файл успешно отсортирован по возрастанию и сохранен: " + fileName
                       : "Файл успешно отсортирован по убыванию и сохранен: " + fileName);
        logMessage("Время сортировки: " + QString::number(elapsed) + " мс");
    }

    // Логирование сообщений в logEdit с отметкой времени
    void logMessage(const QString &message) {
        logEdit->append(QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss] ") + message);
    }
};
