#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QColor>
#include <QEvent>

class HoverButton : public QPushButton
{
    Q_OBJECT
private: /*Members*/
    QColor baseColor, hoverColor, pressedColor, pressedTextColor, initialTextColor;
public:
    HoverButton(QWidget *parent = nullptr);
    HoverButton(QColor _baseColor, QColor _hoverColor, QWidget *parent = nullptr);
    HoverButton(QColor _baseColor, QColor _hoverColor, QColor _pressedColor, QColor _pressedTextColor, QWidget *parent = nullptr);
private: /*Methods*/
    void mainSetup();
    void setBaseColor();
    void setHoverColor();
    void setPressedColor();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private slots:

    void on_toggled(bool checked);
public: /*Destructor*/
    ~HoverButton() override = default;
};

#endif // HOVERBUTTON_H
