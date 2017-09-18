

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PsAcpuLogFilter.h"
#include "PsLogFilterComm.h"
#include "msp_diag_comm.h"


#define    THIS_FILE_ID        PS_FILE_ID_ACPU_LOG_FILTER_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

/*****************************************************************************
 ��������  : ���ݶ���Ŀ�ע����˺�������������ȫ�ֱ������г�ʼ������
 �޸���ʷ      :
  1.��    ��   : 2016��9��5��
    ��    ��   : z00383822
    �޸�����   : ����ȫ�ֱ���

*****************************************************************************/
PS_OM_ACPU_LAYER_MSG_FILTER_CTRL_STRU        g_stAcpuLayerMsgFilterCtrl =
    {0, {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR}};
PS_OM_ACPU_LAYER_MSG_MATCH_CTRL_STRU         g_stAcpuLayerMsgMatchCtrl  =
    {0, {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR}};

/******************************************************************************
   5 ����ʵ��
******************************************************************************/


/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgMatch_Acpu
 ��������  : A�˲����Ϣ�滻�ӿ�
 �������  : VOS_VOID                           *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��14��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID* PS_OM_LayerMsgMatch_Acpu
(
    VOS_VOID                           *pMsg
)
{
    VOS_VOID                           *pResult;

    pResult = PS_OM_LayerMsgCommMatch(pMsg,
                        g_stAcpuLayerMsgMatchCtrl.ulRegCnt,
                        g_stAcpuLayerMsgMatchCtrl.apfuncMatchEntry, 
                        PS_OM_ACPU_LAYER_MSG_MATCH_ITEM_MAX_CNT);
    return pResult;
}

/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgFilter_Acpu
 ��������  : A�˲����Ϣ���˽ӿ�
 �������  : const VOID *pMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:
                ����VOS_TRUE:  ��ʾ����Ϣ��Ҫ���й���
                ����VOS_FALSE: ��ʾ����Ϣ������й���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgFilter_Acpu
(
    const VOS_VOID                     *pMsg
)
{  
    VOS_UINT32                          ulResult;
 
    ulResult = PS_OM_LayerMsgCommFilter(pMsg, 
                    g_stAcpuLayerMsgFilterCtrl.ulRegCnt, 
                    g_stAcpuLayerMsgFilterCtrl.apfuncFilterEntry, 
                    PS_OM_ACPU_LAYER_MSG_FILTER_ITEM_MAX_CNT);
    return ulResult;    
}

/* ��ֹPC���̱�������к������ض��� */
/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgMatchInit
 ��������  : ������DIAG�������ע��Ĺ�����LOG�滻����
             (��������A��������ע�ᣬ�����滻A���ڲ������Ϣ)
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_OM_LayerMsgMatchInit(VOS_VOID)
{
    (VOS_VOID)DIAG_TraceMatchFuncReg(PS_OM_LayerMsgMatch_Acpu);

    return;
}

/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgMatchFuncReg
 ��������  : ע��MsgMatch�ص��ӿ�
 �������  : PS_OM_LAYER_MSG_MATCH_PFUNC          pFunc
 �������  : ��
 ��������ص��ӿڹ���:
             1.���ע��ص��ڲ�û�ж���Ϣ���д�������Ҫ�����ָ�뷵�أ�����
               ��ģ�鲻֪���Ƿ���Ҫ������Ϣ���ݸ���һ��ע��ص����д���
             2.���ע��ص��ڲ�����Ϣ�����˴����򷵻�ֵ�ܹ�ʵ����������:
               �ٷ���VOS_NULL���򽫴���Ϣ������ȫ���ˣ������ٹ�ȡ����
               �ڷ��������ָ�벻ͬ����һ��ָ�룬��ȡ����Ϣ����ʹ�÷��ص�ָ
                 �������滻ԭ��Ϣ�����ݡ���ģ�鲻������滻���ڴ�����ͷţ�
                 �滻ԭ��Ϣʹ�õ��ڴ����ģ�����й���
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgMatchFuncReg
(
    PS_OM_LAYER_MSG_MATCH_PFUNC         pFunc
)
{
    VOS_UINT32                          ulResult;
          
    ulResult = PS_OM_LayerMsgMatchFuncCommReg(pFunc,
                    &(g_stAcpuLayerMsgMatchCtrl.ulRegCnt),
                    g_stAcpuLayerMsgMatchCtrl.apfuncMatchEntry,
                    PS_OM_ACPU_LAYER_MSG_MATCH_ITEM_MAX_CNT);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgFilterInit
 ��������  : ������DIAG�������ע��Ĺ�����LOG���˺���
             (��������A��������ע�ᣬ���ڹ���A���ڲ������Ϣ)
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_OM_LayerMsgFilterInit(VOS_VOID)
{
   (VOS_VOID)DIAG_TraceFilterFuncReg(PS_OM_LayerMsgFilter_Acpu);

    return;
}

/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgFilterFuncReg
 ��������  : ע��MsgMatch�ص��ӿ�
 ��������ص��ӿڹ���:
             1.���ע��ص��ڲ�û�ж���Ϣ���д�������VOS_FALSE������
               ��ģ�鲻֪���Ƿ���Ҫ������Ϣ���ݸ���һ��ע��ص����д���
             2.���ע��ص��ڲ�����Ϣ�����˴�������VOS_TRUE��ʾ����Ϣ
               ��Ҫ���й��ˡ�
 �������  : PS_OM_ACPU_LAYER_MSG_FILTER_PFUNC          pFunc
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgFilterFuncReg
(
    PS_OM_LAYER_MSG_FILTER_PFUNC        pFunc
)
{
    VOS_UINT32                          ulResult;
    
    ulResult = PS_OM_LayerMsgFilterFuncCommReg(pFunc,
                    &(g_stAcpuLayerMsgFilterCtrl.ulRegCnt),
                    g_stAcpuLayerMsgFilterCtrl.apfuncFilterEntry,
                    PS_OM_ACPU_LAYER_MSG_FILTER_ITEM_MAX_CNT);
    return ulResult;
}


