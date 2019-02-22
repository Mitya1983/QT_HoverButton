#include <QPalette>
#include <QDebug>

#include "hoverbutton.h"

HoverButton::HoverButton(QWidget *parent):
    QPushButton (parent),
    baseColor (parent == nullptr ? QColor(255, 255, 255, 255) : parent->palette().button().color()),
    hoverColor (baseColor.darker(125)),
    pressedColor (baseColor.darker(300)),
    pressedTextColor (baseColor)

{
    mainSetup();
    setBaseColor();
    connect(this, &HoverButton::toggled, this, &HoverButton::on_toggled);
}

HoverButton::HoverButton(QColor _baseColor, QColor _hoverColor, QWidget *parent) :
    QPushButton (parent),
    baseColor(std::move(_baseColor)),
    hoverColor (std::move(_hoverColor)),
    pressedColor(baseColor.darker(300)),
    pressedTextColor(baseColor)

{
    mainSetup();
    setBaseColor();
    connect(this, &HoverButton::toggled, this, &HoverButton::on_toggled);
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
    connect(this, &HoverButton::toggled, this, &HoverButton::on_toggled);
}

void HoverButton::setSquare(bool isSquare)
{
    square = isSquare;
}

void HoverButton::setBackgroundImage(const QString path)
{
    background = new QPixmap(path);
    mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    imageLabel->setPixmap(QPixmap(background->scaledToHeight(height(), Qt::SmoothTransformation)));
    mainLayout->addWidget(imageLabel);
    setLayout(mainLayout);
    image = true;
}

void HoverButton::mainSetup()
{
    image = false;
    square = false;
    background = nullptr;
    setAutoFillBackground(true);
    setFlat(true);
    setMouseTracking(true);
    setTabletTracking(true);
    setCursor(Qt::PointingHandCursor);
}

void HoverButton::setBaseColor()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, baseColor);
    if (initialTextColor != QColor("Invalid"))
        pal.setColor(QPalette::ButtonText, initialTextColor);
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

void HoverButton::resizeImage()
{
    QPixmap scaled = background->scaledToHeight(height(), Qt::SmoothTransformation);
    imageLabel->setPixmap(scaled);
}

void HoverButton::enterEvent(QEvent *event)
{
    if (!isChecked() && !image)
    {
        setHoverColor();
        event->accept();
    }
    else
        event->ignore();
}

void HoverButton::leaveEvent(QEvent *event)
{
    if(!isChecked() && !image)
    {
        setBaseColor();
        event->accept();
    }
    else
        event->ignore();
}

void HoverButton::resizeEvent(QResizeEvent *event)
{
    if (square)
    {
        setFixedHeight(width());
        event->accept();
    }
    if (image)
    {
        resizeImage();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void HoverButton::on_toggled(bool checked)
{
    if (checked && !image)
        setPressedColor();
    if (!checked && !image)
        setBaseColor();
}

HoverButton::~HoverButton()
{
    if (background != nullptr)
        delete background;
}
