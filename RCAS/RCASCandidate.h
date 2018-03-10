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

    void setName (const QString& name) { mName = name; }
    void setUID (int ID) { mUID = ID; }
    void setPhone (int phone) { mPhone = phone; }
    void setEmail (const QString& email) { mEmail = email; }
    void setProcess (const QString& process) { mProcess = process; }
    void setRecruiter (const QString& recruiter) { mRecruiter = recruiter; }
    void setTL (const QString& TL) { mTL = TL; }
    void setCollege (const QString& college) { mCollege = college; }
    void setSchool (const QString& school) { mSchool = school; }
    void setLocation (const QString& location) { mLocation = location; }
    void setAssessmentStatus (RCASCandidateStatus status) { mAssessmentStatus = status; }
    void addError (const RCASAssessmentError& error) { mErrorList.append(error); }

    QString name () const { return mName; }
    int UID () const { return mUID; }
    int phone () const { return mPhone; }
    QString email () const { return mEmail; }
    QString process () const { return mProcess; }
    QString recruiter () const { return mRecruiter; }
    QString TL () const { return mTL; }
    QString college () const { return mCollege; }
    QString school () const { return mSchool; }
    QString location () const { return mLocation; }
    RCASCandidateStatus assessmentStatus () const { return mAssessmentStatus; }
    int numAssessmentErrors () const { return mErrorList.size(); }
    const RCASAssessmentError & assementError (int iError) const { return mErrorList[iError]; }

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json);

    double assessmentScore () const;

private:

    QString mName;
    int mUID;
    int mPhone;
    QString mEmail;
    QString mProcess;
    QString mRecruiter;
    QString mTL;
    QString mCollege;
    QString mSchool;
    QString mLocation;
    RCASCandidateStatus mAssessmentStatus;

    QVector <RCASAssessmentError> mErrorList;
};

#endif // RCASCANDIDATE_H
