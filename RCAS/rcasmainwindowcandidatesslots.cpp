#include <QMessageBox>
#include "RCASMainwindow.h"

// When clicking on the "Start" button, switch to the assessment page of the stacked widget
void RCASMainWindow::on_startassessment_button_clicked()
{
    mCandidateID = ui->candidate_table->currentRow();
    mCandidate = mSession.candidate(mCandidateID);

    setErrorButtonsState(false);

    if (mSoundManagerState == RCAS_RECORD && mCandidate.assessmentStatus() != RCAS_UNASSESSED)
    {
        if (QMessageBox::question (this, "Candidate already assessed",
                                   "This candidate has already been assessed. Restarting assessment will clear previous records. Do you want to proceed?") ==
                QMessageBox::Yes)
        {
            mCandidate.clearErrors();
            mCandidate.setAssessmentStatus(RCAS_UNASSESSED);
        }
        else
        {
            return;
        }
    }

    loadAssessmentPage();
}

void RCASMainWindow::on_sessions_button_clicked()
{
    loadSessionsFromJson();
    loadSessionsPage();
    ui->tabWidget->setCurrentIndex(1);
}
