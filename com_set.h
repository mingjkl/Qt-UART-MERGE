#ifndef COM_SET_H
#define COM_SET_H

#include <QWidget>
#include <QMainWindow>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextDocument>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QScrollArea>
#include <QWidget>
#include <QTextBrowser>
#include <QTime>
#include <QMessageBox>
#include <com_set.h>
#include <QLineEdit>
#include <QComboBox>


#define SET_WIDGET_HEIGHT  300
#define SET_WIDGET_WIDTH   580

#define COM_SET_INFO_LABEL_BASE_X   20
#define COM_SET_INFO_LABEL_BASE_Y   20

#define COM_INFO_DISPLAY_BASE_X COM_SET_INFO_LABEL_BASE_X
#define COM_INFO_DISPLAY_BASE_Y COM_SET_INFO_LABEL_BASE_Y + 23
#define COM_INFO_DISPLAY_WIDTH  250
#define COM_INFO_DISPLAY_HEIGHT SET_WIDGET_HEIGHT - COM_SET_INFO_LABEL_BASE_Y - 50

#define COM_INFO_LINEEDIT_BASE_X    COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 20 + 100
#define COM_INFO_LINEEDIT_BASE_Y    COM_INFO_DISPLAY_BASE_Y
#define COM_INFO_LINEEDIT_WIDTH     150
#define COM_INFO_LINEEDIT_HEIGHT    25

namespace Ui {
class com_set;
}

class com_set : public QWidget
{
    Q_OBJECT

public:
    explicit com_set(QWidget *parent = nullptr);
    ~com_set();

    void com_set_widget_show(void);
    void com_set_info_display(QString str);


private:
    Ui::com_set *ui;
    QTextBrowser *com_info_display;
    void com_set_save_button_init(void);

};

#endif // COM_SET_H
