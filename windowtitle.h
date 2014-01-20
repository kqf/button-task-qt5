#ifndef WINDOWTITLE_H
#define WINDOWTITLE_H

#include "titlebutton.h"

#include<QHBoxLayout>
#include <QCoreApplication>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>

class WindowTitle : public QWidget
{
    Q_OBJECT
public:
    explicit WindowTitle(QWidget *parent = 0);
    ~WindowTitle();

signals:

public slots:
   void UpdateWindowTitle();

protected slots:
   void Minimized ();
   void Maximized ();
   void Quit ();

protected:
    void mousePressEvent(QMouseEvent * event = 0);
    void mouseReleaseEvent(QMouseEvent * event = 0);
    void mouseMoveEvent(QMouseEvent * event = 0);

    void resizeEvent(QResizeEvent * event = 0);
    void paintEvent(QPaintEvent * event = 0);

private:
    QPixmap * pixmapCache;
    QLabel title;
    QGridLayout titleLayout;
    QHBoxLayout buttonsLayout;

    // title icon
    QLabel icon;

    // buttons
    TitleButton  maximizeButton;
    TitleButton  minimizeButton;
    TitleButton  closeButton;

    QPoint mousePosition;
};

#endif // WINDOWTITLE_H
