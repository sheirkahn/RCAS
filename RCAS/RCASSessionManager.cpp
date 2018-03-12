#include "RCASSessionManager.h"
#include <QJsonArray>

RCASSessionManager::RCASSessionManager()
{
    mCurrentSessionID = 1;
}

const RCASSession& RCASSessionManager::session (int sessionIndex) const
{
    return mSessionList[sessionIndex];
}

RCASSession& RCASSessionManager::session (int sessionIndex)
{
    return mSessionList[sessionIndex];
}

void RCASSessionManager::addSession(const RCASSession &session)
{
    mSessionList.append(session);
    mCurrentSessionID++;
    mModified = true;
}

void RCASSessionManager::setSession (int iSession, const RCASSession &session)
{
    mSessionList[iSession] = session;
    mModified = true;
}

bool RCASSessionManager::sessionExists(const QString &name, const QString &date) const
{
    foreach (const RCASSession session, mSessionList)
    {
        if (session.assessorName() == name && session.sessionDate() == date)
        {
            return true;
        }
    }

    return false;
}

void RCASSessionManager::writeToJson (QJsonObject& json)
{
    json["currentID"] = mCurrentSessionID;

    QJsonArray sessionArrayJson;
    foreach (RCASSession session, mSessionList)
    {
        QJsonObject sessionObject;
        session.writeToJson (sessionObject);
        sessionArrayJson.append (sessionObject);
    }

    json["sessions"] = sessionArrayJson;

    mModified = false;
}

void RCASSessionManager::readFromJson (const QJsonObject &json)
{
    if (json.contains("currentID") && json["currentID"].isDouble())
        mCurrentSessionID = json["currentID"].toInt ();

    if (json.contains("sessions") && json["sessions"].isArray())
    {
        QJsonArray sessionArrayJson = json["sessions"].toArray();

        mSessionList.clear();
        mSessionList.reserve (sessionArrayJson.size());

        for (int iSession = 0; iSession < sessionArrayJson.size(); ++iSession)
        {
            QJsonObject sessionObjectJson = sessionArrayJson[iSession].toObject();
            RCASSession session;
            session.readFromJson (sessionObjectJson);
            mSessionList.append (session);
        }
    }
}
