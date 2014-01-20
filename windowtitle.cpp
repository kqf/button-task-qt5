#include "windowtitle.h"

WindowTitle::WindowTitle(QWidget *parent) :
    QWidget(parent),
    pixmapCache(0),
    title(this),
    icon(this),
    maximizeButton(TitleButton::BUTTON_MAXIMIZE, this),
    minimizeButton (TitleButton::BUTTON_MINIMIZE, this),
    closeButton(TitleButton::BUTTON_CLOSE, this)
{
    titleLayout.setMargin(0);
    titleLayout.setSpacing(0);
    setLayout(&titleLayout);

    title.setStyleSheet("color: Black ;  font-family: No; font-size:  14px");
    title.setFont(QFont(":/Assets/font/AlternateGotNo3D.ttf"));

    icon.setPixmap(QPixmap(":/titleBar/Assets/images/custom_icon.png"));


    titleLayout.setMargin(3);
    titleLayout.addWidget(&icon          , 0, 0, 0, 3);
    titleLayout.addWidget(&title         , 0, 1, 0, 3, Qt::AlignCenter);
    titleLayout.addLayout(&buttonsLayout , 0, 2, 0, 3, Qt::AlignRight );

    buttonsLayout.addWidget(&minimizeButton);
    buttonsLayout.addWidget(&maximizeButton);
    buttonsLayout.addWidget(&closeButton);

    connect (&minimizeButton, SIGNAL(clicked()), this, SLOT(Minimized()));
    connect (&maximizeButton, SIGNAL(clicked()), this, SLOT(Maximized()));
    connect (&closeButton   , SIGNAL(clicked()), this, SLOT(Quit()));
    setFixedHeight(25);

    UpdateWindowTitle();
}

WindowTitle::~WindowTitle()
{
    delete pixmapCache;
}

void WindowTitle::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);
  delete pixmapCache;
  pixmapCache = new QPixmap(size());
  pixmapCache->fill(Qt::transparent);

  QPainter painter(pixmapCache);

  QColor light(228, 220, 207);
  QRect frame(0, 0, width(), height());

  painter.setPen  (QPen  (light));
  painter.drawRect(frame);
}

void WindowTitle::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  if(pixmapCache != NULL)
  {
    QPainter painter(this);
    painter.drawPixmap(0, 0, *pixmapCache);
  }
}

void  WindowTitle::UpdateWindowTitle()
{
    title.setText( window()->windowTitle() );
}

void  WindowTitle::Minimized()
{
    window()-> showMinimized();
}

void  WindowTitle::Maximized()
{
    if(window()-> windowState() ==  Qt::WindowMaximized)
    {
        window()->showNormal();
    }
    else
    {
        window()->showMaximized();
    }
}

void  WindowTitle::Quit()
{
    QCoreApplication::exit();
}

void  WindowTitle::mousePressEvent(QMouseEvent  * event)
{
    mousePosition = event->pos();
    setCursor(QCursor(Qt::SizeAllCursor));
}

void  WindowTitle::mouseReleaseEvent ( QMouseEvent  * event)
{
  Q_UNUSED (event);
  setCursor(QCursor(Qt::ArrowCursor));
}

void  WindowTitle::mouseMoveEvent ( QMouseEvent  * event)
{
    QPoint p = event-> globalPos();
    window()->move(p - mousePosition);
 }
