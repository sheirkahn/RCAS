#ifndef RCASMAINWINDOW_H
#define RCASMAINWINDOW_H

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

public slots:

    bool on_quit ();

private slots:

    void on_RCASMainWindow_iconSizeChanged(const QSize &iconSize);

    void on_candidate_button_clicked();

    void on_sessions_back_button_clicked();

    void on_start_button_clicked();

    void on_view_button_clicked();

    void on_sessions_button_clicked();

    void on_candidates2_button_clicked();

    void on_createsession_button_clicked();

    void on_candidatelist_button_clicked();

    void on_record_button_clicked();

    void updateDuration (qint64 duration);

    void on_loadsession_button_clicked();

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
};

#endif // RCASMAINWINDOW_H
