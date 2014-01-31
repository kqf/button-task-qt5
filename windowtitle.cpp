#include "windowtitle.h"

WindowTitle::WindowTitle(QWidget * parent) :
    QFrame(parent),
    title(this),
    icon(this),
    maximizeButton(this),
    minimizeButton (this),
    closeButton(this)
{
    titleLayout.setMargin(4);
    titleLayout.setSpacing(4);
    titleLayout.setRowStretch(0, 1);
    setLayout(&titleLayout);


    icon.setPixmap(QPixmap(":/titleBar/Assets/images/custom_icon.png"));


    int nRows = 20;
    title.setMargin(4);

    titleLayout.addLayout(&labelLayout      , 0, 0, 0, nRows, Qt::AlignLeft);
    titleLayout.addLayout(&buttonsLayout , 0, nRows -1, 1, nRows, Qt::AlignRight );

    labelLayout.setSpacing(0);
    labelLayout.addWidget(&icon);
    labelLayout.addWidget(&title);

    buttonsLayout.setSpacing(0);
    buttonsLayout.setMargin(0);

    buttonsLayout.addWidget(&minimizeButton);
    buttonsLayout.addWidget(&maximizeButton);
    buttonsLayout.addWidget(&closeButton);


    minimizeButton.setObjectName("minimizeButton");
    maximizeButton.setObjectName("maximizeButton");
    closeButton.setObjectName("closeButton");

    QSize buttonSize(18, 18);

    minimizeButton.setFixedSize(buttonSize);
    maximizeButton.setFixedSize(buttonSize);
    closeButton.setFixedSize(buttonSize);

    QSize iconSize(22, 14);
    icon.setFixedSize(iconSize);

    connect(&minimizeButton, SIGNAL(clicked()), this, SLOT(Minimized()));
    connect(&maximizeButton, SIGNAL(clicked()), this, SLOT(Maximized()));
    connect(&closeButton   , SIGNAL(clicked()), this, SLOT(Quit()));

    setFixedHeight(28);
    UpdateWindowTitle();
}

WindowTitle::~WindowTitle()
{
}

void  WindowTitle::UpdateWindowTitle()
{
    title.setText(window()->windowTitle());
}

void  WindowTitle::Minimized()
{
    window()->showMinimized();
}

void  WindowTitle::Maximized()
{
    if(window()->windowState() ==  Qt::WindowMaximized)
    {
        maximizeButton.setStyleSheet("background-image: url(:titleBar/Assets/images/maximize.png)");
        window()->showNormal();
    }
    else
    {
        window()->showMaximized();
        maximizeButton.setStyleSheet("background-image: url(:titleBar/Assets/images/restore.png)");
    }
}

void  WindowTitle::Quit()
{
    QCoreApplication::exit();
}

void  WindowTitle::mousePressEvent(QMouseEvent * event)
{
    mousePosition = event->pos();
    setCursor(QCursor(Qt::SizeAllCursor));
}

void  WindowTitle::mouseReleaseEvent(QMouseEvent * event)
{
  Q_UNUSED (event);
  setCursor(QCursor(Qt::ArrowCursor));
}

void  WindowTitle::mouseMoveEvent(QMouseEvent * event)
{
    QPoint p = event->globalPos();
    window()->move(p - mousePosition);
}
