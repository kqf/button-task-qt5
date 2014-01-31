#ifndef WINDOWTITLE_H
#define WINDOWTITLE_H


#include<QHBoxLayout>
#include <QCoreApplication>
#include <QWidget>
#include <QFrame>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

class WindowTitle : public QFrame
{
    Q_OBJECT
public:
    explicit WindowTitle(QWidget * parent = 0);
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

private:
    QLabel title;
    QGridLayout titleLayout;
    QHBoxLayout buttonsLayout;
    QHBoxLayout labelLayout;

    QLabel icon;

    QPushButton  maximizeButton;
    QPushButton  minimizeButton;
    QPushButton  closeButton;

    QPoint mousePosition;
};

#endif // WINDOWTITLE_H
