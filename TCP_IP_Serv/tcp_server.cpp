#include "tcp_server.h"

TCP_Server::TCP_Server(QObject *parent) : QObject(parent)
{
    thisTcpServer = nullptr;
    clientSocket = nullptr;
    timerSocketState = new QTimer();
    server_status = 0;
    fConBink = 0;
    connect(timerSocketState, SIGNAL(timeout()), this, SLOT(HandleStateChange()));

}

TCP_Server::~TCP_Server()
{

    if(server_status == 1){
        foreach(int i,SClients.keys()){
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
        thisTcpServer->close();
        qDebug() << QString::fromUtf8("Сервер остановлен!");
        server_status=0;
    }

    if(timerSocketState->isActive()){
        timerSocketState->stop();
    }
    delete timerSocketState;

    if(thisTcpServer != nullptr){
        delete thisTcpServer;
    }

    server_status=0;

    qDebug() << QString("Сервер успешно завершил работу");

}

void TCP_Server::startingAIK(){

    if(server_status != 1){

        thisTcpServer = new QTcpServer(this);
        connect(thisTcpServer, &QTcpServer::newConnection, this, &TCP_Server::slotNewConnection);
        connect(thisTcpServer, &QTcpServer::acceptError, this, &TCP_Server::emergencyStopSocket);

        if (!thisTcpServer->listen(QHostAddress::Any, 4000) && server_status==0) {
            qWarning() <<  QObject::tr("Невозможно запустить сервер: %1.").arg(thisTcpServer->errorString());
            emit PrintMes(QString("Невозможно запустить сервер: %1. ").arg(thisTcpServer->errorString()));
        } else {
            server_status = 1;
            qDebug() << thisTcpServer->isListening() << "TCPSocket listen on port.";
            emit PrintMes("Сервер КПА-АИК запущен.");
            qDebug() << QString::fromUtf8("Сервер КПА-АИК запущен.");
        }
    } else {
        emit PrintMes("Невозможно запустить сервер, так как сервер запущен.");
        qWarning() << QString::fromUtf8("Невозможно запустить сервер, так как сервер запущен.");
    }

}

void TCP_Server::stopingAIK(){

    if(server_status == 1){
        foreach(int i,SClients.keys()){
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
        thisTcpServer->close();
        emit PrintMes(QString::fromUtf8("Сервер остановлен!"));
        qDebug() << QString::fromUtf8("Сервер остановлен!");
        server_status=0;
    }
}


void TCP_Server::slotNewConnection()
{
    if(server_status == 1){

        clientSocket = thisTcpServer->nextPendingConnection();
        int idusersocs = clientSocket->socketDescriptor();
        SClients[idusersocs] = clientSocket;

        connect(SClients[idusersocs],&QTcpSocket::readyRead,this, &TCP_Server::slotReadClient);
        connect(SClients[idusersocs], &QTcpSocket::disconnected, SClients[idusersocs], [=]()
            {
                SClients[idusersocs]->close();
                SClients.remove(idusersocs);
                emit PrintMes(QString::fromUtf8("Клиент отключился!"));
                qDebug() << QString::fromUtf8("Клиент отключился!");
            });

        QString address = QHostAddress(clientSocket->peerAddress().toIPv4Address()).toString();

        if(address != "127.0.0.1" && address != "192.168.1.90"){
            qDebug()<< QString("Установлено соединение с хостом IP: " + address);
            emit PrintMes(QString("Установлено соединение с хостом IP: " + address));
            timerSocketState->start(1000);
        } else {
            qDebug()<< QString("Установлено соединение с АИК: " + address);
            emit PrintMes(QString("Установлено соединение с АИК: " + address));
            timerSocketState->start(1000);
        }

    }

}

// Обработчик ошибок на сервере КПА-АИК
void TCP_Server::emergencyStopSocket(QAbstractSocket::SocketError socketError){
    qDebug() << QString("Ошибка на сервере. Error:" + QString::number(socketError) + "." + "Соединение с АИК завершено преждевременно.");
    emit PrintERR(QString("Ошибка на сервере. Error:" + QString::number(socketError) + "." + "Соединение с АИК завершено преждевременно."));
}

void TCP_Server::HandleStateChange(){
    //QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QAbstractSocket::SocketState socketState = clientSocket->state();

    switch (socketState) {
        case QAbstractSocket::SocketState::UnconnectedState:
                emit ServerState("Сокет не подключен.");
                break;
        case QAbstractSocket::SocketState::HostLookupState:
                emit ServerState("Сокет выполняет поиск имени хоста...");
                break;
        case QAbstractSocket::SocketState::ConnectingState:
                emit ServerState("Сокет начал устанавливать соединение...");
                break;
        case QAbstractSocket::SocketState::ConnectedState:
                emit ServerState("Соединение установлено.");
                break;
        case QAbstractSocket::SocketState::BoundState:
                emit ServerState("Сокет привязан к адресу и порту.");
                break;
        case QAbstractSocket::SocketState::ClosingState:
                emit ServerState("Сокет вот-вот закроется (возможно, данные все еще ожидают записи)...");
                break;
        case QAbstractSocket::SocketState::ListeningState:
                emit ServerState("Только для внутреннего использования.");
                break;
    }

}

void TCP_Server::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    while(clientSocket->bytesAvailable()>0){

        QString st;
        QByteArray reseivData = clientSocket->readAll();
        QByteArray::iterator it;
        int count = 0;

        for (it = reseivData.begin(); it != reseivData.end(); it++){
            QByteArray b(1, 0);
            b[0] = reseivData.at(count++);
            st += b.toHex() + " ";

        }

        qDebug() << "Приняты данные " + QString::number(reseivData.size()) + " байт: " + st;
        emit PrintMes("Приняты данные " + QString::number(reseivData.size()) + " байт: " + st);

        memset(&tp,         0, sizeof(tp));
        memcpy(&tp, reseivData.data(), sizeof(tp));


        memset(&pIPCmd,     0, sizeof(pIPCmd));
        memcpy(&pIPCmd, tp.bufInf, sizeof(pIPCmd));

        memset(&Rep,         0, sizeof(Rep));

        if( tp.HEAD.wLen == (unsigned short) (reseivData.size() - 2)){
            QString _infoAIK_mes = "HEAD : LEN = " + QString::number(tp.HEAD.wLen)
                                 + ", Time = " + QString("%1").arg(tp.HEAD.fileTime.dwHighDateTime, 4, 16, QLatin1Char( '0' )).toUpper()
                                             + QString("%1").arg(tp.HEAD.fileTime.dwLowDateTime, 4, 16, QLatin1Char( '0' )).toUpper()
                                 + ", PacketType = " + QString("%1").arg(tp.wPacketType, 4, 16, QLatin1Char( '0' )).toUpper();

            emit PrintMes("Приняты данные " + _infoAIK_mes);

            if(tp.wPacketType == PACKET_TYPE_CMD){
                _infoAIK_mes = "Принята КУ : CmdType = " + QString("%1").arg(pIPCmd.wCmdType, 4, 16, QLatin1Char( '0' )).toUpper()
                             + ", CmdCode = " + QString("%1").arg(pIPCmd.dwCmdCode, 4, 16, QLatin1Char( '0' )).toUpper()
                             + ", ParCount = " + QString("%1").arg(pIPCmd.wParCount, 4, 16, QLatin1Char( '0' )).toUpper();

                emit PrintMes(_infoAIK_mes);
                if(pIPCmd.wCmdType == CMD_TYPE)
                    ExecuteAIKCmd(pIPCmd, Rep.REP.wResult);
                else
                    Rep.REP.wResult = ERR_AIK_CMD_TYPE;
            }
            else Rep.REP.wResult = ERR_AIK_IP_TYPE;

            GetSystemTimeAsFileTime(&Rep.HEAD.fileTime);
            Rep.wPacketType = PACKET_TYPE_REPLY;
            Rep.REP.wPacketType = PACKET_TYPE_CMD;
            Rep.REP.wParCount = 0;
            Rep.HEAD.wLen = sizeof (Rep.HEAD) - sizeof (Rep.HEAD.wLen)
                    + sizeof (Rep.wPacketType)
                    + sizeof(Rep.REP.wPacketType)
                    + sizeof (Rep.REP.wResult)
                    + sizeof (Rep.REP.wParCount);

            unsigned short s = Rep.HEAD.wLen + 2;
            QByteArray transmitData((char*) &Rep, s);

            QString st;
            int count = 0;
            QByteArray::iterator it;
            for (it = transmitData.begin(); it != transmitData.end(); it++){
                QByteArray b(1, 0);
                b[0] = transmitData.at(count++);
                st += b.toHex() + " ";

            }

            emit PrintMes("Отправлены данные:" + st);

            if(clientSocket->write(transmitData)){

                _infoAIK_mes = "Выданные данные: " + QString::number(Rep.HEAD.wLen + 2) + " байт";
                emit PrintMes(_infoAIK_mes);

                _infoAIK_mes = "Выдана квитанция: Len = " + QString::number(Rep.HEAD.wLen)
                        + " Result = " + QString("%1").arg((int) Rep.REP.wResult, 4, 16, QLatin1Char( '0' )).toUpper();

                emit PrintMes(_infoAIK_mes);

                if(Rep.REP.wResult == 0){
                    emit PrintMes("Выдана положительная квитанция.");
                } else {
                    emit PrintMes("Выдана отрицательная квитанция, код = "
                                         + QString("%1").arg(Rep.REP.wResult, 4, 16, QLatin1Char( '0' )).toUpper() + ")");
                }
            }
        }
    }

}

void TCP_Server::setfConBink(bool fConBink){
    this->fConBink = fConBink;
}


// Обработка команд АИК->КПА
void TCP_Server::ExecuteAIKCmd(tInfPacketCmd pIPC, WORD pResult){

//    FILE *fbp;
//    tParam *pPars[5] = { 0 };
//    tParamF *pParsF;
//    tParamWS *pParsWS[8] = { 0 };
    QByteArray  msg;
    static QString BalPostFile, str1, str3;

    if ( pIPC.dwCmdCode )
    {
        if ( pIPC.dwCmdCode <= CMD_QTY )
            msg = S_BAL_CMD[pIPC.dwCmdCode - 1];
        else
            if ( pIPC.dwCmdCode >= CMDWP_BAL_BTS2 && pIPC.dwCmdCode <= CMDWP_BAL_GEN_SIG )
                msg = S_BAL_CMDWP[pIPC.dwCmdCode - CMDWP_BAL_BTS2];
            else
                msg = S_BAL_UNKNOWN;
       }
       else msg = S_BAL_UNKNOWN;

       QTextCodec* codec1251 = QTextCodec::codecForName("Windows-1251");
       QString msgUnicode=codec1251->toUnicode(msg);

       emit PrintMes("Принята КУ : " + msgUnicode);
       pResult = ERR_AIK_NO;
       // Реализация команд
       switch ( pIPC.dwCmdCode )
       {
          // БАЛ_АТМ_СТАРТ Включить выдачу АТМ
          case CMD_BAL_ATM_START:
             Init_ATM();
             fATM = true;
             break;

          // БАЛ_АТМ_СТОП Отключить выдачу АТМ
          case CMD_BAL_ATM_STOP:
             atmTimer->stop();
             fATM = false;
             break;

          // БАЛ_АТМ_СБРОС Обнулить АТМ параметры (кроме БАЛ_СОЕД_БИНК, БАЛ_СОЕД_ЦВМ, БАЛ_СОЕД_МКО)
          case CMD_BAL_ATM_RESET:
             sisNPKcnt = sisMRLcnt = sisFCcnt = 0;
             emit SIS_CNT(sisNPKcnt, sisMRLcnt, sisFCcnt);
             sisNPKq = sisMRLq = sisFCq = isisMRLq = pckR2q = 0;
//             lbSisNPKq->Caption = IntToStr(sisNPKq);
//             lbSisMRLq->Caption = IntToStr(sisMRLq);
//             lbSisFCq->Caption  = IntToStr(sisFCq);
//             lbInSisMRLq->Caption = IntToStr(isisMRLq);

             memset(&atm, 0, sizeof(atm));

             if ( ci.fActive )
                {
                    fChkConCVM = true;
                    emit btnTestRS();
                }

             if ( fConBink ) atm[INDX_BAL_CON_BINK] = 1;
             if ( fConMko ) atm[INDX_BAL_CON_MKO] = 1;

             memset(&atm_old, 0xFEFE, sizeof(atm));
             break;

          // БАЛ_ТЕСТ_КПА Тест КПА
          case CMD_BAL_TEST_KPA:
             atm[INDX_BAL_KPA_TEST] = BAL_VAL_KPA_TEST;
             if ( IBPA_N == 6 )
             {
                    Send_KCMD( KCMD_KPA_ON );
                    Sleep( DELAY_KCMD );
                    Send_KCMD( KCMD_BS_ON );
                    Sleep( DELAY_KCMD );
                    Send_KCMD( KCMD_27BS_ON );
                    Sleep( DELAY_KCMD );
                    Send_KCMD( KCMD_27UK_ON );
                    Sleep( DELAY_KCMD );
                    Send_KCMD( KCMD_GET_IKS );
             }
             break;

          // БАЛ_ТЕСТ_ОБМ Проверить доступ к папке обмена
          case CMD_BAL_TEST_EXCH:
             GetLocalTime(&st);
             BalPostFile = QString("test_%1_%2_%3_%4%5%6.bin").
                     arg(st.wDay, 2, 10, QLatin1Char('0')).
                     arg(st.wMonth, 2, 10, QLatin1Char('0')).
                     arg(st.wYear, 4, 10, QLatin1Char('0')).
                     arg(st.wHour, 2, 10, QLatin1Char('0')).
                     arg(st.wMinute, 2, 10, QLatin1Char('0')).
                     arg(st.wSecond, 2, 10, QLatin1Char('0'));


             fp = new QFile(BalPostFile);
             //fp = fopen((sAikShareDir + "\\" + BalPostFile).c_str(), "wb");
             if (fp->open(QIODevice::ReadOnly | QIODevice::Text) )
                {
                    fp->close();
                    fp->remove();
                }
             else
                {
                    pResult = ERR_AIK_DIR_ACS;
                    fp->remove();;
                }
             break;

         // БАЛ_БИНК Установить соединение с КПА_БИНК
         case CMD_BAL_BINK_CON:
          if ( !fConBink )
          {
             emit btnConBink();

          }
          break;

         // БАЛ_БИНК_ОТКЛ Прервать соединение КПА_БИНК
         case CMD_BAL_BINK_DISCON:
          if ( fConBink )
          {
             emit btnDisconBink();
          }
          break;


         // БАЛ_ЦВМ1 Подключить КПА к ЦВМ1. (Подача питания на техн. интерф. ЦВМ1)
         case CMD_BAL_CVM1_CON:
            if ( !ci.fActive )
            {
                cbPort->ItemIndex = cbPort->Items->IndexOf(sCOM_CVM_1);
                cbPortChange(NULL);
            }

            if ( ci.fActive )
            {
                switch ( IBPA_N )
                {
                    case 6:
                    if ( fConKpa )
                    {
                        Send_KCMD( KCMD_5V01_ON );
                        Sleep( DELAY_KCMD );
                        Send_KCMD( KCMD_GET_IKS );
                    }
                    else pResult = ERR_AIK_KPA_WN_NC;
                    break;

                }
            }
            else pResult = ERR_AIK_CVM_NA;
            break;

         // БАЛ_ЦВМ1 Подключить КПА к ЦВМ1. (Подача питания на техн. интерф. ЦВМ1)
         case CMD_BAL_CVM2_CON:
            if ( !ci.fActive )
            {
                cbPort->ItemIndex = cbPort->Items->IndexOf(sCOM_CVM_1);
                cbPortChange(NULL);
            }

            if ( ci.fActive )
            {
                switch ( IBPA_N )
                {
                   case 6:
                   if ( fConKpa )
                   {
                       Send_KCMD( KCMD_5V01_ON );
                       Sleep( DELAY_KCMD );
                       Send_KCMD( KCMD_GET_IKS );
                   }
                   else pResult = ERR_AIK_KPA_WN_NC;
                   break;

               }
            }
            else pResult = ERR_AIK_CVM_NA;
            break;


         // БАЛ_ЦВМ_ОТКЛ Отключить КПА от ЦВМ (откл. питание техн. интерфейса)
         case CMD_BAL_CVM_DISCON:
            atm[INDX_BAL_CON_CVM] = 0;
            cbPort->ItemIndex = 0;
            cbPortChange(NULL);
            if ( ci.fActive ) *pResult = ERR_AIK_CVM_NA;
            switch ( IBPA_N )
                {
                case 6:
                if ( fConKpa )
                    {
                        Send_KCMD( KCMD_5VT_OFF );
                        Sleep( DELAY_KCMD );
                        Send_KCMD( KCMD_GET_IKS );
                    }
                else pResult = ERR_AIK_KPA_WN_NC;
                break;
             case 7:
                if ( hUD )
                {
                   ret = usb_relay_device_close_all_relay_channel( hUD );
                   if ( ret != SUCCESS )
                   {
                      str.printf("������� usb_relay_device_close_all_relay_channel() ������� ��� ������ = %d!", ret);
                      WriteToLog(S_ERR_T_RL + str, clRed);
                   }
                   ret = usb_relay_device_get_status( hUD, &rStatus );
                   if ( ret != SUCCESS )
                   {
                      str.printf("������� usb_relay_device_get_status() ������� ��� ������ = %d!", ret);
                      WriteToLog(S_ERR_T_RL + str, clRed);
                   }

                   if ( rStatus & 1 << (r_27V_T1 - 1) ) pU27_T1_LED->Color = clLime;
                   else                                 pU27_T1_LED->Color = clGreen;

                   if ( rStatus & 1 << (r_27V_T2 - 1) ) pU27_T2_LED->Color = clLime;
                   else                                 pU27_T2_LED->Color = clGreen;

                   if ( rStatus & 3 ) *pResult = ERR_AIK_RN_NC;
                }
                break;
          }
          break;

         case CMD_BAL_CHECK_RS:
            if ( ci.fActive )
            {
                fChkConCVM = true;
                btnTestRS->Click();
            }
            else *pResult = ERR_AIK_CVM_NA;
            break;

         // БАЛ_Ф_НПК Выполнить проверку СИС НПК ( СИС ФК),
         // принятых от сервера монитора МКО или из КПА БИНК
         //
         case CMD_BAL_FILE_NPK:

            indent = 2;
            si_len = LEN_SIS_B;
            StrCopy(etlFile, HomeEDir);
            str3 = "";
            switch ( BalCheckMode )
            {
             //-=-=-= ���������� �������� � ��� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
             case 0x000F:
                if ( sisFCq == 3 )
                {
                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_FC);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CHK_RES);
                   if ( CheckSisFCSimple(str1.c_str(), str3.c_str(), &sfch, &ecp, wFCTimeDelta) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_FC;
                   else
                      atm[INDX_BAL_SIS_REP] = ecp;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_FC;
                break;
             case 0x0001:
                if ( sisNPKq == 1 )
                {
                   StrCat(etlFile, sAikEtl_NPK_One.c_str());

                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_AIK);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_N;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_N;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_N;
                break;
             case 0x0002:
             case 0x0100:
                if ( sisNPKq == sisNPK_Qty_Seq )
                {
                   StrCat(etlFile, sAikEtl_NPK_Seq.c_str());

                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_AIK);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_N;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_N;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_N;
                break;
             // �������� ���������������� ���� ( ������� ������ )
             case 0x0071:
             case 0x0072:
                if ( sisNPKq )
                {
                   q = ((int)iGs.Tau * 1000) / (int)iGs.T;
                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_AIK);
                   j = CheckSis_EMI(str1.c_str(), sisNPKq);
                   if ( j >= q )                                      // patch
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_SN;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SN + (j << 16);
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SN;
                break;
             //-=-=-= �������� �������� � ��� � ��� ���� -=-=-=-=-=-=-=-=-=-=-=-
             case 0x100F:
                if ( sisFCcnt == 3 )
                {
                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_FC);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CHK_RES);
                   if ( CheckSisFCSimple(str1.c_str(), str3.c_str(), &sfch, &ecp, wFCTimeDelta) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_FC;
                   else
                      atm[INDX_BAL_SIS_REP] = ecp;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_FC;
                break;
             case 0x1001:
             case 0x1800:
                if ( sisNPKcnt == 1 )
                {
                   StrCat(etlFile, sAikEtl_NPK_One.c_str());

                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_LAN);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_N;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_N;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_N;
                break;
             case 0x1002:
             case 0x1A00:
                if ( sisNPKcnt == sisNPK_Qty_Seq )
                {
                   StrCat(etlFile, sAikEtl_NPK_Seq.c_str());

                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_LAN);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_N;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_N;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_N;
                break;
             // �������� ���������������� ���� ( ������� ������ )
             case 0x1071:
             case 0x1072:
                if ( sisNPKcnt )
                {
                   q = ((int)iGs.Tau * 1000) / (int)iGs.T;
                   str1 = StrPas(HomeDir) + sNum + StrPas(S_SIS_LAN);
                   j = CheckSis_EMI(str1.c_str(), sisNPKcnt);
                   if ( j >= q )                                      // patch
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_SN;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SN + (j << 16);
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SN;
                break;
          }
          if ( str3 != "" ) FileToLog(S_LOG_T_AIK, S_ERR_T_AIK, str3.c_str());
          break;


       case CMD_BAL_FILE_MRL:
          indent = 0;
          si_len = LEN_SISM_B;
          StrCopy(etlFile, HomeEDir);
          str3 = "";
          switch ( BalCheckMode )
          {
             //-=-=-= ���������� �������� � ��� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
             case 0x0001:
                if ( sisMRLq == 1 )
                {
                   StrCat(etlFile, sAikEtl_MRL_One.c_str());

                   str1 = StrPas(HomeMDir) + sNumM + StrPas(S_SISM_AIK);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_M;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_M;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_M;
                break;
             case 0x0002:
             case 0x0100:
                if ( sisMRLq == sisMRL_Qty_Seq )
                {
                   StrCat(etlFile, sAikEtl_MRL_Seq.c_str());

                   str1 = StrPas(HomeMDir) + sNumM + StrPas(S_SISM_AIK);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_M;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_M;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_M;
                break;
             // �������� ���������������� ���� ( ������� ������ )
             case 0x0071:
             case 0x0072:
                if ( sisMRLq )
                {
                   q = ((int)iGs.Tau * 1000) / (int)iGs.T;
                   str1 = StrPas(HomeMDir) + sNumM + StrPas(S_SISM_AIK);
                   j = CheckSisM_EMI(str1.c_str(), sisMRLq);
                   if ( j >= q )                                      // patch
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_SM;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SM + (j << 16);
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SM;
                break;
             //-=-=-= �������� �������� � ��� � ��� ���� -=-=-=-=-=-=-=-=-=-=-=-
             case 0x1001:
             case 0x1800:
                if ( sisMRLcnt == 1 )
                {
                   StrCat(etlFile, sAikEtl_MRL_One.c_str());

                   str1 = StrPas(HomeMDir) + sNumM + StrPas(S_SISM_LAN);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_M;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_M;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_M;
                break;
             case 0x1002:
             case 0x1A00:
                if ( sisMRLcnt == sisMRL_Qty_Seq )
                {
                   StrCat(etlFile, sAikEtl_MRL_Seq.c_str());

                   str1 = StrPas(HomeMDir) + sNumM + StrPas(S_SISM_LAN);
                   str3 = StrPas(HomeDir) + "\\" + StrPas(S_CMP_RES);
                   if ( CompareSis(str1.c_str(), etlFile, str3.c_str(), indent, si_len, true) )
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_M;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_CMP_M;
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_M;
                break;
             // �������� ���������������� ���� ( ������� ������ )
             case 0x1071:
             case 0x1072:
                if ( sisMRLcnt )
                {
                   q = ((int)iGs.Tau * 1000) / (int)iGs.T;
                   str1 = StrPas(HomeMDir) + sNumM + StrPas(S_SISM_LAN);
                   j = CheckSisM_EMI(str1.c_str(), sisMRLcnt);
                   if ( j >= q )                                      // patch
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_NORM_SM;
                   else
                      atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SM + (j << 16);
                }
                else
                   atm[INDX_BAL_SIS_REP] = BAL_SIS_REP_RX_SM;
                break;
          }
          if ( str3 != "" ) FileToLog(S_LOG_T_AIK, S_ERR_T_AIK, str3.c_str());
          break;




       case CMD_BAL_MKO_CON:
          if ( !fConMko )
          {
             btnConMko->Click();
 //            if ( !fConMko ) *pResult = ERR_AIK_MKO_NA;
          }
          break;
       case CMD_BAL_MKO_DISCON:
          if ( fConMko )
          {
             btnDisconMko->Click();
 //            if ( fConMko ) *pResult = ERR_AIK_MKO_NA;
          }
          break;
       case CMD_BAL_MKO_START:
          if ( fConMko )
             btnMkoReqBAL_K2->Click();
          else
             *pResult = ERR_AIK_MKO_NC;
          break;
       case CMD_BAL_MKO_STOP:
          if ( fConMko )
             btnMkoTapAll->Click();
          else
             *pResult = ERR_AIK_MKO_NC;
          break;
       //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
       // �� � �����������
       case CMDWP_BAL_BTS2:
          if ( pIPC->wParCount != PAR_QTY_BTS2 )
             *pResult = ERR_AIK_PAR_QTY;
          else
          {
             for ( j = 0; j < PAR_QTY_BTS2; ++j )
             {
                pPars[j] = (tParam *)&(pIPC->bufInf[j * 4]);
                if ( pPars[j]->wParType != PAR_TYPE_WORD )
                   *pResult = ERR_AIK_PAR_TYPE;
             }
 /*
             msg.printf("1 - %d,%d | 2 - %d,%d | 3 - %d,%d | 4 - %d,%d | 5 - %d,%d",
                pPars[0]->wParType, pPars[0]->wParValue,
                pPars[1]->wParType, pPars[1]->wParValue,
                pPars[2]->wParType, pPars[2]->wParValue,
                pPars[3]->wParType, pPars[3]->wParValue,
                pPars[4]->wParType, pPars[4]->wParValue);
             WriteToLog(S_LOG_T_AIK + "� ����������� [���,����]: " + msg, clWindowText);
 */
             msg.printf("%02d, %04d, %02d:%02d:%02d",
                pPars[0]->wParValue, pPars[1]->wParValue,
                pPars[2]->wParValue, pPars[3]->wParValue, pPars[4]->wParValue);
             WriteToLog(S_LOG_T_AIK + "� ����������� : " + msg, clWindowText);
 /*
             if ( *pResult == 0 )
             {
                bt.Sec    = pPars[4]->wParValue & SEC_MASK;
                bt.Min    = pPars[3]->wParValue & MIN_MASK;
                bt.Hour   = pPars[2]->wParValue & HOUR_MASK;
                bt.Day4   = pPars[1]->wParValue & DAYS_MASK;
                bt.Year64 = pPars[0]->wParValue & YEAR_MASK;
                WriteToLog(S_LOG_T_BTS
                   + "��������� ���������� �������� ���������� ��� ��� �� ���",
                   clWindowText);
                WriteToLog(S_LOG_T_AIK + "4-� �����: " + IntToStr(bt.Year64)
                   + ", �����: " + IntToStr(bt.Day4) + ", ���: " + IntToStr(bt.Hour)
                   + ", ���: " + IntToStr(bt.Min) + ", ���: " + IntToStr(bt.Sec),
                   clWindowText);
             }
 */
          }
          break;
       case CMDWP_BAL_CHECK:
          if ( pIPC->wParCount != PAR_QTY_CHECK )
             *pResult = ERR_AIK_PAR_QTY;
          else
          {
             pPars[0] = (tParam *)(pIPC->bufInf);
             if ( pPars[0]->wParType != PAR_TYPE_WORD )
                *pResult = ERR_AIK_PAR_TYPE;
             msg.printf("%04X", pPars[0]->wParValue);
             WriteToLog(S_LOG_T_AIK + "� ���������� : " + msg, clWindowText);
             if ( *pResult == 0 )
             {
                sisNPKcnt = sisMRLcnt = sisFCcnt = 0;
                sisNPKq = sisMRLq = sisFCq = isisMRLq = 0;
                atm[INDX_BAL_CHK_MODE] = BalCheckMode = pPars[0]->wParValue;
                atm[INDX_BAL_SIS_REP]  = 0;
                atm[INDX_BAL_CNT_NPK] = 0;
                atm[INDX_BAL_CNT_MRL] = 0;
                atm[INDX_BAL_CNT_FC]  = 0;
                atm[INDX_BAL_C_M_NPK] = 0;
                atm[INDX_BAL_C_M_MRL] = 0;
                atm[INDX_BAL_C_M_FC]  = 0;
                atm[INDX_BAL_C_M_IN_MRL] = 0;
                lbSisNPKcnt->Caption = IntToStr(sisNPKcnt);
                lbSisMRLcnt->Caption = IntToStr(sisMRLcnt);
                lbSisFCcnt->Caption  = IntToStr(sisFCcnt);
                lbSisNPKq->Caption = IntToStr(sisNPKq);
                lbSisMRLq->Caption = IntToStr(sisMRLq);
                lbSisFCq->Caption  = IntToStr(sisFCq);
                lbInSisMRLq->Caption = IntToStr(isisMRLq);
                switch ( BalCheckMode )
                {
                   // �������� ��� ��, 3 ������, ���-�2 --> ��� ����
                   case 0x100F:
 //                   sisFCcnt = 0;        // ������� ��� �� �� ��� �� ��� ����
                   // �������� ��� ��, 3 ������, ���-�2 --> ����
                   case 0x000F:
                      // ���������� ������� ���� ���
                      sfch.type      = TYPE_FC;
                      sfch.ms_qty    = wFCMeasQty;
                      sfch.Nka       = AikNka;

                      day4           = bs.fs.day4;
                      sfch.time_hour = bs.fs.hour;
                      sfch.time_min  = bs.fs.min;
                      sfch.time_sec  = bs.fs.sec + wFCDuration;
                      if ( sfch.time_sec > MAX_SEC )
                      {
                         sfch.time_sec -= (MAX_SEC + 1);
                         ++sfch.time_min;
                         if ( sfch.time_min > MAX_MIN )
                         {
                            sfch.time_min = 0;
                            ++sfch.time_hour;
                            if ( sfch.time_hour > MAX_HOUR )
                            {
                               sfch.time_hour = 0;
                               ++day4;
                               if ( day4 > MAX_DAY4 ) day4 = 0;
                            }
                         }
                      }
                      sfch.time_day = day4 & DAY_MASK;
                      break;
                   // ������ ��� ���, 1 �����, ���-�2 --> ��� ����
                   case 0x1001:
                   // ������ ��� ���, 1 �����, ���-�2 --> ���� ����
                   case 0x1010:
 /*
                      if ( BalCheckMode == 0x1001 )
                         sisNPKcnt = 0;    // ������� ��� ��� �� ��� �� ��� ����
                      if ( BalCheckMode == 0x1010 )
                         sisMRLcnt = 0;    // ������� ��� ��� �� ��� �� ��� ����
 */
                   // ������ ��� ���, 1 �����, ���-�2 --> ����
                   case 0x0001:
                   // ������ ��� ���, 1 �����, ���-�2 --> ����
                   case 0x0010:
                      if ( ci.fActive )
                      {
                         StrCopy(SisMFile, HomeEDir);
                         StrCat(SisMFile, sAikSrc_MRL_One.c_str());
                         len = GetFileLength(SisMFile);
                         simPQ = len / LEN_SISM_B;
                         RsTxSisM();
                         // ������� ���� ��� ��� � ���� ��� ��� �� ��� �� ��� ����
                      }
                      else
                         *pResult = ERR_AIK_CVM_NC;
                      break;
                   // ������ ��� ��� � ��� ���, 30 ������ ���� (150 ������� ��� ���)
                   // ���� --> ���-�2 --> ����
                   case 0x0100:
                      break;
                   //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                   // ������ ��� ��� � ��� ���, ������� �������, ���-�2 --> ����
                   case 0x0002:
                   // ������ ��� ���, ������� 32 ������, ���-�2 --> ��� ����
                   case 0x1002:
                   // ������ ��� ���, ������� 10 �������, ���-�2 --> ���� ����
                   case 0x1020:
 /*
                      if ( BalCheckMode == 0x1002 )
                         sisNPKcnt = 0;
                      if ( BalCheckMode == 0x1020 )
                         sisMRLcnt = 0;
 */
                      if ( ci.fActive )
                      {
                         StrCopy(SisMFile, HomeEDir);
                         StrCat(SisMFile, sAikSrc_MRL_Seq.c_str());
                         len = GetFileLength(SisMFile);
                         simPQ = len / LEN_SISM_B;
                         RsTxSisM();
                         // ������� ������� ��� ��� � ������� ��� ��� �� ��� �� ��� ����
                      }
                      else
                         *pResult = ERR_AIK_CVM_NC;
                      break;
                   // �������� �������� � ������������� ��� (���� ���)
                   // ���� ���� --> ���-�2 --> ���, ���� ����
                   case 0x1800:
 //                     sisNPKcnt = sisMRLcnt = 0;
                      if ( fConBink )
                      {
                         StrCopy(netSisMFile, HomeEDir);
                         StrCat(netSisMFile, sAikSrc_MRL_One.c_str());
                         netTxSisM();
                         // ������� ���� ��� ��� � ���� ��� �� ��� �� ��� ����
                      }
                      else
                         *pResult = ERR_AIK_KPABINK_NC;
                      break;
                   // �������� �������� � ������������� ��� (������� ���)
                   // ���� ���� --> ���-�2 --> ���, ���� ����
                   case 0x1A00:
 //                     sisNPKcnt = sisMRLcnt = 0;
                      if ( fConBink )
                      {
                         StrCopy(netSisMFile, HomeEDir);
                         StrCat(netSisMFile, sAikSrc_MRL_Seq.c_str());
                         netTxSisM();
                         // ������� ������� ��� ��� � ������� ��� �� ��� �� ��� ����
                      }
                      else
                         *pResult = ERR_AIK_KPABINK_NC;
                      break;
                   //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                   // �������� ���������������� ���� ������� ( 115, 125, 135 ) ���
                   case 0x0071:
                   case 0x1071:
                   // �������� ���������������� ���� ������� ( 125, 135, 145 ) ���
                   case 0x0072:
                   case 0x1072:
                      break;
                }
                atm[INDX_BAL_SIS_REP] = 0;
             }
          }
          break;
       case CMDWP_BAL_GEN_SIG:
          if ( pIPC->wParCount != PAR_QTY_GEN_SIG )
             *pResult = ERR_AIK_PAR_QTY;
          else
          {
             pPars[0] = (tParam  *)&(pIPC->bufInf[0]);    // +0
             if ( pPars[0]->wParType != PAR_TYPE_WORD )
                *pResult = ERR_AIK_PAR_TYPE;
             pParsF   = (tParamF *)&(pIPC->bufInf[4]);    // +4
             if ( pParsF->wParType != PAR_TYPE_REAL )
                *pResult = ERR_AIK_PAR_TYPE;
             for ( j = 1; j < 5; ++j )                    // +10 ( 4 + 6 )
             {
                pPars[j] = (tParam *)&(pIPC->bufInf[10+(j-1)*4]);
                if ( pPars[j]->wParType != PAR_TYPE_WORD )
                   *pResult = ERR_AIK_PAR_TYPE;
             }
             for ( j = 0; j < 8; ++j )                    // +26 ( 10 + 4 * 4 )
             {
                pParsWS[j] = (tParamWS *)&(pIPC->bufInf[26+j*4]);
                if ( pParsWS[j]->wParType != PAR_TYPE_WORD_SIGN )
                   *pResult = ERR_AIK_PAR_TYPE;
             }
             // ������ �������� ���������� � ���������
             iGs.Freq    = pPars[0]->wParValue;
             iGs.Power   = pParsF->fParValue;
             iGs.Tau     = pPars[1]->wParValue;
             iGs.T       = pPars[2]->wParValue;
             iGs.Q       = pPars[3]->wParValue;
             iGs.Ch_Mask = pPars[4]->wParValue;
             for ( j = 0; j < 8; ++j )
                iGs.Tone_Ofs[j] = pParsWS[j]->wsParValue;
             WriteToLog(S_LOG_T_AIK + "� ����������� :", clWindowText);
             msg.printf("    F = %d ���, P = %+2.1f dBm, tg = %d �, Tg = %d ��, Q = %d",
                (int)iGs.Freq, iGs.Power, (int)iGs.Tau, (int)iGs.T, (int)iGs.Q);
             WriteToLog(S_LOG_T_AIK + msg, clTeal);
             msg.printf("    M = 0x%02X,  Ofs = [ %d, %d, %d, %d, %d, %d, %d, %d ]",
                     iGs.Ch_Mask    , (int)iGs.Tone_Ofs[7], (int)iGs.Tone_Ofs[6],
                (int)iGs.Tone_Ofs[5], (int)iGs.Tone_Ofs[4], (int)iGs.Tone_Ofs[3],
                (int)iGs.Tone_Ofs[2], (int)iGs.Tone_Ofs[1], (int)iGs.Tone_Ofs[0] );
             WriteToLog(S_LOG_T_AIK + msg, clTeal);
             if ( !fConKpa ) *pResult = ERR_AIK_KPA_WN_NC;
             if ( *pResult == 0 )
             {
                Apply_Generator_Settings();
                btnSet->Click();
                WriteToLog(S_LOG_T_WND + "���������� ��������� ���������� �������������", clWindowText);
                Sleep( 1000 );
                WriteToLog(S_LOG_T_WND + "��������� ������������ ��� ����", clWindowText);
                btnGen->Click();
                tmoGenTimer->Enabled = true;
                fGen = true;
             }
          }
          break;


          default:
                pResult = ERR_AIK_CMD_CODE;
                break;
       }



}

void TCP_Server::Init_ATM()
{
//   atmTimer->Enabled = false;
//   memset(&atm, 0, sizeof(atm));
////   if ( ci.fActive ) atm[INDX_BAL_CON_CVM] = 1;
//   if ( ci.fActive )
//   {
//      fChkConCVM = true;
//      btnTestRS->Click();
//   }
//   if ( fConBink ) atm[INDX_BAL_CON_BINK] = 1;
//   if ( fConMko ) atm[INDX_BAL_CON_MKO] = 1;
//   memset(&atm_old, 0xFEFE, sizeof(atm));
//   atmTimer->Enabled = true;
}
