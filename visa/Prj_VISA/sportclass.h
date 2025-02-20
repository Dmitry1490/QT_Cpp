#ifndef SPORTCLASS_H
#define SPORTCLASS_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

//Структура с настройками порта
struct Settings {
    QString name;
    qint32 baudRate = 115200;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
};
class SPortClass : public QObject
{
    Q_OBJECT
public:
    explicit SPortClass(QObject *parent = 0);
    ~SPortClass();
    QSerialPort thisPort;
    Settings SettingsPort;
signals:
    void outPort(QByteArray data); //Сигнал вывода полученных данных
    void errorConnect();
    void error_(QByteArray err);

public slots:
    void connectPort(QString comname); //Слот подключения порта
    void disconnectPort(); //Слот отключения порта
    void WriteToPort(QByteArray data); //Слот от правки данных в порт
    void handleError(QSerialPort::SerialPortError error);//

private slots:
    void ReadInPort(); //Слот чтения из порта по ReadyRead
};

#endif // SPORTCLASS_H
