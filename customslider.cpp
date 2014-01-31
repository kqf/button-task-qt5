#include "customslider.h"

CustomSlider::CustomSlider(QWidget * parent) :
    QWidget(parent),
    animation(new QPropertyAnimation(this, "position")),
    sliderPosition(0)
{
    animation->setDuration(500);
    connect(animation, SIGNAL(finished()), this, SIGNAL(clicked()));
}


CustomSlider::~CustomSlider()
{
    delete animation;
}

void CustomSlider::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::blue));

    QPainterPath FillPath;

    qreal centerX = width()/2;
    qreal centerY = height()/2;

    qreal radius = 0.35*height()/2;
    qreal buttonWidth = width()/2;
    qreal buttonHeight = 2*radius;

    qreal Y = centerY - radius;

    FillPath.addEllipse(centerX - buttonWidth/2           , Y, 2*radius              , buttonHeight);
    FillPath.addRect   (centerX - buttonWidth/2 +   radius, Y, buttonWidth - 2*radius, buttonHeight);
    FillPath.addEllipse(centerX + buttonWidth/2 - 2*radius, Y, 2*radius              , buttonHeight);
    FillPath.setFillRule(Qt::WindingFill);

    painter.fillPath(FillPath,  QColor(228 - sliderPosition*(83),
                                       220 - sliderPosition*(2),
                                       207 - sliderPosition*(130)));

    QPainterPath TextPath;

    QFont textFont("AlternateGotNo3D");
    textFont.setPixelSize(height()/24);

    QString on("ON");
    QString off("OFF");

    QFontMetrics metrix(textFont);

    qreal onX = centerX - buttonWidth/2 + radius - metrix.width(on)/2;
    qreal onY = centerY + metrix.height()/2;

    qreal offX = centerX + buttonWidth/2 -radius - metrix.width(off)/2;
    qreal offY = centerY + metrix.height()/2;

    TextPath.addText(QPointF(onX, onY), textFont, on);
    TextPath.addText(QPointF(offX, offY), textFont, off);
    painter.fillPath(TextPath, Qt::white);

    QPainterPath ButtonPath;
    qreal delta = 4;
    qreal radiusB = radius - delta;

    ButtonPath.addEllipse( centerX - buttonWidth/2  + delta
                           + sliderPosition *( 2*buttonWidth/2 - 2*radius)
                          , Y + delta, 2*radiusB, 2*radiusB);

    painter.fillPath(ButtonPath, QColor(250, 250, 250));
    update();
}

bool CustomSlider::withinArea(QPoint point) const
{
    qreal radius = 0.35*height()/2;

    qreal x = point.x();
    qreal y = point.y();

    qreal lCenterX =   width()/4 + radius;
    qreal rCenterX = 3*width()/4 - radius;
    qreal CenterY =  height()/2;

    bool leftCircle =  dist(x, y, lCenterX, CenterY) <= radius;
    bool rightCircle = dist(x, y, rCenterX, CenterY) <= radius;

    bool withinWidth = (x > lCenterX) && (x < rCenterX);
    bool withinHeight = fabs(height()/2 - y) < radius;
    bool rectangle = withinHeight && withinWidth;

    return leftCircle || rightCircle || rectangle;
}

void CustomSlider::mousePressEvent(QMouseEvent * event)
{
    if( !withinArea(event->pos()) )
        return;

    animation->stop();
    animation->setStartValue(sliderPosition);
    animation->setEndValue((int(sliderPosition) + 1) % 2);
    animation->start();
}


