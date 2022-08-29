#ifndef BARWIDGET_H
#define BARWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QProgressBar>
#include <QLabel>

namespace Ui {
class barwidget;
}

class barwidget : public QWidget
{
    Q_OBJECT


public:
    explicit barwidget(QWidget *parent = nullptr);
    ~barwidget();

    QProgressBar *pb[40];
    QProgressBar *pb_c[40];
    QLabel *pbl[40];

private:
    Ui::barwidget *ui;
};

#endif // BARWIDGET_H
