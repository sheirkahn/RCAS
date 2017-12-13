#include "rcasmainwindow.h"
#include "ui_rcasmainwindow.h"

RCASMainWindow::RCASMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RCASMainWindow)
{
    ui->setupUi(this);
}

RCASMainWindow::~RCASMainWindow()
{
    delete ui;
}
