#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QtNetwork>
#include "Bal12_Aik.h"



const QByteArray S_BAL_CMD[CMD_QTY] =
{
   S_BAL_ATM_START,     S_BAL_ATM_STOP,      S_BAL_ATM_RESET,
   S_BAL_TEST_KPA,      S_BAL_TEST_EXCH,
   S_BAL_BINK_CON,      S_BAL_BINK_DISCON,
   S_BAL_CVM1_CON,      S_BAL_CMD_RSVD_9,
   S_BAL_CVM2_CON,      S_BAL_CMD_RSVD_11,   S_BAL_CVM_DISCON,
   S_BAL_FILE_NPK,      S_BAL_FILE_MRL,
   S_BAL_ARX_PROT,      S_BAL_NEW_SESN,      S_BAL_END_SESN,
   S_BAL_CHECK_RS,      S_BAL_CMD_RSVD_19,
   S_BAL_MKO_CON,       S_BAL_MKO_DISCON,
   S_BAL_MKO_START,     S_BAL_MKO_STOP,
   S_BAL_CMD_RSVD_24,   S_BAL_CMD_RSVD_25,   S_BAL_CMD_RSVD_26,
   S_BAL_CMD_RSVD_27,   S_BAL_CMD_RSVD_28,   S_BAL_CMD_RSVD_29,
   S_BAL_CMD_RSVD_30,   S_BAL_CMD_RSVD_31
};

const QByteArray S_BAL_CMDWP[CMDWP_QTY] =
{
   S_BAL_BTS2,          S_BAL_CHECK,         S_BAL_GEN_SIG
};

class TCP_Server : public QObject
{
    Q_OBJECT
public:
    explicit TCP_Server(QObject *parent = nullptr);
    ~TCP_Server();

signals:
    void PrintMes(QString);
    void PrintERR(QString);
    void ServerState(QString);
    void SIS_CNT(int sisNPKcnt, int sisMRLcnt, int sisFCcnt);

public slots:

    void startingAIK();
    void stopingAIK();
    void slotNewConnection();
    void emergencyStopSocket(QAbstractSocket::SocketError socketError);
    void slotReadClient();
    //void slotClientDisconnected();
    void ExecuteAIKCmd(tInfPacketCmd pIPC, WORD pResult);
    void HandleStateChange();
    void Init_ATM();
    void setfConBink(bool fConBink);
    void btnTestRS();
    void btnConBink();
    void btnDisconBink();

private:
    bool server_status;
    QMap<int,QTcpSocket *> SClients;
    QTcpServer  *    thisTcpServer;
    QTcpSocket  *    clientSocket;
    QTimer      *    timerSocketState;
    tPacket          tp;
    tInfPacketCmd    pIPCmd;
    tPacketRep       Rep;
    QTimer      *    atmTimer;
    //KCMD             *pK;
    WORD             atm[BAL_ATM_PAR_QTY], atm_old[BAL_ATM_PAR_QTY];
    bool             fConBink;
    bool             fATM, fChkConCVM, fStopServBal;
    bool             fConMko;
    UINT             IBPA_N;
    SYSTEMTIME       st;
    QFile       *    fp;

    // tsNetBink /////////////////////////////////////////////////////////////
    int               sisNPKcnt, sisMRLcnt, sisFCcnt;

     // tsNetMko //////////////////////////////////////////////////////////////
    int               sisNPKq, sisMRLq, sisFCq, isisMRLq, pckR2q;
};

#endif // TCP_SERVER_H
