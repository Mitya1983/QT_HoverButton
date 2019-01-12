#include <QPalette>
#include <QDebug>

#include "hoverbutton.h"

HoverButton::HoverButton(QWidget *parent)
    : QPushButton (parent)
{
    mainSetup();
    setBaseColor();
}

HoverButton::HoverButton(QColor _baseColor, QColor _hoverColor, QWidget *parent) :
    QPushButton (parent),
    baseColor(std::move(_baseColor)),
    hoverColor (std::move(_hoverColor))
{
    mainSetup();
    setBaseColor();
}

HoverButton::HoverButton(QColor _baseColor, QColor _hoverColor, QColor _pressedColor, QColor _pressedTextColor, QWidget *parent):
    QPushButton (parent),
    baseColor(std::move(_baseColor)),
    hoverColor(std::move(_hoverColor)),
    pressedColor(std::move(_pressedColor)),
    pressedTextColor(std::move(_pressedTextColor))
{
    mainSetup();
    setBaseColor();
    qDebug() << initialTextColor;
}

void HoverButton::mainSetup()
{
    setAutoFillBackground(true);
    setFlat(true);
    setMouseTracking(true);
}

void HoverButton::setBaseColor()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, baseColor);
    setPalette(pal);
}

void HoverButton::setHoverColor()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, hoverColor);
    setPalette(pal);
}

void HoverButton::setPressedColor()
{
    initialTextColor = palette().buttonText().color();
    QPalette pal = palette();
    pal.setColor(QPalette::Button, pressedColor);
    pal.setColor(QPalette::ButtonText, pressedTextColor);
    setPalette(pal);
}

void HoverButton::enterEvent(QEvent *event)
{
    setHoverColor();
    event->accept();
}

void HoverButton::leaveEvent(QEvent *event)
{
    setBaseColor();
    event->accept();
}

void HoverButton::on_toggled(bool checked)
{
    if (checked)
        setPressedColor();
    if (!checked)
        setBaseColor();
}
