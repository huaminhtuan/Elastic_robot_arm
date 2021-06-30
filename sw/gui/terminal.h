#ifndef TERMINAL_H
#define TERMINAL_H

#include <memory>
#include <QMainWindow>
#include "settingWindow.h"

using namespace std;

namespace Ui {
class Terminal;
}

class Terminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Terminal(QWidget *parent = nullptr);
    ~Terminal();

private slots:
    void on_btnConnectJoint1_clicked();

    void on_btnConnectJoint2_clicked();

private:
    Ui::Terminal *ui;
    unique_ptr<SettingWindow> setting;
};

#endif // TERMINAL_H
