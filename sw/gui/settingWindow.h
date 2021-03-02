#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingWindow; }
QT_END_NAMESPACE

class SettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    QTimer *timer;
    void on_btnConnect_clicked();

private:
    Ui::SettingWindow *ui;
};
#endif // SETTINGWINDOW_H
