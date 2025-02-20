#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QObject>
#include <QByteArray>
#include "sysinfoapi.h"
#include <QTextCodec>
#include <QMessageBox>
#include "tcp_server.h"
#include "tcp_client.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTcpServer;

enum class TypePrint
{
    AIK,
    MonitorMKO,
    KPA_BINK
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Сервер АИК
    void on_startingAIK_clicked();
    void on_stopingAIK_clicked();
    void PrintMesAIK(QString);
    void AIKState(QString);
    void on_btn_Clear_Aik_clicked();
    void SIS_CNT(int sisNPKcnt, int sisMRLcnt, int sisFCcnt);

    // Монитор МКО
    void on_startingMonitorMKO_clicked();
    void on_stopMonitorMKO_clicked();
    void PrintMesMonitorMKO(QString);
    void MonitorMKOState(QString);
    void on_btn_Clear_MKO_clicked();
    void displayErrorMonitorMKO(QAbstractSocket::SocketError socketError);


    // КПА БИНК
    void on_startingKPA_BINK_clicked();
    void on_stopKPA_BINK_clicked();
    void PrintMesKPA_BINK(QString data);
    void KPA_BINK_State(QString data);
    void on_btn_Clear_KPA_BINK_clicked();
    void displayErrorKPA_BINK(QAbstractSocket::SocketError socketError);

    // Печать
    void Print(QString data, TypePrint prnt);
    void PrintERR(QString data, TypePrint prnt);


private:
    Ui::MainWindow *ui;
    TCP_Server  *    AIK_server;
    tcp_client  *    monitorMKO;
    tcp_client  *    KPA_BINK;


};
#endif // MAINWINDOW_H
