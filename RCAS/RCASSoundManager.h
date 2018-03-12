#ifndef RCASSOUNDMANAGER_H
#define RCASSOUNDMANAGER_H

#include <QObject>

#include <QAudioEncoderSettings>
#include <QAudioRecorder>
#include <QMediaPlayer>

enum RCASSoundManagerState
{
    RCAS_RECORD = 0,
    RCAS_REVIEW = 1
};

class RCASSoundManager
{
public:
    RCASSoundManager();

public slots:

    // Set the file location to which audio should be recorded
    void setRecordingFileLocation (QUrl fileURL);

    // Set the file location from which audio should be played back
    void setPlaybackFileLocation (QUrl fileURL);

    // Record/pause audio
    void recordAudio ();
    void pauseRecording ();

    // Playback/pause audio
    void playAudio (qint64 loc = 0);
    void pausePlayback ();

public:

    QAudioEncoderSettings   audioSettings;
    QAudioRecorder          audioRecorder;
    QMediaPlayer            audioPlayer;
};

#endif // RCASSOUNDMANAGER_H
