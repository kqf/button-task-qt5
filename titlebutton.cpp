#include "titlebutton.h"
#include <iostream>

TitleButton::TitleButton(ButtonType t, QWidget *parent):
    QAbstractButton(parent),
    type(t),
    currentPicture(0)
{
    QString normalName(":/titleBar/Assets/images/");
    QString clickedName(":/titleBar/Assets/images/");
    switch(type)
    {
    case BUTTON_MINIMIZE:
        normalName += "minimize.png";
        break;
    case BUTTON_MAXIMIZE:
        normalName += "maximize.png";
        clickedName += "restore.png";
        break;
     case BUTTON_CLOSE:
        normalName += "close.png";
        break;
     }
    if ( !normalPicture.load(normalName) )
        qErrnoWarning(0, "Cannot load picture");
    if ( !clickedPicture.load(clickedName) && type == BUTTON_MAXIMIZE)
        qErrnoWarning(0, "Cannot load picture");

    currentPicture = &normalPicture;
    connect(this, SIGNAL(clicked()), this, SLOT(changeStateToClicked()) );
}

TitleButton::~TitleButton()
{
    delete currentPicture;
}

void TitleButton::paintEvent(QPaintEvent  *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, *currentPicture);
}

QSize TitleButton::sizeHint() const
{
    return QSize(currentPicture->width(),
                 currentPicture->height());
}

void TitleButton::changeStateToClicked()
{
    if (clickedPicture.isNull())
        return;

    if ( currentPicture == &clickedPicture)
        currentPicture = &normalPicture;
    else
        currentPicture = &clickedPicture;
}
