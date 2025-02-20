#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AIK_server = new TCP_Server;
    connect(AIK_server, &TCP_Server::PrintMes, this, &MainWindow::PrintMesAIK);
    connect(AIK_server, &TCP_Server::ServerState, this, &MainWindow::AIKState);
    connect(AIK_server, &TCP_Server::SIS_CNT,this, &MainWindow::SIS_CNT);

    monitorMKO = new tcp_client;
    connect(monitorMKO, &tcp_client::PrintMes, this, &MainWindow::PrintMesMonitorMKO);
    connect(monitorMKO, &tcp_client::ClientState, this, &MainWindow::MonitorMKOState);
    connect(monitorMKO, &tcp_client::SocketERR, this, &MainWindow::displayErrorMonitorMKO);

    KPA_BINK = new tcp_client;
    connect(KPA_BINK, &tcp_client::PrintMes, this, &MainWindow::PrintMesKPA_BINK);
    connect(KPA_BINK, &tcp_client::ClientState, this, &MainWindow::KPA_BINK_State);
    connect(KPA_BINK, &tcp_client::SocketERR, this, &MainWindow::displayErrorKPA_BINK);
    connect(KPA_BINK, &tcp_client::SocketState, AIK_server, &TCP_Server::setfConBink);

    //Маска на ввод IP адреса Монитора МКО
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegExp ipRegex ("^" + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange + "$");

    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->lineEditPortMKO_2->setValidator(ipValidator);

}

MainWindow::~MainWindow()
{
    // Удаляю UI
    delete ui;
    delete AIK_server;
    delete monitorMKO;
    qDebug() << QString("Сокет Монитора МКО завершил работу.");
    delete KPA_BINK;
    qDebug() << QString("Сокет КПА_БИНК завершил работу.");

    qDebug() << QString("Все соединения завершены. Приложение безопасно закрыто.");
    Print(QString("Все соединения завершены. Приложение безопасно закрыто."), TypePrint::AIK);
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void MainWindow::Print(QString data, TypePrint prntType)
{
    try {
        QString messange = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + " >> " + data;
        QTextCharFormat fmt;
        switch (prntType)
        {
            case TypePrint::AIK:
                fmt = ui->textinfo_AIK->currentCharFormat();
                fmt.setForeground(QBrush(Qt::black));
                ui->textinfo_AIK->setCurrentCharFormat(fmt);
                ui->textinfo_AIK->textCursor().insertText(messange + '\r'); // Вывод текста в консоль
                ui->textinfo_AIK->moveCursor(QTextCursor::End);//Scroll
                break;
            case TypePrint::MonitorMKO:
                fmt = ui->textinfo_Monitor_MKO->currentCharFormat();
                fmt.setForeground(QBrush(Qt::black));
                ui->textinfo_Monitor_MKO->setCurrentCharFormat(fmt);
                ui->textinfo_Monitor_MKO->textCursor().insertText(messange + '\r'); // Вывод текста в консоль
                ui->textinfo_Monitor_MKO->moveCursor(QTextCursor::End);//Scroll      
                break;           
            case TypePrint::KPA_BINK:
                fmt = ui->textinfo_Monitor_MKO->currentCharFormat();
                fmt.setForeground(QBrush(Qt::black));
                ui->textinfo_KPA_BINK->setCurrentCharFormat(fmt);
                ui->textinfo_KPA_BINK->textCursor().insertText(messange + '\r'); // Вывод текста в консоль
                ui->textinfo_KPA_BINK->moveCursor(QTextCursor::End);//Scroll
                break;

        }
    }  catch (const std::exception &e) {
        qDebug() << "Exception:" << e.what();
    }
}

//+++++++++++++[Процедура вывода ошибки в консоль]++++++++++++++++++++++++++++++++++++++++
void MainWindow::PrintERR(QString data, TypePrint prntType)
{
    try {
        QString messange = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + " >> " + data;
        QTextCharFormat fmt;
        switch (prntType)
        {
            case TypePrint::AIK:
                fmt = ui->textinfo_AIK->currentCharFormat();
                fmt.setForeground(QBrush(Qt::red));
                ui->textinfo_AIK->setCurrentCharFormat(fmt);
                ui->textinfo_AIK->textCursor().insertText(messange + '\r'); // Вывод текста в консоль
                ui->textinfo_AIK->moveCursor(QTextCursor::End);//Scroll
                break;
            case TypePrint::MonitorMKO:
                fmt = ui->textinfo_Monitor_MKO->currentCharFormat();
                fmt.setForeground(QBrush(Qt::red));
                ui->textinfo_Monitor_MKO->setCurrentCharFormat(fmt);
                ui->textinfo_Monitor_MKO->textCursor().insertText(messange + '\r'); // Вывод текста в консоль
                ui->textinfo_Monitor_MKO->moveCursor(QTextCursor::End);//Scroll
                break;
            case TypePrint::KPA_BINK:
                fmt = ui->textinfo_KPA_BINK->currentCharFormat();
                fmt.setForeground(QBrush(Qt::black));
                ui->textinfo_KPA_BINK->setCurrentCharFormat(fmt);
                ui->textinfo_KPA_BINK->textCursor().insertText(messange + '\r'); // Вывод текста в консоль
                ui->textinfo_KPA_BINK->moveCursor(QTextCursor::End);//Scroll
                break;
        }
    }  catch (const std::exception &e) {
        qDebug() << "Exception:" << e.what();
    }

}




////-------------------------------------------------------------------------
////++++++++++++[АИК]++++++++++++++++++++++++++++++++++++++++++++++++

// Старт сервера КПА-АИК (КПА сервер АИК Клиент) Кнопка Старт
void MainWindow::on_startingAIK_clicked()
{ 
    AIK_server->startingAIK();
}

// Остатновка сервера КПА-АИК (КПА сервер АИК Клиент) Кнопка СТОП
void MainWindow::on_stopingAIK_clicked()
{
    AIK_server->stopingAIK();

}

void MainWindow::PrintMesAIK(QString data){
    Print(data, TypePrint::AIK);
}

void MainWindow::AIKState(QString data){
    ui->labelStatePortAIK->setText(data);
};

void MainWindow::on_btn_Clear_Aik_clicked()
{
    ui->textinfo_AIK->clear();
}

void MainWindow::SIS_CNT(int sisNPKcnt, int sisMRLcnt, int sisFCcnt){
    ui->label_counter_SIS_NPK_cnt->setText(QString::number(sisNPKcnt));
    ui->label_counter_SIS_MRL_cnt->setText(QString::number(sisMRLcnt));
    ui->label_counter_SIS_FK_cnt->setText(QString::number(sisFCcnt));
}

//-------------------------------------------------------------------------
//++++++++++++[МОНИТОР МКО]++++++++++++++++++++++++++++++++++++++++++++++++


// Подключение к серверу Монитора МКО (кнопка Соединить)
void MainWindow::on_startingMonitorMKO_clicked()
{
    monitorMKO->connect_TCP_Client(ui->lineEditADR_KPA_BINK->text(), ui->lineEditPortMKO->text().toInt());
}


// Разъединение с сервером Монитора МКО (кнопка Разъединить)
void MainWindow::on_stopMonitorMKO_clicked()
{
    monitorMKO->disconnectFromHost();
}

// Вывод состояния сетевого порта Монитора МКО
void MainWindow::MonitorMKOState(QString data){
    ui->labelStatePortMKO->setText(data);
};

// Вывод на консоль вводы/вывода Монитора МКО
void MainWindow::PrintMesMonitorMKO(QString data)
{
    Print(data, TypePrint::MonitorMKO);
}

// Кнопка очистить (Монитор МКО)
void MainWindow::on_btn_Clear_MKO_clicked()
{
    ui->textinfo_Monitor_MKO->clear();
}

// Вывод ошибок сокета
void MainWindow::displayErrorMonitorMKO(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            QMessageBox::information(this, "QTCPClient", "Удаленный хост монитора МКО закрыл соединение.");
            Print("Удаленный хост монитора МКО закрыл соединение.",TypePrint::MonitorMKO);
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPClient", "Адрес хоста монитора МКО не найден.");
            Print("Адрес хоста монитора МКО не найден.", TypePrint::MonitorMKO);
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPClient", "Монитор МКО отклонил соединение (или истекло время ожидания).");
            Print("Монитор МКО отклонил соединение (или истекло время ожидания).", TypePrint::MonitorMKO);
        break;
        default:
            QMessageBox::information(this, "QTCPClient", QString(socketError));
        break;
    }
}

//-------------------------------------------------------------------------
//++++++++++++[КПА БИНК]++++++++++++++++++++++++++++++++++++++++++++++++

// Подключение к серверу КПА_БИНК (кнопка Соединить)
void MainWindow::on_startingKPA_BINK_clicked()
{
    KPA_BINK->connect_TCP_Client(ui->lineEditADR_KPA_BINK->text(), ui->lineEditPortKPA_BINK->text().toInt());
}

// Разъединение с сервером КПА_БИНК (кнопка Разъединить)
void MainWindow::on_stopKPA_BINK_clicked()
{
    KPA_BINK->disconnectFromHost();


}

// Вывод состояния сетевого порта КПА_БИНК
void MainWindow::KPA_BINK_State(QString data){
    ui->labelStatePortKPA_BINK->setText(data);
};

// Вывод на консоль вводы/вывода КПА_БИНК
void MainWindow::PrintMesKPA_BINK(QString data){
    Print(data, TypePrint::KPA_BINK);
}

// Вывод ошибок сокета
void MainWindow::displayErrorKPA_BINK(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            QMessageBox::information(this, "QTCPClient", "Удаленный хост КПА БИНК закрыл соединение.");
            Print("Удаленный хост КПА БИНК закрыл соединение.",TypePrint::KPA_BINK);
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPClient", "Адрес хоста КПА БИНК не найден.");
            Print("Адрес хоста КПА БИНК не найден.", TypePrint::KPA_BINK);
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPClient", "КПА БИНК отклонил соединение (или истекло время ожидания).");
            Print("КПА БИНК отклонил соединение (или истекло время ожидания).", TypePrint::KPA_BINK);
        break;
        default:
            QMessageBox::information(this, "QTCPClient", QString(socketError));
        break;
    }
}

// Кнопка очистить (КПА_БИНК)
void MainWindow::on_btn_Clear_KPA_BINK_clicked()
{
    ui->textinfo_KPA_BINK->clear();
}




