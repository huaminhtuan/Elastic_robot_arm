#include "settingWindow.h"
#include "ui_settingWindow.h"
#include "QtSerialPort"

SettingWindow::SettingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    /* Create a timer*/
    timer = new QTimer(this);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}


void SettingWindow::on_btnConnect_clicked()
{

}
