#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QColor>
#include <QEvent>
#include <QPixmap>
#include <QGridLayout>
#include <QLabel>
#include <QResizeEvent>

class HoverButton : public QPushButton
{
    Q_OBJECT
private: /*Members*/
    QColor baseColor, hoverColor, pressedColor, pressedTextColor, initialTextColor;
    bool square, image;
    QPixmap *background;
    QGridLayout *mainLayout;
    QLabel *imageLabel;
public: /*Methods*/
    /*If no colors is paased to constructor the background color will be either taken from parent background color either
      (if parent is nullptr) will be set to white, the hover, pressed and pressed text colors will be calculated on base of baclground color*/
    HoverButton(QWidget *parent = nullptr);
    /*Pressed and pressed text color will be calcultaed on base of background color*/
    HoverButton(QColor _baseColor, QColor _hoverColor, QWidget *parent = nullptr);
    HoverButton(QColor _baseColor, QColor _hoverColor, QColor _pressedColor, QColor _pressedTextColor, QWidget *parent = nullptr);
    void setSquare(bool);
    void setBackgroundImage(const QString path);
private: /*Methods*/
    //Setting up the button (flat, autoFillBackground, mouse and tablet tracking)
    void mainSetup();
    //Aplying background color
    void setBaseColor();
    //Aplying hover color
    void setHoverColor();
    //Aplying pressed color
    void setPressedColor();
    //Resising background image
    void resizeImage();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_toggled(bool checked);
public: /*Destructor*/
    ~HoverButton() override;
};

#endif // HOVERBUTTON_H
