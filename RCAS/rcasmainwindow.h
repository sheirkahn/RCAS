#ifndef RCASMAINWINDOW_H
#define RCASMAINWINDOW_H

#include <QAudioEncoderSettings>
#include <QAudioRecorder>
#include <QDialog>
#include <QMainWindow>
#include <QMediaPlayer>

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

    bool validate_new_session () const;
    bool readCandidatesFromCSVFile (const QString& fileName) const;

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

private:

    Ui::RCASMainWindow*     ui;
    bool                    recording;
    QAudioRecorder*         audioRecorder;
    QAudioEncoderSettings   audioSettings;
    QMediaPlayer*           audioPlayer;
};

#endif // RCASMAINWINDOW_H
