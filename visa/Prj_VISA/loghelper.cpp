#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <iostream>
#include <QDir>
#include "loghelper.h"

QString LogHelper::m_logFileName;
QString LogHelper::m_logFileName2;
void LogHelper::clearLogFile()
{
    // Создание пустого файла лога
    FILE *pFile=fopen(qPrintable(m_logFileName), "w+");
    if(!pFile)
    {
        fclose(pFile);
    }
    FILE *pFile2=fopen(qPrintable(m_logFileName2), "w+");
    if(!pFile)
    {
        fclose(pFile);
    }
}

void LogHelper::printToLogFile(const QString &text)
{
    // Лог-файл открывается в режиме добавления данных
    FILE *pFile=fopen(qPrintable(m_logFileName), "a+");
    if(!pFile)
    {
        printf("Log %s file not writable\n", qPrintable(m_logFileName));
        return;
    }
    // Быстрый вывод текста в файл лога
    fprintf(pFile, "%s", qPrintable(text));
    // Лог-файл закрывается
    fclose(pFile);

    FILE *pFile2=fopen(qPrintable(m_logFileName2), "a+");
    if(!pFile2)
    {
        printf("Log %s file not writable\n", qPrintable(m_logFileName2));
        return;
    }
    // Быстрый вывод текста в файл лога
    fprintf(pFile2, "%s", qPrintable(text));
    // Лог-файл закрывается
    fclose(pFile2);
}

void LogHelper::smartPrintDebugMessage(QString msg)
{
    msg.trimmed();
    // Подготовка текста для вывода
    QTime currTime = QTime::currentTime();
    QString timeText = currTime.toString("hh:mm:ss:zzz");
    msg=timeText+" "+msg;
    // Быстрый вывод в консоль
    fprintf(stderr, "%s", qPrintable(msg));
    // Вывод в файл лога
    printToLogFile(msg);

}
// Обработчик (хендлер) вызовов qDebug()
// Внутри этого обработчика нельзя использовать вызовы qDebug(), т. к. получится рекурсия
void LogHelper::myMessageOutput(QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &msgText)
{
    Q_UNUSED(context)
    switch (type) {
    case QtDebugMsg:
        // Отладочный вывод возможен только при компиляции в режиме отладки
#ifdef QT_DEBUG
        smartPrintDebugMessage(msgText + "\n");
#endif
        break;
    case QtWarningMsg:
        smartPrintDebugMessage("[WRN] "+msgText+"\n");
        QMessageBox::warning(nullptr, "Application warning message",
                             msgText,
                             QMessageBox::Ok);
        break;
    case QtCriticalMsg:
        smartPrintDebugMessage("[CRERR] "+msgText+"\n");
        QMessageBox::warning(nullptr, "Application critical message",
                             msgText,
                             QMessageBox::Ok);
        break;
    case QtFatalMsg:
        smartPrintDebugMessage("[FTERR] "+msgText+"\n");
        abort();
    case QtInfoMsg:
        smartPrintDebugMessage("[INF] "+msgText+"\n");
        break;
    }
}

void LogHelper::setDebugMessageHandler()
{
    // Задается статическое значение имени файла лога
    m_logFileName=qApp->applicationDirPath()+"/logs/logKPA.txt";

    if(!QDir(qApp->applicationDirPath()+"/logs").exists())
    {
        QDir().mkdir(qApp->applicationDirPath()+"/logs");
    }
    printf("\nSet log file to %s\n", qPrintable(m_logFileName));

    m_logFileName2=qApp->applicationDirPath()+"/logs/logKPA" +QDateTime::currentDateTime().toString("_DddMMThhmmss") + ".txt";
    printf("\nSet log file to %s\n", qPrintable(m_logFileName2));
    // Лог-файл очищается
   // clearLogFile();
    // Устанавливается Qt-обработчик консольного вывода
    qInstallMessageHandler(myMessageOutput);
}

