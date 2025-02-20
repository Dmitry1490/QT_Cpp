#include "tcp_client.h"

tcp_client::tcp_client(QObject *parent) : QObject(parent)
{

    socket_status = 0;
    timerSocketState = new QTimer();
    connect(timerSocketState, SIGNAL(timeout()), this, SLOT(HandleStateChange()));

}

tcp_client::~tcp_client()
{

    if(socket_status != 0){
        this_socket->close();
        this_socket->deleteLater();
    }

    if(timerSocketState!= NULL){
        timerSocketState->stop();
        timerSocketState->deleteLater();
    }

    qDebug() << QString("Клиент завершил работу");

}


void tcp_client::connect_TCP_Client(QString adr, int port){

    if(!socket_status){
        this_socket = new QTcpSocket(this);


        connect(this_socket, &QTcpSocket::readyRead, this, &tcp_client::readSocket);
        connect(this_socket, &QTcpSocket::disconnected, this, &tcp_client::discardSocket);
        connect(this_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error) , this, &tcp_client::displayError);

        this_socket->connectToHost(adr, port);

        if(this_socket->waitForConnected()){
            emit PrintMes(QString::fromUtf8("Соединение с сервером установлено."));
            timerSocketState->start(1000);
            socket_status = 1;
        }
        else
        {
            //QMessageBox::critical(this,"QTCPClient", QString("Произошла следующая ошибка: %1.").arg(this_socket->errorString()));
            PrintERR(QString("Произошла следующая ошибка: %1.").arg(this_socket->errorString()));
        }
    } else {
        switch (this_socket->state()) {
            case QAbstractSocket::SocketState::ConnectedState:
                emit PrintMes(QString::fromUtf8("Соединение уже установлено."));
                break;
            case QAbstractSocket::SocketState::UnconnectedState:
            {
                this_socket->connectToHost(adr, port);

                if(this_socket->waitForConnected()){
                    emit PrintMes(QString::fromUtf8("Соединение установлено."));
                    timerSocketState->start(1000);
                }
                else
                {
                    //QMessageBox::critical(this,"QTCPClient", QString("Произошла следующая ошибка: %1.").arg(this_socket->errorString()));
                    PrintERR(QString("Произошла следующая ошибка: %1.").arg(this_socket->errorString()));
                }
                break;
            }
        }
    }

}

void tcp_client::HandleStateChange(){

    switch (this_socket->state()) {
        case QAbstractSocket::SocketState::UnconnectedState:
                emit ClientState("Сокет не подключен.");
                emit SocketState(false);
                break;
        case QAbstractSocket::SocketState::HostLookupState:
                emit ClientState("Сокет выполняет поиск имени хоста...");
                break;
        case QAbstractSocket::SocketState::ConnectingState:
                emit ClientState("Сокет начал устанавливать соединение...");
                break;
        case QAbstractSocket::SocketState::ConnectedState:
                emit ClientState("Соединение установлено.");
                emit SocketState(true);
                break;
        case QAbstractSocket::SocketState::BoundState:
                emit ClientState("Сокет привязан к адресу и порту.");
                break;
        case QAbstractSocket::SocketState::ClosingState:
                emit ClientState("Сокет вот-вот закроется (возможно, данные все еще ожидают записи)...");
                break;
        case QAbstractSocket::SocketState::ListeningState:
                emit ClientState("Только для внутреннего использования.");
                break;
    }

}

// Чтение сокета
void tcp_client::readSocket()
{
    while(this_socket->bytesAvailable()>0){
        QByteArray reseivData = this_socket->readAll();

        QString st;
        QByteArray::iterator it;
        int count = 0;

        for (it = reseivData.begin(); it != reseivData.end(); it++){
            QByteArray b(1, 0);
            b[0] = reseivData.at(count++);
            st += b.toHex() + " ";

        }

        PrintMes(("Приняты данные " + QString::number(reseivData.size()) + " байт: " + st));
    }
}

void tcp_client::discardSocket()
{
    HandleStateChange();
    PrintMes(QString::fromUtf8("Соединение разорвано."));
}

// Разъединение с сервером
void tcp_client::disconnectFromHost()
{
    if(socket_status){
        this_socket->disconnectFromHost();
    }
}

// Обработка ошибок сокета
void tcp_client::displayError(QAbstractSocket::SocketError socketError)
{

    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            //QMessageBox::information(this, "QTCPClient", "Удаленный хост закрыл соединение.");
            emit SocketERR(QAbstractSocket::RemoteHostClosedError);
        break;
        case QAbstractSocket::HostNotFoundError:
            //QMessageBox::information(this, "QTCPClient", "Адрес хоста не найден.");
            emit SocketERR(QAbstractSocket::HostNotFoundError);
        break;
        case QAbstractSocket::ConnectionRefusedError:
            //QMessageBox::information(this, "QTCPClient", "Соединение было отклонено узлом (или истекло время ожидания).");
            emit SocketERR(QAbstractSocket::ConnectionRefusedError);
        break;
        default:
            emit SocketERR(socketError);
        break;
    }
}


QTcpSocket * tcp_client::getThisSocket(){
    if(socket_status){
        return this_socket;
    } else {
        return nullptr;
    }
}



