#ifndef RCASCANDIDATE_H
#define RCASCANDIDATE_H

#include <QJsonObject>
#include <QVector>
#include "RCASAssessmentError.h"

enum RCASCandidateStatus {
    RCAS_UNASSESSED = 0,
    RCAS_INTERVIEW = 1,
    RCAS_TRAINING = 2,
    RCAS_REJECT = 3
};

class RCASCandidate
{

public:

    RCASCandidate ();

    void setName (const QString& name) { mName = name; mModified = true; }
    void setUID (const QString& ID) { mUID = ID; mModified = true; }
    void setPhone (const QString& phone) { mPhone = phone; mModified = true; }
    void setEmail (const QString& email) { mEmail = email; mModified = true; }
    void setProcess (const QString& process) { mProcess = process; mModified = true; }
    void setRecruiter (const QString& recruiter) { mRecruiter = recruiter; mModified = true; }
    void setTL (const QString& TL) { mTL = TL; mModified = true; }
    void setCollege (const QString& college) { mCollege = college; mModified = true; }
    void setSchool (const QString& school) { mSchool = school; mModified = true; }
    void setLocation (const QString& location) { mLocation = location; mModified = true; }
    void setAudioFilePath (const QString& path) { mAudioFilePath = path; mModified = true; }
    void setAssessmentStatus (RCASCandidateStatus status) { mAssessmentStatus = status; mModified = true; }
    void addError (const RCASAssessmentError& error) { mErrorList.append(error); mModified = true; }
    void setModified (bool val) { mModified = val; }

    const QString & name () const { return mName; }
    const QString & UID () const { return mUID; }
    const QString & phone () const { return mPhone; }
    const QString & email () const { return mEmail; }
    const QString & process () const { return mProcess; }
    const QString & recruiter () const { return mRecruiter; }
    const QString & TL () const { return mTL; }
    const QString & college () const { return mCollege; }
    const QString & school () const { return mSchool; }
    const QString & location () const { return mLocation; }
    const QString & audioFilePath () const { return mAudioFilePath; }
    RCASCandidateStatus assessmentStatus () const { return mAssessmentStatus; }
    int numAssessmentErrors () const { return mErrorList.size(); }
    const RCASAssessmentError & assementError (int iError) const { return mErrorList[iError]; }
    bool modified () const { return mModified; }

    void writeToJson (QJsonObject &json);
    void readFromJson (const QJsonObject &json);

    int assessmentScore () const;

private:

    bool mModified;
    QString mName;
    QString mUID;
    QString mPhone;
    QString mEmail;
    QString mProcess;
    QString mRecruiter;
    QString mTL;
    QString mCollege;
    QString mSchool;
    QString mLocation;
    QString mAudioFilePath;
    RCASCandidateStatus mAssessmentStatus;

    QVector <RCASAssessmentError> mErrorList;
};

#endif // RCASCANDIDATE_H
