#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QPainter>
#include <QSizeGrip>
#include <QSpacerItem>
#include <QMainWindow>

#include <QStyleOption>
#include <QStylePainter>



#include "windowtitle.h"
#include "customslider.h"



class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);
    void setWindowTitle(const QString & title);

signals:
    void WindowTitleChanged();

protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent  * event);

private:
    enum MainWindowStates {STATE_ON, STATE_OFF};

    QGridLayout mainLayout;
    WindowTitle mainTitle;
    QSizeGrip sizeGrip;

    CustomSlider button;
    QLabel textLabel;
    QSpacerItem spacer;

    MainWindowStates currentState;
    enum { SHADOW_SIZE = 4 };

    int currentShadowSize;

private slots:
    void changeStates();

};

#endif // MAINWINDOW_H
