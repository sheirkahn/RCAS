#include "rcasmainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

RCASMainWindow::RCASMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RCASMainWindow)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect (ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT (on_quit()), Qt::UniqueConnection);
    connect (ui->createsession_button, SIGNAL(clicked(bool)), this, SLOT (on_createsession_button_clicked()), Qt::UniqueConnection);

    // Set up the first page of the stacked widget
    ui->stackedWidget->setCurrentIndex(0);
    ui->title_label->setText("Please select an option");

    // Set tab names
    ui->tabWidget->setTabText (0, "New assessment session");
    ui->tabWidget->setTabText (1, "Older assessment sessions");

    // Set current date for the date edit
    ui->assessmentdate_edit->setDate(QDate::currentDate());
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
    this->close();
    return true;
}

void RCASMainWindow::closeEvent (QCloseEvent * event)
{
  if (on_quit() != true)
  {
    event->ignore();
  }
}

// When clicking on the "candidates >>" button, switch to the candidates page of the stacked widget
void RCASMainWindow::on_candidate_button_clicked()
{
    ui->title_label->setText("List of candidates");
    ui->stackedWidget->setCurrentIndex(1);
}

// When clicking on the "<< Back" button, switch to the sessions page of the stacked widget
void RCASMainWindow::on_sessions_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->title_label->setText("Please select an option");
}

// When clicking on the "Start" button, switch to the assessment page of the stacked widget
void RCASMainWindow::on_start_button_clicked()
{
    ui->title_label->setText("Candidate assessment");
    ui->stackedWidget->setCurrentIndex(2);
}

// When clicking on the "Review" button, switch to the assessment page of the stacked widget
void RCASMainWindow::on_view_button_clicked()
{
    ui->title_label->setText("Candidate assessment");
    ui->stackedWidget->setCurrentIndex(2);
}

// When clicking on the "<< Sessions list" button, switch to the sessions page of the stacked widget
void RCASMainWindow::on_sessions_button_clicked()
{
    ui->title_label->setText("List of saved sessions");
    ui->stackedWidget->setCurrentIndex(0);
}

// When clicking on the "<< Candidates list" button, switch to the candidate page of the stacked widget
void RCASMainWindow::on_candidates2_button_clicked()
{
    ui->title_label->setText("List of candidates");
    ui->stackedWidget->setCurrentIndex(1);
}

void RCASMainWindow::on_createsession_button_clicked()
{
    if (!this->validate_new_session())
    {
        QMessageBox::information (this, "Check details", "Incomplete information provided to create a new assessment session. Please check the details provided.");
        return;
    }

    // Read the CSV file and populate the candidate list
    if (!this->readCandidatesFromCSVFile (ui->candidatelist_edit->text()))
    {
        QMessageBox::critical (this, "Invalid CSV file", "The selected file does not contain the needed information. Please make sure to select the right file.");
        return;
    }

    ui->title_label->setText("List of candidates");
    ui->stackedWidget->setCurrentIndex(1);
}

void RCASMainWindow::on_candidatelist_button_clicked()
{

    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("CSV files (*.csv)"));
    if (QFile::exists(newFileName))
    {
        ui->candidatelist_edit->setText(newFileName);
    }
}
