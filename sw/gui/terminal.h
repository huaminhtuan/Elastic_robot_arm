#ifndef TERMINAL_H
#define TERMINAL_H

#include <QScrollArea>

namespace Ui {
class Terminal;
}

class Terminal : public QScrollArea
{
    Q_OBJECT

public:
    explicit Terminal(QWidget *parent = nullptr);
    ~Terminal();

private:
    Ui::Terminal *ui;
};

#endif // TERMINAL_H
