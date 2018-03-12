#include "RCASMainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QByteArray>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>
#include <QSettings>
#include <QTableWidgetItem>
#include <typeinfo>
#include <iostream>
#include "RCASCandidate.h"
#include "RCASSession.h"

void RCASMainWindow::loadSettings()
{
    QSettings settings ("Rubicon", "RCAS");

    if (settings.contains("data folder"))
    {
        mDataFolder = settings.value ("data folder").toString();
        mSessionListFile = settings.value ("sessions file").toString();
    }
    else
    {
        QMessageBox::information(0, "Select location to store data",
                                 "Please select a directory under which RCAS can store data.");

        mDataFolder = QFileDialog::getExistingDirectory(this, "RCAS data folder location", QDir::homePath());
        mDataFolder = mDataFolder + QDir::separator() + "RCAS_DATA";

        QDir dataDir;
        if (!dataDir.exists (mDataFolder))
        {
            dataDir.mkdir(mDataFolder);
        }

        mSessionListFile = mDataFolder + QDir::separator() + "Sessions_list.json";

        settings.setValue(QString ("data folder"), mDataFolder);
        settings.setValue(QString ("sessions file"), mSessionListFile);
    }
}

void RCASMainWindow::loadSessionsFromJson ()
{
    QFile sessionsJsonFile (mSessionListFile);

    if (!sessionsJsonFile.open(QIODevice::ReadWrite))
    {
        qWarning("Couldn't open sessions file.");
    }
    else
    {
        QByteArray sessionsData = sessionsJsonFile.readAll();
        QJsonDocument loadJsonDoc (QJsonDocument::fromJson(sessionsData));
        mSessionManager.readFromJson(loadJsonDoc.object());
    }

    // Create entries in the sessions page
    int numSession = mSessionManager.numSession();
    ui->sessionsTable->setRowCount(numSession);
    ui->sessionsTable->setColumnCount(3);
    for (int iSession = 0; iSession < numSession; iSession++)
    {
        RCASSession session = mSessionManager.session(iSession);
        qDebug() << session.ID() << session.sessionDate() << session.assessorName();

        QTableWidgetItem* item = new QTableWidgetItem (QString::number (session.ID()));
        ui->sessionsTable->setItem(iSession, 0, item);

        item = new QTableWidgetItem (session.sessionDate());
        ui->sessionsTable->setItem(iSession, 1, item);

        item = new QTableWidgetItem (session.assessorName());
        ui->sessionsTable->setItem(iSession, 2, item);
    }

    qDebug() << "Reading stored session details - " << mSessionManager.numSession() << "sessions read.";
}

void RCASMainWindow::saveSessionsToJson ()
{
    QFile sessionsJsonFile (mSessionListFile);

    if (sessionsJsonFile.open(QIODevice::ReadWrite))
    {
        qDebug() << "Current session ID: " << mSessionManager.currentSessionID();

        QJsonObject sessionsManagerObject;
        mSessionManager.writeToJson (sessionsManagerObject);

        QJsonDocument sessionsJsonDoc (sessionsManagerObject);
        sessionsJsonFile.write (sessionsJsonDoc.toJson());
    }
}

bool RCASMainWindow::validate_new_session() const
{
    if (ui->assessorname_edit->text().isEmpty())
    {
        return false;
    }

    if (!ui->assessmentdate_edit->date().isValid() || ui->assessmentdate_edit->date() < QDate::currentDate())
    {
        return false;
    }

    if (!QFile::exists (ui->candidatelist_edit->text()))
    {
        return false;
    }

    return true;
}

bool RCASMainWindow::createSessionFromCSVFile (const QString &fileName)
{
    QFile file(fileName);
    if (!file.open (QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray header = file.readLine ();
    if (header.isEmpty())
    {
        return false;
    }

    QList <QByteArray> headerWords = header.split(',');
    int numHeaderWords = headerWords.size();
    if (numHeaderWords != 11)
    {
        return false;
    }

    QList <QByteArray> lines;
    while (!file.atEnd ())
    {
        lines.append(file.readLine ());
    }

    int numCandidates = lines.size();
    if (!numCandidates)
    {
        return false;
    }

    // Create a new session and add to the session manager
    RCASSession newSession;
    newSession.setID (mSessionManager.currentSessionID());
    newSession.setAssessorName(this->ui->assessorname_edit->text());
    newSession.setSessionDate(this->ui->assessmentdate_edit->text());

    ui->candidate_table->setRowCount(numCandidates);
    ui->candidate_table->setColumnCount(10);

    // Populate the table widget with the list of candidates and create candidates for the session
    for (int i = 0; i < numCandidates; i++)
    {
        QList <QByteArray> candidateDetails = lines[i].split(',');

        for (int j = 1; j < numHeaderWords; j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem (QString (candidateDetails[j]));
            ui->candidate_table->setItem(i, j-1, item);
        }

        // Create a candidate and add to the new session
        RCASCandidate candidate;
        candidate.setName (QString (candidateDetails[1]).trimmed());
        candidate.setUID (QString (candidateDetails[2]).trimmed());
        candidate.setPhone (QString (candidateDetails[3]).trimmed());
        candidate.setEmail (QString (candidateDetails[4]).trimmed());
        candidate.setProcess (QString (candidateDetails[5]).trimmed());
        candidate.setRecruiter (QString (candidateDetails[6]).trimmed());
        candidate.setTL (QString (candidateDetails[7]).trimmed());
        candidate.setCollege (QString (candidateDetails[8]).trimmed());
        candidate.setSchool (QString (candidateDetails[9]).trimmed());
        candidate.setLocation (QString (candidateDetails[10]).trimmed());

        QString audioFilePath = mDataFolder + QDir::separator() + candidate.name() + "_" + QString::number(newSession.ID()) + ".wav";
        candidate.setAudioFilePath (audioFilePath.trimmed());

        newSession.addCandidate (candidate);
    }

    mSessionManager.addSession(newSession);

    mSession = newSession;
    mSessionID = newSession.ID();

    saveSessionsToJson();
    return true;
}

void RCASMainWindow::loadSession (const RCASSession session)
{
    int numCandidates = session.numCandidates();

    ui->candidate_table->setRowCount(numCandidates);
    ui->candidate_table->setColumnCount(10);

    // Populate the table widget with the list of candidates and create candidates for the session
    for (int i = 0; i < numCandidates; i++)
    {
        const RCASCandidate c = session.candidate(i);

        QTableWidgetItem* item = new QTableWidgetItem (c.name());
        ui->candidate_table->setItem(i, 0, item);

        item = new QTableWidgetItem (c.UID());
        ui->candidate_table->setItem(i, 1, item);

        item = new QTableWidgetItem (c.phone());
        ui->candidate_table->setItem(i, 2, item);

        item = new QTableWidgetItem (c.email());
        ui->candidate_table->setItem(i, 3, item);

        item = new QTableWidgetItem (c.process());
        ui->candidate_table->setItem(i, 4, item);

        item = new QTableWidgetItem (c.recruiter());
        ui->candidate_table->setItem(i, 5, item);

        item = new QTableWidgetItem (c.TL());
        ui->candidate_table->setItem(i, 6, item);

        item = new QTableWidgetItem (c.college());
        ui->candidate_table->setItem(i, 7, item);

        item = new QTableWidgetItem (c.school());
        ui->candidate_table->setItem(i, 8, item);

        item = new QTableWidgetItem (c.location());
        ui->candidate_table->setItem(i, 9, item);
    }

    mSessionID = session.ID();
    mSession = session;
}
