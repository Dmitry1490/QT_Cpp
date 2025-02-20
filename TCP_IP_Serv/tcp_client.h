#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QObject>
#include <QtNetwork>
#include "QMessageBox"

class tcp_client : public QObject
{
    Q_OBJECT
public:
    explicit tcp_client(QObject *parent = nullptr);
    ~tcp_client();

signals:
    void PrintMes(QString);
    void PrintERR(QString);
    void ClientState(QString);
    void SocketERR(QAbstractSocket::SocketError socketError);
    void SocketState(bool);

public slots:
    void connect_TCP_Client(QString adr, int port);
    void HandleStateChange();
    void readSocket();
    void discardSocket();
    void disconnectFromHost();
    void displayError(QAbstractSocket::SocketError socketError);
    QTcpSocket * getThisSocket();


private:
    bool socket_status;
    QTcpSocket  * this_socket;
    QTimer      * timerSocketState;

};

#endif // TCP_CLIENT_H
