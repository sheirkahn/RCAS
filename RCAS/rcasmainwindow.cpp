#include "rcasmainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QCloseEvent>

RCASMainWindow::RCASMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RCASMainWindow)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect (ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT (on_quit()));

    // Set up the UI
    ui->stackedWidget->setCurrentIndex(0);
}

RCASMainWindow::~RCASMainWindow()
{
    delete ui;
}

void RCASMainWindow::on_RCASMainWindow_iconSizeChanged(const QSize &iconSize)
{

}

bool RCASMainWindow::on_quit()
{
    return true;
}

void RCASMainWindow::closeEvent (QCloseEvent * event)
{
  if (on_quit() != true)
  {
    event->ignore();
  }
}

// Launch a file selector to load the session details
void RCASMainWindow::on_pushButton_2_clicked()
{
}

// Load the list of older sessions
void RCASMainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
