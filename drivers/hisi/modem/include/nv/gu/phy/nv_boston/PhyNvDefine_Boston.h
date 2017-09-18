/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phyNvDefine_Boston
  �� �� ��   : ����
  ��    ��   : h00165915
  ��������   : 2016��7��1��
  ����޸�   :
  ��������   : PhyNvDefine.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��7��1��
    ��    ��   : h00165915
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PHYNVDEFINE_BOSTON_H__
#define __PHYNVDEFINE_BOSTON_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "nv_common_interface.h"

#pragma pack(1)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ET֧�ֵ����MIPI���� */
#define UCOM_NV_ET_MIPI_NUM             ( 6 )
#define UCOM_NV_PA_GAIN_NUM_MAX         ( 4 )                                   /* pa gain���� */

#define UCOM_NV_ET_APT_TRIGGER_NUM      ( 2 )
#define UCOM_NV_W_TX_DCDC_MIPI_NUM      ( 4 )                                   /* DCDC MIPI���� */

/* CDMA tas mipi���Ԫ���� */
#define UCOM_NV_CDMA_TAS_MIPI_NUM       ( 4 )
#define UCOM_NV_W_TEMP_NUM              ( 0x10  )                               /* �¶Ȳ������õ��¶ȵ㣬ǰ5���ֱ���� -20,0,20,40,60����6�������ֽڶ��� */

/* MRX���֧����Ч��λ,Ŀǰ���֧��5�� */
#define UCOM_NV_W_MRX_GAIN_MAX_NUM      ( 5 )

#define UCOM_NV_GUC_MIPI_INIT_UNIT_MAX_NUM      ( 16 )

#define UCOM_NV_TAS_DPDT_MIPI_UNIT_MAX_NUM      ( 4 )
#define UCOM_NV_G_NOTCH_MIPI_UNIT_MAX_NUM       ( 4 )
#define UCOM_NV_G_PAVCC_MIPI_UNIT_MAX_NUM       ( 4 )
#define UCOM_NV_G_TUNER_MIPI_UNIT_MAX_NUM       ( 4 )
#define UCOM_NV_G_MIPI_INIT_UNIT_MAX_NUM        ( 16 )
#define UCOM_NV_MAX_MIPI_ANT_UNIT_NUMBER        ( 4 )

/*****************************************************************************
 �ṹ��    : UCOM_NV_FEM_PIN_TO_GPIO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NV_FEMPIN_TO_GPIO_STRU������tl drv��nvͷ�ļ���
*****************************************************************************/
typedef NV_FEMPIN_TO_GPIO_STRU UCOM_NV_FEM_PIN_TO_GPIO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GPIO_MIPI_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FEM_GPIO_MIPIDEV_CTRL_STRU������tl drv��nvͷ�ļ���
*****************************************************************************/
typedef FEM_GPIO_MIPIDEV_CTRL_STRU UCOM_NV_GPIO_MIPI_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RFFE_GPIO_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFFE_GPIO_VALUE_STRU������tl drv��nvͷ�ļ���
*****************************************************************************/
typedef RFFE_GPIO_VALUE_STRU UCOM_NV_RFFE_GPIO_VALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF_NV_MIPIDEV_04CMD������tl drv��nvͷ�ļ���
*****************************************************************************/
typedef RF_NV_MIPIDEV_04CMD UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU;

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_DL_RFIC_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����RFIC����,����RFIC ID,ͨ���ţ������PORT��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitRficIdx                  :2;         /* RFIC ID��[0,2]�ֱ��ʾRFIC1��RFIC2��RFIC3 */
    VOS_UINT32                          bitRficRxCh                 :2;         /* ����RXͨ���ţ�ÿ��RFIC��3��ͨ�����ֱ���RX1��RX2��RX3; ��������4*4MIMO�̶�ʹ��RX1A1B+RX3A3B,���ǲ���ͬһ��TX_PLL1���ƣ����MIMO��������ѡRXͨ������4����2��ʱ��
                                                                                ֻ����Main��Div Ant,RFIC������RxCh��Ҫ��дʹ�õ�ͨ���ţ����֧��2�ճ�����RxCh��ʾʹ�õ�Rxͨ����;
                                                                                4R ��2R����ͬһ��NV */


    VOS_UINT32                          bitRfPortCrossFlag          :1;         /*�������ߵ��ź����ӵ��� RFIC DRX Port�ڣ������Ҫ��CTUͨ�����浽������ֻ֧��2�յĽ���*/
    VOS_UINT32                          bitMainAntRxPortSel         :4;         /* ����LNA��RFIC�˿�ѡ�񣬼��ź�ͨ���ĸ��˿����뵽RFIC */
    VOS_UINT32                          bitDivAntRxPortSel          :4;         /* �ּ�LNA��RFIC�˿�ѡ�� */
    VOS_UINT32                          bitRsv0                     :3;         /* Ԥ��λ */
    VOS_UINT32                          bitRsv1                     :4;
    VOS_UINT32                          bitRsv2                     :4;
    VOS_UINT32                          bitRsv3                     :4;
    VOS_UINT32                          bitRsv4                     :4;

} UCOM_NV_GUC_BAND_DL_RFIC_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_BAND_UL_RFIC_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����RFIC����,����RFIC ID,ͨ���ţ������PORT��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitRficIdx                 :2;          /* ����ͨ�����ڵ�RFIC ID,֧���շ����� */
    VOS_UINT32                          bitRficTxCh                :2;          /* ����ͨ���ţ�����MIMO�̶�ʹ��Tx1Ch,��˵���������MIMO�󣬲�ȡ��ͨ������������£���дTx1Iq1,Tx2Iq������2Txת1Tx����NV�����Ժ�Rxһ��*/
    VOS_UINT32                          bitMainAntRficTxPortSel    :8;          /* ����PORT��ѡ�� */
    VOS_UINT32                          bitMainAntRficTxMrxPortSel :4;           /*���л���ͨ����Mrxͨ����ѡ��0: MRX1 RF input selected  1: MRX2 RF input selected*/
    VOS_UINT32                          bitRsv0                    :4;
    VOS_UINT32                          bitRsv1                    :4;
    VOS_UINT32                          bitRsv2                    :4;
    VOS_UINT32                          bitRsv3                    :4;

}UCOM_NV_GUC_BAND_UL_RFIC_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_DL_PATH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��PATH������RFICͨ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitRxAntNum                 :3;         /* ���������� */
    VOS_UINT32                          bitRsv0                     :5;
    VOS_UINT32                          bitRsv1                     :8;
    VOS_UINT32                          bitRsv2                     :8;
    VOS_UINT32                          bitRsv3                     :8;

    UCOM_NV_GUC_BAND_DL_RFIC_PARA_STRU  stBandDlRficPara;                       /* ����RFIC���� */

} UCOM_NV_GUC_BAND_DL_PATH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_UL_PATH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��PATH������RFICͨ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitAptPdmPinSel             :3;
    VOS_UINT32                          bitGsmRampSel               :3;
    VOS_UINT32                          bitGmskDataSel              :3;
    VOS_UINT32                          bitRsv0                     :3;
    VOS_UINT32                          bitRsv1                     :4;
    VOS_UINT32                          bitRsv2                     :8;
    VOS_UINT32                          bitRsv3                     :8;

    UCOM_NV_GUC_BAND_UL_RFIC_PARA_STRU  stBandUlRficPara;                       /* RFIC���� */
}UCOM_NV_GUC_BAND_UL_PATH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_DL_GPIO_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ǰ������GPIO���ã��������߿��أ�TUNER�ȣ�֧�����߿��غ�TUNER��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulMainRxAntSel;                         /*ASMͨ·�ϵ��л�����,�����߿��ػ��ȥ*/
    VOS_UINT32                              ulMainRxAntSelExt;                      /*ASMͨ·�ϵ��л�����,�����߿��ػ��ȥ*/
    VOS_UINT32                              ulDivRxAntSel;
    VOS_UINT32                              ulDivRxAntSelExt;
    VOS_UINT32                              ulMainRxTunerSel;                       /*ASMͨ·�ϵ��л�����*/
    VOS_UINT32                              ulMainRxTunerSelExt;
    VOS_UINT32                              ulDivRxTunerSel;
    VOS_UINT32                              ulDivRxTunerSelExt;
    VOS_UINT32                              ulRsv0;                             /* Ԥ�� */
    VOS_UINT32                              ulRsv1;
    VOS_UINT32                              ulRsv2;
    VOS_UINT32                              ulRsv3;
    VOS_UINT32                              ulRsv4;
    VOS_UINT32                              ulRsv5;
    VOS_UINT32                              ulRsv6;
    VOS_UINT32                              ulRsv7;
} UCOM_NV_GUC_BAND_DL_GPIO_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_DL_MIPI_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ǰ������MIPI���ã��������߿��أ�TUNER�ȣ�֧�����߿��غ�TUNER��������
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU              astMipiMainAntRxSel[RX_ANT_SEL_MIPI_NUM];            /*Ant Mipi num=4,��Ҫ��Ƶ����*/
    PHY_MIPIDEV_UNIT_STRU              astMipiDivAntRxSel[RX_ANT_SEL_MIPI_NUM ];
    PHY_MIPIDEV_UNIT_STRU              astMipiMainTunerRxSel[ANT_TUNER_MIPI_NUM ];
    PHY_MIPIDEV_UNIT_STRU              astMipiDivTunerRxSel[ANT_TUNER_MIPI_NUM ];           /*Tuner Mipi num=2,��Ҫ��Ƶ����*/
    PHY_MIPIDEV_UNIT_STRU              astMipiMainAntRxCloseSel[RX_ANT_SEL_MIPI_NUM];       /* ����NV */
    PHY_MIPIDEV_UNIT_STRU              astMipiMRsv0[RX_ANT_SEL_MIPI_NUM];                   /* Ԥ�� */
    PHY_MIPIDEV_UNIT_STRU              astMipiMRsv1[RX_ANT_SEL_MIPI_NUM];
} UCOM_NV_GUC_BAND_DL_MIPI_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_DL_FEM_PATH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��PATH��ǰ������MIPI���ã��������߿��أ�TUNER�ȣ�
             ֧�����߿��غ�TUNER��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_GUC_BAND_DL_GPIO_PARA_STRU           stBandDlGpioPara;              /* ÿ��PATH����GPIO���� */
    UCOM_NV_GUC_BAND_DL_MIPI_PARA_STRU           stBandDlMipiPara;              /* ÿ��PATH����MIPI���� */
}UCOM_NV_GUC_BAND_DL_FEM_PATH_PARA_STRU;

typedef  UCOM_NV_GUC_BAND_DL_FEM_PATH_PARA_STRU      UCOM_NV_GSM_RF_DL_FEM_PATH_STRU;
typedef  UCOM_NV_GUC_BAND_DL_FEM_PATH_PARA_STRU      UCOM_NV_CDMA_RF_DL_FEM_PATH_STRU;
typedef  UCOM_NV_GUC_BAND_DL_FEM_PATH_PARA_STRU      UCOM_NV_W_DL_FEM_PATH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_UL_GPIO_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����GPIO���ã��������߿��أ�TUNER�ȣ�֧�����߿��غ�TUNER��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulTxAntSel;                             /* �������߿��� */
    VOS_UINT32                              ulTxAntSelExt;
    VOS_UINT32                              ulTxTuner;                              /* ����Tuner���� */
    VOS_UINT32                              ulTxTunerExt;
    VOS_UINT32                              ulPaEnCtrl;                             /* PA�߿ؿ��� */
    VOS_UINT32                              ulPaHighModeCtrl;                       /* PA����������� */
    VOS_UINT32                              ulPaMidModeCtrl;                        /* PA����������� */
    VOS_UINT32                              ulPaLowModeCtrl;                        /* PA����������� */
    VOS_UINT32                              ulPaUltraLowModeCtrl;                   /* utralow */
    VOS_UINT32                              ulGpioAntClose;
} UCOM_NV_GUC_BAND_UL_GPIO_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_UL_MIPI_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MIPI���ã��������߿��أ�TUNER�ȣ�֧�����߿��غ�TUNER��������
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU               astMipiAntSelTx[TX_ANT_SEL_MIPI_NUM];   /* MIPI�������߿���  TX_ANT_SEL_MIPI_NUM =4 */
    PHY_MIPIDEV_UNIT_STRU               astMipiTunerTx[ANT_TUNER_MIPI_NUM];     /* MIPI����TUNER���� Tx Tuner is only for Gsm,num=2 */

    PHY_MIPIDEV_UNIT_STRU               astMipiPaOnCtrl[PA_MODE_MIPI_NUM];      /* MIPI PA On���� */
    PHY_MIPIDEV_UNIT_STRU               astMipiPaOffCtrl[PA_MODE_MIPI_NUM];     /* MIPI PA OFF���� */
    PHY_MIPIDEV_UNIT_STRU               astMipiPaHighMode[PA_MODE_MIPI_NUM];    /* MIPI PA����������� PA_MODE_MIPI_NUM=4 */
    PHY_MIPIDEV_UNIT_STRU               astMipiPaMidMode[PA_MODE_MIPI_NUM];     /* MIPI PA����������� PA_MODE_MIPI_NUM=4 */
    PHY_MIPIDEV_UNIT_STRU               astMipiPaLowMode[PA_MODE_MIPI_NUM];     /* MIPI PA����������� PA_MODE_MIPI_NUM=4 */
    PHY_MIPIDEV_UNIT_STRU               astMipiPaUltraLowMode[PA_MODE_MIPI_NUM];
    PHY_MIPIDEV_UNIT_STRU               astMipiAntSelTxClose[TX_ANT_SEL_MIPI_NUM];
    PHY_MIPIDEV_UNIT_STRU               stMipiPaTrigger;                        /* GSM�� */
} UCOM_NV_GUC_BAND_UL_MIPI_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_BAND_EXT_LNA_PATH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LNA��������������ṹ��Ϣ
*****************************************************************************/
typedef struct
{
    NV_EXT_LNA_ANTINFO_STRU                    stMainAntLnaInfo;
    NV_EXT_LNA_ANTINFO_STRU                    stDivAntLnaInfo;
    PHY_MIPIDEV_UNIT_STRU                      astRsv[LNA_MIPI_TRIG_NUM];       /* Ԥ�� */

}UCOM_NV_GUC_BAND_EXT_LNA_PATH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RX_AGC_CAL_RESULT_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGCĳһ��PATH��Ӧ���ܵ�У׼�����GUCֻ��һ��PATH������BAND
*****************************************************************************/
typedef struct
{
    NV_RX_AGC_CAL_RESULT_STRU           stMainAntAgcCalResult;                  /* �������߶�Ӧ��AGCУ׼��� */
    NV_RX_AGC_CAL_RESULT_STRU           stDivAntAgcCalResult;                   /* �ּ����߶�Ӧ��AGCУ׼��� */

}UCOM_NV_GUC_RX_AGC_CAL_RESULT_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : NV_GUC_RX_DCOC_CAL_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ĳһ��PATH��DCOC��У׼���
*****************************************************************************/
typedef struct
{
    NV_RX_DCOC_CAL_RESULT_STRU          astMainAntCalResult;                    /* ������DCOCУ׼��� */
    NV_RX_DCOC_CAL_RESULT_STRU          astDivAntCalResult;                     /* �ּ���DCOCУ׼��� */
}UCOM_NV_GUC_RX_PATH_DCOC_CAL_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RX_AGC_TABLE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ĳһ��PATH��ÿ��������ѡ���AGC TABLE INDEX������INDEXȥ������Ӧ��
 AGC���л����ޡ�AGC DEFAULT GAIN��AGC��RFIC������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitMainAntRxAgcTableIdx         :4;     /* �������߶�Ӧ��AGC TABLE INDEX */
    VOS_UINT32                          bitDivAntRxAgcTableIdx          :4;     /* �ּ����߶�Ӧ��AGC TABLE INDEX */
    VOS_UINT32                          bitRsv0                         :4;
    VOS_UINT32                          bitRsv1                         :4;
    VOS_UINT32                          bitRsv2                         :8;
    VOS_UINT32                          bitRsv3                         :8;
}UCOM_NV_GUC_RX_AGC_TABLE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RF_BAND_CONFIG_STRU
 �ṹ˵��  : GUC Band Config����
*****************************************************************************/
typedef struct
{
    UCOM_NV_GUC_BAND_DL_PATH_PARA_STRU stBandDlPathPara;                        /* ������� */
    UCOM_NV_GUC_BAND_UL_PATH_PARA_STRU stBandUlPathPara;                        /* ������� */

}UCOM_NV_GUC_RF_BAND_CONFIG_STRU;

typedef UCOM_NV_GUC_RF_BAND_CONFIG_STRU       UCOM_NV_GSM_RF_BAND_CONFIG_STRU;
typedef UCOM_NV_GUC_RF_BAND_CONFIG_STRU       UCOM_NV_CDMA_BAND_CONFIG_STRU;
typedef UCOM_NV_GUC_RF_BAND_CONFIG_STRU       UCOM_NV_W_RF_BAND_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_BAND_UL_FEM_PATH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ǰ���������ã�ÿ��PATH������
*****************************************************************************/
typedef struct
{
    UCOM_NV_GUC_BAND_UL_GPIO_PARA_STRU           stBandUlGpioPara;              /* ����GPIO���� */
    UCOM_NV_GUC_BAND_UL_MIPI_PARA_STRU           stBandUlMipiPara;              /* ����MIPI���� */
}UCOM_NV_GUC_BAND_UL_FEM_PATH_PARA_STRU;

typedef  UCOM_NV_GUC_BAND_UL_FEM_PATH_PARA_STRU    UCOM_NV_GSM_RF_UL_FEM_PATH_STRU;
typedef  UCOM_NV_GUC_BAND_UL_FEM_PATH_PARA_STRU    UCOM_NV_CDMA_RF_UL_FEM_PATH_STRU;
typedef  UCOM_NV_GUC_BAND_UL_FEM_PATH_PARA_STRU    UCOM_NV_W_UL_FEM_PATH_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RF_EXT_LNA_PATH_STRU
 �ṹ˵��  : ����LNA ���� Path �ܽṹ�����ṹ�嶨�壬����Band�ţ�Path��Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GUC_BAND_EXT_LNA_PATH_PARA_STRU stExtLnaPathPara;
}UCOM_NV_GSM_RF_EXT_LNA_PATH_STRU;

typedef   UCOM_NV_GUC_BAND_EXT_LNA_PATH_PARA_STRU    UCOM_NV_CDMA_RF_EXT_LNA_PATH_STRU;
typedef   UCOM_NV_GUC_BAND_EXT_LNA_PATH_PARA_STRU    UCOM_NV_W_EXT_LNA_PATH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_GUC_RF_RX_CAL_FREQ_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ׼��Ƶ���б�ÿ��BAND���֧��32��Ƶ�㣬��NV����BAND��
*****************************************************************************/
typedef struct
{
    PHY_UINT32                              ulValidCalFreqNum;                      /* ��ҪУ׼��Ƶ����� */
    PHY_UINT32                              aulRxCalFreqList[RF_RX_MAX_FREQ_NUM];   /* RF_RX_FREQ_NUM =32 ,GUTL��λ100KHz,CDMA:1KHz*/

}NV_GUC_RF_RX_CAL_FREQ_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NV_GUC_RF_TX_CAL_FREQ_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ׼��Ƶ���б�ÿ��BAND���֧��32��Ƶ�㣬��NV����BAND��
*****************************************************************************/
typedef struct
{
    PHY_UINT32                          ulValidCalFreqNum;                      /* ��ҪУ׼��Ƶ����� */
    PHY_UINT32                          aulTxCalFreqList[RF_TX_MAX_FREQ_NUM];   /* RF_RX_FREQ_NUM =32 ,GUTL��λ100KHz,CDMA:1KHz*/
}NV_GUC_RF_TX_CAL_FREQ_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NV_RF_TX_CAL_FREQ_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ׼��Ƶ���б�ÿ��BAND���֧��32��Ƶ�㣬��NV����BAND��
*****************************************************************************/
typedef   NV_GUC_RF_TX_CAL_FREQ_LIST_STRU       UCOM_NV_GSM_RF_TX_CAL_FREQ_LIST_STRU;
typedef   NV_GUC_RF_TX_CAL_FREQ_LIST_STRU       UCOM_NV_WCDMA_RF_TX_CAL_FREQ_LIST_STRU;
typedef   NV_GUC_RF_TX_CAL_FREQ_LIST_STRU       UCOM_NV_CDMA_RF_TX_CAL_FREQ_LIST_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RF_RX_CAL_FREQ_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ׼��Ƶ���б�ÿ��BAND���֧��32��Ƶ�㣬��NV����BAND��
*****************************************************************************/
typedef   NV_GUC_RF_RX_CAL_FREQ_LIST_STRU       UCOM_NV_GSM_RF_RX_CAL_FREQ_LIST_STRU;
typedef   NV_GUC_RF_RX_CAL_FREQ_LIST_STRU       UCOM_NV_CDMA_RF_RX_CAL_FREQ_LIST_STRU;
typedef   NV_GUC_RF_RX_CAL_FREQ_LIST_STRU       UCOM_NV_WCDMA_RF_RX_CAL_FREQ_LIST_STRU;


/*****************************************************************************
 �ṹ��    : NV_ALG_RX_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU
 �ṹ˵��  : GSM/WCDMA/CDMA ��AGC�����л�����
*****************************************************************************/
typedef   NV_ALG_RX_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU     UCOM_NV_GSM_ALG_RX_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU;
typedef   NV_ALG_RX_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU     UCOM_NV_CDMA_ALG_RX_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU;
typedef   NV_ALG_RX_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU     UCOM_NV_W_ALG_RX_AGC_THRESHOLD_TABLE_BANK_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_ALG_RX_FAST_AGC_SWITCH_THRESHOLD_TABLE_BANK_STRU
 �ṹ˵��  : GSM��AGC�����л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwBlockInitAgc[AGC_MAX_TABLE_NUM];    /* ���ٲ�����ʼ��λ */
    VOS_UINT16                          auhwNoBlockInitAgc[AGC_MAX_TABLE_NUM];  /* ���ٲ�����ʼ��λ */
    NV_RX_AGC_GAIN_THRESHOLD_STRU       astAgcSwitchTable[AGC_MAX_TABLE_NUM];   /*AGC_MAX_TABLE = 10*/

}UCOM_NV_GSM_ALG_RX_AGC_FAST_SWITCH_THRESHOLD_TABLE_BANK_STRU;

/*****************************************************************************
 �ṹ��    : NV_GUC_RF_RX_AGC_TABLE_USED_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC��TABLE INDEX�����֧��6��PATH��GUCֻ��Ҫʹ��һ��PATH������BAND
*****************************************************************************/
typedef     UCOM_NV_GUC_RX_AGC_TABLE_INFO_STRU      UCOM_NV_GSM_RF_RX_AGC_TABLE_USED_INFO_STRU;
typedef     UCOM_NV_GUC_RX_AGC_TABLE_INFO_STRU      UCOM_NV_CDMA_RF_RX_AGC_TABLE_USED_INFO_STRU;
typedef     UCOM_NV_GUC_RX_AGC_TABLE_INFO_STRU      UCOM_NV_W_RF_RX_AGC_TABLE_USED_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_AGC_CAL_RESULT_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC��У׼���ֵ����������ֵ��Ƶ��ֵ
*****************************************************************************/
typedef UCOM_NV_GUC_RX_AGC_CAL_RESULT_TABLE_STRU   UCOM_NV_GSM_RX_AGC_CAL_RESULT_TABLE_STRU;
typedef UCOM_NV_GUC_RX_AGC_CAL_RESULT_TABLE_STRU   UCOM_NV_CDMA_RX_AGC_CAL_RESULT_TABLE_STRU;
typedef UCOM_NV_GUC_RX_AGC_CAL_RESULT_TABLE_STRU   UCOM_NV_W_RX_AGC_CAL_RESULT_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_PATH_DCOC_CAL_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCOC��У׼���ֵ,����У׼���ֺ�BBP�ϱ��Ĳ���ֱ��ֵ
*****************************************************************************/
typedef     UCOM_NV_GUC_RX_PATH_DCOC_CAL_RESULT_STRU     UCOM_NV_GSM_RX_PATH_DCOC_CAL_RESULT_STRU;
typedef     UCOM_NV_GUC_RX_PATH_DCOC_CAL_RESULT_STRU     UCOM_NV_CDMA_RX_PATH_DCOC_CAL_RESULT_STRU;
typedef     UCOM_NV_GUC_RX_PATH_DCOC_CAL_RESULT_STRU     UCOM_NV_W_RX_PATH_DCOC_CAL_RESULT_STRU;

typedef     NV_RX_DCOC_CAL_RESULT_STRU                   NV_GUC_RX_DCOC_CAL_RESULT_STRU;

typedef     NV_RX_DCOC_COMP_VAlUE_STRU                   NV_GUC_RX_DCOC_COMP_VAlUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_PATH_IP2_CAL_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP2��У׼���ֵ
*****************************************************************************/
typedef NV_RX_PATH_IP2_CAL_RESULT_STRU      UCOM_NV_GSM_RX_PATH_IP2_CAL_RESULT_STRU;
typedef NV_RX_PATH_IP2_CAL_RESULT_STRU      UCOM_NV_CDMA_RX_PATH_IP2_CAL_RESULT_STRU;
typedef NV_RX_PATH_IP2_CAL_RESULT_STRU      UCOM_NV_W_RX_PATH_IP2_CAL_RESULT_STRU;

typedef NV_RX_IP2_CAL_RESULT_STRU           UCOM_NV_W_RX_IP2_CAL_RESULT_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_RF_RX_AGC_RFIC_TABLE_BANK_STRU
 Э����  :
 ö��˵��  : AGC��λ�л�������,boston��֮��ʹ��(��ΪRF�仯)
*****************************************************************************/
typedef NV_RF_RX_AGC_RFIC_TABLE_BANK_STRU   UCOM_NV_G_RF_RX_AGC_RFIC_TABLE_BANK_STRU;
typedef NV_RF_RX_AGC_RFIC_TABLE_BANK_STRU   UCOM_NV_CDMA_RF_RX_AGC_RFIC_TABLE_BANK_STRU;
typedef NV_RF_RX_AGC_RFIC_TABLE_BANK_STRU   UCOM_NV_W_RF_RX_AGC_RFIC_TABLE_BANK_STRU;

/*****************************************************************************
 ö����    : NV_GUC_RF_RX_AGC_GAIN_TABLE_BANK_STRU
 Э����  :
 ö��˵��  : AGC GAIN
*****************************************************************************/
typedef NV_RF_RX_AGC_GAIN_TABLE_BANK_STRU   UCOM_NV_G_RF_RX_AGC_GAIN_TABLE_BANK_STRU;
typedef NV_RF_RX_AGC_GAIN_TABLE_BANK_STRU   UCOM_NV_CDMA_RF_RX_AGC_GAIN_TABLE_BANK_STRU;
typedef NV_RF_RX_AGC_GAIN_TABLE_BANK_STRU   UCOM_NV_W_RF_RX_AGC_GAIN_TABLE_BANK_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RF_RX_RFFE_ILOSS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ǰ�˵Ĳ���ֵ��CDMAֻ��1��PATH��ÿ��PATH���֧��˫�գ�����Band��
*****************************************************************************/
typedef NV_RX_PATH_ILOSS_STRU       UCOM_NV_CDMA_RF_RX_RFFE_ILOSS_STRU;
typedef NV_RX_PATH_ILOSS_STRU       UCOM_NV_W_RF_RX_RFFE_ILOSS_STRU;


typedef NV_RX_AGC_GAIN_DEFAULT_STRU  NV_GUC_RX_AGC_GAIN_DEFAULT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RF_HW_BASIC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC��ABB���ӹ�ϵNV�����RFIC������RFIC��ABB����ͨ����
*****************************************************************************/
typedef  NV_MODEM_RF_HW_BASIC_INFO_STRU    UCOM_NV_GUC_RF_HW_BASIC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_TAS_DPDT_MIPI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :CDMA TAS MIPI �ṹ��
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU                    astTasDpdtThrough[UCOM_NV_CDMA_TAS_MIPI_NUM];    /* ֱͨ */
    PHY_MIPIDEV_UNIT_STRU                    astTasDpdtSwap[UCOM_NV_CDMA_TAS_MIPI_NUM];       /* ���� */
}UCOM_NV_GUC_TAS_DPDT_MIPI_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BAND_BIT_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BAND�Ƿ�֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwBandMask;                             /* bit0Ϊ1��ʾ֧��band1, ���� */
    VOS_UINT32                          uwBandMaskEx;
}UCOM_NV_W_BAND_BIT_MASK_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_FE_FEATURE_BAND_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BAND�Ƿ�֧������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_BAND_BIT_MASK_STRU        stAptOnOffMask;
    UCOM_NV_W_BAND_BIT_MASK_STRU        stEtOnOffMask;
    UCOM_NV_W_BAND_BIT_MASK_STRU        stDpdOnOffMask;

    UCOM_NV_W_BAND_BIT_MASK_STRU        stRslv0Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU        stRslv1Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU        stRslv2Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU        stRslv3Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU        stRslv4Mask;

}UCOM_NV_W_FE_TX_FEATURE_CTRL_STRU;

typedef UCOM_NV_W_FE_TX_FEATURE_CTRL_STRU     UCOM_NV_CDMA_FE_TX_FEATURE_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_FE_RX_FEATURE_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BAND�Ƿ�֧������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_BAND_BIT_MASK_STRU            stRslv0Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU            stRslv1Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU            stRslv2Mask;
    UCOM_NV_W_BAND_BIT_MASK_STRU            stRslv3Mask;

}UCOM_NV_W_FE_RX_FEATURE_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BBP_TX_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W����ʱ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxChanDelay;                         /* ���е�����ʱ���� */
    VOS_UINT16                          uhwTxInitDelay;                         /* ��ǰ������RF��chip����ȡֵ��Χ0~1023������ֵ800us����3072chip */
    VOS_UINT16                          uhwTxOffDelay;                          /* �Ӻ�ر�����RF��chip���� */
    VOS_UINT16                          uhwTxIdleOnDelay;                       /* ��ǰ������RF IDLE״̬��chip����ȡֵ��Χ0~1023������ֵ100us����384chip */
    VOS_UINT16                          uhwTxIdleOffDelay;                      /* �Ӻ�ر�����RF IDLE״̬��chip���� */
    VOS_UINT16                          uhwTxAbbInitDelay;
    VOS_UINT16                          uhwTxAbbOffDelay;
    VOS_UINT16                          shwTxGainOpenTime;                      /* ���з��书����Чʱ�䣬��λchip����ʾ���з��书������ǰ����ʱ϶ͷ���ʱ��������Ƶ������
                                                                                   ������Ƶ��������ʱ��Ϊʹ���з��书��������ʱ϶ͷ����Ч������ǰ�����з��书�ʼ�����������Ƶ���� */
    VOS_UINT16                          uhwEtDataPathIntDelay;                  /* ET����ͨ·������ʱ */

    VOS_UINT16                          uhwTxPaStableTime;                      /* ���书�ʱ仯��RF��PA���ȶ�ʱ�䣬����MRXͨ�����ú���ȶ�ʱ�䣨MRX��������ʱ϶ͷλ�ÿ���������λchip */
    VOS_UINT16                          uhwMrxAbbStableTime;                    /* MRX ABB�߿ؿ����󣬵ȴ�uhwMrxAbbStableTime��������MRX���ʹ��ƣ���λchip */
    VOS_UINT16                          uhwReserved2;
    VOS_UINT16                          uhwReserved3;
    VOS_UINT16                          uhwReserved4;
    VOS_UINT16                          uhwReserved5;
    VOS_UINT16                          uhwReserved6;
    VOS_UINT16                          uhwReserved7;
    VOS_UINT16                          uhwReserved8;
    VOS_UINT16                          uhwReserved9;
    VOS_UINT16                          uhwReserved10;

}UCOM_NV_W_BBP_TX_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_BAND_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W����ʱ����
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU     stPaGainSwichTiming;                /* PA�����л�ʱ�� */
    UCOM_NV_W_MIPI_APT_TIMING_CFG_STRU      stMipiAptTimingInfo;
    VOS_UINT16                              uhwPaOnAdvanceChip;
    VOS_UINT16                              uhwPaOffDelayChip;
    VOS_UINT16                              uhwTxPhaseCompTiming;
    VOS_UINT16                              uhwReserved0;
    VOS_UINT16                              uhwReserved1;
    VOS_UINT16                              uhwReserved2;
    VOS_UINT16                              uhwReserved3;
    VOS_UINT16                              uhwReserved4;
    VOS_UINT16                              uhwReserved5;
    VOS_UINT16                              uhwReserved6;
    VOS_UINT16                              uhwReserved7;
    VOS_UINT16                              uhwReserved8;
}UCOM_NV_W_TX_BAND_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TX_BAND_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����ʱ����
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_PA_GAIN_SWITCH_TIMING_STRU stPaGainSwichTiming;                /* PA�����л�ʱ�� */
    VOS_UINT16                              uhwPaOnAdvanceChip;
    VOS_UINT16                              uhwPaOffDelayChip;
    VOS_UINT16                              uhwAptPaVccTiming;
    VOS_UINT16                              uhwAptTrig1Timing;
    VOS_UINT16                              uhwAptTrig2Timing;
    VOS_UINT16                              uhwReserved0;
    VOS_UINT16                              uhwReserved1;
    VOS_UINT16                              uhwReserved2;
    VOS_UINT16                              uhwReserved3;
    VOS_UINT16                              uhwReserved4;
    VOS_UINT16                              uhwReserved5;
    VOS_UINT16                              uhwReserved6;
    VOS_UINT16                              uhwReserved7;
    VOS_UINT16                              uhwReserved8;
}UCOM_NV_CDMA_TX_BAND_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_UL_CFR_GATE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwDefaultCfrFirstGate;
    VOS_UINT32                              uwDefaultCfrSecondGate;
    VOS_UINT32                              uwDpdCfrFirstGate;
    VOS_UINT32                              uwDpdCfrSecondGate;
}UCOM_NV_W_UL_CFR_GATE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_MAXPOWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxMaxPowerRach;                             /* ����Ƶ�Σ����н�����DPCH�����RACHʱUE�����������书�ʣ���λ0.1dbm;��0��ΪRACH,��1��ΪDPCH, */
    VOS_INT16                                   shwTxMaxPowerDpch;                             /* ����Ƶ�Σ����н�����DPCH�����RACHʱUE�����������书�ʣ���λ0.1dbm;��0��ΪRACH,��1��ΪDPCH, */
    VOS_INT16                                   ashwTxMaxPowerTempComp[UCOM_NV_W_TEMP_NUM];    /* ����书�ʲ������棬��λ0.1dbm;3��Ƶ�Σ�5��Ԥ�ȶ�����¶ȵ�:-20,0,20,40,60,��6�������ڶ��룬��ʹ�� */
}UCOM_NV_WCDMA_TX_MAXPOWER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_MAXPOWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxMinPower;                                  /* UE�������С���书�ʣ���λ0.1dbm;3��Ƶ�Σ�5��Ԥ�ȶ�����¶ȵ�:-20,0,20,40,60,��6�������ڶ��룬��ʹ�� */
    VOS_INT16                                   shwRslv;                                        /* ���� */
    VOS_INT16                                   ashwTxMinPowerTempComp[UCOM_NV_W_TEMP_NUM];     /* ��С���书���¶Ȳ��� */
}UCOM_NV_WCDMA_TX_MINPOWER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_POWER_STANDARD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_WCDMA_TX_MAXPOWER_STRU              stTxWiredMaxPower;              /* ���� */
    UCOM_NV_WCDMA_TX_MAXPOWER_STRU              stTxWirelessMaxPower;           /* ���� */
    UCOM_NV_WCDMA_TX_MINPOWER_STRU              stTxMinPower;
}UCOM_NV_W_TX_POWER_STANDARD_STRU;


/*****************************************************************************
 �ṹ��    : NV_GUC_BAND_UL_DCDC_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCDC���Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDcdcType              :2;             /* 0: PDM, 1:MIPI */
    VOS_UINT32                          uwDcdcPinCtrlEn         :2;             /* �Ƿ�ʹ��DCDC GPIO PIN������ */
    VOS_UINT32                          uwDcdcPinNum            :8;             /* ��Ӧ��PIN�� 0 - 31, FFΪ��Ч */
    VOS_UINT32                          uwDcdcDefaultPdmValue   :8;             /* ��ʹ��APTʱ��PDM��ʽʱ��Ĭ������ֵ��
                                                                                   ʹ�������APT��(�ϲ㲻������ֵ��ȡ��������ʶ�Ӧ��ֵ) */
    VOS_UINT32                          uwRsv0                  :4;             /* ���� */
    VOS_UINT32                          uwRsv1                  :8;             /* ���� */

    PHY_MIPIDEV_UNIT_STRU               astDcdcDefaultMipiWord[UCOM_NV_W_TX_DCDC_MIPI_NUM];              /* ��ʹ��APTʱ��MIPI��ʽʱ��Ĭ������ֵ��
                                                                                   ʹ�������APT��(�ϲ㲻������ֵ��ȡ��������ʶ�Ӧ��ֵ) */

    VOS_UINT32                          uwRsv2;                                 /* ���� */
    VOS_UINT32                          uwRsv3;                                 /* ���� */
    VOS_UINT32                          uwRsv4;                                 /* ���� */
} NV_W_UL_DCDC_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_UL_MIPI_VBIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_CMD_STRU                astVbiasH2ULGain[UCOM_NV_PA_GAIN_NUM_MAX];
}UCOM_NV_W_UL_MIPI_VBIAS_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_UL_DCDC_ET_APT_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    NV_W_UL_DCDC_PARA_STRU              stDcdcPara;
    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptOn[UCOM_NV_ET_MIPI_NUM];    /* MIPI ET/APT On���� */
    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptOff[UCOM_NV_ET_MIPI_NUM];   /* MIPI ET/APT OFF���� */

    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptH[UCOM_NV_ET_MIPI_NUM];     /* MIPI ET/APT����������� UCOM_NV_ET_MIPI_NUM=6 */
    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptM[UCOM_NV_ET_MIPI_NUM];     /* MIPI ET/APT����������� UCOM_NV_ET_MIPI_NUM=6 */
    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptL[UCOM_NV_ET_MIPI_NUM];     /* MIPI ET/APT����������� UCOM_NV_ET_MIPI_NUM=6 */
    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptUL[UCOM_NV_ET_MIPI_NUM];    /* MIPI ET/APT������������� UCOM_NV_ET_MIPI_NUM=6 */

    PHY_MIPIDEV_CMD_STRU                astAptPaVccH2ULGain[UCOM_NV_PA_GAIN_NUM_MAX];
    UCOM_NV_W_UL_MIPI_VBIAS_STRU        astMipiAptPaVbias[UCOM_NV_W_TX_PA_VBIAS_NUM];
    PHY_MIPIDEV_UNIT_STRU               astMipiEtAptTrigger[UCOM_NV_ET_APT_TRIGGER_NUM];
}UCOM_NV_W_UL_DCDC_ET_APT_CFG_STRU;

typedef UCOM_NV_W_UL_DCDC_ET_APT_CFG_STRU     UCOM_NV_CDMA_UL_DCDC_ET_APT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_RX_AGC_FREQ_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ׼��WCDMA��Ƶ��Ƶ��,boston��֮��ʹ��(��ΪRF�仯)
*****************************************************************************/
typedef NV_RX_AGC_FREQ_COMP_CAL_STRU UCOM_NV_WCDMA_RX_AGC_FREQ_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU
 �ṹ˵��  : �ջ�tuner�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwBandSupport;                      /* ��ӦbitΪ1��ʾ���band֧�ֶ�̬���ߵ�г,����֧�� */
    VOS_UINT32                              uwBandExten;                        /* �Ժ�band ID���ܳ���32 */
    VOS_UINT16                              uhwActiveTime;                      /* ���ߵ�г������ǰ֡ͷ�������������д򿪺�WBBPÿ����֡ͷ��ǰcpu_tx_sw_active_time�������ã���λΪchip */
    VOS_UINT16                              uhwSampleTime;                      /* ���ߵ�гƽ��������,Ĭ������Ϊ4 */
    VOS_UINT16                              uhwDelayFrame;                      /* ���һ�ֵ�г��ĵȴ�ʱ�䣬��λ֡ */
    VOS_UINT16                              uhwEchoLossThreshold;               /* ���ߵ�г�ز��������,����0.1dBm */
    VOS_UINT32                              uwForWardGpioWord;                  /* פ�����ǰ������ */
    VOS_UINT32                              uwReverseGpioWord;                  /* פ����ⷴ������ */
    PHY_MIPIDEV_CMD_STRU                    stTunerMipiCmd;                     /* MIPI������ */
    UCOM_NV_W_ANT_TUNER_CODE_STRU           stAntTunerCode;                     /* ���ߵ�г������Ϣ */
} UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_TUNER_CTRL_INFO_STRU
 �ṹ˵��  : ���ߵ�г�Ŀ��ƽṹ��,MIPI��tuner,���Ǽ��ݶ����ͺţ��ṩ���6��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16  enAntTunerMode;                     /* 0:Ӳ����֧�֣�1:֧�ֿ�����2:֧��AP+Sensor, 3:֧�ֶ�̬��г */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16           enAntTunerCtrlType;                 /* ���ߵ�г��ͨ��MIPI���ƻ���GPIO,0��ʾGPIO,1��ʾMIPI */
    PHY_MIPIDEV_UNIT_STRU                   stTunerActiveReg;                   /* tuner�Ĺ�����ʼ�������֣�����һЩ�Ĵ���ֻ��Ҫģʽ��������һ�� */
    PHY_MIPIDEV_UNIT_STRU                   stTunerIdleReg;                     /* ����tunerΪIDLE̬��͹���̬�Ŀ����� */
    UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU    stCloseLoopTunerCtrl;               /* �ջ�tuner���� */
} UCOM_NV_W_ANT_TUNER_CTRL_INFO_STRU;

typedef UCOM_NV_W_ANT_TUNER_CTRL_INFO_STRU UCOM_NV_CDMA_ANT_TUNER_CTRL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_MIPI_INIT_WORD_STRU
 �ṹ˵��  : ������ģ��ʼ������,��ʼ��mipi�����Ľӿ�
*****************************************************************************/
typedef struct
{
   PHY_MIPIDEV_UNIT_STRU        astMipiInitWord[UCOM_NV_GUC_MIPI_INIT_UNIT_MAX_NUM];

}UCOM_NV_GUC_MIPI_INIT_WORD_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_REDUCE_CURRENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwReduceCurrentEn;                     /* ��������ʹ�� */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16       enCtrlMode;                             /* ���Ʒ�ʽMIPI��GPIO */
    VOS_UINT32                          uwGpioMask;                             /* ��������ʹ�õĹܽ� */
    PHY_MIPIDEV_UNIT_STRU               stDefaultMipiData;                      /* �ں�����������Ӧ��PMU��ַ��ȱʡʱ�ĵ���ֵ(��һ��ʱ϶), */
    PHY_MIPIDEV_UNIT_STRU               stLimitMipiData;                        /* �ں�����������Ӧ��PMU��ַ��ȱʡʱ�ĵ���ֵ(��һ��ʱ϶) */
}UCOM_NV_GSM_REDUCE_CURRENT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MIPI_INIT_WORD_STRU
 �ṹ˵��  : ������ģ��ʼ������,��ʼ��mipi�����Ľӿ�
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU                   astMipiInitWord[UCOM_NV_W_MIPI_INIT_WORD_NUM];
}UCOM_NV_W_MIPI_INIT_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_MIPI_COMM_STRU
 Э����  :
 �ṹ˵��  : ����һЩmipi���ܹ���ָ���
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU                   astMipiWord[UCOM_NV_MIPI_COMM_NUM];
}UCOM_NV_MIPI_COMM_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ET_MIPI_WORD_STRU
 Э����  :
 �ṹ˵��  : ����һЩmipi���ܹ���ָ���
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU                   astMipiWord[UCOM_NV_ET_MIPI_MAX_NUM];
}UCOM_NV_ET_MIPI_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_DPD_SELF_CAL_FE_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_ET_DPD_MRX_CFG_STRU       stMrxCfgInfo;                           /* ET ��DPDУ׼ʱ��MRX���ò��� */
    UCOM_NV_ET_MIPI_WORD_STRU           stEtDpdCalMipiCfg;                      /* ET ��DPDУ׼ʱ��ET����������Ҫ���� */
}UCOM_NV_W_ET_DPD_SELF_CAL_FE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RFFE_MIPI_ET_CTRL_STRU
 Э����  :
 �ṹ˵��  : Et��MIPIָ��
*****************************************************************************/

typedef struct
{
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtOn;                         /* ET������mipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtOff;                        /* ET�����ر�mipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtMode;                       /* ET��������ΪET ģʽmipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiMAptMode;                     /* ET��������ΪM APT ģʽmipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiLAptMode;                     /* ET��������ΪL APT ģʽmipi������ */
}UCOM_NV_W_RFFE_MIPI_ET_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_SELF_CAL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDpdBackOffPower;                          /* DPD��У׼�����е������ʻ���ֵ����λ0.1dB */
    VOS_UINT16                          auhwDpdLinearGainIndex[UCOM_NV_BBP_DPD_LUT_MAX_NUM];  /* DPD��У׼�����ж�Ӧÿ��DPD�������gain index,��Чֵ0-63���㷨�Ƽ�8����PA�й� */
    UCOM_NV_W_ET_DPD_MRX_CFG_STRU       stDpdMrxCfg;                             /* ET ��DPDУ׼ʱ��MRX���ò��� */
    UCOM_NV_MIPI_COMM_STRU              stMipiReserved;                         /* ET ��DPDУ׼ʱ��ET����������Ҫ���� */
}UCOM_NV_W_DPD_SELF_CAL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_LUT_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD LUT ��������ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSinToneFreqTableMode;                /* Sine������ѡ��0:1.92M����,1:1.92M�����,
                                                                                2:0.96M����,3:0.96M�����,4:0.48M����,5:0.48M����� */
    VOS_UINT16                          uhwDpdAlgSel;                           /* DPD�㷨ѡ�� */
    VOS_UINT16                          uhwPaGainCorrectFactor;                 /* LUT��һ�����ֵ */
    VOS_UINT16                          uhwProtectIndex;                        /* LUT��������ֵ */
    VOS_UINT16                          uhwDpdAveSwitch;                        /* LUT��ƽ���㷨���� */
    VOS_UINT16                          uhwDpdAveLength;                        /* LUT��ƽ���㷨ƽ������  */
}UCOM_NV_W_DPD_LUT_CAL_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD ����ز���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_LUT_CAL_PARA_STRU                          stDpdLutCalPara;   /* DPD LUT ��������ز��� */
    UCOM_NV_W_DPD_SELF_CAL_INFO_STRU                         stDpdSelfCalPara;
}UCOM_NV_W_DPD_CAL_PARA_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_MIPI_INIT_WORD_STRU
 �ṹ˵��  : ������ģ��ʼ������,��ʼ��mipi�����Ľӿ�
*****************************************************************************/
typedef struct
{
   PHY_MIPIDEV_UNIT_STRU        astMipiInitWord[ UCOM_NV_G_MIPI_INIT_UNIT_MAX_NUM ];

}UCOM_NV_GSM_MIPI_INIT_WORD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_CLOSE_MIPI_PA_VCC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : close vcc control
*****************************************************************************/
typedef struct
{
  PHY_MIPIDEV_UNIT_STRU   astMipiClosePaVcc[UCOM_NV_G_PAVCC_MIPI_UNIT_MAX_NUM];
}UCOM_NV_GSM_CLOSE_MIPI_PA_VCC_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_PA_VCC_MIPI_CMD_FRAME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��PaVcc��mipiָ��֡
*****************************************************************************/
typedef struct
{
    PHY_MIPIDEV_UNIT_STRU               astMipiPaVcc[UCOM_NV_G_PAVCC_MIPI_UNIT_MAX_NUM];
}UCOM_NV_G_PA_VCC_MIPI_CMD_FRAME_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_TUNER_CTRL_INFO_STRU
 �ṹ˵��  : ���ߵ�г�Ŀ��ƽṹ��,MIPI��tuner,���Ǽ��ݶ����ͺţ��ṩ���6��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16  enAntTunerMode;                     /* Ӳ���Ƿ�֧�����ߵ�г��0��֧�֣�1֧�� */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16           enAntTunerCtrlType;                 /* ���ߵ�г��ͨ��MIPI���ƻ���GPIO,0��ʾGPIO,1��ʾMIPI */
    UCOM_NV_GSM_TUNER_GPIO_MASK_STRU        stTunerGpioMask;
    PHY_MIPIDEV_UNIT_STRU                   astTunerActiveReg[UCOM_NV_G_TUNER_MIPI_UNIT_MAX_NUM];  /* tuner�Ĺ�����ʼ�������֣�����һЩ�Ĵ���ֻ��Ҫģʽ��������һ�� */
    PHY_MIPIDEV_UNIT_STRU                   astTunerIdleReg[UCOM_NV_G_TUNER_MIPI_UNIT_MAX_NUM];    /* ����tunerΪIDLE̬��͹���̬�Ŀ����� */
} UCOM_NV_G_ANT_TUNER_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_NOTCH_CHAN_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߿����˲���ͨ���Ŀ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwNotchSupportFlag;                /* DCS1800 TX NOTCH����֧�ֱ�־��1��ʾ֧�֣�0��ʾ��֧�� */
    VOS_UINT16                              uhwNotchControlMode;                /* NOTCH���Ʒ�ʽ:1��ʾGPIOģʽ��2��ʾMipi��ʽ��3��ʾGPIO+MIPI��Ϸ�ʽ */
    VOS_UINT32                              uwNotchGpioSetValue;                /* Nothc GPIO����ֵ��uhwNotchControlMode=1����3ʱ��Ч */
    VOS_UINT32                              uwNotchGpioDefaultValue;            /* Nothc GPIO����ֵ��uhwNotchControlMode=1����3ʱ��Ч */
    PHY_MIPIDEV_UNIT_STRU                   astNotchMipiNew[UCOM_NV_G_NOTCH_MIPI_UNIT_MAX_NUM]; /* ����NOTCHͨ��MIPI�ӿڿ��Ƶ�ַ */
    UCOM_NV_GSM_NOTCH_POWER_COMP_STRU       stNotchPowerComp;                   /* Notch���书�ʲ��� */

 }UCOM_NV_GSM_NOTCH_CHAN_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RF_RFIC_INIT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC��ʼ���Ĵ���
*****************************************************************************/
typedef   NV_MODEM_RF_RFIC_INIT_STRU       UCOM_NV_GUC_RF_RFIC_INIT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TEMP_DEFINE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :�¶ȱ���
*****************************************************************************/
typedef   NV_MODEM_TEMP_DEFINE_STRU        UCOM_NV_GUC_TEMP_DEFINE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :����Ƶ����¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulFreq;                              /* ��ǰƵ��,GUTL��λ��100KHz,Cģ��λ��KHz*/
    VOS_INT8                                acTempCompValue[MAX_TEMP_DEFINE_NUM];/* TX���²���λ0.1dB��RX���²���λ0.125dB */
}UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TEMP_COMP_SINGEL_LEVEL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��PA GAIN��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqNum;                           /* Ƶ�����,ĿǰGUC���֧��3��Ƶ�� */
    VOS_UINT16                             usRsv;
    UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU    astTempComp[UCOM_NV_TRX_TEMP_COMP_FREQ_NUM];
}UCOM_NV_TEMP_COMP_SINGEL_LEVEL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUC_RF_RFIC_INIT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 4��PA GAIN��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_COMP_SINGEL_LEVEL_STRU    astTxTempComp[UCOM_NV_PA_GAIN_MAX_NUM];/* 0--������,1--������,2--������,3--�������� */
}UCOM_NV_GUC_TX_TEMP_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RX_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :RX AGC��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqNum;                           /* Ƶ����� */
    VOS_UINT16                             usRsv;
    UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU    astTempComp[UCOM_NV_TRX_TEMP_COMP_FREQ_NUM];
}UCOM_NV_GUC_RX_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_MRX_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MRX��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqNum;                           /* Ƶ����� */
    VOS_UINT16                             usRsv;
    UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU    astTempComp[UCOM_NV_TRX_TEMP_COMP_FREQ_NUM];
}UCOM_NV_GUC_MRX_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_APT_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APT/ET��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqNum;                           /* Ƶ����� */
    VOS_UINT16                             usRsv;
    UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU    astTempComp[UCOM_NV_W_APT_FREQ_COMP_NUM];
}UCOM_NV_GUC_APT_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DPD_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqNum;                           /* Ƶ����� */
    VOS_UINT16                             usRsv;
    UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU    astTempComp[UCOM_NV_W_DPD_FREQ_COMP_NUM];
}UCOM_NV_GUC_DPD_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ET_TIMEDELAY_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET TIME DELAY��Ӧ���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqNum;                           /* Ƶ����� */
    VOS_UINT16                             usRsv;
    UCOM_NV_TEMP_COMP_SINGLE_FREQ_STRU    astTempComp[UCOM_NV_ET_DELAY_TEMP_COMP_MAX_NUM];
}UCOM_NV_GUC_ET_TIME_DELAY_TEMP_COMP_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of phyNvDefine_Boston */

