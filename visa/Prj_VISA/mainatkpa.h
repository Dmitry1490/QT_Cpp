#ifndef MAINATKPA_H
#define MAINATKPA_H

#include <QMainWindow>
#include <QThread>
#include "sportclass.h"
#include "QSerialPort"



QT_BEGIN_NAMESPACE
namespace Ui { class MainATKPA; }
QT_END_NAMESPACE

class MainATKPA : public QMainWindow
{
    Q_OBJECT

public slots:
    void errCon();
    void mcheckOutpBS(bool on);// Примем состояния напряжения на выходе
    void mcheckVIBS(float vp, float ip); // Прием значения напряжения и силы тока
    void mcheckVIMaxBS(float vp, float ip);

    void mcheckOutpUKS(bool on);// Примем состояния напряжения на выходе
    void mcheckVIUKS(float vp, float ip); // Прием значения напряжения и силы тока
    void mcheckVIMaxUKS(float vp, float ip);

private slots:

    void handleRead(QByteArray message);
    void handleReadBS(QByteArray message);
    void handleReadUKS(QByteArray message);
    void slotTimer();
    void on_bConnect_clicked(bool checked);
    void appendLogs(QString message);

    void on_comboBoxBS_currentTextChanged(const QString &arg1);

    void on_comboBoxUKS_currentTextChanged(const QString &arg1);

    void on_bBSonoff_clicked(bool checked);

    void on_bUKSonoff_clicked(bool checked);

    void on_bUUKS_clicked();

    void on_bOpenTK1_clicked();

    void on_bOpenTK2_clicked();

    void on_bOnCVM1_clicked();

    void on_bOnCVM2_clicked();

    void on_bOnOBBAL_clicked();

    void on_bOffOBBAL_2_clicked();

    void on_bSigON_clicked();

    void on_bSifNeitr_clicked();

    void on_radSec2_toggled(bool checked);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_radLPI1_toggled(bool checked);

    void on_pushButton_clicked();

    void on_radConMain_toggled(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_bTestRS_clicked();

signals:

    void writeData(QByteArray data);
    void clickConnect(QString comname);
    void clickDisconnect();

    void clickConnectBS(QString comname);
    void clickDisconnectBS();
    void sigCheckOutpBS();
    void sigChangeOutpBS(bool on);
    void sigCheckVIBS();
    void sigChangeVBS(float vp, float ip);
    void sigCheckVIMaxBS();

    void clickConnectUKS(QString comname);
    void clickDisconnectUKS();
    void sigCheckOutpUKS();
    void sigChangeOutpUKS(bool on);
    void sigCheckVIUKS();
    void sigChangeVUKS(float vp, float ip);
    void sigCheckVIMaxUKS();

public:
    MainATKPA(QWidget *parent = nullptr);
    ~MainATKPA();

private:
    Ui::MainATKPA *ui;

    void connectAll();
    void disconnectAll();
    void sendKPA(QString cmd);
    bool    flagConBS = false,
            flagConUKS = false,
            flagConKPA = false,
            flagConRS1 = false,
            flagPPS = false,
            flagStartBS  = false,
            flagStartUKS = false;
    QString portNameBS,
            portNameUKS,
            portNameKPA,
            readdata,
            bufreaddata;
    QTimer *timer;

    int fgr,sgr; //ИКС

    int const iValueBS=6; // ток защиты БС
    float const  iValueUKS=1.3; // ток защиты УКС
    QSerialPort *portRS1 = new QSerialPort;
    QSerialPort *portRS2 = new QSerialPort;
    QThread *thread_New = new QThread;//Создаем поток для работы с ком-портами
    SPortClass *PortNew = new SPortClass();//Создаем обьект по классу
};
#endif // MAINATKPA_H
