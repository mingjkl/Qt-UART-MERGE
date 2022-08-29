#include "com_set.h"
#include "ui_com_set.h"

com_set::com_set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::com_set)
{
    ui->setupUi(this);

    this->setFixedHeight(SET_WIDGET_HEIGHT);
    this->setFixedWidth(SET_WIDGET_WIDTH);

    QLabel *com_info_label = new QLabel;
    com_info_label->setParent(this);
    com_info_label->setText("COM Info");
    com_info_label->move(COM_SET_INFO_LABEL_BASE_X, COM_SET_INFO_LABEL_BASE_Y);
    com_info_label->show();

    com_info_display = new QTextBrowser;
    com_info_display->setParent(this);
    com_info_display->setFixedHeight(COM_INFO_DISPLAY_HEIGHT);
    com_info_display->setFixedWidth(COM_INFO_DISPLAY_WIDTH);
    com_info_display->move(COM_INFO_DISPLAY_BASE_X, COM_INFO_DISPLAY_BASE_Y);

    com_info_display->show();

    QLabel *com_rename_label = new QLabel;
    com_rename_label->setParent(this);
    com_rename_label->setText("Rename");
    com_rename_label->move(COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 30, COM_INFO_DISPLAY_BASE_Y + 5);
    com_rename_label->show();

    QLabel *com_setBaudRate_label  = new QLabel;
    com_setBaudRate_label->setParent(this);
    com_setBaudRate_label->setText("BaudRate");
    com_setBaudRate_label->move(COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 30, COM_INFO_DISPLAY_BASE_Y + 5  + (COM_INFO_LINEEDIT_HEIGHT + 5) * 1);
    com_setBaudRate_label->show();

    QLabel *com_setDataBits_label  = new QLabel;
    com_setDataBits_label->setParent(this);
    com_setDataBits_label->setText("DataBits");
    com_setDataBits_label->move(COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 30, COM_INFO_DISPLAY_BASE_Y + 5  + (COM_INFO_LINEEDIT_HEIGHT + 5) * 2);
    com_setDataBits_label->show();


    QLabel *com_setStopBits_label  = new QLabel;
    com_setStopBits_label->setParent(this);
    com_setStopBits_label->setText("StopBits");
    com_setStopBits_label->move(COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 30, COM_INFO_DISPLAY_BASE_Y + 5  + (COM_INFO_LINEEDIT_HEIGHT + 5) * 3);
    com_setStopBits_label->show();


    QLabel *com_setParity_label  = new QLabel;
    com_setParity_label->setParent(this);
    com_setParity_label->setText("Parity");
    com_setParity_label->move(COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 30, COM_INFO_DISPLAY_BASE_Y + 5  + (COM_INFO_LINEEDIT_HEIGHT + 5) * 4);
    com_setParity_label->show();



    QLabel *com_setFlowControl_label  = new QLabel;
    com_setFlowControl_label->setParent(this);
    com_setFlowControl_label->setText("FlowControl");
    com_setFlowControl_label->move(COM_INFO_DISPLAY_BASE_X + COM_INFO_DISPLAY_WIDTH + 30, COM_INFO_DISPLAY_BASE_Y + 5  + (COM_INFO_LINEEDIT_HEIGHT + 5) * 5);
    com_setFlowControl_label->show();


    QLineEdit *com_rename_le = new QLineEdit;
    com_rename_le->setParent(this);
    com_rename_le->setFixedHeight(COM_INFO_LINEEDIT_HEIGHT);
    com_rename_le->setFixedWidth(COM_INFO_LINEEDIT_WIDTH);
    com_rename_le->move(COM_INFO_LINEEDIT_BASE_X, COM_INFO_LINEEDIT_BASE_Y);


    QComboBox *com_setBaudRate = new QComboBox;
    com_setBaudRate->setParent(this);
    com_setBaudRate->setFixedHeight(COM_INFO_LINEEDIT_HEIGHT);
    com_setBaudRate->setFixedWidth(COM_INFO_LINEEDIT_WIDTH);
    com_setBaudRate->move(COM_INFO_LINEEDIT_BASE_X, COM_INFO_LINEEDIT_BASE_Y + (COM_INFO_LINEEDIT_HEIGHT + 5) * 1);
    com_setBaudRate->show();

    QComboBox *com_setDataBits = new QComboBox;
    com_setDataBits->setParent(this);
    com_setDataBits->setFixedHeight(COM_INFO_LINEEDIT_HEIGHT);
    com_setDataBits->setFixedWidth(COM_INFO_LINEEDIT_WIDTH);
    com_setDataBits->move(COM_INFO_LINEEDIT_BASE_X, COM_INFO_LINEEDIT_BASE_Y + (COM_INFO_LINEEDIT_HEIGHT + 5) * 2);
    com_setDataBits->show();

    QComboBox *com_setStopBits = new QComboBox;
    com_setStopBits->setParent(this);
    com_setStopBits->setFixedHeight(COM_INFO_LINEEDIT_HEIGHT);
    com_setStopBits->setFixedWidth(COM_INFO_LINEEDIT_WIDTH);
    com_setStopBits->move(COM_INFO_LINEEDIT_BASE_X, COM_INFO_LINEEDIT_BASE_Y + (COM_INFO_LINEEDIT_HEIGHT + 5) * 3);
    com_setStopBits->show();

    QComboBox *com_setParity = new QComboBox;
    com_setParity->setParent(this);
    com_setParity->setFixedHeight(COM_INFO_LINEEDIT_HEIGHT);
    com_setParity->setFixedWidth(COM_INFO_LINEEDIT_WIDTH);
    com_setParity->move(COM_INFO_LINEEDIT_BASE_X, COM_INFO_LINEEDIT_BASE_Y + (COM_INFO_LINEEDIT_HEIGHT + 5) * 4);
    com_setParity->show();

    QComboBox *com_setFlowControl = new QComboBox;
    com_setFlowControl->setParent(this);
    com_setFlowControl->setFixedHeight(COM_INFO_LINEEDIT_HEIGHT);
    com_setFlowControl->setFixedWidth(COM_INFO_LINEEDIT_WIDTH);
    com_setFlowControl->move(COM_INFO_LINEEDIT_BASE_X, COM_INFO_LINEEDIT_BASE_Y + (COM_INFO_LINEEDIT_HEIGHT + 5) * 5);
    com_setFlowControl->show();

    com_set_save_button_init();
}


void com_set::com_set_save_button_init(void)
{

    QPushButton *com_set_save_button = new QPushButton;
    com_set_save_button->setParent(this);
    com_set_save_button->setFixedHeight(30);
    com_set_save_button->setFixedWidth(100);
    com_set_save_button->move(SET_WIDGET_WIDTH - 100 - 40,  SET_WIDGET_HEIGHT - 30 - 25);
    com_set_save_button->setText("Save");
    com_set_save_button->show();
    connect(com_set_save_button, &QPushButton::clicked, [=]()
    {


    });

}


void com_set::com_set_info_display(QString str)
{
    com_info_display->append(str);




}

void com_set::com_set_widget_show(void)
{
    this->show();
    com_info_display->clear();
}

com_set::~com_set()
{
    delete ui;
}
