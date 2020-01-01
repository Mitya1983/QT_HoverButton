#include <QPalette>
#include <QDebug>
#include "hoverbutton.h"

void MT::HoverButton::_main_setup()
{
    _background_image = false;
    _is_square = false;
    _background = nullptr;
    setAutoFillBackground(true);
    setFlat(true);
    setMouseTracking(true);
    setTabletTracking(true);
    setCursor(Qt::PointingHandCursor);
}

void MT::HoverButton::_set_base_color()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, _base_color);
    if (_initial_text_color != QColor("Invalid")){
        pal.setColor(QPalette::ButtonText, _initial_text_color);
    }
    setPalette(pal);
}

void MT::HoverButton::_set_hover_color()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, _hover_color);
    if (_initial_text_color != QColor("Invalid")){
        pal.setColor(QPalette::ButtonText, _initial_text_color);
    }
    setPalette(pal);
}

void MT::HoverButton::_set_pressed_color()
{
    _initial_text_color = palette().buttonText().color();
    QPalette pal = palette();
    pal.setColor(QPalette::Button, _pressed_color);
    pal.setColor(QPalette::ButtonText, _pressed_text_color);
    setPalette(pal);
}

void MT::HoverButton::_resize_image()
{
    QPixmap scaled = _background->scaledToHeight(height(), Qt::SmoothTransformation);
    _image_label->setPixmap(scaled);
}

void MT::HoverButton::enterEvent(QEvent *event)
{
    if (!isChecked() && !_background_image){
        _set_hover_color();
        event->accept();
    }
    else{
        event->ignore();
    }
}

void MT::HoverButton::leaveEvent(QEvent *event)
{
    if(!isChecked() && !_background_image){
        _set_base_color();
        event->accept();
    }
    else{
        event->ignore();
    }
}

void MT::HoverButton::resizeEvent(QResizeEvent *event)
{
    if (_is_square){
        if (width() > height())
            setFixedHeight(width());
        if (width() < height())
            setFixedWidth(height());
        event->accept();
    }
    if (_background_image){
        _resize_image();
        event->accept();
    }
    else{
        event->ignore();
    }
}

void MT::HoverButton::on_toggled(bool checked)
{
    if (checked && !_background_image){
        _set_pressed_color();
    }
    if (!checked && !_background_image){
        _set_hover_color();
    }
}

void MT::HoverButton::on_pressed()
{
    _set_pressed_color();
}

void MT::HoverButton::on_released()
{
    if (!isCheckable()){
        _set_base_color();
    }
}

MT::HoverButton::HoverButton(QWidget *parent):
    QPushButton(parent),
    _base_color(parent == nullptr ? QColor(255, 255, 255, 255) : parent->palette().button().color()),
    _hover_color(_base_color.darker(125)),
    _pressed_color(_base_color.darker(300)),
    _pressed_text_color(_base_color)

{
    _main_setup();
    _set_base_color();
    connect(this, &MT::HoverButton::toggled, this, &MT::HoverButton::on_toggled);
    connect(this, &MT::HoverButton::pressed, this, &MT::HoverButton::on_pressed);
    connect(this, &MT::HoverButton::released, this, &MT::HoverButton::on_released);
}

MT::HoverButton::HoverButton(QColor *base_color, QColor *hover_color, QWidget *parent) :
    QPushButton(parent),
    _base_color(std::move(*base_color)),
    _hover_color(hover_color == nullptr ? _base_color.darker(125) : std::move(*hover_color)),
    _pressed_color(_base_color.darker(300)),
    _pressed_text_color(_base_color)

{
    _main_setup();
    _set_base_color();
    connect(this, &MT::HoverButton::toggled, this, &MT::HoverButton::on_toggled);
    connect(this, &MT::HoverButton::pressed, this, &MT::HoverButton::on_pressed);
    connect(this, &MT::HoverButton::released, this, &MT::HoverButton::on_released);
}

void MT::HoverButton::set_base_color(QColor color)
{
    _base_color = color;
    _set_base_color();
    _hover_color = _base_color.darker(125);
    _pressed_color = _base_color.darker(300);
}

void MT::HoverButton::set_hover_color(QColor color)
{
    _hover_color = color;
}

void MT::HoverButton::set_pressed_color(QColor color)
{
    _pressed_color = color;
}

void MT::HoverButton::set_pressed_text_color(QColor color)
{
    _pressed_text_color = color;
}

void MT::HoverButton::set_initial_text_color(QColor color)
{
    _initial_text_color = color;
}

void MT::HoverButton::set_background_transparency(int transparency)
{
    _base_color.setAlpha(transparency);
    _hover_color.setAlpha(transparency);
    _pressed_color.setAlpha(transparency);
    _set_base_color();
}

void MT::HoverButton::set_is_square(bool value)
{
    _is_square = value;
}

void MT::HoverButton::set_background_image(const QString &path)
{
    _background = new QPixmap(path);
    _main_layout = new QVBoxLayout(this);
    _main_layout->setContentsMargins(0, 0, 0, 0);
    _image_label = new QLabel(this);
    _image_label->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    _main_layout->addWidget(_image_label);
    setLayout(_main_layout);
    _image_label->setScaledContents(true);
    _image_label->setPixmap(*_background);
    _background_image = true;
}

void MT::HoverButton::set_background_image_text(const QString text)
{
    if (_main_layout != nullptr){
        QLabel *image_text = new QLabel();
        image_text->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        image_text->setText(text);
        _main_layout->addWidget(image_text);
        QFont font = image_text->font();
        font.setBold(true);
        font.setPointSize(_main_layout->parentWidget()->height()/10);
        image_text->setFont(font);
    }
}

MT::HoverButton::~HoverButton()
{
    if (_background != nullptr){
        delete _background;
    }
}
