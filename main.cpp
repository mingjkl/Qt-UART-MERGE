#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if(a.exec() == 1047)
    {
        QProcess::startDetached(qApp->applicationFilePath());
        return 0;
    }

    return a.exec();
}
