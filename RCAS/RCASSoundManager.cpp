#include "RCASSoundManager.h"

RCASSoundManager::RCASSoundManager()
{
    // Initialize audio settings
    audioSettings.setCodec("audio/pwm");
    audioSettings.setQuality(QMultimedia::NormalQuality);

    // Initialize audio recorder
    audioRecorder.setEncodingSettings(audioSettings);

    // Initialize audio (media) player
    audioPlayer.setAudioRole(QAudio::UnknownRole); // CHECK FROM WINDOWS WORKING VERSION
}

// Set the file location to which audio should be recorded
void RCASSoundManager::setRecordingFileLocation (QUrl fileURL)
{
    audioRecorder.setOutputLocation (fileURL);
}

// Set the file location from which audio should be played back
void RCASSoundManager::setPlaybackFileLocation (QUrl fileURL)
{
    audioPlayer.setMedia (fileURL);
}

// Record/pause audio
void RCASSoundManager::recordAudio ()
{
    audioRecorder.record();
}

void RCASSoundManager::pauseRecording ()
{
    audioRecorder.pause();
}

// Playback/pause audio
void RCASSoundManager::playAudio (qint64 loc)
{
    audioPlayer.setPosition (loc);
    audioPlayer.play();
}

void RCASSoundManager::pausePlayback ()
{
    audioPlayer.pause();
}
