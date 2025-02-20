#include "sportclass.h"
#include <qdebug.h>
#include <QThread>
#include <QMessageBox>
#include <QTimer>
SPortClass::SPortClass(QObject *parent) :
    QObject(parent)
{

}
SPortClass::~SPortClass()
{

}
//Подключение к порту
void SPortClass::connectPort(QString comname){
    if(!thisPort.isOpen())
    {
        thisPort.setPortName(comname);
        thisPort.setBaudRate(SettingsPort.baudRate);
        thisPort.setDataBits(SettingsPort.dataBits);
        thisPort.setParity(SettingsPort.parity);
        thisPort.setStopBits(SettingsPort.stopBits);
        thisPort.setFlowControl(SettingsPort.flowControl);
        thisPort.setReadBufferSize(64);
        if (thisPort.open(QIODevice::ReadWrite))
        {
            outPort("КПА успешно подключена");

            connect(&thisPort,SIGNAL(readyRead()),this,SLOT(ReadInPort()));
            connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
            QTimer::singleShot(1000,this, [this]()
            {

                thisPort.write("L40\n");

                QTimer::singleShot(100,this, [this]()
                {
                    thisPort.write("D1\n");
                });
                QTimer::singleShot(200,this, [this]()
                {
                    thisPort.write("C1\n");
                });
                QTimer::singleShot(300,this, [this]()
                {
                    thisPort.write("D4\n");
                });
            });

        }else
        {
            outPort(" Ошибка подключения КПА");
            errorConnect();
        }
    }
}
//Отключение порта
void SPortClass::disconnectPort(){
    if(thisPort.isOpen())
    {
        disconnect(&thisPort,SIGNAL(readyRead()),this,SLOT(ReadInPort()));
        disconnect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        thisPort.close();
        //outPort("КПА отключена");
    }
}
//Запись данных в порт
void SPortClass :: WriteToPort(QByteArray data){//Запись данных в порт
    if(thisPort.isOpen())
    {
        thisPort.write(data);
    }
}
//Чтение данных из порта
void SPortClass :: ReadInPort()
{
    QString data;
    data = thisPort.readAll().trimmed();
    outPort(data.toUtf8());
}
void SPortClass::handleError(QSerialPort::SerialPortError error)//
{
    error_(("Ошибка в КПА - " + thisPort.errorString()).toUtf8());
    disconnectPort();
    emit errorConnect();
}
