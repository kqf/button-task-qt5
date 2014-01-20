#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QStateMachine>
#include <QSignalTransition>
#include <QColor>
#include <QMouseEvent>

#include<iostream>

class CustomSlider :  public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float position READ position WRITE setSliderPosition)
    Q_PROPERTY(QColor background READ background WRITE setBackground)


public:
    explicit CustomSlider(QWidget * parent = 0);
    ~CustomSlider();

    float position() const { return sliderPosition; }
    void setSliderPosition(float p) { sliderPosition = p; }

    QColor background() const { return canvasColor; }
    void setBackground(QColor color) {  canvasColor = color; }

    QSize sizeHint() const { return QSize(width(), height()); }


protected:
    void paintEvent(QPaintEvent * event = 0);
    void mousePressEvent(QMouseEvent * event = 0);
//    void resizeEvent(QResizeEvent * event = 0);

signals:
    void clicked();

public slots:
//    void buttonClicked();

private:
    QStateMachine * stateSwitcher;
    QState * state1;
    QState * state2;
    QSignalTransition * transition1;
    QSignalTransition * transition2;
    QColor canvasColor;

    float sliderPosition;
};

#endif // CUSTOMSLIDER_H
