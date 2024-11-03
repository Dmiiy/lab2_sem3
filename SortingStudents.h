//
// Created by dimak on 03.11.2024.
//

#ifndef LAB2_SEM3_SORTINGSTUDENTS_H
#define LAB2_SEM3_SORTINGSTUDENTS_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QRandomGenerator>
#include <algorithm>
#include "sorting/User.h"
#include "sorting/QuickSorter.h"


class SortingStudents : public QMainWindow {
    //Q_OBJECT

public:
    SortingStudents(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Инициализация центрального виджета и макета
        auto *centralWidget = new QWidget(this);
        auto *mainLayout = new QVBoxLayout(centralWidget);
        setCentralWidget(centralWidget);

        // Инициализация компонентов интерфейса
        arraySizeInput = new QLineEdit(this);
        arraySizeInput->setPlaceholderText("Введите количество пользователей");

        outputDisplay = new QTextEdit(this);
        outputDisplay->setReadOnly(true);

        generateButton = new QPushButton("Сгенерировать и отсортировать", this);

        sortFieldComboBox = new QComboBox(this);
        sortFieldComboBox->addItems({"Фамилия", "Возраст"});

        sortOrderComboBox = new QComboBox(this);
        sortOrderComboBox->addItems({"По возрастанию", "По убыванию"});

        // Добавление виджетов в макет
        mainLayout->addWidget(new QLabel("Количество пользователей:", this));
        mainLayout->addWidget(arraySizeInput);
        mainLayout->addWidget(new QLabel("Поле для сортировки:", this));
        mainLayout->addWidget(sortFieldComboBox);
        mainLayout->addWidget(new QLabel("Порядок сортировки:", this));
        mainLayout->addWidget(sortOrderComboBox);
        mainLayout->addWidget(generateButton);
        mainLayout->addWidget(outputDisplay);

        // Соединение кнопки с функцией генерации и сортировки пользователей
        connect(generateButton, &QPushButton::clicked, this, &SortingStudents::onGenerateAndSortUsers);
    }

private slots:

    void onGenerateAndSortUsers() {
        bool ok;
        int count = arraySizeInput->text().toInt(&ok);
        if (!ok || count <= 0) {
            outputDisplay->append("Некорректное количество пользователей.");
            return;
        }

        // Генерация списка пользователей
        ArraySequence<User> users;
        for (int i = 0; i < count; ++i) {
            users.append(User::generateRandomUser());
        }

        // Определение поля и порядка сортировки
        QString sortField = sortFieldComboBox->currentText();
        QString sortOrder = sortOrderComboBox->currentText();
        HelpClass helpClass;
        // Выбор нужного компаратора на основе выбранного поля и порядка
        if (sortField == "Фамилия") {
            if (sortOrder == "По возрастанию") {
                QuickSorter sorter(helpClass.compareByLastNameAscending);
                sorter.sort(&users);
            } else {
                QuickSorter sorter(helpClass.compareByLastNameDescending);
                sorter.sort(&users);
            }
        } else if (sortField == "Возраст") {
            if (sortOrder == "По возрастанию") {
                QuickSorter sorter(helpClass.compareByAgeAscending);
                sorter.sort(&users);
            } else {
                QuickSorter sorter(helpClass.compareByAgeDescending);
                sorter.sort(&users);
            }
        }

        // Вывод результата
        outputDisplay->clear();
        outputDisplay->append("Отсортированный список пользователей:");
        for (int i = 0; i < users.getLength(); ++i) {
            User user = users[i];
            outputDisplay->append(
                    user.getFirstName() + " " + user.getLastName() + ", возраст: " + QString::number(user.getAge()));
        }
    }

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLineEdit *arraySizeInput;
    QTextEdit *outputDisplay;
    QPushButton *generateButton;
    QComboBox *sortFieldComboBox;
    QComboBox *sortOrderComboBox;
};

#endif //LAB2_SEM3_SORTINGSTUDENTS_H
