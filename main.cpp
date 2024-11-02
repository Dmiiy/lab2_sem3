#include <QApplication>

#include "include/animation/BubbleSortWidget.h"
#include "include/animation/CountingSortWidget.h"
#include "include/animation/HeapSortWidget.h"
#include "include/animation/QuickSortWidget.h"
#include "include/animation/SelectionSortWidget.h"
#include "include/animation/ShakerSortWidget.h"
#include "include/animation/ShellSortWidget.h"
#include "include/animation/MergeSortWidget.h"
#include "include/animation/InsertionSortWidget.h"
#include "include/animation/BinaryInsertionSortWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BubbleSortWidget widget;
    widget.show();

    return app.exec();
}