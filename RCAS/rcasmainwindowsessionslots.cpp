#include "RCASMainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

// When clicking the "select CSV file" button
void RCASMainWindow::on_candidatelist_button_clicked()
{
    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("CSV files (*.csv)"));
    if (QFile::exists(newFileName))
    {
        ui->candidatelist_edit->setText(newFileName);
    }
}

// When clicking the "Create session" button
void RCASMainWindow::on_createsession_button_clicked()
{
    if (!this->validate_new_session())
    {
        QMessageBox::warning (this, "Check details", "Incomplete information provided to create a new assessment session. Please check the details provided.");
        return;
    }

    if (mSessionManager.sessionExists (ui->assessorname_edit->text(), ui->assessmentdate_edit->text()))
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


// When clicking the button to load candidates from a selected session
void RCASMainWindow::on_loadsession_button_clicked()
{
    mSession = mSessionManager.session(ui->sessionsTable->currentRow());
    mSessionID = mSession.ID();
    loadSession (mSession);

    mSoundManagerState = RCAS_REVIEW;

    loadCandidatesPage();
}
