#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QColor>
#include <QMouseEvent>
#include <cmath>


class CustomSlider :  public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal position READ position WRITE setSliderPosition)


public:
    explicit CustomSlider(QWidget * parent = 0);
    ~CustomSlider();

    qreal position() const { return sliderPosition; }
    void setSliderPosition(qreal p) { sliderPosition = p; }

    QSize sizeHint() const { return QSize(width(), height()); }


protected:
    void paintEvent(QPaintEvent * event = 0);
    void mousePressEvent(QMouseEvent * event = 0);

signals:
    void clicked();

private:
    bool withinArea(QPoint pos) const;

    // euclidian distance --
    qreal dist(qreal x1, qreal y1, qreal x2, qreal y2) const { return sqrt( pow(x1 - x2, 2) + pow(y1 - y2, 2) ); }

private:
    QPropertyAnimation * animation;
    qreal sliderPosition;

};

#endif // CUSTOMSLIDER_H
