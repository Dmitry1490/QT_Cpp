#ifndef SPORTPOWER_H
#define SPORTPOWER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>


struct settings {
    QString name;
    qint32 baudRate = 115200;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
};

class SPortPower: public QObject
{
    Q_OBJECT
public:
    explicit SPortPower(QObject *parent = 0);
    ~SPortPower();;
    QSerialPort thisPort;
    settings SettingsPort;
signals:
    void error_(QByteArray err);
    void outPort(QByteArray data); //Сигнал вывода полученных данных

    void sigCheckOutp(bool on);
    void sigCheckVI(float vp, float ip);
    void sigCheckVIMax(float vp, float ip);

public slots:
    void connectPort(); //Слот подключения порта
    void disconnectPort(); //Слот отключения порта
    void sPPcheckOutp();
    void sPPchangeOutp(bool on);
    void sPPcheckVI();
    void sPPchangeV(float vp, float ip);
    void sPPcheckVIMax();
private:
    QString readdata;
};

#endif // SPORTPOWER_H
