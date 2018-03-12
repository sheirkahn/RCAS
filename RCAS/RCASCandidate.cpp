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
    int numError = mErrorList.size();

    int errCount[16];
    int errScore[16];
    for (int iErr = 0; iErr < 16; iErr++)
    {
        errCount[iErr] = 0;
        errScore[iErr] = 0;
    }

    for (int iErr = 0; iErr < numError; iErr++)
    {
        RCASAssessmentError e = mErrorList[iErr];

        switch (e.type())
        {
        case RCAS_NO_ERROR: break;
        case FATAL_FIRST_LANGUAGE_INFLUENCE: errCount[0] = errCount[0] + 1; break;
        case FATAL_CLARITY_OF_SPEECH: errCount[1] = errCount[1] + 1; break;
        case FATAL_LOSS_OF_WORDS: errCount[2] = errCount[2] + 1; break;
        case LANG_ROS: errCount[3] = errCount[3] + 1; break;
        case LANG_GRAMMAR: errCount[4] = errCount[4] + 1; break;
        case LANG_WORDS_VOCABULARY: errCount[5] = errCount[5] + 1; break;
        case LANG_PRONUNCIATION: errCount[6] = errCount[6] + 1; break;
        case LANG_COMPREHENSION: errCount[7] = errCount[7] + 1; break;
        case LANG_FILLERS_VERBALIZATION: errCount[8] = errCount[8] + 1; break;
        case LANG_VOCALIZATION: errCount[9] = errCount[9] + 1; break;
        case CSP_CALL_FLOW_PROTOCOL_COMPLIANCE: errCount[10] = errCount[10] + 1; break;
        case CSP_PERSONALIZATION: errCount[11] = errCount[11] + 1; break;
        case CSP_ACKNOWLEDGEMENT_EMOTIONS_EMPATHY: errCount[12] = errCount[12] + 1; break;
        case CSP_OWNERSHIP_CALL_CONTROL: errCount[13] = errCount[13] + 1; break;
        case CSP_PROBING_ENQUIRING: errCount[14] = errCount[14] + 1; break;
        case CSP_QUALITY_OF_SOLUTION: errCount[15] = errCount[15] + 1; break;
        }
    }

    if (errCount[3] < 2) errScore[3] = 2;
    else if (errCount[3] < 3) errScore[3] = 1;

    if (errCount[4] < 2) errScore[4] = 2;
    else if (errCount[4] < 7) errScore[3] = 1;

    if (errCount[5] < 2) errScore[5] = 2;
    else if (errCount[5] < 4) errScore[5] = 1;

    if (errCount[6] < 2) errScore[6] = 2;
    else if (errCount[6] < 7) errScore[6] = 1;

    if (errCount[7] < 2) errScore[7] = 2;
    else if (errCount[7] < 4) errScore[7] = 1;

    if (errCount[8] < 2) errScore[8] = 2;
    else if (errCount[8] < 4) errScore[8] = 1;

    if (errCount[9] < 2) errScore[9] = 2;
    else if (errCount[9] < 4) errScore[9] = 1;

    if (errCount[10] < 2) errScore[10] = 2;
    else if (errCount[10] < 3) errScore[10] = 1;

    if (errCount[11] < 1) errScore[11] = 2;
    else if (errCount[11] < 2) errScore[11] = 1;

    if (errCount[12] < 3) errScore[12] = 2;
    else if (errCount[12] < 4) errScore[12] = 1;

    if (errCount[13] < 3) errScore[13] = 2;
    else if (errCount[13] < 4) errScore[13] = 1;

    if (errCount[14] == 0) errScore[14] = 2;

    if (errCount[15] == 0) errScore[15] = 2;

    // Language score
    int finalScore = errScore[3]*10 + errScore[4]*25 + errScore[5]*10 +
            errScore[6]*20 + errScore[7]*10 + errScore[8]*10 + errScore[9]*15;

    // CSP score
    finalScore += (errScore[10]*20 + errScore[11]*15 + errScore[12]*15 +
            errScore[13]*20 + errScore[14]*20 + errScore[15]*10);

    // Normalization
    finalScore /= 4;

    // Fatality
    if (errCount[0] > 0 || errCount[1] > 0 || errCount[2] > 0)
        finalScore *= -1;

    return finalScore;
}
