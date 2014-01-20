#include "customslider.h"
using std::cout;
using std::endl;


CustomSlider::CustomSlider(QWidget *parent) :
    QWidget(parent),
    stateSwitcher(new QStateMachine),
    state1(new QState(stateSwitcher)),
    state2(new QState(stateSwitcher)),
    sliderPosition(0)

{
    canvasColor = QColor(228, 220, 207);
    QColor onColor = QColor(145, 218, 77);

    state1->assignProperty(this, "background", canvasColor);
    state2->assignProperty(this, "background", onColor);
    state1->assignProperty(this, "position", sliderPosition);
    state2->assignProperty(this, "position", 1);


    stateSwitcher-> setInitialState(state1);

    QSignalTransition *transition1 = state1->addTransition(this, SIGNAL(clicked()), state2);
    transition1->addAnimation(new QPropertyAnimation(this, "background"));
    transition1->addAnimation(new QPropertyAnimation(this, "position"));

    QSignalTransition *transition2 = state2->addTransition(this, SIGNAL(clicked()), state1);
    transition2->addAnimation(new QPropertyAnimation(this, "background"));
    transition2->addAnimation(new QPropertyAnimation(this, "position"));

    stateSwitcher->start();

    setMinimumSize(200, 200);
}

CustomSlider::~CustomSlider()
{
    delete stateSwitcher;
}

void CustomSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::blue));

    QPainterPath FillPath;

    float centerX = width()/2;
    float centerY = height()/2;

    float radius = 0.35*height()/2;
    float buttonWidth = width()/2;
    float buttonHeight = 2*radius;

    float Y = centerY - radius;

    // left circle
    FillPath.addEllipse(centerX - buttonWidth/2           , Y, 2*radius              , buttonHeight);
    FillPath.addRect   (centerX - buttonWidth/2 +   radius, Y, buttonWidth - 2*radius, buttonHeight);
    FillPath.addEllipse(centerX + buttonWidth/2 - 2*radius, Y, 2*radius              , buttonHeight);
    FillPath.setFillRule(Qt::WindingFill);
    painter.fillPath(FillPath, canvasColor);

    QPainterPath TextPath;
    QFont textFont(":/Assets/font/AlternateGotNo3D.ttf");

    QString on("ON");
    QString off("OFF");

    QFontMetrics metrix(textFont);
    float onX = centerX - buttonWidth/2 + radius - metrix.width(on)/2;
    float onY = centerY + metrix.height()/2;

    float offX = centerX + buttonWidth/2 -radius - metrix.width(off)/2;
    float offY = centerY + metrix.height()/2;

    TextPath.addText(QPointF(onX, onY), textFont, on);
    TextPath.addText(QPointF(offX, offY), textFont, off);
    painter.fillPath(TextPath, Qt::white);

    QPainterPath ButtonPath;
    float delta = 4;
    float radiusB = radius - delta;

    ButtonPath.addEllipse( centerX - buttonWidth/2  + delta
                           + sliderPosition *( 2*buttonWidth/2 - 2*radius)
                          , Y + delta, 2*radiusB, 2*radiusB);

    painter.fillPath(ButtonPath, Qt::white);
    update();
}

void CustomSlider::mousePressEvent(QMouseEvent * event)
{
    float radius = 0.35*height()/2;
    QPoint center( mapFromGlobal( QPoint(width()/4 + radius + sliderPosition*(width()/2 - 2*radius),
                                         height()/2)) );
    QPoint point = center - mapFromGlobal(event->pos());

    if(point.manhattanLength() < radius)
        emit clicked();
}


