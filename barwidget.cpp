#include "barwidget.h"
#include "ui_barwidget.h"
#include <QLabel>
#include <QBarSet>
#include <QBarSeries>
#include <QChar>
#include <QChartView>
#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QProcess>
#include <QProgressBar>

#define BAR_BASE_X 50
#define BAR_BASE_Y 50
#define BAR_FIX_HEIGHT 15
#define BAR_FIX_WEIDTH 200
#define SET_BAR_WIDGET_HEIGHT   (BAR_FIX_HEIGHT + (BAR_FIX_HEIGHT + 2) * 40)
#define SET_BAR_WIDGET_WIDTH    (BAR_BASE_X * 2 + BAR_FIX_WEIDTH + 100)



barwidget::barwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::barwidget)
{
    ui->setupUi(this);

    this->setFixedHeight(SET_BAR_WIDGET_HEIGHT + 40);
    this->setFixedWidth(SET_BAR_WIDGET_WIDTH + 50);

    QLabel *ed_lb = new QLabel;
    ed_lb->setParent(this);
    ed_lb->move(BAR_BASE_X, BAR_FIX_HEIGHT);
    ed_lb->setText("ED");
    ed_lb->show();

    QLabel *score_lb = new QLabel;
    score_lb->setParent(this);
    score_lb->move(BAR_BASE_X + BAR_FIX_WEIDTH, BAR_FIX_HEIGHT);
    score_lb->setText("Score");
    score_lb->show();

    for(int p = 0; p < 40; p++)
    {
        pb[p] = new QProgressBar;
        pb_c[p] = new QProgressBar;
        pbl[p] = new QLabel;

        pbl[p]->setParent(this);
        pbl[p]->move(BAR_BASE_X - 20, (BAR_FIX_HEIGHT + 2) * p + 40);
        pbl[p]->setText(QString::number((p + 1) * 2));
        pbl[p]->show();

        pb[p]->setParent(this);
        pb[p]->setFixedHeight(BAR_FIX_HEIGHT);
        pb[p]->setFixedWidth(BAR_FIX_WEIDTH);
        pb[p]->move(BAR_BASE_X, (BAR_FIX_HEIGHT + 2) * p + 40);

        pb_c[p]->setParent(this);
        pb_c[p]->setFixedHeight(BAR_FIX_HEIGHT);
        pb_c[p]->setFixedWidth(BAR_FIX_WEIDTH);
        pb_c[p]->move(BAR_BASE_X + BAR_FIX_WEIDTH, (BAR_FIX_HEIGHT + 2) * p + 40);

        pb[p]->show();
    }


}

barwidget::~barwidget()
{
    delete ui;
}
