#include "RCASCandidate.h"
#include <QJsonArray>

RCASCandidate::RCASCandidate ()
{
    mAssessmentStatus = RCAS_UNASSESSED;
    mModified = false;
}

void RCASCandidate::writeToJson (QJsonObject& json)
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
    json["audioPath"] = mAudioFilePath;
    json["status"] = mAssessmentStatus;

    QJsonArray errArray;
    foreach (RCASAssessmentError err, mErrorList)
    {
        QJsonObject errObject;
        err.writeToJson(errObject);
        errArray.append(errObject);
    }

    json["errors"] = errArray;

    mModified = false;
}

void RCASCandidate::readFromJson (const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("UID") && json["UID"].isString())
        mUID = json["UID"].toString();

    if (json.contains("phone") && json["phone"].isString())
        mPhone = json["phone"].toString();

    if (json.contains("email") && json["email"].isString())
        mEmail = json["email"].toString();

    if (json.contains("process") && json["process"].isString())
        mProcess = json["process"].toString();

    if (json.contains("recruiter") && json["recruiter"].isString())
        mRecruiter = json["recruiter"].toString();

    if (json.contains("TL") && json["TL"].isString())
        mTL = json["TL"].toString();

    if (json.contains("college") && json["college"].isString())
        mCollege = json["college"].toString();

    if (json.contains("school") && json["school"].isString())
        mSchool = json["school"].toString();

    if (json.contains("location") && json["location"].isString())
        mLocation = json["location"].toString();

    if (json.contains("audioPath") && json["audioPath"].isString())
        mAudioFilePath = json["audioPath"].toString();

    if (json.contains("status") && json["status"].isDouble())
        mAssessmentStatus = (RCASCandidateStatus) json["status"].toInt();

    if (json.contains("errors") && json["errors"].isArray())
    {
        QJsonArray errJsonArray = json["errors"].toArray();

        mErrorList.clear();
        mErrorList.reserve (errJsonArray.size());

        for (int iErr = 0; iErr < errJsonArray.size(); ++iErr)
        {
            QJsonObject errJson = errJsonArray[iErr].toObject();
            RCASAssessmentError err;
            err.readFromJson (errJson);
            mErrorList.append(err);
        }
    }
}

int RCASCandidate::assessmentScore () const
{
    return 50;
}
