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

    virtual void closeEvent (QCloseEvent *);

public slots:
    bool on_quit ();

private slots:

    void on_RCASMainWindow_iconSizeChanged(const QSize &iconSize);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::RCASMainWindow *ui;
};

#endif // RCASMAINWINDOW_H
