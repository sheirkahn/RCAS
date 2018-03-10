#include "RCASAssessmentError.h"

QString RCASAssessmentError::textString () const
{
    QString errStr;
    switch (mType)
    {
    case FATAL_FIRST_LANGUAGE_INFLUENCE: errStr = QString ("First language influence"); break;
    case FATAL_CLARITY_OF_SPEECH: errStr = QString ("Clarity of speech"); break;
    case FATAL_LOSS_OF_WORDS: errStr = QString ("Loss of words"); break;
    case LANG_ROS: errStr = QString ("Rate of speech"); break;
    case LANG_GRAMMAR: errStr = QString ("Grammar"); break;
    case LANG_WORDS_VOCABULARY: errStr = QString ("Words/vocabulary"); break;
    case LANG_PRONUNCIATION: errStr = QString ("Pronunciation"); break;
    case LANG_COMPREHENSION: errStr = QString ("Comprehension"); break;
    case LANG_FILLERS_VERBALIZATION: errStr = QString ("Fillers/verbalization"); break;
    case LANG_VOCALIZATION: errStr = QString ("Vocalization"); break;
    case CSP_CALL_FLOW_PROTOCOL_COMPLIANCE: errStr = QString ("Call flow protocol compliance"); break;
    case CSP_PERSONALIZATION: errStr = QString ("Personalization"); break;
    case CSP_LISTENING_SKILLS: errStr = QString ("Listening skills"); break;
    case CSP_ACKNOWLEDGEMENT_EMOTIONS_EMPATHY: errStr = QString ("Acknowledgement - emotions empathy"); break;
    case CSP_OWNERSHIP_CALL_CONTROL: errStr = QString ("Ownership - call control"); break;
    case CSP_PROBING_ENQUIRING: errStr = QString ("Probing/enquiring"); break;
    case CSP_QUALITY_OF_SOLUTION: errStr = QString ("Quality of solution"); break;
    case CSP_EXPECTATION_SETTING: errStr = QString ("Expectation setting"); break;
    }

    return errStr;
}

void RCASAssessmentError::write (QJsonObject &json) const
{
    json["time"] = mTime;
    json["type"] = mType;
}

void RCASAssessmentError::read (const QJsonObject &json)
{
    if (json.contains("time") && json["time"].isDouble())
        mTime = (qint64) json["time"].toInt();

    if (json.contains("type") && json["type"].isDouble())
        mType = (RCASErrorType) json["type"].toInt();
}
