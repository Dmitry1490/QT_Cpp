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

/***** ���� �������������� ������� *****/
#define PACKET_TYPE_REPLY     1           // ���������                       [+]
#define PACKET_TYPE_CMD       2           // ������� ����������              [+]
#define PACKET_TYPE_KPI       3           // ������ ���                      [-]
#define PACKET_TYPE_ATM       4           // �������� ����������             [+]
#define PACKET_TYPE_PTM       5           // ����������� ����������          [-]
#define PACKET_TYPE_MSG       6           // ��������� ���������             [-]
#define PACKET_TYPE_CG        7           // ������ �����������              [-]
#define PACKET_TYPE_PAR_REQ   8           // ������ ����������               [-]
#define PACKET_TYPE_PAR_REP   9           // ����� ����������                [-]
#define PACKET_TYPE_RAM_REQ   10          // ������ ����� ���                [-]
#define PACKET_TYPE_RAM_REP   11          // ����� ����� ���                 [-]
#define PACKET_TYPE_ARRAY     12          // �������� ������                 [-]
#define PACKET_TYPE_PROT      13          // ��������� � �������� ������ ��� [-]
#define PACKET_TYPE_TIME      14          // ����� ������������� ���         [-]

/***** ������� *****/
#define CMD_TYPE              1

/***** ������� ��� *****/
#define CMD_QTY               31          // ���-�� ������ ��� ����������
#define CMDWP_QTY             3           // ���-�� ������ � �����������

#define S_BAL_ATM_START       "$���_���_�����"
#define S_BAL_ATM_STOP        "$���_���_����"
#define S_BAL_ATM_RESET       "$���_���_�����"
#define S_BAL_TEST_KPA        "$���_����_���"
#define S_BAL_TEST_EXCH       "$���_����_�����"
#define S_BAL_BINK_CON        "$���_����"
#define S_BAL_BINK_DISCON     "$���_����_����"
#define S_BAL_CVM1_CON        "$���_���1"
#define S_BAL_CMD_RSVD_9      "$���_��_���_9"
#define S_BAL_CVM2_CON        "$���_���2"
#define S_BAL_CMD_RSVD_11     "$���_��_���_11"
#define S_BAL_CVM_DISCON      "$���_���_����"
#define S_BAL_FILE_NPK        "$���_�_���"
#define S_BAL_FILE_MRL        "$���_�_���"
#define S_BAL_ARX_PROT        "$���_���_����"
#define S_BAL_NEW_SESN        "$���_���_�����"
#define S_BAL_END_SESN        "$���_���_�����"
#define S_BAL_CHECK_RS        "$���_���_���"
#define S_BAL_CMD_RSVD_19     "$���_��_���_19"
#define S_BAL_MKO_CON         "$���_���"
#define S_BAL_MKO_DISCON      "$���_���_����"
#define S_BAL_MKO_START       "$���_���_�����"
#define S_BAL_MKO_STOP        "$���_���_����"
#define S_BAL_CMD_RSVD_24     "$���_��_���_24"
#define S_BAL_CMD_RSVD_25     "$���_��_���_25"
#define S_BAL_CMD_RSVD_26     "$���_��_���_26"
#define S_BAL_CMD_RSVD_27     "$���_��_���_27"
#define S_BAL_CMD_RSVD_28     "$���_��_���_28"
#define S_BAL_CMD_RSVD_29     "$���_��_���_29"
#define S_BAL_CMD_RSVD_30     "$���_��_���_30"
#define S_BAL_CMD_RSVD_31     "$���_��_���_31"

#define S_BAL_BTS2            "$���_��2"
#define S_BAL_CHECK           "$���_������"
#define S_BAL_GEN_SIG         "$���_���_���"

#define S_BAL_UNKNOWN         "$���_???"

#define CMD_BAL_ATM_START     1           // �������� ������ ���
#define CMD_BAL_ATM_STOP      2           // ��������� ������ ���
#define CMD_BAL_ATM_RESET     3           // �������� ��� ���������
#define CMD_BAL_TEST_KPA      4           // ���� ��� ���-�2
#define CMD_BAL_TEST_EXCH     5           // �������� ������� � ����� ������ ���
#define CMD_BAL_BINK_CON      6           // ���������� ���������� � ��� ����-�2
#define CMD_BAL_BINK_DISCON   7           // ��������� ���������� � ��� ����-�2
#define CMD_BAL_CVM1_CON      8           // �������� ������� �� ���-1 � ������� COM-����
#define CMD_BAL_CMD_RSVD_9    9           // ������
#define CMD_BAL_CVM2_CON      10          // �������� ������� �� ���-2 � ������� COM-����
#define CMD_BAL_CMD_RSVD_11   11          // ������
#define CMD_BAL_CVM_DISCON    12          // ������� COM-���� � ��������� ������� �� ���
#define CMD_BAL_FILE_NPK      13          // ��������� �� ����� ������ ��� ���� ���_���
                                          // � �������� ��� ������ � ��������
                                          // � ������������ � ������� ������
#define CMD_BAL_FILE_MRL      14          // ��������� �� ����� ������ ��� ���� ���_���
                                          // � �������� ��� ������ � ��������
                                          // � ������������ � ������� ������
#define CMD_BAL_ARX_PROT      15          // �������� ����� ���������� ���
                                          // � ����� ������ ��� BALPOST
#define CMD_BAL_NEW_SESN      16          // ������ ����� ����� �� ���
#define CMD_BAL_END_SESN      17          // ��������� ����� �� ���
#define CMD_BAL_CHECK_RS      18          // ���� ������ �� �� � ���
#define CMD_BAL_CMD_RSVD_19   19          // ������
#define CMD_BAL_MKO_CON       20          // ���������� ���������� � ��������� ���
#define CMD_BAL_MKO_DISCON    21          // �������� ���������� � ��������� ���
#define CMD_BAL_MKO_START     22          // ������ ������ �������� ���
#define CMD_BAL_MKO_STOP      23          // ������ ��� ������ �������� ���
#define CMD_BAL_CMD_RSVD_24   24          // ������
#define CMD_BAL_CMD_RSVD_25   25          // ������
#define CMD_BAL_CMD_RSVD_26   26          // ������
#define CMD_BAL_CMD_RSVD_27   27          // ������
#define CMD_BAL_CMD_RSVD_28   28          // ������
#define CMD_BAL_CMD_RSVD_29   29          // ������
#define CMD_BAL_CMD_RSVD_30   30          // ������
#define CMD_BAL_CMD_RSVD_31   31          // ������

#define CMDWP_BAL_BTS2        32          // ���������� ����� ��2
#define CMDWP_BAL_CHECK       33          // ������ ������ ���
#define CMDWP_BAL_GEN_SIG     34          // ��������� ����������� ������� ��� ����

#define PAR_QTY_BTS2          5           // ���-�� ���������� ������� $���_��2
#define PAR_QTY_CHECK         1           // ���-�� ���������� ������� $���_������
#define PAR_QTY_GEN_SIG       14          // ���-�� ���������� ������� $���_���_���

/***** ���� ���������� ��� *****/
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

/***** ��� *****/
#define ATM_TYPE              1

/***** ��� ��� *****/
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

/***** ��������� ��� ��� *****/
#define S_BAL_KPA_TEST        "      $���_���_���� = "
#define S_BAL_CHK_MODE        "      $���_���_���� = "
#define S_BAL_SIS_REP         "      $���_��_��� = "
#define S_BAL_CON_BINK        "      $���_����_���� = "
#define S_BAL_CNT_NPK         "      $���_��_��� = "
#define S_BAL_CNT_MRL         "      $���_��_��� = "
#define S_BAL_CNT_FC          "      $���_��_��  = "
#define S_BAL_CON_CVM         "      $���_����_��� = "
#define S_BAL_CON_MKO         "      $���_����_��� = "
#define S_BAL_CNT_MKO         "      $���_��_��� = "
#define S_BAL_C_M_NPK         "      $���_���_��� = "
#define S_BAL_C_M_MRL         "      $���_���_��� = "
#define S_BAL_C_M_FC          "      $���_���_��  = "
#define S_BAL_C_M_IN_MRL      "      $���_���_��_��� = "
#define S_BAL_C_M_OZIS        "      $���_���_���� = "
#define S_BAL_C_CMD           "      $���_�����  = "
#define S_BAL_ATM_17          "      $���_���_17 = "
#define S_BAL_ATM_18          "      $���_���_18 = "
#define S_BAL_ATM_19          "      $���_���_19 = "
#define S_BAL_ATM_20          "      $���_���_20 = "

#define BAL_VAL_KPA_TEST      0x1234

#define BAL_SIS_REP_NORM_FC   0x4444      // ����� ���_��
#define BAL_SIS_REP_NORM_N    0x5555      // ����� ���_���
#define BAL_SIS_REP_NORM_SN   0x6666      // ����� ���_��� � ����������� ����
#define BAL_SIS_REP_NORM_M    0x7777      // ����� ���_���
#define BAL_SIS_REP_NORM_SM   0x8888      // ����� ���_��� � ����������� ����

#define BAL_SIS_REP_RX_FC     0x0004      // ���_�� �� �������
#define BAL_SIS_REP_RX_N      0x0005      // ���_��� �� ������ ��� ������� �� ��� ����� �������
#define BAL_SIS_REP_RX_SN     0x0006      // ���_��� � ����������� ���� �� ������
//efine BAL_SIS_REP_RX_S�N    0x0X06      // � - ���� ���-�� ��������� ����, � �������� ���_���
#define BAL_SIS_REP_RX_M      0x0007      // ���_��� �� ������ ��� ������� �� ��� ����� �������
#define BAL_SIS_REP_RX_SM     0x0008      // ���_��� � ����������� ���� �� ������
//efine BAL_SIS_REP_RX_S�M    0x0X08      // � - ���� ���-�� ��������� ����, � �������� ���_���

#define BAL_SIS_REP_CMP_N     0x000A      // ��������(��) ���_��� �� ������� � ��������
#define BAL_SIS_REP_CMP_M     0x000E      // ��������(��) ���_��� �� ������� � ��������

#define BAL_SIS_REP_FC_STRUCT 0x0010      // ������� ���_�� (���������)
#define BAL_SIS_REP_FC_NKA    0x0020      // ������� ���_�� (����� ��)
#define BAL_SIS_REP_FC_MSQTY  0x0040      // ������� ���_�� (����� ���������)
#define BAL_SIS_REP_FC_TIME   0x0080      // ������� ���_�� (�����)

/***** ���� ������ *****/
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

#define S_ERR_AIK_TP_FMT      "������� ������ ������������� ������"
#define S_ERR_AIK_IP_TYPE     "�� ��������� ��� ��������������� ������"
#define S_ERR_AIK_CMD_TYPE    "�� ��������� ��� ��"
#define S_ERR_AIK_CMD_CODE    "�� ��������� ��� ��"
#define S_ERR_AIK_PAR_QTY     "�������� ���������� ����������"
#define S_ERR_AIK_PAR_TYPE    "�������� ��� ����������"

#define S_ERR_AIK_DIR_ACS     "��� ������� � ����� ������ ���"
#define S_ERR_AIK_RD_FL       "������ ������ ����� �� ����� ������ ���"

#define S_ERR_AIK_CVM_NC      "��� ���������� � ���29"
#define S_ERR_AIK_KPABINK_NC  "��� ���������� � ��� ����"
#define S_ERR_AIK_CVM_NA      "���������� ����������\/��������� ���������� � ���29"
#define S_ERR_AIK_KPABINK_NA  "���������� ����������\/��������� ���������� � ��� ����"

#define S_ERR_AIK_KPA_WN_NC   "��� ���������� � ���� N"
#define S_ERR_AIK_KPA_WN_NA   "���������� ����������\/��������� ���������� � ���� N"

#define S_ERR_AIK_MKO_NC      "��� ���������� � ��������� ���"
#define S_ERR_AIK_MKO_NA      "���������� ����������\/��������� ���������� � ��������� ���"

#define S_ERR_AIK_RN_NC       "��� �������� ���� 1 �\/��� 2 [ +27� �� ]"
#define S_ERR_AIK_R1_NO       "��� �������� ���� 1 [ +27� ��1 ]"
#define S_ERR_AIK_R2_NO       "��� �������� ���� 2 [ +27� ��2 ]"

//---------------------------------------------------------------------------
// Structures definitions
//---------------------------------------------------------------------------

#include "windows.h"

#pragma pack(push)
#pragma pack(1)

/***** ��������� ������������� ������ *****/
#pragma pack(push, 1)
typedef struct _tph
{
   WORD     wLen;
   FILETIME fileTime;

} tHeadTransportPacket;
#pragma pack(pop)

/***** ������������ ����� *****/
typedef struct _tp
{
   tHeadTransportPacket HEAD;                   // ��������� ����. ������
   WORD                 wPacketType;            // ���. ����� : ���������
   BYTE                 bufInf[AIK_IPK_SIZE];   // ���. ����� : ���.�����

} tPacket;

//---------------------------------------------------------------------------

/***** �������������� ����� - ��������� *****/
#pragma pack(push, 1)
typedef struct _rpi
{
   WORD                 wPacketType;
   WORD                 wResult;
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketRep;
#pragma pack(pop)

/***** ������������ ����� - ��������� *****/
#pragma pack(push, 1)
typedef struct _rp
{
   tHeadTransportPacket HEAD;                   // ????????? ????. ??????
   WORD                 wPacketType;            // ???. ????? : ?????????
   tInfPacketRep        REP;                    // ???. ????? : ???.?????

} tPacketRep;
#pragma pack(pop)

//---------------------------------------------------------------------------

/***** �������������� ����� - ������� *****/
#pragma pack(push, 1)
typedef struct _cpi
{
   WORD                 wCmdType;
   DWORD                dwCmdCode;
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketCmd;
#pragma pack(pop)

/***** ������������ ����� - ������� *****/
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

/***** �������������� ����� - ��� *****/
typedef struct _atmpar
{
   WORD                 wATMType;
   WORD                 wParNum;
   BYTE                 cParLen;
   WORD                 wParVal;

} tATMPar;

/***** �������������� ����� - ��� *****/
typedef struct _atmpi
{
   WORD                 wParCount;
   BYTE                 bufInf[AIK_INF_SIZE];

} tInfPacketATM;

/***** ������������ ����� - ��� *****/
typedef struct _atmp
{
   tHeadTransportPacket HEAD;                   // ��������� ����. ������
   WORD                 wPacketType;            // ���. ����� : ���������
   tInfPacketATM        ATM;                    // ���. ����� : ���.�����

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

/***** ��������� �������� ��� *****/
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
   WORD     TypeInf;       // 6 - ���
   WORD     TypeKum;       // 1, 2, 3  ( ���_�, ���_�, ���_�� )
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
   WORD        TypeInf;    // 7 - ���������� �������� ���
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

