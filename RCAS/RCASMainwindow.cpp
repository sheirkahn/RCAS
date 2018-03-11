#include "RCASMainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSound>

RCASMainWindow::RCASMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RCASMainWindow)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect (ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT (on_quit()), Qt::UniqueConnection);
    connect (ui->createsession_button, SIGNAL(clicked(bool)), this, SLOT (on_createsession_button_clicked()), Qt::UniqueConnection);

    // AUDIO RECORDER DURATION SIGNAL
    // connect(audioRecorder, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)), Qt::UniqueConnection);

    // Load settings
    loadSettings();

    // Load the first page (sessions page, with create session tab selected)
    loadSessionsPage(true);

    // Load existing sessions from JSON file
    QApplication::setOverrideCursor(Qt::WaitCursor);
    loadSessionsFromJson ();
    QApplication::restoreOverrideCursor();
}

RCASMainWindow::~RCASMainWindow()
{
    delete ui;
}

void RCASMainWindow::loadSessionsPage (bool firstLoad)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->title_label->setText("Please select an option");

    if (firstLoad)
    {
        // Set tab names
        ui->tabWidget->setTabText (0, "New assessment session");
        ui->tabWidget->setTabText (1, "Older assessment sessions");

        // Set current date for the date edit
        ui->assessmentdate_edit->setDate(QDate::currentDate());

        ui->tabWidget->setCurrentIndex(0);
        ui->assessorname_edit->setFocus();
    }
}

void RCASMainWindow::loadCandidatesPage()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->title_label->setText("List of candidates");

    if (mSoundManagerState == RCAS_RECORD)
    {
        ui->startassessment_button->setVisible(true);
        ui->review_button->setVisible(false);
    }
    else
    {
        ui->startassessment_button->setVisible(false);
        ui->review_button->setVisible(true);
    }
}

void RCASMainWindow::loadAssessmentPage()
{
    mCandidateID = ui->candidate_table->currentRow();
    mCandidate = mSession.candidate(mCandidateID);

    ui->stackedWidget->setCurrentIndex(2);
    ui->title_label->setText("Candidate assessment");

    ui->recordplay_button->setText(mSoundManagerState == RCAS_RECORD ? "Record" : "Play");
    ui->recordplay_button->setEnabled(false);

    ui->startstop_button->setText("Start");
    ui->startstop_button->setEnabled(true);
}

void RCASMainWindow::on_RCASMainWindow_iconSizeChanged(const QSize &iconSize)
{}

void RCASMainWindow::updateDuration(qint64 duration)
{
    ui->duration_edit->setText(QDateTime::fromTime_t(duration/1000).toUTC().toString("hh:mm:ss"));
}

bool RCASMainWindow::on_quit()
{
    if (mSessionManager.modified())
    {
        if (QMessageBox::question
                (this, "Save changes?", "You have unsaved changes. Save changes before quitting?") ==
                QMessageBox::Yes)
        {
            saveSessionsToJson();
        }
    }

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
    QList <QTableWidgetItem*> selectedItems = ui->candidate_table->selectedItems();
    if (selectedItems.empty())
    {
        QMessageBox::warning (this, "Select a candidate", "Please select a candidate from the list to start the assessment.");
        return;
    }
    else
    {
        ui->record_nameedit->setText(selectedItems[0]->text());
        ui->record_idedit->setText(selectedItems[2]->text());

        ui->title_label->setText("Candidate assessment");
        ui->stackedWidget->setCurrentIndex(2);

        ui->duration_edit->setText("00:00:00");
    }
}

// When clicking on the "Review" button, switch to the assessment page of the stacked widget
void RCASMainWindow::on_view_button_clicked()
{
    loadAssessmentPage();
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

// When clicking the "Create session" button
void RCASMainWindow::on_createsession_button_clicked()
{
    if (!this->validate_new_session())
    {
        QMessageBox::warning (this, "Check details", "Incomplete information provided to create a new assessment session. Please check the details provided.");
        return;
    }

    if (mSessionManager.sessionExists (ui->assessmentdate_edit->text(), ui->assessmentdate_edit->text()))
    {
        QMessageBox::warning (this, "Session exists", "Session with this assessor name and date already exists. Please load it from saved sessions.");
        return;
    }

    // Read the CSV file and create a new session from it
    if (!this->createSessionFromCSVFile (ui->candidatelist_edit->text()))
    {
        QMessageBox::critical (this, "Invalid CSV file", "The selected file does not contain the needed information. Please make sure to select the right file.");
        return;
    }

    mSoundManagerState = RCAS_RECORD;

    loadCandidatesPage();
}

// When clicking the "select CSV file" button
void RCASMainWindow::on_candidatelist_button_clicked()
{
    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("CSV files (*.csv)"));
    if (QFile::exists(newFileName))
    {
        ui->candidatelist_edit->setText(newFileName);
    }
}

// When clicking the button to load candidates from a selected session
void RCASMainWindow::on_loadsession_button_clicked()
{
    mSession = mSessionManager.session(ui->sessionsTable->currentRow());
    mSessionID = mSession.ID();
    loadSession (mSession);

    mSoundManagerState = RCAS_REVIEW;

    loadCandidatesPage();
}

void RCASMainWindow::on_record_button_clicked()
{
#if 0
    if (recording)
    {
        recording = false;
        ui->record_button->setText("Record");
        audioRecorder->pause();
    }
    else
    {
        recording = true;
        ui->record_button->setText("Pause");
        audioRecorder->record();
    }
#else
#endif
}
