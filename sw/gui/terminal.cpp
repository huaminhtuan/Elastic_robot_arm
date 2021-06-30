#include <memory>
#include "terminal.h"
#include "ui_terminal.h"

Terminal::Terminal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Terminal)
{
    ui->setupUi(this);
}

Terminal::~Terminal()
{
    delete ui;
}

void Terminal::on_btnConnectJoint1_clicked()
{
    setting.reset(new SettingWindow());
    setting->show();
    SettingWindow::curPort = 1;
}

void Terminal::on_btnConnectJoint2_clicked()
{
    setting.reset(new SettingWindow());
    setting->show();
    SettingWindow::curPort = 2;
}
