#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define MAX_MERGE_COM_CNT   10

#define MAIN_WINDOIW_HEIGHT 900
#define MAIN_WINDOIW_WIDTH  900

#define BTN_BASE_X  20
#define BTN_BASE_Y  20
#define BTN_FIX_HEIGHT  100
#define BTN_FIX_WIDTH  120
#define BTN_INTERVAL  3
#define BTN_SET_BASE_X BTN_BASE_X + BTN_FIX_WIDTH
#define BTN_SET_BASE_Y BTN_BASE_Y
#define BTN_SET_FIX_HEIGHT  25
#define BTN_SET_FIX_WIDTH   50
#define SCROLL_AREA_BASE_X  20
#define SCROLL_AREA_BASE_Y  20
#define SCROLL_AREA_HEIGHT  MAIN_WINDOIW_HEIGHT - 100
#define SCROLL_AREA_WIDTH  250
#define RX_DATA_DISPLAY_AREA_X  SCROLL_AREA_BASE_X + SCROLL_AREA_WIDTH + 10
#define RX_DATA_DISPLAY_AREA_Y  SCROLL_AREA_BASE_Y
#define RX_DATA_DISPLAY_AREA_HEIGHT SCROLL_AREA_HEIGHT
#define RX_DATA_DISPLAY_AREA_WIDTH  MAIN_WINDOIW_WIDTH - RX_DATA_DISPLAY_AREA_X - 535
#define RX_STR_BC_MARK_BASE_X   BTN_BASE_X + BTN_FIX_WIDTH + BTN_SET_FIX_WIDTH + 5
#define RX_STR_BC_MARK_BASE_Y   BTN_BASE_Y
#define RX_STR_BC_MARK_FIX_HEIGHT   BTN_FIX_HEIGHT
#define RX_STR_BC_MARK_FIX_WIDTH    5
#define BTN_ALL_CLOSE_FIX_HEIGHT    30
#define BTN_ALL_CLOSE_FIX_WIDTH     100
#define BTN_ALL_CLOSE_BASE_X    MAIN_WINDOIW_WIDTH - BTN_ALL_CLOSE_FIX_WIDTH - 15
#define BTN_ALL_CLOSE_BASE_Y    MAIN_WINDOIW_HEIGHT - BTN_ALL_CLOSE_FIX_HEIGHT - 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void flush_uart_table(void);


private:
    Ui::MainWindow *ui;
    void flush_com_button_init(void);
    void com_button_init(void);
    void com_info_sim(void);
    void rx_data_display_init(void);
    void rx_data_display_insert(QString client, QString data, bool time_display, int bc_p);
    void com_open(int p);
    void com_close(int p);
    void com_all_close(void);
    void com_set_button_init(void);
    void com_send_button_init(void);
    void com_hex_button_init(void);
    void com_time_button_init(void);
    void com_rx_str_color_mark_init(void);
    void com_all_close_button_init(void);
    void rx_data_display_clean_button_init(void);
    void com_info_init(void);
    void com_info_ui_reinit(void);
    void com_button_creat(int p);
    QByteArray QString2Hex(QString str);

    QPushButton *com_button[MAX_MERGE_COM_CNT];
    QSerialPort *com[MAX_MERGE_COM_CNT];
    QPushButton *com_hex_button[MAX_MERGE_COM_CNT];
    QPushButton *com_send_button[MAX_MERGE_COM_CNT];
    QPushButton *com_set_button[MAX_MERGE_COM_CNT];
    QPushButton *com_time_button[MAX_MERGE_COM_CNT];
    QLabel *rx_str_bc_mark[MAX_MERGE_COM_CNT];
    QPushButton *com_all_close_button;
    QPushButton *rx_data_display_clean_button;
    QScrollArea *com_button_sa;
    QPushButton *com_flush_button;


    struct com_info_s
    {
        QString portNanme;
        QString description;
        bool hasVendorIdentifier;
        QString vendorIdentifier;
        bool hasproductIdentifier;
        QString productIdentifier;
        QString manufacturer;
        QString serialNumber;
        bool online;
        bool open;
        QString open_status_str;
        QString rename;
        bool time_display;
        bool hex_display;

    } com_info[MAX_MERGE_COM_CNT];

    int active_com_cnt = 0;

    QWidget *com_button_sa_w;
    QTextBrowser *rx_data_display;
    QString rx_data_str[MAX_MERGE_COM_CNT];
    QString btn_sel_bc = "#E0EEF9";
    QByteArray rx_data_str_ba[MAX_MERGE_COM_CNT];

};
#endif // MAINWINDOW_H




