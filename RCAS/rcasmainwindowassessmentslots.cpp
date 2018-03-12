#include "RCASMainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QFile>

// When clicking on the "<< Candidates list" button, switch to the candidate page of the stacked widget
void RCASMainWindow::on_candidates2_button_clicked()
{
    if (mCandidate.modified())
    {
        mSession.setModified(true);
        mSession.setCandidate(mCandidateID, mCandidate);

        mSessionManager.setSession (mSessionID - 1, mSession);
    }

    loadCandidatesPage();
}

void RCASMainWindow::on_recordplay_button_clicked ()
{
    mAudioManager.setPlaybackFileLocation(QUrl::fromLocalFile(mCandidate.audioFilePath()));

    if (mSoundManagerState == RCAS_RECORD)
    {
        if (ui->recordplay_button->text() == QString ("Record"))
        {
            ui->recordplay_button->setText(QString("Pause"));
            mAudioManager.recordAudio();

            setErrorButtonsState(true);
            ui->error_table->setEnabled(true);
            ui->candidates2_button->setEnabled(false);
        }
        else
        {
            ui->recordplay_button->setText(QString("Record"));
            mAudioManager.pauseRecording();

            setErrorButtonsState(false);
            ui->error_table->setEnabled(false);
            ui->candidates2_button->setEnabled(true);

            int candidateScore = mCandidate.assessmentScore();

            bool fatalScore = false;
            if (candidateScore < 0)
            {
                fatalScore = true;
                candidateScore *= -1;
            }

            ui->scoreEdit->setText (QString::number(candidateScore));
            if (fatalScore)
            {
                ui->scoreEdit->setStyleSheet ("QLineEdit { color : red; }");
            }
        }
    }
    else
    {
        ui->error_table->setEnabled(true);
        setErrorButtonsState(false);

        if (ui->recordplay_button->text() == QString ("Play"))
        {
            qint64 playbackLoc = 0;

            if (ui->error_table->currentRow() > -1)
            {
                int errorIndex = ui->error_table->currentRow();
                RCASAssessmentError e = mCandidate.assementError(errorIndex);
                playbackLoc = e.time() - 41000;
                if (playbackLoc < 0)
                {
                    playbackLoc = 0;
                }
            }
            else
            {
                ui->error_table->setEnabled(false);
            }

            ui->recordplay_button->setText(QString("Pause"));
            mAudioManager.playAudio (playbackLoc);

            ui->candidates2_button->setEnabled(false);
        }
        else
        {
            ui->recordplay_button->setText(QString("Play"));
            mAudioManager.pausePlayback();

            ui->error_table->setEnabled(true);
            ui->candidates2_button->setEnabled(true);
        }
    }
}

void RCASMainWindow::setErrorButtonsState (bool state)
{
    ui->FLI_button->setEnabled(state);
    ui->clarity_button->setEnabled(state);
    ui->wordloss_button->setEnabled(state);
    ui->ROS_button->setEnabled(state);
    ui->grammar_button->setEnabled(state);
    ui->words_button->setEnabled(state);
    ui->pronunciation_button->setEnabled(state);
    ui->comprehension_button->setEnabled(state);
    ui->fillers_button->setEnabled(state);
    ui->vocalization_button->setEnabled(state);
    ui->callflow_button->setEnabled(state);
    ui->personalization_button->setEnabled(state);
    ui->acknowledgement_button->setEnabled(state);
    ui->ownership_button->setEnabled(state);
    ui->enquiry_button->setEnabled(state);
    ui->solutionquality_button->setEnabled(state);
}

void RCASMainWindow::updateDuration(qint64 duration)
{
    mDuration = duration;
    ui->duration_edit->setText(QDateTime::fromTime_t(duration/1000).toUTC().toString("hh:mm:ss"));
}

void RCASMainWindow::on_FLI_clicked ()
{
    RCASAssessmentError e;
    e.setType (FATAL_FIRST_LANGUAGE_INFLUENCE);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_clarity_clicked ()
{
    RCASAssessmentError e;
    e.setType (FATAL_CLARITY_OF_SPEECH);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_wordsloss_clicked ()
{
    RCASAssessmentError e;
    e.setType (FATAL_LOSS_OF_WORDS);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_ros_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_ROS);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_grammar_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_GRAMMAR);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_vocab_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_WORDS_VOCABULARY);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_pronunc_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_PRONUNCIATION);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_comprehen_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_COMPREHENSION);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_fillers_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_FILLERS_VERBALIZATION);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_vocaliz_clicked ()
{
    RCASAssessmentError e;
    e.setType (LANG_VOCALIZATION);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_callflow_clicked ()
{
    RCASAssessmentError e;
    e.setType (CSP_CALL_FLOW_PROTOCOL_COMPLIANCE);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_personaliz_clicked ()
{
    RCASAssessmentError e;
    e.setType (CSP_PERSONALIZATION);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_acknowl_clicked ()
{
    RCASAssessmentError e;
    e.setType (CSP_ACKNOWLEDGEMENT_EMOTIONS_EMPATHY);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_ownersh_clicked ()
{
    RCASAssessmentError e;
    e.setType (CSP_OWNERSHIP_CALL_CONTROL);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_probing_clicked ()
{
    RCASAssessmentError e;
    e.setType (CSP_PROBING_ENQUIRING);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}

void RCASMainWindow::on_qos_clicked ()
{
    RCASAssessmentError e;
    e.setType (CSP_QUALITY_OF_SOLUTION);
    e.setTime(mDuration);

    mCandidate.addError(e);

    int numErrors = ui->error_table->rowCount();
    ui->error_table->setRowCount(numErrors + 1);
    QString durText = QDateTime::fromTime_t(mDuration/1000).toUTC().toString("hh:mm:ss");
    ui->error_table->setItem(numErrors, 0, new QTableWidgetItem (durText));
    ui->error_table->setItem(numErrors, 1, new QTableWidgetItem (e.textString()));
}
