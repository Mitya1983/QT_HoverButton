#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QColor>
#include <QEvent>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QResizeEvent>
namespace MT {

class HoverButton : public QPushButton
{Q_OBJECT
private:
    QColor _base_color;
    QColor _hover_color;
    QColor _pressed_color;
    QColor _pressed_text_color;
    QColor _initial_text_color;
    QPixmap *_background;
    QVBoxLayout *_main_layout;
    QLabel *_image_label;
    bool _background_image;
    bool _is_square;

    void _main_setup();
    void _set_base_color();
    void _set_hover_color();
    void _set_pressed_color();
    void _resize_image();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_toggled(bool checked);
    void on_pressed();
    void on_released();
public:
    //CONSTRUCTORS
    HoverButton(QWidget *parent = nullptr);
    HoverButton(QColor *base_color, QColor *hover_color = nullptr, QWidget *parent = nullptr);
    HoverButton(const HoverButton &other) = delete;
    HoverButton(HoverButton &&other) = delete;
    //OPERATORS
    HoverButton &operator=(const HoverButton &other) = delete;
    HoverButton &operator=(HoverButton &&other) =delete;
    //SETTERS
    void set_base_color(QColor color);
    void set_hover_color(QColor color);
    void set_pressed_color(QColor color);
    void set_pressed_text_color(QColor color);
    void set_initial_text_color(QColor color);
    void set_background_transparency(int transparency);
    void set_is_square(bool value);
    void set_background_image(const QString &path);
    void set_background_image_text(const QString text);
    //GETTERS

    //FUNCTIONS

    //DESTRUCTOR
    ~HoverButton() override;
};
} // namespace MT
#endif // HOVERBUTTON_H
