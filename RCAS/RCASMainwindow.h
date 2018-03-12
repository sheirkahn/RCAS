#ifndef RCASMAINWINDOW_H
#define RCASMAINWINDOW_H

#include "ui_rcasmainwindow.h"
#include <QAudioEncoderSettings>
#include <QAudioRecorder>
#include <QDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QUrl>
#include "RCASSessionManager.h"
#include "RCASSoundManager.h"

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

private:

    void loadSettings ();
    void loadSessionsFromJson ();
    void saveSessionsToJson ();
    bool validate_new_session () const;

    bool createSessionFromCSVFile (const QString& fileName);
    void loadSession (const RCASSession session);
    void assessCandidate (const RCASCandidate candidate);

    void loadSessionsPage (bool firstLoad = false);
    void loadCandidatesPage ();
    void loadAssessmentPage ();

    void setErrorButtonsState (bool state);

public slots:

    bool on_quit ();

private slots:

    void on_RCASMainWindow_iconSizeChanged(const QSize &iconSize);

    void on_createsession_button_clicked(); // Create session button (sessions page)
    void on_loadsession_button_clicked(); // When loading a session (sessions page)
    void on_candidatelist_button_clicked(); // When selecting a CSV file with candidates info

    void on_sessions_button_clicked(); // When going back to sessions page from candidates page
    void on_startassessment_button_clicked(); // When starting assessment of selected candidate

    void on_candidates2_button_clicked();
    void on_recordplay_button_clicked();


    void on_FLI_clicked ();
    void on_clarity_clicked ();
    void on_wordsloss_clicked ();
    void on_ros_clicked ();
    void on_grammar_clicked ();
    void on_vocab_clicked ();
    void on_pronunc_clicked ();
    void on_comprehen_clicked ();
    void on_fillers_clicked ();
    void on_vocaliz_clicked ();
    void on_callflow_clicked ();
    void on_personaliz_clicked ();
    void on_acknowl_clicked ();
    void on_ownersh_clicked ();
    void on_probing_clicked ();
    void on_qos_clicked ();

    void updateDuration(qint64 duration);

private:

    Ui::RCASMainWindow*     ui;
    QString                 mDataFolder;
    QString                 mSessionListFile;

    RCASSessionManager      mSessionManager;
    RCASSession             mSession;
    RCASCandidate           mCandidate;
    int                     mSessionID;
    int                     mCandidateID;

    RCASSoundManager        mAudioManager;
    RCASSoundManagerState   mSoundManagerState;
    qint64                  mDuration;
};

#endif // RCASMAINWINDOW_H
