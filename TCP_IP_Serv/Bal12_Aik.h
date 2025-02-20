//---------------------------------------------------------------------------

#ifndef _BAL12_AIK_H_
#define _BAL12_AIK_H_

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------

#define MKOMON_PORT           2002              //
#define S_MKOMON_PORT         "2002"            // MKO2 monitor 14F160
#define S_MKOMON_IP           "192.168.1.15"    //

#define SERV_BAL_PORT         4000
#define S_SERV_BAL_PORT       "4000"

#define S_AIK_IP              "192.168.1.90"
#define S_AIK_HOSTNAME        "K14F160-KAPRI"

#define AIK_NKA               7
#define S_AIK_SHARE_DIR       "\\K14F160-KAPRI\BALPOST"
/*
#define S_AIK_BAL_R_FILE      "\\bal_000.bin"
#define S_AIK_BAL_B_FILE      "\\bal_000.bak"
*/
#define AIK_BUF_SIZE          17408
#define AIK_IPK_SIZE          16640
#define AIK_INF_SIZE          16384

/***** Типы информационных пакетов *****/
#define PACKET_TYPE_REPLY     1           // квитанция                       [+]
#define PACKET_TYPE_CMD       2           // команда управления              [+]
#define PACKET_TYPE_KPI       3           // массив КПИ                      [-]
#define PACKET_TYPE_ATM       4           // адресная телеметрия             [+]
#define PACKET_TYPE_PTM       5           // позиционная телеметрия          [-]
#define PACKET_TYPE_MSG       6           // текстовое сообщение             [-]
#define PACKET_TYPE_CG        7           // запуск циклограммы              [-]
#define PACKET_TYPE_PAR_REQ   8           // запрос параметров               [-]
#define PACKET_TYPE_PAR_REP   9           // ответ параметров                [-]
#define PACKET_TYPE_RAM_REQ   10          // запрос дампа ОЗУ                [-]
#define PACKET_TYPE_RAM_REP   11          // ответ дампа ОЗУ                 [-]
#define PACKET_TYPE_ARRAY     12          // двоичный массив                 [-]
#define PACKET_TYPE_PROT      13          // сообщение в протокол сеанса АИК [-]
#define PACKET_TYPE_TIME      14          // время моделирования НОК         [-]

/***** Команды *****/
#define CMD_TYPE              1

/***** Команды БАЛ *****/
#define CMD_QTY               31          // кол-во команд без параметров
#define CMDWP_QTY             3           // кол-во команд с параметрами

#define S_BAL_ATM_START       "$БАЛ_АТМ_СТАРТ"
#define S_BAL_ATM_STOP        "$БАЛ_АТМ_СТОП"
#define S_BAL_ATM_RESET       "$БАЛ_АТМ_СБРОС"
#define S_BAL_TEST_KPA        "$БАЛ_ТЕСТ_КПА"
#define S_BAL_TEST_EXCH       "$БАЛ_ТЕСТ_ОБМЕН"
#define S_BAL_BINK_CON        "$БАЛ_БИНК"
#define S_BAL_BINK_DISCON     "$БАЛ_БИНК_ОТКЛ"
#define S_BAL_CVM1_CON        "$БАЛ_ЦВМ1"
#define S_BAL_CMD_RSVD_9      "$БАЛ_КУ_РЕЗ_9"
#define S_BAL_CVM2_CON        "$БАЛ_ЦВМ2"
#define S_BAL_CMD_RSVD_11     "$БАЛ_КУ_РЕЗ_11"
#define S_BAL_CVM_DISCON      "$БАЛ_ЦВМ_ОТКЛ"
#define S_BAL_FILE_NPK        "$БАЛ_Ф_НПК"
#define S_BAL_FILE_MRL        "$БАЛ_Ф_МРЛ"
#define S_BAL_ARX_PROT        "$БАЛ_АРХ_ПРОТ"
#define S_BAL_NEW_SESN        "$БАЛ_НОВ_СЕАНС"
#define S_BAL_END_SESN        "$БАЛ_ЗАВ_СЕАНС"
#define S_BAL_CHECK_RS        "$БАЛ_СДН_ЦВМ"
#define S_BAL_CMD_RSVD_19     "$БАЛ_КУ_РЕЗ_19"
#define S_BAL_MKO_CON         "$БАЛ_МКО"
#define S_BAL_MKO_DISCON      "$БАЛ_МКО_ОТКЛ"
#define S_BAL_MKO_START       "$БАЛ_МКО_СТАРТ"
#define S_BAL_MKO_STOP        "$БАЛ_МКО_СТОП"
#define S_BAL_CMD_RSVD_24     "$БАЛ_КУ_РЕЗ_24"
#define S_BAL_CMD_RSVD_25     "$БАЛ_КУ_РЕЗ_25"
#define S_BAL_CMD_RSVD_26     "$БАЛ_КУ_РЕЗ_26"
#define S_BAL_CMD_RSVD_27     "$БАЛ_КУ_РЕЗ_27"
#define S_BAL_CMD_RSVD_28     "$БАЛ_КУ_РЕЗ_28"
#define S_BAL_CMD_RSVD_29     "$БАЛ_КУ_РЕЗ_29"
#define S_BAL_CMD_RSVD_30     "$БАЛ_КУ_РЕЗ_30"
#define S_BAL_CMD_RSVD_31     "$БАЛ_КУ_РЕЗ_31"

#define S_BAL_BTS2            "$БАЛ_ШВ2"
#define S_BAL_CHECK           "$БАЛ_СВЕРКА"
#define S_BAL_GEN_SIG         "$БАЛ_ГЕН_ИМП"

#define S_BAL_UNKNOWN         "$БАЛ_???"

#define CMD_BAL_ATM_START     1           // включить выдачу АТМ
#define CMD_BAL_ATM_STOP      2           // отключить выдачу АТМ
#define CMD_BAL_ATM_RESET     3           // обнулить АТМ параметры
#define CMD_BAL_TEST_KPA      4           // тест КПА БАЛ-К2
#define CMD_BAL_TEST_EXCH     5           // проверка доступа к папке обмена АИК
#define CMD_BAL_BINK_CON      6           // установить соединение с КПА БИНК-К2
#define CMD_BAL_BINK_DISCON   7           // завершить соединение с КПА БИНК-К2
#define CMD_BAL_CVM1_CON      8           // включить питание ТК ЦВМ-1 и открыть COM-порт
#define CMD_BAL_CMD_RSVD_9    9           // резерв
#define CMD_BAL_CVM2_CON      10          // включить питание ТК ЦВМ-2 и открыть COM-порт
#define CMD_BAL_CMD_RSVD_11   11          // резерв
#define CMD_BAL_CVM_DISCON    12          // закрыть COM-порт и отключить питание ТК ЦВМ
#define CMD_BAL_FILE_NPK      13          // прочитать из папки обмена АИК файл СИС_НПК
                                          // и провести его сверку с эталоном
                                          // в соответствии с режимом сверки
#define CMD_BAL_FILE_MRL      14          // прочитать из папки обмена АИК файл СИС_МРЛ
                                          // и провести его сверку с эталоном
                                          // в соответствии с режимом сверки
#define CMD_BAL_ARX_PROT      15          // записать архив протоколов КПА
                                          // в папку обмена АИК BALPOST
#define CMD_BAL_NEW_SESN      16          // начать новый сеанс ПО КПА
#define CMD_BAL_END_SESN      17          // завершить сеанс ПО КПА
#define CMD_BAL_CHECK_RS      18          // тест обмена по ТК с ЦВМ
#define CMD_BAL_CMD_RSVD_19   19          // резерв
#define CMD_BAL_MKO_CON       20          // установить соединение с монитором МКО
#define CMD_BAL_MKO_DISCON    21          // прервать соединение с монитором МКО
#define CMD_BAL_MKO_START     22          // выдать заявку монитору МКО
#define CMD_BAL_MKO_STOP      23          // отбить все заявки монитору МКО
#define CMD_BAL_CMD_RSVD_24   24          // резерв
#define CMD_BAL_CMD_RSVD_25   25          // резерв
#define CMD_BAL_CMD_RSVD_26   26          // резерв
#define CMD_BAL_CMD_RSVD_27   27          // резерв
#define CMD_BAL_CMD_RSVD_28   28          // резерв
#define CMD_BAL_CMD_RSVD_29   29          // резерв
#define CMD_BAL_CMD_RSVD_30   30          // резерв
#define CMD_BAL_CMD_RSVD_31   31          // резерв

#define CMDWP_BAL_BTS2        32          // установить время ШВ2
#define CMDWP_BAL_CHECK       33          // начать сверку СИС
#define CMDWP_BAL_GEN_SIG     34          // генерация импульсного сигнала для СВАН

#define PAR_QTY_BTS2          5           // кол-во параметров команды $БАЛ_ШВ2
#define PAR_QTY_CHECK         1           // кол-во параметров команды $БАЛ_СВЕРКА
#define PAR_QTY_GEN_SIG       14          // кол-во параметров команды $БАЛ_ГЕН_СИГ

/***** Типы параметров АИК *****/
#define PAR_TYPE_BYTE         1
#define PAR_TYPE_BYTE_SIGN    2
#define PAR_TYPE_WORD         3
#define PAR_TYPE_WORD_SIGN    4
#define PAR_TYPE_DWORD        5
#define PAR_TYPE_DWORD_SIGN   6
#define PAR_TYPE_REAL         7
#define PAR_TYPE_DOUBLE       8
#define PAR_TYPE_STRING0      9
#define PAR_TYPE_MBYTE        10

/***** АТМ *****/
#define ATM_TYPE              1

/***** АТМ БАЛ *****/
#define BAL_ATM_PAR_QTY       20

#define INDX_BAL_KPA_TEST     0
#define INDX_BAL_CHK_MODE     1
#define INDX_BAL_SIS_REP      2
#define INDX_BAL_CON_BINK     3
#define INDX_BAL_CNT_NPK      4
#define INDX_BAL_CNT_MRL      5
#define INDX_BAL_CNT_FC       6
#define INDX_BAL_CON_CVM      7
#define INDX_BAL_CON_MKO      8
#define INDX_BAL_CNT_MKO      9
#define INDX_BAL_C_M_NPK      10
#define INDX_BAL_C_M_MRL      11
#define INDX_BAL_C_M_FC       12
#define INDX_BAL_C_M_IN_MRL   13
#define INDX_BAL_C_M_OZIS     14
#define INDX_BAL_C_CMD        15
#define INDX_BAL_ATM_17       16
#define INDX_BAL_ATM_18       17
#define INDX_BAL_ATM_19       18
#define INDX_BAL_ATM_20       19

/***** Параметры АТМ БАЛ *****/
#define S_BAL_KPA_TEST        "      $БАЛ_РЕЗ_ТЕСТ = "
#define S_BAL_CHK_MODE        "      $БАЛ_РЕЖ_СВЕР = "
#define S_BAL_SIS_REP         "      $БАЛ_КВ_СИС = "
#define S_BAL_CON_BINK        "      $БАЛ_СОЕД_БИНК = "
#define S_BAL_CNT_NPK         "      $БАЛ_СЧ_НПК = "
#define S_BAL_CNT_MRL         "      $БАЛ_СЧ_МРЛ = "
#define S_BAL_CNT_FC          "      $БАЛ_СЧ_ФК  = "
#define S_BAL_CON_CVM         "      $БАЛ_СОЕД_ЦВМ = "
#define S_BAL_CON_MKO         "      $БАЛ_СОЕД_МКО = "
#define S_BAL_CNT_MKO         "      $БАЛ_СЧ_МКО = "
#define S_BAL_C_M_NPK         "      $БАЛ_СЧМ_НПК = "
#define S_BAL_C_M_MRL         "      $БАЛ_СЧМ_МРЛ = "
#define S_BAL_C_M_FC          "      $БАЛ_СЧМ_ФК  = "
#define S_BAL_C_M_IN_MRL      "      $БАЛ_СЧМ_ВХ_МРЛ = "
#define S_BAL_C_M_OZIS        "      $БАЛ_СЧМ_ОЗИС = "
#define S_BAL_C_CMD           "      $БАЛ_ККБАЛ  = "
#define S_BAL_ATM_17          "      $БАЛ_АТМ_17 = "
#define S_BAL_ATM_18          "      $БАЛ_АТМ_18 = "
#define S_BAL_ATM_19          "      $БАЛ_АТМ_19 = "
#define S_BAL_ATM_20          "      $БАЛ_АТМ_20 = "

#define BAL_VAL_KPA_TEST      0x1234

#define BAL_SIS_REP_NORM_FC   0x4444      // норма СИС_ФК
#define BAL_SIS_REP_NORM_N    0x5555      // норма СИС_НПК
#define BAL_SIS_REP_NORM_SN   0x6666      // норма СИС_НПК с измерениями СВАН
#define BAL_SIS_REP_NORM_M    0x7777      // норма СИС_МРЛ
#define BAL_SIS_REP_NORM_SM   0x8888      // норма СИС_МРЛ с измерениями СВАН

#define BAL_SIS_REP_RX_FC     0x0004      // СИС_ФК не приняты
#define BAL_SIS_REP_RX_N      0x0005      // СИС_НПК не принят или приняты не все файлы цепочки
#define BAL_SIS_REP_RX_SN     0x0006      // СИС_НПК с измерениями СВАН не принят
//efine BAL_SIS_REP_RX_SХN    0x0X06      // Х - факт кол-во измерений СВАН, в принятых СИС_НПК
#define BAL_SIS_REP_RX_M      0x0007      // СИС_МРЛ не принят или приняты не все файлы цепочки
#define BAL_SIS_REP_RX_SM     0x0008      // СИС_МРЛ с измерениями СВАН не принят
//efine BAL_SIS_REP_RX_SХM    0x0X08      // Х - факт кол-во измерений СВАН, в принятых СИС_МРЛ

#define BAL_SIS_REP_CMP_N     0x000A      // принятый(ые) СИС_НПК не совпали с эталоном
#define BAL_SIS_REP_CMP_M     0x000E      // принятый(ые) СИС_МРЛ не совпали с эталоном

#define BAL_SIS_REP_FC_STRUCT 0x0010      // ненорма СИС_ФК (структура)
#define BAL_SIS_REP_FC_NKA    0x0020      // ненорма СИС_ФК (номер КА)
#define BAL_SIS_REP_FC_MSQTY  0x0040      // ненорма СИС_ФК (число измерений)
#define BAL_SIS_REP_FC_TIME   0x0080      // ненорма СИС_ФК (время)

/***** Коды ошибок *****/
#define ERR_AIK_QTY           23

#define ERR_AIK_NO            0
#define ERR_AIK_TP_FMT        1
#define ERR_AIK_IP_TYPE       2
#define ERR_AIK_CMD_TYPE      3
#define ERR_AIK_CMD_CODE      4
#define ERR_AIK_PAR_QTY       5
#define ERR_AIK_PAR_TYPE      6

#define ERR_AIK_DIR_ACS       10
#define ERR_AIK_RD_FL         11

#define ERR_AIK_CVM_NC        12
#define ERR_AIK_KPABINK_NC    13
#define ERR_AIK_CVM_NA        14
#define ERR_AIK_KPABINK_NA    15

#define ERR_AIK_KPA_WN_NC     16
#define ERR_AIK_KPA_WN_NA     17

#define ERR_AIK_MKO_NC        18
#define ERR_AIK_MKO_NA        19

#define ERR_AIK_RN_NC         20
#define ERR_AIK_R1_NO         21
#define ERR_AIK_R2_NO         22

#define S_ERR_AIK_TP_FMT      "Нарушен формат транспортного пакета"
#define S_ERR_AIK_IP_TYPE     "Не распознан тип информационного пакета"
#define S_ERR_AIK_CMD_TYPE    "Не распознан тип КУ"
#define S_ERR_AIK_CMD_CODE    "Не распознан код КУ"
#define S_ERR_AIK_PAR_QTY     "Неверное количество параметров"
#define S_ERR_AIK_PAR_TYPE    "Неверный тип параметров"

#define S_ERR_AIK_DIR_ACS     "Нет доступа к папке обмена АИК"
#define S_ERR_AIK_RD_FL       "Ошибка чтения файла из папки обмена АИК"

#define S_ERR_AIK_CVM_NC      "Нет соединения с ЦВМ29"
#define S_ERR_AIK_KPABINK_NC  "Нет соединения с КПА БИНК"
#define S_ERR_AIK_CVM_NA      "Невозможно установить\/разорвать соединение с ЦВМ29"
#define S_ERR_AIK_KPABINK_NA  "Невозможно установить\/разорвать соединение с КПА БИНК"

#define S_ERR_AIK_KPA_WN_NC   "Нет соединения с Окно N"
#define S_ERR_AIK_KPA_WN_NA   "Невозможно установить\/разорвать соединение с Окно N"

#define S_ERR_AIK_MKO_NC      "Нет соединения с монитором МКО"
#define S_ERR_AIK_MKO_NA      "Невозможно установить\/разорвать соединение с монитором МКО"

#define S_ERR_AIK_RN_NC       "Нет закрытия Реле 1 и\/или 2 [ +27В ТК ]"
#define S_ERR_AIK_R1_NO       "Нет открытия Реле 1 [ +27В ТК1 ]"
#define S_ERR_AIK_R2_NO       "Нет открытия Реле 2 [ +27В ТК2 ]"

//---------------------------------------------------------------------------
// Structures definitions
//---------------------------------------------------------------------------

#include "windows.h"

#pragma pack(push)
#pragma pack(1)

/***** Заголовок транспортного пакета *****/
#pragma pack(push, 1)
typedef struct _tph
{
   WORD     wLen;
   FILETIME fileTime;

} tHeadTransportPacket;
#pragma pack(pop)

/***** Транспортный пакет *****/
typedef struct _tp
{
   tHeadTransportPacket HEAD;                   // заголовок тран. пакета
   WORD                 wPacketType;            // инф. пакет : заголовок
   BYTE                 bufInf[AIK_IPK_SIZE];   // инф. пакет : инф.часть

} tPacket;

//---------------------------------------------------------------------------

/***** Информационная часть - Квитанция *****/
#pragma pack(push, 1)
typedef struct _rpi
{
   WORD                 wPacketType;
   WORD                 wResult;
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketRep;
#pragma pack(pop)

/***** Транспортный пакет - Квитанция *****/
#pragma pack(push, 1)
typedef struct _rp
{
   tHeadTransportPacket HEAD;                   // ????????? ????. ??????
   WORD                 wPacketType;            // ???. ????? : ?????????
   tInfPacketRep        REP;                    // ???. ????? : ???.?????

} tPacketRep;
#pragma pack(pop)

//---------------------------------------------------------------------------

/***** Информационная часть - Команда *****/
#pragma pack(push, 1)
typedef struct _cpi
{
   WORD                 wCmdType;
   DWORD                dwCmdCode;
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketCmd;
#pragma pack(pop)

/***** Транспортный пакет - Команда *****/
#pragma pack(push, 1)
typedef struct _cp
{
   tHeadTransportPacket HEAD;                   // ????????? ????. ??????
   WORD                 wPacketType;            // ???. ????? : ?????????
   tInfPacketCmd        CMD;                    // ???. ????? : ???.?????

} tPacketCmd;
#pragma pack(pop)

//---------------------------------------------------------------------------
/*
typedef struct _mkpi
{
   WORD                 wFrCount;
   WORD                 wFrLen;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketMKPI;

typedef struct _mkp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketMKPI       MKPI;

} tPacketMKPI;
*/
//---------------------------------------------------------------------------

/***** Информационная часть - АТМ *****/
typedef struct _atmpar
{
   WORD                 wATMType;
   WORD                 wParNum;
   BYTE                 cParLen;
   WORD                 wParVal;

} tATMPar;

/***** Информационная часть - АТМ *****/
typedef struct _atmpi
{
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketATM;

/***** Транспортный пакет - АТМ *****/
typedef struct _atmp
{
   tHeadTransportPacket HEAD;                   // заголовок тран. пакета
   WORD                 wPacketType;            // инф. пакет : заголовок
   tInfPacketATM        ATM;                    // инф. пакет : инф.часть

} tPacketATM;

typedef struct _par
{
   WORD                 wParType;
   WORD                 wParValue;

} tParam;


typedef struct _parF
{
   WORD                 wParType;
   float                fParValue;

} tParamF;


typedef struct _parWS
{
   WORD                 wParType;
   short                wsParValue;

} tParamWS;

//---------------------------------------------------------------------------
/*
typedef struct _ptmpi
{
   WORD                 wPTMType;
   WORD                 wPTMLen;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketPTM;

typedef struct _ptmp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketPTM        PTM;

} tPacketPTM;

//---------------------------------------------------------------------------

typedef struct _mespi
{
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketMsg;

typedef struct _mesp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketMsg        MSG;

} tPacketMsg;

//---------------------------------------------------------------------------

typedef struct _cgpi
{
   WORD                 wPriority;
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketCG;

typedef struct _cgp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketCG         CG;

} tPacketCG;

//---------------------------------------------------------------------------

typedef struct _prqpi
{
   WORD                 wParType;
   WORD                 wParAddr;

} tInfPacketParReq;

typedef struct _prqp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   WORD                 wParCount;
   tInfPacketParReq     PARREQ[AIK_INF_SIZE];

} tPacketParReq;

//---------------------------------------------------------------------------

typedef struct _ppi
{
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketPar;

typedef struct _pp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketPar        PAR;

} tPacketPar;

//---------------------------------------------------------------------------

typedef struct _rrqpi
{
   WORD                 wRAMType;
   DWORD                dwRAMAddr;
   WORD                 wRAMLen;
   DWORD                dwReserved;

} tInfPacketRAMReq;

typedef struct _rrqp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketRAMReq     RAMREQ;

} tPacketRAMReq;

//---------------------------------------------------------------------------

typedef struct _rampi
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketRAMReq     RAMREQ;
   BYTE                 RAM[AIK_INF_SIZE];

} tPacketRAM;

//---------------------------------------------------------------------------

typedef struct _arpi
{
   WORD                 wArrayType;
   WORD                 wArrayLen;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketArray;

typedef struct _arp
{
   tHeadTransportPacket HEAD;
   WORD                 wPacketType;
   tInfPacketArray      ARRAY;

} tPacketArray;

//---------------------------------------------------------------------------

typedef enum
{
   nUnknounPacketType,
   nPacketTypeREP    =  1,
   nPacketTypeCMD    =  2,
   nPacketTypeMKPI   =  3,
   nPacketTypeATM    =  4,
   nPacketTypePTM    =  5,
   nPacketTypeMSG    =  6,
   nPacketTypeCG     =  7,
   nPacketTypePRQ    =  8,
   nPacketTypePAR    =  9,
   nPacketTypeRRQ    = 10,
   nPacketTypeRAM    = 11,
   nPacketTypeARRAY  = 12,
   nPacketTypeCount

} tPacketType;

typedef enum
{
   nUnknounParType,
   nParTypeByte         =  1,
   nParTypeByte_Sign    =  2,
   nParTypeWord         =  3,
   nParTypeWord_Sign    =  4,
   nParTypeDword        =  5,
   nParTypeDword_Sign   =  6,
   nParTypeFloat        =  7,
   nParTypeDouble       =  8,
   nParTypeString       =  9,
   nParTypeCount

} tParType;

typedef enum
{
   nTx,
   nRx,
   nMsgDirCount

} nMsgDir;
*/

//---------------------------------------------------------------------------

/***** Структуры монитора МКО *****/
typedef union
{
   struct
   {
      WORD err    :3;
      WORD ib     :1;
      WORD g2     :1;
      WORD g1     :1;
      WORD rsvd   :2;
      WORD k2     :1;
      WORD k1     :1;
      WORD scc    :4;
      WORD me     :1;
      WORD bus    :1;

   } b;
   WORD w;

} tResultMT;

typedef union
{
   struct
   {
      WORD n      :5;
      WORD sa     :5;
      WORD tr     :1;
      WORD addr   :5;

   } b;
   WORD w;

} tMTKS;

typedef union
{
   struct
   {
      WORD h      :1;
      WORD g      :1;
      WORD f      :1;
      WORD e      :1;
      WORD d      :1;
      WORD rsvd   :3;
      WORD c      :1;
      WORD b      :1;
      WORD a      :1;
      WORD addr   :5;

   } b;
   WORD w;

} tMTOS;

typedef struct
{
   WORD     Len;
   FILETIME Time;

} tHeadZom;

typedef struct
{
   tMTKS    Mask;          // 0xFBE0 - DW w/o TR, 0xFFE0 - DW, 0xF800 - CI
   tMTKS    Value;

} tElemKum;

typedef struct
{
   WORD     TypeInf;       // 6 - КУМ
   WORD     TypeKum;       // 1, 2, 3  ( КУМ_З, КУМ_О, КУМ_ОВ )
   WORD     Count;
   tElemKum Elem[10];

} tHeadInfKum;

typedef struct
{
   tHeadZom    Head;
   tHeadInfKum Inf;

} tZomKum;

typedef struct
{
   WORD        TypeInf;    // 7 - информация монитора МКО
   tResultMT   WResult;
   WORD        Count;
   WORD        Data[36];

} tHeadInfMko;

typedef struct
{
   tHeadZom    Head;
   tHeadInfMko Inf;

} tZomInfMko;

//---------------------------------------------------------------------------

#pragma pack(pop)

//---------------------------------------------------------------------------

#endif

