#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "barwidget.h"


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

QSerialPort *com[MAX_MERGE_COM_CNT];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedHeight(MAIN_WINDOIW_HEIGHT);
    this->setFixedWidth(MAIN_WINDOIW_WIDTH);

    flush_uart_table();

    rx_data_display_init();
    com_all_close_button_init();
    rx_data_display_clean_button_init();
    flush_com_button_init();
    rx_data_barwidget_button_init();
//    thread_sc = new cthread();
//    thread_sc->start();

    bar_widget = new barwidget;

}

MainWindow::~MainWindow()
{
    com_all_close();
    delete ui;
}



QString rx_data_str_backcolor[20] =
{
    "#00008B",
    "#008000",
    "#008080",
    "#1E90FF",
    "#7B68EE",
    "#8B008B",
    "#BA55D3",
    "#CD5C5C",
    "#D2691E",
    "#DC143C",
    "#00008B",
    "#008000",
    "#008080",
    "#1E90FF",
    "#7B68EE",
    "#8B008B",
    "#BA55D3",
    "#CD5C5C",
    "#D2691E",
    "#DC143C",
};




void MainWindow::rx_data_display_insert(QString client, QString data, bool time_display, int bc_p)
{
    QString str;
    QDateTime time = QDateTime::currentDateTime();
    QString time_str = time.toString("hh:mm:ss:zzz");


    if(time_display == false)
    {
        str = "<font style=\"background-color:" + rx_data_str_backcolor[bc_p] + ";\" color=\"white\">[ " + client + " ] </font>" + ": " + data + '\n';
    }
    else
    {
        str = "<font style=\"background-color:" + rx_data_str_backcolor[bc_p] + ";\" color=\"white\">[ " + client + " ] </font>" + "[ " + time_str + " ]: " + data + '\n';
    }

    //rx_data_display->insertPlainText(str);
    rx_data_display->append(str);

}

void MainWindow::rx_data_display_init(void)
{

    rx_data_display = new QTextBrowser;
    rx_data_display->setParent(this);
    rx_data_display->setFixedHeight(RX_DATA_DISPLAY_AREA_HEIGHT);
    rx_data_display->setFixedWidth(RX_DATA_DISPLAY_AREA_WIDTH);
    rx_data_display->move(RX_DATA_DISPLAY_AREA_X, RX_DATA_DISPLAY_AREA_Y);



    rx_data_display->show();

    QFont font = QFont(this->rx_data_display->font());
    font.setPointSize(10);

    rx_data_display->setFont(font);

}


void MainWindow::com_close(int p)
{
    if(com_info[p].open == true)
    {
        com[p]->close();
        com_button[p]->setStyleSheet("");
        com_info[p].open = false;
        //rx_str_bc_mark[p]->hide();
    }

}
void MainWindow::com_all_close(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_close(p);
        rx_str_bc_mark[p]->hide();
        qDebug() << com_info[p].portNanme << "Close";
    }
}

void MainWindow::com_open(int p)
{
    com[p] = new QSerialPort();
    com[p]->setPortName(com_info[p].portNanme);
    com[p]->setBaudRate(QSerialPort::Baud115200);
    com[p]->setDataBits(QSerialPort::Data8);
    com[p]->setStopBits(QSerialPort::OneStop);
    com[p]->setParity(QSerialPort::NoParity);
    com[p]->setFlowControl(QSerialPort::NoFlowControl);

    if(com[p]->open(QIODevice::ReadWrite))
    {
        qDebug() << com_info[p].portNanme << "Open";
    }
    else
    {
        QMessageBox::information(this,tr("错误"),tr("打开串口失败！"),QMessageBox::Ok);
    }

}

void MainWindow::com_button_init(void)
{

    com_button_sa = new QScrollArea;

    com_button_sa->setParent(this);
    com_button_sa->setGeometry(SCROLL_AREA_BASE_X, SCROLL_AREA_BASE_Y, SCROLL_AREA_WIDTH, SCROLL_AREA_HEIGHT);

    com_button_sa_w = new QWidget;



    //com_button_sa_w->setGeometry(0, 0, SCROLL_AREA_WIDTH - BTN_BASE_X, /*SCROLL_AREA_HEIGHT - BTN_BASE_Y*/1050);


    if(active_com_cnt > 8)
    {
        com_button_sa_w->setGeometry(0, 0, SCROLL_AREA_WIDTH - BTN_BASE_X,
                                     (SCROLL_AREA_HEIGHT - BTN_BASE_Y) +
                                     (active_com_cnt - 7) * (BTN_FIX_HEIGHT + BTN_INTERVAL));

        qDebug() << (SCROLL_AREA_HEIGHT - BTN_BASE_Y) + (active_com_cnt - 8) * (BTN_FIX_HEIGHT + BTN_INTERVAL);

    }
    else
    {
         com_button_sa_w->setGeometry(0, 0, SCROLL_AREA_WIDTH - BTN_BASE_X, SCROLL_AREA_HEIGHT);
    }
    com_button_sa->setWidget(com_button_sa_w);
    com_button_sa->setAlignment(Qt::AlignRight);


    QTextDocument *td;
    QPixmap pm;
    QPainter *painter;
    QIcon icon;

    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {


        com_button[p] = new QPushButton;
        com_button[p]->setParent(com_button_sa_w);
        com_button[p]->setFixedHeight(BTN_FIX_HEIGHT);
        com_button[p]->setFixedWidth(BTN_FIX_WIDTH);
        com_button[p]->move(BTN_BASE_X, BTN_BASE_Y + (BTN_FIX_HEIGHT + BTN_INTERVAL) * p);

        QTextStream btn_display_info_manufacturer(&com_info[p].manufacturer);
        btn_display_info_manufacturer.setFieldWidth(12);
        QTextStream btn_display_info_rename(&com_info[p].rename);
        btn_display_info_rename.setFieldWidth(12);


        td = new QTextDocument();
        td->setDocumentMargin(0);
        td->setHtml("<body><b><font color=black size=3>" + btn_display_info_rename.read(12) + "</b></body>" +
                    "<body><font color=black size=3><code>" + com_info[p].portNanme + "<br/>" +
                    btn_display_info_manufacturer.read(12) + "<br/>" +
                    com_info[p].serialNumber + "</code></font></body>");

        pm = QPixmap(td->size().toSize());
        pm.fill(Qt::transparent);
        painter = new QPainter(&pm);
        td->drawContents(painter);
        painter->end();

        icon = QIcon(pm);

        com_button[p]->setIcon(icon);
        com_button[p]->setIconSize(pm.size());

        if(com_info[p].online)
        {
            com_button[p]->show();
            qDebug() << p;
        }
        else
        {
            com_button[p]->hide();
        }

        connect(com_button[p], &QPushButton::clicked, [=]()
        {

            if(com_info[p].open == true)
            {

                com_close(p);

                com_button[p]->setStyleSheet("");
                rx_str_bc_mark[p]->hide();
            }
            else
            {
                com_info[p].open = true;
                com_open(p);

                com_button[p]->setStyleSheet("background-color:" + btn_sel_bc + ";");
                rx_str_bc_mark[p]->show();

                QObject::connect(com[p], &QSerialPort::readyRead, [=]()
                {
                    QByteArray astr = com[p]->readAll();
                    qDebug() << "a:" << astr;
                    if(!astr.isNull())
                    {

                        rx_data_str[p] += astr;
                        rx_data_str_ba[p] += astr;

                        int index = rx_data_str[p].indexOf("\r\n");


                        while(index != -1)
                        {
                            QString temp_string = rx_data_str[p].mid(0, index + 2);

                            if(com_info[p].hex_display == true)
                            {
                                QByteArray temp_byte = rx_data_str_ba[p].mid(0, index + 2);
                                temp_byte = temp_byte.toHex(' ');
                                temp_byte = temp_byte.toUpper();
                                rx_data_display_insert(com_info[p].rename, temp_byte, com_info[p].time_display, p);
                            }
                            else
                            {
                                rx_data_display_insert(com_info[p].rename, temp_string, com_info[p].time_display, p);
                            }

                            rx_data_str[p].remove(0, index + 2);
                            rx_data_str_ba[p].remove(0, index + 2);
                            rx_data_display->moveCursor(QTextCursor::End);
                            index = rx_data_str[p].indexOf("\r\n");

                            if(temp_string.startsWith("BAR-2-2-80-"))
                            {
                                qDebug() << "start" << temp_string;
                                QString bar_hex_str = temp_string.mid(11, 80);
                                qDebug() << bar_hex_str;
                                QString bar_hex_str_temp;
                                for(int p3 = 0; p3 < 40; p3++)
                                {
                                    bar_hex_str_temp = bar_hex_str.mid(p3 * 2, 2);
                                    qDebug() << p3 << bar_hex_str_temp << bar_hex_str_temp.toInt(0, 16);
                                    bar_widget->pb[p3]->setValue(bar_hex_str_temp.toInt(0, 16));

                                }
                            }

                            if(temp_string.startsWith("BAC-2-2-80-"))
                            {
                                qDebug() << "start" << temp_string;
                                QString bar_hex_str = temp_string.mid(11, 80);
                                qDebug() << bar_hex_str;
                                QString bar_hex_str_temp;
                                for(int p3 = 0; p3 < 40; p3++)
                                {
                                    bar_hex_str_temp = bar_hex_str.mid(p3 * 2, 2);
                                    qDebug() << p3 << bar_hex_str_temp << bar_hex_str_temp.toInt(0, 16);
                                    bar_widget->pb_c[p3]->setValue(bar_hex_str_temp.toInt(0, 16));

                                }
                            }

                        }


                        astr.clear();
                    }
                });

                QObject::connect(com[p], &QSerialPort::aboutToClose, [=]()
                {
                    qDebug() << "com close" << p;
                });
            }
        });

    }

}

void MainWindow::rx_data_barwidget_button_init(void)
{
    bar_widget_button = new QPushButton;
    bar_widget_button->setParent(this);
    bar_widget_button->setFixedHeight(BTN_ALL_CLOSE_FIX_HEIGHT);
    bar_widget_button->setFixedWidth(BTN_ALL_CLOSE_FIX_WIDTH);
    bar_widget_button->move(BTN_ALL_CLOSE_BASE_X - (BTN_ALL_CLOSE_FIX_WIDTH + 10) * 3, BTN_ALL_CLOSE_BASE_Y);
    bar_widget_button->setText("Bar");
    bar_widget_button->show();
    connect(bar_widget_button, &QPushButton::clicked, [=]()
    {

        bar_widget->show();
    });
}

void MainWindow::rx_data_display_clean_button_init(void)
{
    rx_data_display_clean_button = new QPushButton;
    rx_data_display_clean_button->setParent(this);
    rx_data_display_clean_button->setFixedHeight(BTN_ALL_CLOSE_FIX_HEIGHT);
    rx_data_display_clean_button->setFixedWidth(BTN_ALL_CLOSE_FIX_WIDTH);
    rx_data_display_clean_button->move(BTN_ALL_CLOSE_BASE_X - BTN_ALL_CLOSE_FIX_WIDTH - 10, BTN_ALL_CLOSE_BASE_Y);
    rx_data_display_clean_button->setText("Clean");
    rx_data_display_clean_button->show();
    connect(rx_data_display_clean_button, &QPushButton::clicked, [=]()
    {
        rx_data_display->clear();
    });
}

void MainWindow::com_all_close_button_init(void)
{
    com_all_close_button = new QPushButton;
    com_all_close_button->setParent(this);
    com_all_close_button->setFixedHeight(BTN_ALL_CLOSE_FIX_HEIGHT);
    com_all_close_button->setFixedWidth(BTN_ALL_CLOSE_FIX_WIDTH);
    com_all_close_button->move(BTN_ALL_CLOSE_BASE_X, BTN_ALL_CLOSE_BASE_Y);
    com_all_close_button->setText("Close All");
    com_all_close_button->show();

    connect(com_all_close_button, &QPushButton::clicked, [=]()
    {
        com_all_close();

//        com_info_ui_reinit();
//        flush_uart_table();
    });

}

void MainWindow::com_rx_str_color_mark_init(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        rx_str_bc_mark[p] = new QLabel;
        rx_str_bc_mark[p]->setParent(com_button_sa_w);
        rx_str_bc_mark[p]->setFixedHeight(RX_STR_BC_MARK_FIX_HEIGHT);
        rx_str_bc_mark[p]->setFixedWidth(RX_STR_BC_MARK_FIX_WIDTH);
        rx_str_bc_mark[p]->move(RX_STR_BC_MARK_BASE_X, RX_STR_BC_MARK_BASE_Y + (BTN_FIX_HEIGHT + BTN_INTERVAL) * p);
        rx_str_bc_mark[p]->setStyleSheet("background-color:" + rx_data_str_backcolor[p] + ";");
        rx_str_bc_mark[p]->hide();
    }
}

void MainWindow::com_time_button_init(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_time_button[p] = new QPushButton;
        com_time_button[p]->setParent(com_button_sa_w);
        com_time_button[p]->setFixedHeight(BTN_SET_FIX_HEIGHT);
        com_time_button[p]->setFixedWidth(BTN_SET_FIX_WIDTH);
        com_time_button[p]->move(BTN_SET_BASE_X, BTN_SET_BASE_Y + (BTN_FIX_HEIGHT + BTN_INTERVAL) * p);
        com_time_button[p]->setText("TIME");
        if(com_info[p].online)
        {
            com_time_button[p]->show();
            qDebug() << p;
        }
        else
        {
            com_time_button[p]->hide();
        }
        connect(com_time_button[p], &QPushButton::clicked, [=]()
        {
            if(com_info[p].time_display == true)
            {
                com_info[p].time_display = false;
                com_time_button[p]->setStyleSheet("");
            }
            else
            {
                com_info[p].time_display = true;
                com_time_button[p]->setStyleSheet("background-color:" + btn_sel_bc + ";");
            }

        });
    }
}

void MainWindow::com_hex_button_init(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_hex_button[p] = new QPushButton;
        com_hex_button[p]->setParent(com_button_sa_w);
        com_hex_button[p]->setFixedHeight(BTN_SET_FIX_HEIGHT);
        com_hex_button[p]->setFixedWidth(BTN_SET_FIX_WIDTH);
        com_hex_button[p]->move(BTN_SET_BASE_X, 25 + BTN_SET_BASE_Y + (BTN_FIX_HEIGHT + BTN_INTERVAL) * p);
        com_hex_button[p]->setText("HEX");
        if(com_info[p].online)
        {
            com_hex_button[p]->show();
            qDebug() << p;
        }
        else
        {
            com_hex_button[p]->hide();
        }
        connect(com_hex_button[p], &QPushButton::clicked, [=]()
        {
            if(com_info[p].hex_display == true)
            {
                com_info[p].hex_display = false;
                com_hex_button[p]->setStyleSheet("");
            }
            else
            {
                com_info[p].hex_display = true;
                com_hex_button[p]->setStyleSheet("background-color:" + btn_sel_bc + ";");
            }

        });
    }
}

void MainWindow::com_send_button_init(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_send_button[p] = new QPushButton;
        com_send_button[p]->setParent(com_button_sa_w);
        com_send_button[p]->setFixedHeight(BTN_SET_FIX_HEIGHT);
        com_send_button[p]->setFixedWidth(BTN_SET_FIX_WIDTH);
        com_send_button[p]->move(BTN_SET_BASE_X, 50 + BTN_SET_BASE_Y + (BTN_FIX_HEIGHT + BTN_INTERVAL) * p);
        com_send_button[p]->setText("SEND");
        if(com_info[p].online)
        {
            com_send_button[p]->show();
            qDebug() << p;
        }
        else
        {
            com_send_button[p]->hide();
        }
    }
}

void MainWindow::com_set_button_init(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_set_button[p] = new QPushButton;
        com_set_button[p]->setParent(com_button_sa_w);
        com_set_button[p]->setFixedHeight(BTN_SET_FIX_HEIGHT);
        com_set_button[p]->setFixedWidth(BTN_SET_FIX_WIDTH);
        com_set_button[p]->move(BTN_SET_BASE_X, 75 + BTN_SET_BASE_Y + (BTN_FIX_HEIGHT + BTN_INTERVAL) * p);
        com_set_button[p]->setText("SET");
        if(com_info[p].online)
        {
            com_set_button[p]->show();
            qDebug() << p;
        }
        else
        {
            com_set_button[p]->hide();
        }

        connect(com_set_button[p], &QPushButton::clicked, [=]()
        {
            com_set_widget = new com_set;

            com_set_widget->com_set_widget_show();

            com_set_widget->com_set_info_display("PortNanme: " + com_info[p].portNanme);
            com_set_widget->com_set_info_display("Manufacturer: " + com_info[p].manufacturer);
            com_set_widget->com_set_info_display("SserialNumber: " + com_info[p].serialNumber);
            if(com_info->hasVendorIdentifier == true)
            {
                qDebug() << com_info->vendorIdentifier;
                com_set_widget->com_set_info_display("VendorIdentifier: " + com_info[p].vendorIdentifier);
            }
            if(com_info->hasproductIdentifier == true)
            {
                com_set_widget->com_set_info_display("ProductIdentifier: " + com_info[p].productIdentifier);
            }
            com_set_widget->com_set_info_display("Description: " + com_info[p].description);

        });
    }
}

void MainWindow::flush_com_button_init(void)
{

    com_flush_button = new QPushButton;
    com_flush_button->setParent(this);
    com_flush_button->setFixedHeight(BTN_ALL_CLOSE_FIX_HEIGHT);
    com_flush_button->setFixedWidth(BTN_ALL_CLOSE_FIX_WIDTH);
    com_flush_button->move(BTN_ALL_CLOSE_BASE_X - (BTN_ALL_CLOSE_FIX_WIDTH + 10) * 2, BTN_ALL_CLOSE_BASE_Y);
    com_flush_button->setText("Flush COM");
    com_flush_button->show();

    connect(com_flush_button, &QPushButton::clicked, [=]()
    {
//        qDebug() << "restart";
//        com_all_close();
//        qApp->exit(1047);

    });

}

void MainWindow::com_info_sim(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_info[p].portNanme = "info.portName()";
        com_info[p].description =  "info.description()";
        com_info[p].hasVendorIdentifier = true;
        com_info[p].manufacturer = "info.manufacturer()";
        com_info[p].serialNumber = "info.serialNumber()";
        com_info[p].vendorIdentifier = "info.vendorIdentifier()";
        com_info[p].productIdentifier = "info.productIdentifier()";
        com_info[p].hasproductIdentifier = true;
        com_info[p].rename = "rename";
        com_info[p].open = false;
        com_info[p].open_status_str = "close";
    }
}

void MainWindow::com_info_init(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_info[p].portNanme = "";
        com_info[p].description = "";
        com_info[p].hasVendorIdentifier = false;
        com_info[p].vendorIdentifier = "";
        com_info[p].hasproductIdentifier = false;
        com_info[p].productIdentifier = "";
        com_info[p].manufacturer = "";
        com_info[p].serialNumber = "";
        com_info[p].online = false;
        com_info[p].open = false;
        com_info[p].open_status_str = "";
        com_info[p].rename = "";
        com_info[p].time_display = false;
        com_info[p].hex_display = false;

        rx_data_str[p] = "";



    }

    active_com_cnt = 0;
}

void com_reopen(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        if((com_info->open == true) && (com[p]->isOpen() == false))
        {
            com[p]->reset();
            com[p] = new QSerialPort();
            com[p]->setPortName(com_info[p].portNanme);
            com[p]->setBaudRate(QSerialPort::Baud115200);
            com[p]->setDataBits(QSerialPort::Data8);
            com[p]->setStopBits(QSerialPort::OneStop);
            com[p]->setParity(QSerialPort::NoParity);
            com[p]->setFlowControl(QSerialPort::NoFlowControl);

            if(com[p]->open(QIODevice::ReadWrite))
            {
                qDebug() << com_info[p].portNanme << "reopen";
            }
            else
            {
                qDebug() << com_info[p].portNanme << "reopen fail";
            }
        }
    }

}

void MainWindow::com_info_ui_reinit(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {

        delete com_button[p];
        delete com_set_button[p];
        delete com_send_button[p];
        delete com_hex_button[p];
        delete com_time_button[p];
    }

    delete com_button_sa_w;
    delete com_button_sa;
}

void MainWindow::flush_uart_table(void)
{
    for(int p = 0; p < MAX_MERGE_COM_CNT; p++)
    {
        com_info[p].online = false;
    }

    active_com_cnt = 0;

    QJsonObject json_obj_info;
    QJsonObject com_json;

    com_info_init();

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        //ui->comboBoxPort->addItem(info.portName());
        com_info[active_com_cnt].portNanme = info.portName();
        com_info[active_com_cnt].description =  info.description();
        com_info[active_com_cnt].hasVendorIdentifier = info.hasVendorIdentifier();
        com_info[active_com_cnt].manufacturer = info.manufacturer();
        com_info[active_com_cnt].serialNumber = info.serialNumber();
        com_info[active_com_cnt].vendorIdentifier = info.vendorIdentifier();
        com_info[active_com_cnt].productIdentifier = info.productIdentifier();
        com_info[active_com_cnt].hasproductIdentifier = info.hasProductIdentifier();
        com_info[active_com_cnt].open = false;
        com_info[active_com_cnt].open_status_str = "close";
        com_info[active_com_cnt].online = true;

        com_info[active_com_cnt].rename = info.portName();

        if(com_info[active_com_cnt].rename == QString("COM11"))
        {
            com_info[active_com_cnt].rename = QString("RX-NET");
        }
        if(com_info[active_com_cnt].rename == QString("COM9"))
        {
            com_info[active_com_cnt].rename = QString("RX-APP");
        }
        if(com_info[active_com_cnt].rename == QString("COM7"))
        {
            com_info[active_com_cnt].rename = QString("TX-NET");
        }
        if(com_info[active_com_cnt].rename == QString("COM6"))
        {
            com_info[active_com_cnt].rename = QString("TX-APP");
        }

        json_obj_info.insert("portName", info.portName());
        json_obj_info.insert("description", info.description());
        json_obj_info.insert("hasVendorIdentifier", info.hasVendorIdentifier());
        json_obj_info.insert("manufacturer", info.manufacturer());
        json_obj_info.insert("serialNumber", info.serialNumber());
        json_obj_info.insert("vendorIdentifier", info.vendorIdentifier());
        json_obj_info.insert("productIdentifier", info.productIdentifier());
        json_obj_info.insert("hasProductIdentifier", info.hasProductIdentifier());

        com_json.insert(info.portName(), json_obj_info);

        active_com_cnt++;
    }

    com_button_init();
    com_time_button_init();
    com_hex_button_init();
    com_send_button_init();
    com_set_button_init();
    com_rx_str_color_mark_init();

    QJsonDocument doc(com_json);
    QByteArray json = doc.toJson();
    QFile file(".//com_info.json");
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();

//    file.open(QFile::ReadOnly);
//    QByteArray json_read = file.readAll();
//    file.close();
//    QJsonDocument doc_json_read = QJsonDocument::fromJson(json_read);
//    if(doc_json_read.isObject())
//    {
//        QJsonObject obj_com_read = doc_json_read.object();
//        QStringList keys = obj_com_read.keys();

//        for(int p = 0; p < keys.size(); ++p)
//        {
//            QString key = keys.at(p);
//            QJsonObject com_info_json_read = obj_com_read.value(key).toObject();
//            qDebug() << com_info_json_read.value("manufacturer");
//        }

//        qDebug() << keys;
//    }
}

