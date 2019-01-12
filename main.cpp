#include "hoverbutton.h"
#include <QApplication>
#include <QColor>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QColor test(Qt::white);
    QColor test1(Qt::black);
    QColor test2(Qt::green);
    QColor test3(Qt::yellow);
    HoverButton w(test, test1, test2, test3);
    w.setCheckable(true);
    w.show();

    return a.exec();
}
