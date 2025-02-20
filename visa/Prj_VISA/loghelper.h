#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QDebug>

class LogHelper
{
public:
    static void setDebugMessageHandler();

    static void myMessageOutput(QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &msgText);

protected:

    static void smartPrintDebugMessage(QString msg);
    static void printToLogFile(const QString &text);
    static void clearLogFile();

    static QString m_logFileName;
    static QString m_logFileName2;
};

#endif // LOGHELPER_H
