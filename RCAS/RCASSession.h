#ifndef RCASSESSION_H
#define RCASSESSION_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include "RCASCandidate.h"

class RCASSession
{
public:
    RCASSession ();

    void setID (int ID) { mID = ID; mModified = true; }
    void setAssessorName (const QString& name) { mAssessorName = name; mModified = true; }
    void setSessionDate (const QString& date) { mSessionDate = date; mModified = true; }
    void addCandidate (const RCASCandidate& candidate) { mCandidateList.append(candidate); mModified = true; }
    void setCandidate (int iCandidate, const RCASCandidate& newCandidate) { mCandidateList[iCandidate] = newCandidate; mModified = true; }
    void setModified (bool val) { mModified = val; }

    int ID () const { return mID; }
    const QString & assessorName () const { return mAssessorName; }
    const QString & sessionDate () const { return mSessionDate; }
    int numCandidates () const { return mCandidateList.size(); }
    const RCASCandidate& candidate (int iCandidate) const { return mCandidateList[iCandidate]; }
    bool modified () const { return mModified; }

    bool readCandidatesFromCSVFile (const QString &fileName);
    void writeToJson (QJsonObject &json);
    void readFromJson (const QJsonObject &json);

private:

    bool mModified;
    int mID;
    QString mAssessorName;
    QString mSessionDate;
    QVector <RCASCandidate> mCandidateList;
};

#endif // RCASSESSION_H
