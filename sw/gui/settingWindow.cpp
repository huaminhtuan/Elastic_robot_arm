#include "settingWindow.h"
#include "ui_settingWindow.h"

int SettingWindow::curPort = 0;

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
