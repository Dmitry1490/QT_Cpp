//Программное обеспечение для проведения автономных испытаний КПА
//Разработчик: Подвигин В.А.
//Версия: 1.3(x64)


#include "mainatkpa.h"
#include "ui_mainatkpa.h"
#include "wdmtmkv2.cpp"
#include "Bal_Cs.cpp"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <iostream>
#include "visa.h"
#include <stdio.h>
#include <string.h>



static ViSession defaultRM;
static ViSession instr;
static ViUInt32 retCount;
static ViUInt32 writeCount;
static ViStatus status;
static char buffer[100];
static char stringinput[512];


QRegExp rx("\\d{,3},\\d{,3}");
MainATKPA::MainATKPA(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainATKPA)
{
    ui->setupUi(this);
    qDebug() << "\n\n      Старт программы " << QDateTime::currentDateTime().toString("dd.MM.yy HH:mm:ss") << "\n";
    //Поток КПА
    PortNew->moveToThread(thread_New);//помешаем класс  в поток
    PortNew->thisPort.moveToThread(thread_New);//Помещаем сам порт в поток
    thread_New->start();

    connect(this,SIGNAL(clickConnect(QString)),PortNew,SLOT(connectPort(QString)));
    connect(this,SIGNAL(clickDisconnect()),PortNew,SLOT(disconnectPort()));
    connect(PortNew,SIGNAL(outPort(QByteArray)),this,SLOT(handleRead(QByteArray)));
    connect(this,SIGNAL(writeData(QByteArray)),PortNew,SLOT(WriteToPort(QByteArray)));
    connect(PortNew,SIGNAL(errorConnect()),this,SLOT(errCon()));
    connect(PortNew, SIGNAL(error_(QByteArray)), this, SLOT(handleRead(QByteArray)));//Лог ошибок



    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(slotTimer()));
    timer->start(1000);

    for (int i=0;i<32;++i)
    {
        ui->comboBoxBS->addItem(QString::number(i,'f',2));
    }
    for (int i=0;i<53;++i)
    {
        ui->comboBoxUKS->addItem(QString::number(i,'f',2));
    }
    ui->bConnect->click();
//=============== Подлкючение МКО ==================
    TmkOpen();
    int res = tmkconfig(0);
    bcdefbase(0);
    //поиск свободного tmk
    for(int i=1;i<=tmkgetmaxn();++i){
        if((res != 0)){
            res = tmkconfig(i);
        }
    }


    // Connection info

    strcpy (stringinput,"*IDN?\n");
    status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
    if (status < VI_SUCCESS)
    {
        printf ("Error writing to the device.\n");
    }

    /*
            * Now we will attempt to read back a response from the device to
            * the identification query that was sent.  We will use the viRead
            * function to acquire the data.  We will try to read back 100 bytes.
            * This function will stop reading if it finds the termination character
            * before it reads 100 bytes.
            * After the data has been read the response is displayed.
            */

    //ViStatus _VI_FUNC  viRead          (ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);

    status = viRead (instr, (ViBuf)buffer, 100, &retCount);
    if (status < VI_SUCCESS)
    {
        printf ("Error reading a response from the device.\n");
    }
    else
    {
        printf ("\nData read: %*s\n", retCount, buffer);
    }

}

MainATKPA::~MainATKPA()
{
    disconnectAll();
    qDebug() << "\n\n      Завершение программы " << QDateTime::currentDateTime().toString("dd.MM.yy HH:mm:ss") << "\n";
    delete ui;
}


void MainATKPA::on_bConnect_clicked(bool checked)
{
    if(checked)
    {
        ui->bConnect->setText("Отключиться");
        connectAll();        
    }else
    {
        ui->bConnect->setText("Подключиться");
        disconnectAll();
    }
}

void MainATKPA::connectAll(){
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if((info.hasProductIdentifier() ? QByteArray::number(info.productIdentifier(),10) : QByteArray()) == "29987"){
            //Подключение КПА
            portNameKPA = info.portName();
            flagConKPA = true;
        }
    }
    flagConBS = true;
    status=viOpenDefaultRM (&defaultRM);
    if (status < VI_SUCCESS)
    {
        flagConBS=false;
    }
    status = viOpen (defaultRM,"USB0::0x0957::0x0907::MY54008497::0::INSTR", VI_NULL, VI_NULL, &instr);
    if (status < VI_SUCCESS)
    {
        flagConBS=false;
    }




    if(flagConKPA && flagConBS ||true){
        ui->bConnect->setText("Отключиться");

        status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, 5000);
        status = viSetAttribute (instr, VI_ATTR_ASRL_BAUD, 4800);
        status = viSetAttribute (instr, VI_ATTR_ASRL_DATA_BITS, 8);
        status = viSetAttribute (instr, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE);
        status = viSetAttribute (instr, VI_ATTR_ASRL_STOP_BITS, VI_ASRL_STOP_ONE);
        status = viSetAttribute (instr, VI_ATTR_TERMCHAR_EN, VI_TRUE);
        status = viSetAttribute (instr, VI_ATTR_TERMCHAR, 0xA);

        strcpy (stringinput,"OUTP OFF,(@1:2)\n");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

        strcpy (stringinput,"VOLT 6,(@1)");
            status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

        strcpy (stringinput,"VOLT 1.3,(@2)");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

        //Подключение КПА
        clickConnect(portNameKPA);
        appendLogs("================ Устройство успешно подключено ================");

        ui->groupBox->setEnabled(true);
        ui->groupBox_2->setEnabled(true);
        ui->groupBox_3->setEnabled(true);
        ui->groupBox_4->setEnabled(true);
        ui->groupBox_5->setEnabled(true);
        ui->groupBox_8->setEnabled(true);
        ui->groupBox_9->setEnabled(true);
        ui->groupBox_10->setEnabled(true);
        ui->groupBox_11->setEnabled(true);

        ui->comboBoxBS->setCurrentText("27.00");
        ui->comboBoxUKS->setCurrentText("27.00");
        bcdefbus(BUS_1);

        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(0);
        ui->radConMain->setChecked(true);
        ui->radSec1->setChecked(true);




    }else{
        if(!flagConBS){
            appendLogs("Ошибка при подключении питания");
        }
        if(!flagConKPA){
            appendLogs("Ошибка при подключении УКС");
        }
        status = viClose (instr);
        status = viClose (defaultRM);
        flagConBS = false;
        flagConKPA = false;
        ui->bConnect->setChecked(false);
        ui->bConnect->setText("Подключиться");
    }
}

void MainATKPA::disconnectAll(){
    // Дисконнект КПА
    flagConKPA = false;
    ui->lPPS->setStyleSheet("QLabel {"
                            "background-color:  rgb(240, 240, 240);"
                            "border: 1px solid #959c9b;"
                            "border-radius: 10px;"
                            "font: 150 10pt\"MS Shell Dlg 2\";"
                            "color:rgb(0); }");
    ui->lCVM1->setStyleSheet("QLabel {"
                             "background-color:  rgb(240, 240, 240);"
                             "border: 1px solid #959c9b;"
                             "border-radius: 10px;"
                             "font: 150 14pt\"MS Shell Dlg 2\";"
                             "color:rgb(0); }");
    ui->lCVM2->setStyleSheet("QLabel {"
                             "background-color:  rgb(240, 240, 240);"
                             "border: 1px solid #959c9b;"
                             "border-radius: 10px;"
                             "font: 150 14pt\"MS Shell Dlg 2\";"
                             "color:rgb(0); }");
    ui->lobog->setStyleSheet("QLabel {"
                             "background-color:  rgb(240, 240, 240);"
                             "border: 1px solid #959c9b;"
                             "border-radius: 10px;"
                             "font: 150 14pt\"MS Shell Dlg 2\";"
                             "color:rgb(0); }");
    ui->lTestRS->setStyleSheet("QLabel {"
                               "background-color:  rgb(240, 240, 240);"
                               "border: 1px solid #959c9b;"
                               "border-radius: 10px;"
                               "font: 150 14pt\"MS Shell Dlg 2\";"
                               "color:rgb(0); }");
    ui->lTestRS->setText("");

    if(PortNew->thisPort.isOpen()){
        clickDisconnect();
    }

    appendLogs("==================== Устройство отключено =====================");
    bufreaddata = "-";
    if(ui->bConnect->isChecked()){
        ui->bConnect->setChecked(false);
        ui->bConnect->setText("Подключиться");
    }

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(false);
    ui->groupBox_4->setEnabled(false);
    ui->groupBox_5->setEnabled(false);
    ui->groupBox_8->setEnabled(false);
    ui->groupBox_9->setEnabled(false);
    ui->groupBox_10->setEnabled(false);
    ui->groupBox_11->setEnabled(false);

    ui->bBSonoff->setText("ВКЛ БС");
    ui->bUKSonoff->setText("ВКЛ УКС");

    status = viClose (instr);
    status = viClose (defaultRM);
}

void MainATKPA::on_comboBoxBS_currentTextChanged(const QString &arg1)
{
   /* sigChangeVBS(arg1.toFloat(),iValueBS);
    if(flagStartBS == true){
        sigCheckVIMaxBS();
    }

    flagStartBS = true;*/

    strcpy (stringinput,"VOLT " + arg1.toUtf8() + ",(@1)");
    status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
}

void MainATKPA::on_comboBoxUKS_currentTextChanged(const QString &arg1)
{

    strcpy (stringinput,"VOLT " + arg1.toUtf8() + ",(@2)");

    status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
}

void MainATKPA::on_bBSonoff_clicked(bool checked)
{
    if(checked)
    {
        strcpy (stringinput,"OUTP ON,(@1)");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
        ui->bBSonoff->setChecked(true);
        ui->bBSonoff->setText("ВЫКЛ БС");
        appendLogs("(ИП БС) Подача напряжения на БС включена");


    } else
    {
        strcpy (stringinput,"OUTP OFF,(@1)\n");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
        ui->bBSonoff->setChecked(false);
        ui->bBSonoff->setText("ВКЛ БС");
        appendLogs("(ИП БС) Подача напряжения на БС выключена");
    }
}

void MainATKPA::on_bUKSonoff_clicked(bool checked)
{
    if(checked)
    {
        strcpy (stringinput,"OUTP ON,(@2)\n");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
        ui->bUKSonoff->setChecked(true);
        ui->bUKSonoff->setText("ВЫКЛ УКС");
        appendLogs("(ИП УКС) Подача напряжения на УКС включена");
    } else
    {
        strcpy (stringinput,"OUTP OFF,(@2)\n");
        status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
        ui->bUKSonoff->setChecked(false);
        ui->bUKSonoff->setText("ВКЛ УКС");
        appendLogs("(ИП УКС) Подача напряжения на УКС выключена");
    }
}

// Примем состояния напряжения на выходе БС
void MainATKPA::mcheckOutpBS(bool on)
{
    if(!on){
        ui->bBSonoff->setChecked(false);
        ui->bBSonoff->setText("ВКЛ БС");
        appendLogs("(ИП БС) Подача напряжения на БС выключена");
    } else {
        ui->bBSonoff->setChecked(true);
        ui->bBSonoff->setText("ВЫКЛ БС");
        appendLogs("(ИП БС) Подача напряжения на БС включена");
    }
}

// Прием значения напряжения и силы тока
void MainATKPA::mcheckVIBS(float vp, float ip)
{
    ui->label_BS1->setText("Напряжение БС: " + QString::number(vp,'f',2));
    ui->label_BS2->setText("Ток БС: " + QString::number(ip,'f',2));
    ui->label_BS3->setText("Мощность БС: " + QString::number(vp*ip,'f',2));
}

void MainATKPA::mcheckVIMaxBS(float vp, float ip)
{
    ui->comboBoxBS->setEditText(QString::number(vp,'f',2));
    appendLogs("(ИП БС) Значение установленного напряжения БС: " + QString::number(vp,'f',2) + " В");

}

void MainATKPA::mcheckVIMaxUKS(float vp, float ip)
{
    ui->comboBoxUKS->setEditText(QString::number(vp,'f',2));
    appendLogs("(ИП УКС) Значение установленного напряжения УКС: " + QString::number(vp,'f',2) + " В");
}

// Примем состояния напряжения на выходе БС
void MainATKPA::mcheckOutpUKS(bool on)
{
    if(!on){
        ui->bUKSonoff->setChecked(false);
        ui->bUKSonoff->setText("ВКЛ УКС");
        appendLogs("(ИП УКС) Подача напряжения на УКС выключена");
    } else {
        ui->bUKSonoff->setChecked(true);
        ui->bUKSonoff->setText("ВЫКЛ УКС");
        appendLogs("(ИП УКС) Подача напряжения на УКС включена");
    }
}

// Прием значения напряжения и силы тока
void MainATKPA::mcheckVIUKS(float vp, float ip)
{
    ui->label_UKS1->setText("Напряжение УКС: " + QString::number(vp,'f',2));
    ui->label_UKS2->setText("Ток УКС: " + QString::number(ip,'f',2));
    ui->label_UKS3->setText("Мощность УКС: " + QString::number(vp*ip,'f',2));
}



void MainATKPA::handleRead(QByteArray message)
{
    readdata = QString::fromUtf8(message);
    if(readdata.contains(rx) & (bufreaddata != readdata)) //Проверка сообщения через регуряное выражение
    {
        bufreaddata = readdata;
        fgr = readdata.split(',')[0].toInt();
        sgr = readdata.split(',')[1].toInt();

        if(sgr & 2){
            ui->lCVM2->setStyleSheet("QLabel {"
                                     "background-color: #18d6ad;;"
                                     "border: 1px solid black;"
                                     "border-radius: 10px;"
                                     "font: 150 14pt\"MS Shell Dlg 2\";"
                                     "color:rgb(0); }");
        }else{
            ui->lCVM2->setStyleSheet("QLabel {"
                                     "background-color:  rgb(240, 240, 240);"
                                     "border: 1px solid #959c9b;"
                                     "border-radius: 10px;"
                                     "font: 150 14pt\"MS Shell Dlg 2\";"
                                     "color:rgb(0); }");
        }
        if(sgr & 4){
            ui->lCVM1->setStyleSheet("QLabel {"
                                     "background-color: #18d6ad;;"
                                     "border: 1px solid black;"
                                     "border-radius: 10px;"
                                     "font: 150 14pt\"MS Shell Dlg 2\";"
                                     "color:rgb(0); }");
        }else{
            ui->lCVM1->setStyleSheet("QLabel {"
                                     "background-color:  rgb(240, 240, 240);"
                                     "border: 1px solid #959c9b;"
                                     "border-radius: 10px;"
                                     "font: 150 14pt\"MS Shell Dlg 2\";"
                                     "color:rgb(0); }");
        }
        if(sgr & 8){
            ui->lobog->setStyleSheet("QLabel {"
                                     "background-color: #18d6ad;;"
                                     "border: 1px solid black;"
                                     "border-radius: 10px;"
                                     "font: 150 14pt\"MS Shell Dlg 2\";"
                                     "color:rgb(0); }");
        }else{
            ui->lobog->setStyleSheet("QLabel {"
                                     "background-color:  rgb(240, 240, 240);"
                                     "border: 1px solid #959c9b;"
                                     "border-radius: 10px;"
                                     "font: 150 14pt\"MS Shell Dlg 2\";"
                                     "color:rgb(0); }");
        }

        appendLogs("(УКС) Принято состояние индикаторов: " + readdata);
    }else if(readdata == "PPS")
    {
        if(flagPPS == true){
            ui->lPPS->setStyleSheet("QLabel {"
                                    "background-color: #18d6ad;;"
                                    "border: 1px solid black;"
                                    "border-radius: 10px;"
                                    "font: 150 10pt\"MS Shell Dlg 2\";"
                                    "color:rgb(0); }");
            flagPPS = false;
        }else{
            ui->lPPS->setStyleSheet("QLabel {"
                                    "background-color:  rgb(240, 240, 240);"
                                    "border: 1px solid #959c9b;"
                                    "border-radius: 10px;"
                                    "font: 150 10pt\"MS Shell Dlg 2\";"
                                    "color:rgb(0); }");
            flagPPS = true;
        }
    }else {
        if (bufreaddata != readdata)
            appendLogs("(УКС) Принято сообщение: " + readdata);
    }
}

void MainATKPA::handleReadBS(QByteArray message)
{
    appendLogs("(ИП БС) Ошибка: " + QString::fromUtf8(message));
    disconnectAll();
}
void MainATKPA::handleReadUKS(QByteArray message)
{
    appendLogs("(ИП УКС) Ошибка: " + QString::fromUtf8(message));
    disconnectAll();
}

void MainATKPA::errCon(){
   // disconnectAll();
    QMessageBox::information(this, "Ошибка", "Ошибка подключения к порту.");
}

void MainATKPA::slotTimer()
{
    QString bufvalue;
    //Питание
       if(flagConBS)
        {

           strcpy (stringinput,"MEAS:VOLT? (@1)");
           status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
           memset(buffer,0,100);
           status = viRead (instr, (ViBuf)buffer, 100, &retCount);
           ui->label_BS1->setText("Напряжение БС: " + QString(buffer));

           strcpy (stringinput,"MEAS:CURR? (@1) ");
           status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
           memset(buffer,0,100);
           status = viRead (instr, (ViBuf)buffer, 100, &retCount);
           ui->label_BS2->setText("Ток БС: " + QString(buffer));

           /*strcpy (stringinput,"MEAS:POW? (@1)");
           status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
           memset(buffer,0,100);
           status = viRead (instr, (ViBuf)buffer, 100, &retCount);
           ui->label_BS3->setText("Мощность БС: " + QString(buffer));*/


           strcpy (stringinput,"MEAS:VOLT? (@2)");
           status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
           memset(buffer,0,100);
           status = viRead (instr, (ViBuf)buffer, 100, &retCount);
           ui->label_UKS1->setText("Напряжение УКС: " + QString(buffer));

           strcpy (stringinput,"MEAS:CURR? (@2) ");
           status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
           memset(buffer,0,100);
           status = viRead (instr, (ViBuf)buffer, 100, &retCount);
           ui->label_UKS2->setText("Ток УКС: " + QString(buffer));

         /*  strcpy (stringinput,"MEAS:POW? (@2)");
           status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
           memset(buffer,0,100);
           status = viRead (instr, (ViBuf)buffer, 100, &retCount);
           ui->label_UKS3->setText("Мощность УКС: " + QString(buffer));*/


       }else {
           ui->label_BS1->setText("Напряжение БС: ");
           ui->label_BS2->setText("Ток БС: ");
           ui->label_BS3->setText("Мощность БС: ");

           ui->label_UKS1->setText("Напряжение УКС: ");
           ui->label_UKS2->setText("Ток УКС: ");
           ui->label_UKS3->setText("Мощность УКС: ");
       }
}

void MainATKPA::sendKPA(QString cmd){
    if(PortNew->thisPort.isOpen()){
        writeData(cmd.toUtf8());
        appendLogs("(УКС) Отправлена команда: " + cmd.remove(cmd.size()-1,2));
    }
}

void MainATKPA::on_bUUKS_clicked()
{
    sendKPA("A4\n");
}

void MainATKPA::on_bOpenTK1_clicked()
{
    sendKPA("B1\n");
}

void MainATKPA::on_bOpenTK2_clicked()
{
    sendKPA("B3\n");
}

void MainATKPA::on_bOnCVM1_clicked()
{
    sendKPA("F" + QString::number(ui->spinBoxTime ->value()) + "\n");
}

void MainATKPA::on_bOnCVM2_clicked()
{
    sendKPA("G" + QString::number(ui->spinBoxTime ->value()) + "\n");
}

void MainATKPA::on_bOnOBBAL_clicked()
{
    sendKPA("H" + QString::number(ui->spinBoxTime ->value()) + "\n");
}

void MainATKPA::on_bOffOBBAL_2_clicked()
{
    sendKPA("I" + QString::number(ui->spinBoxTime ->value()) + "\n");
}

void MainATKPA::on_bSigON_clicked()
{
    sendKPA("J" + QString::number(ui->spinBoxTime2 ->value()) + "\n");
}

void MainATKPA::on_bSifNeitr_clicked()
{
    sendKPA("K" + QString::number(ui->spinBoxTime2 ->value()) + "\n");
}

void MainATKPA::on_radSec2_toggled(bool checked)
{
    if(checked){
        sendKPA("D2\n");
    }else{
        sendKPA("D1\n");
    }
}

void MainATKPA::on_comboBox_2_currentIndexChanged(int index)
{
    if(index==0){
        sendKPA("C1\n");
    }else if (index==1){
        sendKPA("C2\n");
    }else if(index==2){
        sendKPA("C3\n");
    }
}

void MainATKPA::on_comboBox_currentIndexChanged(int index)
{
    if(index==0){
        sendKPA("D4\n");
    }else if (index==1){
        sendKPA("D3\n");
    }else if(index==2){
        sendKPA("D5\n");
    }
}

void MainATKPA::on_radLPI1_toggled(bool checked)
{
    if (checked){
        appendLogs("(МКО) Выбор ЛПИ 1");
        bcdefbus(BUS_1);
    }else{
        appendLogs("(МКО) Выбор ЛПИ 2");
        bcdefbus(BUS_2);
    }
}

void MainATKPA::on_pushButton_clicked()
{
    try {
        USHORT vBuf[2], comWrd;
        vBuf[0] = 0;
        *(vBuf+1) = 0x0DE6;
        comWrd = CW(13,RT_RECEIVE,1,2);
        CSWord(vBuf,2,false);
        bcputw(0,comWrd);
        bcputblk(1, vBuf, 2);
        bcstart(0,DATA_BC_RT);
        appendLogs("(МКО) Команда отправлена");
    } catch (const std::exception &e) {
        qDebug() << "Exception:" << e.what();
    }
}

void MainATKPA::appendLogs(QString message){
    ui->textLogs->append(message);
    qDebug() << message;
}

void MainATKPA::on_radConMain_toggled(bool checked)
{
    if(checked){
        sendKPA("L" + QString::number(ui->spinBoxTime ->value()) + "\n");
    }else{
        sendKPA("M" + QString::number(ui->spinBoxTime ->value()) + "\n");
    }
}

void MainATKPA::on_pushButton_2_clicked(bool checked)
{
    if(checked){
        sendKPA("A1\n");

    }else{
        sendKPA("A0\n");
    }
}

void MainATKPA::on_bTestRS_clicked()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if(((info.hasProductIdentifier() ? QByteArray::number(info.productIdentifier(),10) : QByteArray()) == "24577" & (flagConRS1 == false))){
            //Подключение RS1
            portRS1->setPortName(info.portName());
            flagConRS1 = true;
        }
        if(((info.hasProductIdentifier() ? QByteArray::number(info.productIdentifier(),10) : QByteArray()) == "24577") & (flagConRS1 == true) & (info.portName() != portRS1->portName())){
            //Подключение RS2
            portRS2->setPortName(info.portName());
        }
    }
    portRS1->setBaudRate(115200);
    portRS2->setBaudRate(115200);
    portRS1->open(QIODevice::ReadWrite);
    portRS2->open(QIODevice::ReadWrite);
    if(portRS1->isOpen() & portRS2->isOpen())
    {
        portRS1->write("test");
        portRS1->waitForBytesWritten(100);
        portRS2->waitForReadyRead(100);
        if(portRS2->readAll() == "test")
        {
            portRS2->write("test");
            portRS2->waitForBytesWritten(100);
            portRS1->waitForReadyRead(100);
            if(portRS1->readAll() == "test"){
                ui->lTestRS->setText("Норма");
                ui->lTestRS->setStyleSheet("QLabel {"
                                           "background-color: #18d6ad;;"
                                           "border: 1px solid black;"
                                           "border-radius: 10px;"
                                           "font: 150 14pt\"MS Shell Dlg 2\";"
                                           "color:rgb(0); }");
            }else{
                ui->lTestRS->setText("Не норма");
                ui->lTestRS->setStyleSheet("QLabel {"
                                           "background-color: #a11010;"
                                           "border: 1px solid black;"
                                           "border-radius: 10px;"
                                           "font: 150 14pt\"MS Shell Dlg 2\";"
                                           "color: #FFFFFF; }");

            }
        }else{
            ui->lTestRS->setText("Не норма");
            ui->lTestRS->setStyleSheet("QLabel {"
                                       "background-color: #a11010;"
                                       "border: 1px solid black;"
                                       "border-radius: 10px;"
                                       "font: 150 14pt\"MS Shell Dlg 2\";"
                                       "color: #FFFFFF; }");
        }
    }else{
        ui->lTestRS->setText("Не норма");
        ui->lTestRS->setStyleSheet("QLabel {"
                                   "background-color: #a11010;"
                                   "border: 1px solid black;"
                                   "border-radius: 10px;"
                                   "font: 150 14pt\"MS Shell Dlg 2\";"
                                   "color: #FFFFFF; }");
    }
    flagConRS1 = false;
    if(portRS1->isOpen())
    {
        portRS1->close();
    }
    if(portRS2->isOpen())
    {
        portRS2->close();
    }
}

