#ifndef RCASASSESSMENTERROR_H
#define RCASASSESSMENTERROR_H

#include <QJsonObject>

enum RCASErrorType {
    RCAS_NO_ERROR = 0,
    FATAL_FIRST_LANGUAGE_INFLUENCE = 1,
    FATAL_CLARITY_OF_SPEECH = 2,
    FATAL_LOSS_OF_WORDS = 3,
    LANG_ROS = 4,
    LANG_GRAMMAR = 5,
    LANG_WORDS_VOCABULARY = 6,
    LANG_PRONUNCIATION = 7,
    LANG_COMPREHENSION = 8,
    LANG_FILLERS_VERBALIZATION = 9,
    LANG_VOCALIZATION = 10,
    CSP_CALL_FLOW_PROTOCOL_COMPLIANCE = 11,
    CSP_PERSONALIZATION = 12,
    CSP_LISTENING_SKILLS = 13,
    CSP_ACKNOWLEDGEMENT_EMOTIONS_EMPATHY = 14,
    CSP_OWNERSHIP_CALL_CONTROL = 15,
    CSP_PROBING_ENQUIRING = 16,
    CSP_QUALITY_OF_SOLUTION = 17,
    CSP_EXPECTATION_SETTING = 18
};

class RCASAssessmentError
{
public:

    RCASAssessmentError (qint64 errTime = 0, RCASErrorType errType = RCAS_NO_ERROR)
    {
        mTime = errTime;
        mType = errType;
    }

    void setTime (qint64 t) { mTime = t; }
    void setType (RCASErrorType newType) { mType = newType; }

    qint64 time () const { return mTime; }
    RCASErrorType type () const { return mType; }

    QString textString () const;

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json);

private:

    qint64          mTime;
    RCASErrorType   mType;
};

#endif // RCASASSESSMENTERROR_H
