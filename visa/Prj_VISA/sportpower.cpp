#include "sportpower.h"
#include <QDebug>
SPortPower::SPortPower(QObject *parent) :
    QObject(parent)
{

}
SPortPower::~SPortPower()
{

}
void SPortPower::connectPort(QString comname){
    if(!thisPort.isOpen()){
        thisPort.setPortName(comname);
        thisPort.setBaudRate(SettingsPort.baudRate);
        thisPort.setDataBits(SettingsPort.dataBits);
        thisPort.setParity(SettingsPort.parity);
        thisPort.setStopBits(SettingsPort.stopBits);
        thisPort.setFlowControl(SettingsPort.flowControl);
        thisPort.setReadBufferSize(64);
        if (thisPort.open(QIODevice::ReadWrite)) {
           connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
           thisPort.write("OUTP 0\n");
        }else{
           error_("Ошибка подключения");
        }
    }
}
void SPortPower::disconnectPort(){

    if(thisPort.isOpen()){
        thisPort.write("OUTP 0\n");
        thisPort.waitForBytesWritten(100);
        disconnect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        thisPort.close();
    }
}

void SPortPower::handleError(QSerialPort::SerialPortError)//
{
    error_((thisPort.portName() + ": " + thisPort.errorString()).toUtf8());
    disconnectPort();
}
void SPortPower::sPPcheckOutp()//
{
    if (thisPort.isOpen()){
        thisPort.write("OUTP?\n");
        thisPort.waitForBytesWritten(50);
        thisPort.waitForReadyRead(100);
        if(thisPort.readLine().trimmed() == "0"){
            emit sigCheckOutp(false);
        }else{
            emit sigCheckOutp(true);
        }
    }
}
void SPortPower::sPPchangeOutp(bool on)//
{
    if (thisPort.isOpen()){
        if(on){
            thisPort.write("OUTP 1\n");
            thisPort.waitForBytesWritten(50);
        }else{
            thisPort.write("OUTP 0\n");
            thisPort.waitForBytesWritten(50);
        }
    }
}
void SPortPower::sPPcheckVI()//
{
    float vP,iP;
    QString buf;
    if (thisPort.isOpen()){

        thisPort.write(":MEAS:VOLT?\n");
        thisPort.waitForBytesWritten(50);
        thisPort.waitForReadyRead(100);
        buf = thisPort.readLine();
        buf.remove("+");
        buf = buf.trimmed();
        buf.resize(buf.size()-1);
        if(buf.contains("-")){
            vP = 0;
        }
        vP = buf.toFloat();

        thisPort.write(":MEAS:CURR?\n");
        thisPort.waitForBytesWritten(50);
        thisPort.waitForReadyRead(100);
        buf = thisPort.readLine();
        buf.remove("+");
        buf = buf.trimmed();
        buf.resize(buf.size()-1);
        if(buf.contains("-")){
            iP = 0;
        }
        iP = buf.toFloat();

        emit sigCheckVI(vP,iP);
    }
}
void SPortPower::sPPchangeV(float vp, float ip)//
{
    if(thisPort.isOpen()){
        thisPort.write((QString("APPL %1,%2\n").arg(vp).arg(ip)).toUtf8());
        thisPort.waitForBytesWritten(50);
    }
}

void SPortPower::sPPcheckVIMax()
{    
    if (thisPort.isOpen()){
        float vp,ip;
        thisPort.write("APPL?\n");
        thisPort.waitForBytesWritten(5000);
        thisPort.waitForReadyRead(1000);
        readdata = thisPort.readAll();
        readdata = readdata.remove('+');
        vp = (readdata.split(',')[0]).toFloat();
        ip = (readdata.split(',')[1]).toFloat();
        emit sigCheckVIMax(vp,ip);        
    }
}

