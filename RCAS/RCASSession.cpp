#include "RCASSession.h"
#include <QFile>
#include <QJsonArray>

RCASSession::RCASSession ()
{
    mModified = false;
}

void RCASSession::writeToJson (QJsonObject& json)
{
    json["session_id"] = mID;
    json["name"] = mAssessorName;
    json["date"] = mSessionDate;

    QJsonArray candidateArray;
    foreach (RCASCandidate cand, mCandidateList)
    {
        QJsonObject candJson;
        cand.writeToJson(candJson);

        candidateArray.append(candJson);
    }

    json["candidates"] = candidateArray;

    mModified = false;
}

void RCASSession::readFromJson (const QJsonObject &json)
{
    if (json.contains("session_id") && json["session_id"].isDouble())
        mID = json["session_id"].toInt();

    if (json.contains("name") && json["name"].isString())
        mAssessorName = json["name"].toString();

    if (json.contains("date") && json["date"].isString())
        mSessionDate = json["date"].toString();

    if (json.contains("candidates") && json["candidates"].isArray())
    {
        QJsonArray candJsonArray = json["candidates"].toArray();

        mCandidateList.clear();
        mCandidateList.reserve (candJsonArray.size());

        for (int iCandidate = 0; iCandidate < candJsonArray.size(); ++iCandidate)
        {
            QJsonObject candJson = candJsonArray[iCandidate].toObject();
            RCASCandidate cand;
            cand.readFromJson (candJson);
            mCandidateList.append(cand);
        }
    }
}

bool RCASSession::readCandidatesFromCSVFile (const QString &fileName)
{
    QFile csvFile(fileName);
    if (!csvFile.open (QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray header = csvFile.readLine ();
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
    while (!csvFile.atEnd ())
    {
        lines.append(csvFile.readLine ());
    }

    int numCandidates = lines.size();
    if (!numCandidates)
    {
        return false;
    }

    for (int i = 0; i < numCandidates; i++)
    {
        QList <QByteArray> candidateDetails = lines[i].split(',');

        RCASCandidate c;
        c.setName (QString (candidateDetails[1]));
        c.setUID (QString (candidateDetails[2]));
        c.setPhone (QString (candidateDetails[3]));
        c.setEmail (QString (candidateDetails[4]));
        c.setProcess (QString (candidateDetails[5]));
        c.setRecruiter (QString (candidateDetails[6]));
        c.setTL (QString (candidateDetails[7]));
        c.setCollege (QString (candidateDetails[8]));
        c.setSchool (QString (candidateDetails[9]));
        c.setLocation (QString (candidateDetails[10]));
        c.setModified (false);
    }

    return true;
}
