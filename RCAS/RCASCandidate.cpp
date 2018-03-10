#include "RCASCandidate.h"
#include <QJsonArray>

RCASCandidate::RCASCandidate ()
{
    mAssessmentStatus = RCAS_UNASSESSED;
}

void RCASCandidate::write (QJsonObject& json) const
{
    json["name"] = mName;
    json["UID"] = mUID;
    json["phone"] = mPhone;
    json["email"] = mEmail;
    json["process"] = mProcess;
    json["recruiter"] = mRecruiter;
    json["TL"] = mTL;
    json["college"] = mCollege;
    json["school"] = mSchool;
    json["location"] = mLocation;
    json["status"] = mAssessmentStatus;

    QJsonArray errArray;
    foreach (const RCASAssessmentError err, mErrorList)
    {
        QJsonObject errObject;
        err.write(errObject);
        errArray.append(errObject);
    }

    json["errors"] = errArray;
}

void RCASCandidate::read (const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("UID") && json["UID"].isDouble())
        mName = json["UID"].toInt();

    if (json.contains("phone") && json["phone"].isDouble())
        mName = json["phone"].toInt();

    if (json.contains("email") && json["email"].isString())
        mName = json["email"].toString();

    if (json.contains("process") && json["process"].isString())
        mName = json["process"].toString();

    if (json.contains("recruiter") && json["recruiter"].isString())
        mName = json["recruiter"].toString();

    if (json.contains("TL") && json["TL"].isString())
        mName = json["TL"].toString();

    if (json.contains("college") && json["college"].isString())
        mName = json["college"].toString();

    if (json.contains("school") && json["school"].isString())
        mName = json["school"].toString();

    if (json.contains("location") && json["location"].isString())
        mName = json["location"].toString();

    if (json.contains("status") && json["status"].isDouble())
        mName = (RCASCandidateStatus) json["status"].toInt();

    if (json.contains("errors") && json["errors"].isArray()) {
        QJsonArray errJsonArray = json["errors"].toArray();

        mErrorList.clear();
        mErrorList.reserve (errJsonArray.size());

        for (int iErr = 0; iErr < errJsonArray.size(); ++iErr)
        {
            QJsonObject errJson = errJsonArray[iErr].toObject();
            RCASAssessmentError err;
            err.read (errJson);
            mErrorList.append(err);
        }
    }
}

double RCASCandidate::assessmentScore () const
{
    return 0;
}
