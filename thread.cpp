#include "thread.h"
#include <QDebug>
#include <QTime>
#include <QProcess>
#include "mainwindow.h"
#include <QApplication>

extern void com_reopen(void);

cthread::cthread()
{

}

int cnt = 0;

void cthread::run()
{
    while(true)
    {

        this->sleep(1);


        com_reopen();
        qDebug() << "thread";

    }
}
