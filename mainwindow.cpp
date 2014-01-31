#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
    QWidget(parent),
    sizeGrip(this),
    button(this),
    textLabel(this),
    spacer(100, 100),
    currentState(STATE_OFF),
    currentShadowSize(0)
{
    setLayout(&mainLayout);
    mainLayout.setMargin(currentShadowSize);
    mainLayout.setSpacing(0);
    mainLayout.setRowStretch(1 , 1);

    mainLayout.addWidget(&mainTitle, 0 , 0 , 1 , 1);
    mainLayout.addWidget(&button);


    textLabel.setStyleSheet("QLabel { color: rgb(204, 204, 204); font-style: bold; font-size: 16px; }");
    QFont font("AlternateGotNo3D");

    textLabel.setFont(font);
    textLabel.setText("USE SLIDER TO SWITCH WINDOW STATES");


    setAutoFillBackground(false);
    setAttribute(Qt::WA_TranslucentBackground, true);

    mainLayout.addWidget(&textLabel, 2, 0, 1, 1, Qt::AlignHCenter);
    mainLayout.addItem(&spacer, 3, 0, 1, 1, Qt::AlignHCenter);


    sizeGrip.hide();
    mainTitle.hide();

    connect(this, SIGNAL(WindowTitleChanged()), &mainTitle, SLOT(UpdateWindowTitle()) );
    connect(&button, SIGNAL(clicked()), this, SLOT(changeStates()) );

    QDesktopWidget desktop;
    QRect geom = desktop.availableGeometry(desktop.primaryScreen());

    resize(800, 600);
    move(geom.width()/2 - width()/2, geom.height()/2 - height()/2);
    setMinimumSize(400, 400);
    setWindowTitle(tr("Button"));

}


void MainWindow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QStyleOption options;
    options.init(this);
    QStylePainter p(this);
    p.drawPrimitive(QStyle::PE_Widget, options);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(255, 255, 255)));


    painter.drawRect(currentShadowSize, currentShadowSize, width() - 2*currentShadowSize, height() - 2*currentShadowSize);

    update();

}

void  MainWindow::setWindowTitle( const  QString  & title)
{
    QWidget :: setWindowTitle(title);
    emit WindowTitleChanged();
}

void  MainWindow::resizeEvent(QResizeEvent  * event)
{
    Q_UNUSED(event);
    if(isMaximized() || currentState == STATE_OFF)
        currentShadowSize = 0;
    else
        currentShadowSize = SHADOW_SIZE;

    mainLayout.setMargin(currentShadowSize);

    sizeGrip.move   (width () - 30 - currentShadowSize, height () - 30 - currentShadowSize);
    sizeGrip.resize (           30,             30);

}

void MainWindow::changeStates()
{
    int deltaWindowSize = 28;
    int shadowCorrection = 2*SHADOW_SIZE;

    switch (currentState)
    {
    case STATE_OFF:
        currentState = STATE_ON;

        mainTitle.show();
        sizeGrip.show();

        setWindowFlags(Qt::FramelessWindowHint);

        resize(width() + shadowCorrection, height() + deltaWindowSize + shadowCorrection );
        move(pos().x() - shadowCorrection/2, pos().y() - shadowCorrection/2);

        update();
        show();
        break;

    case STATE_ON:
        currentState = STATE_OFF;

        mainTitle.hide();
        sizeGrip.hide();


        Qt::WindowFlags flags = windowFlags() ;
        flags &= ~Qt::FramelessWindowHint;
        setWindowFlags(flags);

        resize(width() - shadowCorrection, height() - deltaWindowSize - shadowCorrection);
        move(pos().x() + shadowCorrection/2, pos().y() + shadowCorrection/2);

        update();
        show();
        break;
    }
}
