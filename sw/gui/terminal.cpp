#include "terminal.h"
#include "ui_terminal.h"

Terminal::Terminal(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::Terminal)
{
    ui->setupUi(this);
}

Terminal::~Terminal()
{
    delete ui;
}
