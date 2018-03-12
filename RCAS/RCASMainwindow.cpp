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

    // Sessions creation/selection page
    connect (ui->createsession_button, SIGNAL(clicked(bool)), this, SLOT (on_createsession_button_clicked()), Qt::UniqueConnection);
    connect (ui->loadsession_button, SIGNAL(clicked(bool)), this, SLOT (on_loadsession_button_clicked()), Qt::UniqueConnection);
    connect (ui->candidatelist_button, SIGNAL(clicked(bool)), this, SLOT (on_candidatelist_button_clicked()), Qt::UniqueConnection);

    // Candidates page
    connect (ui->startassessment_button, SIGNAL(clicked(bool)), this, SLOT (on_startassessment_button_clicked()), Qt::UniqueConnection);
    connect (ui->sessions_button, SIGNAL(clicked(bool)), this, SLOT (on_sessions_button_clicked()), Qt::UniqueConnection);

    // Assessment page
    connect (ui->candidates2_button, SIGNAL(clicked(bool)), this, SLOT (on_candidates2_button_clicked()), Qt::UniqueConnection);
    connect (ui->recordplay_button, SIGNAL(clicked(bool)), this, SLOT (on_recordplay_button_clicked()), Qt::UniqueConnection);

    connect (ui->FLI_button, SIGNAL(clicked(bool)), this, SLOT (on_FLI_clicked ()), Qt::UniqueConnection);
    connect (ui->clarity_button, SIGNAL(clicked(bool)), this, SLOT (on_clarity_clicked()), Qt::UniqueConnection);
    connect (ui->wordloss_button, SIGNAL(clicked(bool)), this, SLOT (on_wordsloss_clicked(FATAL_LOSS_OF_WORDS)), Qt::UniqueConnection);
    connect (ui->ROS_button, SIGNAL(clicked(bool)), this, SLOT (on_ros_clicked()), Qt::UniqueConnection);
    connect (ui->grammar_button, SIGNAL(clicked(bool)), this, SLOT (on_grammar_clicked()), Qt::UniqueConnection);
    connect (ui->words_button, SIGNAL(clicked(bool)), this, SLOT (on_vocab_clicked()), Qt::UniqueConnection);
    connect (ui->pronunciation_button, SIGNAL(clicked(bool)), this, SLOT (on_pronunc_clicked()), Qt::UniqueConnection);
    connect (ui->comprehension_button, SIGNAL(clicked(bool)), this, SLOT (on_comprehen_clicked()), Qt::UniqueConnection);
    connect (ui->fillers_button, SIGNAL(clicked(bool)), this, SLOT (on_fillers_clicked()), Qt::UniqueConnection);
    connect (ui->vocalization_button, SIGNAL(clicked(bool)), this, SLOT (on_vocaliz_clicked()), Qt::UniqueConnection);
    connect (ui->callflow_button, SIGNAL(clicked(bool)), this, SLOT (on_callflow_clicked()), Qt::UniqueConnection);
    connect (ui->personalization_button, SIGNAL(clicked(bool)), this, SLOT (on_personaliz_clicked()), Qt::UniqueConnection);
    connect (ui->acknowledgement_button, SIGNAL(clicked(bool)), this, SLOT (on_acknowl_clicked()), Qt::UniqueConnection);
    connect (ui->ownership_button, SIGNAL(clicked(bool)), this, SLOT (on_ownersh_clicked()), Qt::UniqueConnection);
    connect (ui->enquiry_button, SIGNAL(clicked(bool)), this, SLOT (on_probing_clicked()), Qt::UniqueConnection);
    connect (ui->solutionquality_button, SIGNAL(clicked(bool)), this, SLOT (on_qos_clicked()), Qt::UniqueConnection);

    // AUDIO RECORDER DURATION SIGNAL
    connect(&mAudioManager.audioPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)), Qt::UniqueConnection);
    connect(&mAudioManager.audioRecorder, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)), Qt::UniqueConnection);

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
        ui->tabWidget->setTabText (1, "Saved assessment sessions");

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
        ui->startassessment_button->setText("Assess >>");
    }
    else
    {
        ui->startassessment_button->setText("Review >>");
    }
}

void RCASMainWindow::loadAssessmentPage()
{
    mCandidateID = ui->candidate_table->currentRow();
    mCandidate = mSession.candidate(mCandidateID);

    ui->stackedWidget->setCurrentIndex(2);
    ui->title_label->setText("Candidate assessment");

    ui->recordplay_button->setText(mSoundManagerState == RCAS_RECORD ? "Record" : "Play");
    ui->recordplay_button->setEnabled(true);

    ui->candidatename_edit->setText(mCandidate.name());
    ui->candidateid_edit->setText(mCandidate.UID());

    ui->duration_edit->setText("00:00:00");

    int candidateScore = mCandidate.assessmentScore();

    bool fatalScore = false;
    if (candidateScore < 0)
    {
        fatalScore = true;
        candidateScore *= -1;
    }

    ui->scoreEdit->setText(mSoundManagerState == RCAS_RECORD ? QString::number(100) : QString::number(candidateScore));
    if (fatalScore)
    {
        ui->scoreEdit->setStyleSheet ("QLineEdit { color : red; }");
    }

    setErrorButtonsState(false);

    if (mSoundManagerState == RCAS_REVIEW)
    {
        int numError = mCandidate.numAssessmentErrors();

        ui->error_table->setRowCount(numError);
        ui->error_table->setColumnCount(2);

        for (int iError = 0; iError < numError; iError++)
        {
            RCASAssessmentError e = mCandidate.assementError(iError);
            ui->error_table->setItem(iError, 0, new QTableWidgetItem (e.time()));
            ui->error_table->setItem(iError, 1, new QTableWidgetItem (e.textString()));
        }

        mAudioManager.setPlaybackFileLocation(QUrl::fromLocalFile(mCandidate.audioFilePath()));
    }
    else
    {
        ui->error_table->setRowCount(0);
        ui->error_table->setColumnCount(2);
        mAudioManager.setRecordingFileLocation(QUrl::fromLocalFile(mCandidate.audioFilePath()));
    }
}

void RCASMainWindow::on_RCASMainWindow_iconSizeChanged(const QSize &iconSize)
{}

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



