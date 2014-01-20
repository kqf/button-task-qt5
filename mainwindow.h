#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QPainter>
#include <QSizeGrip>
#include <QPushButton>
#include <QSpacerItem>


#include <iostream>

#include "windowtitle.h"
#include "customslider.h"



class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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

private slots:
   void changeStates();

};

#endif // MAINWINDOW_H
