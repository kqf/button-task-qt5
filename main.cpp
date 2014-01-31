#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase fontDB;
    fontDB.addApplicationFont(":titleBar/Assets/font/AlternateGotNo3D.ttf");

    QFile file(":/titleBar/Assets/style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(QLatin1String(file.readAll()));

    MainWindow * w = new MainWindow();
    w->show();

    return a.exec();
}
