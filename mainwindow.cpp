#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    sizeGrip(this),
    button(this),
    textLabel(this),
    spacer(100, 100),
    currentState(STATE_OFF)
{
    setLayout(&mainLayout);
    mainLayout.setMargin(0);
    mainLayout.setSpacing(0);
    mainLayout.setRowStretch(1 , 1);

    mainLayout.addWidget(&mainTitle, 0 , 0 , 1 , 1);
    mainLayout.addWidget(&button);


    textLabel.setStyleSheet("QLabel { color: rgb(228, 220, 207); font-style: bold; font-size: 12px; }");
    textLabel.setFont(QFont(":/Assets/font/AlternateGotNo3D.ttf"));
    textLabel.setText("USE SLIDER TO SWITCH WINDOW STATES");

    mainLayout.addWidget(&textLabel, 2, 0, 1, 1, Qt::AlignHCenter);
    mainLayout.addItem(&spacer, 3, 0, 1, 1, Qt::AlignHCenter);


    sizeGrip.hide();
    mainTitle.hide();

    connect(this, SIGNAL(WindowTitleChanged()), &mainTitle, SLOT(UpdateWindowTitle()) );
    connect(&button, SIGNAL(clicked()), this, SLOT(changeStates()) );
    resize(800, 600);
    setMinimumSize(200, 200);
    setWindowTitle(tr("Button"));

}


void MainWindow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QBrush background(QColor(255 , 255, 255));

    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width(), height());
}

void  MainWindow::setWindowTitle( const  QString  & title)
{
    QWidget :: setWindowTitle(title);
    emit WindowTitleChanged();
}

void  MainWindow::resizeEvent(QResizeEvent  * event)
{
    Q_UNUSED(event);
    sizeGrip.move   (width () - 30, height () - 30);
    sizeGrip.resize (           30,             30);
}

void MainWindow::changeStates()
{
    switch (currentState) {
    case STATE_OFF:
        currentState = STATE_ON;

        mainTitle.show();
        sizeGrip.show();

        setWindowFlags(Qt::FramelessWindowHint);
        show();
        break;

    case STATE_ON:
        currentState = STATE_OFF;
        mainTitle.hide();
        sizeGrip.hide();
        show();

        Qt::WindowFlags flags = windowFlags();
        flags &= ~Qt::FramelessWindowHint;
        setWindowFlags(flags);
        show();
        break;
    }
}
