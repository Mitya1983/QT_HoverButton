#include "hoverbutton.h"
#include <QApplication>
#include <QColor>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *widget = new QWidget();
    QColor test(Qt::white);
    QColor test1(Qt::green);
    QColor test2(Qt::black);
    QColor test3(Qt::yellow);
//    HoverButton w(test, test1, test2, test3);
    MT::HoverButton w(widget);
    widget->setMinimumSize(400, 400);
    widget->setAutoFillBackground(true);
    QPalette pallete = widget->palette();
    pallete.setColor(QPalette::ColorGroup::All, QPalette::ColorRole::Window, Qt::green);
    widget->setPalette(pallete);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(&w, 0, 0, Qt::AlignCenter);
    w.setMinimumSize(widget->width()/2, widget->height()/2);
    w.set_background_image("/home/mitya/Projects/TV_Menu/Data/icons/tv_icon.png");
    w.set_background_image_text("TEST");
    w.set_background_transparency(125);
    MT::HoverButton w1(widget);
    w1.setMinimumSize(widget->width()/2, widget->height()/2);
    w1.set_background_image("/home/mitya/Projects/TV_Menu/Data/icons/tv_icon.png");
    w1.set_background_image_text("TEST!");
    w1.set_background_transparency(125);
    layout->addWidget(&w1, 0, 1, Qt::AlignCenter);
    widget->setLayout(layout);
    widget->show();

    return a.exec();
}
