#ifndef RCASMAINWINDOW_H
#define RCASMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class RCASMainWindow;
}

class RCASMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RCASMainWindow(QWidget *parent = 0);
    ~RCASMainWindow();

private:
    Ui::RCASMainWindow *ui;
};

#endif // RCASMAINWINDOW_H
