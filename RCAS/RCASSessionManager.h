#ifndef RCASSESSIONMANAGER_H
#define RCASSESSIONMANAGER_H

#include <QJsonObject>
#include <QVector>
#include "RCASSession.h"

class RCASSessionManager
{
public:
    RCASSessionManager();

    bool modified () const { return mModified; }
    int currentSessionID () const { return mCurrentSessionID; }
    int numSession () const { return mSessionList.size(); }
    const RCASSession& session (int sessionIndex ) const;
    RCASSession& session (int sessionIndex);

    bool sessionExists (const QString& name, const QString& date) const;
    void addSession (const RCASSession& session);
    void setSession (int iSession, const RCASSession& newSession);

    void writeToJson (QJsonObject &json);
    void readFromJson (const QJsonObject &json);

private:

    bool mModified;
    int mCurrentSessionID;
    QVector <RCASSession> mSessionList;

};

#endif // RCASSESSIONMANAGER_H
