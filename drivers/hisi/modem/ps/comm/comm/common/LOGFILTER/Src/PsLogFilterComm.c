

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PsLogFilterInterface.h"
#include "PsLib.h"


#define    THIS_FILE_ID        PS_FILE_ID_LOG_FILTER_COMM_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/


/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgMatchFuncCommReg
 ��������  : A C��ע��MsgMatch�ص��ӿ�
 �������  : ��Ҫע���MsgMatchFunc����:
                PS_OM_LAYER_MSG_MATCH_PFUNC         pFunc,
             ��¼ע���MsgMatchFunc�ĸ�����ÿע��һ��+1:
                VOS_UINT32                         *pulRegCnt,
             �洢MsgMatchFunc����������:
                PS_OM_LAYER_MSG_MATCH_PFUNC         apfuncMatchEntry[],
             �洢MsgMatchFunc������������������:
                VOS_UINT32                          ulMsgMatchItemMaxCnt
��������ص��ӿڹ���:
             1.���ע��ص��ڲ�û�ж���Ϣ���д�������Ҫ�����ָ�뷵�أ�����
               ��ģ�鲻֪���Ƿ���Ҫ������Ϣ���ݸ���һ��ע��ص����д���
             2.���ע��ص��ڲ�����Ϣ�����˴����򷵻�ֵ�ܹ�ʵ����������:
               �ٷ���VOS_NULL���򽫴���Ϣ������ȫ���ˣ������ٹ�ȡ����
               �ڷ��������ָ�벻ͬ����һ��ָ�룬��ȡ����Ϣ����ʹ�÷��ص�ָ
                 �������滻ԭ��Ϣ�����ݡ���ģ�鲻������滻���ڴ�����ͷţ�
                 �滻ԭ��Ϣʹ�õ��ڴ����ģ�����й���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgMatchFuncCommReg
(
    PS_OM_LAYER_MSG_MATCH_PFUNC         pFunc,
    VOS_UINT32                         *pulRegCnt,
    PS_OM_LAYER_MSG_MATCH_PFUNC        *apfuncMatchEntry,
    VOS_UINT32                          ulMsgMatchItemMaxCnt
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMaxLoop;

    if ((VOS_NULL_PTR == pFunc)
        || (VOS_NULL_PTR == pulRegCnt)
        || (VOS_NULL_PTR == apfuncMatchEntry))
    {
        return VOS_ERR;
    }

    ulIndex     = *pulRegCnt;
    ulMaxLoop   = PS_MIN(ulIndex, ulMsgMatchItemMaxCnt);

    for (ulLoop = 0; ulLoop < ulMaxLoop; ulLoop++)
    {
        if (apfuncMatchEntry[ulLoop] == pFunc)
        {
            return VOS_OK;
        }
    }

    if (ulMsgMatchItemMaxCnt > ulIndex)
    {
       *pulRegCnt   += 1;
        apfuncMatchEntry[ulIndex] = pFunc;

        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgCommMatch
 ��������  : A C�˲����Ϣ�滻�ӿ�
 �������  : ��Ҫ�������Ϣ:
                VOS_VOID                           *pMsg,
             ��¼�Ѿ�ע���MsgMatchFunc�ĸ���:
                VOS_UINT32                          ulRegCnt,
             ��¼�Ѿ�ע���MsgMatchFunc������:
                PS_OM_LAYER_MSG_MATCH_PFUNC         apfuncMatchEntry[],
             �洢MsgMatchFunc������������������:
                VOS_UINT32                          ulMsgMatchItemMaxCnt
 �������  : ��
 �� �� ֵ  : VOS_VOID*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��14��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID* PS_OM_LayerMsgCommMatch
(
    VOS_VOID                           *pMsg,
    VOS_UINT32                          ulRegCnt,
    PS_OM_LAYER_MSG_MATCH_PFUNC        *apfuncMatchEntry,
    VOS_UINT32                          ulMsgMatchItemMaxCnt
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulEntryCnt;
    VOS_VOID                           *pResult    = pMsg;

    ulEntryCnt      = PS_MIN(ulRegCnt, ulMsgMatchItemMaxCnt);

    for (ulIndex = 0; ulIndex < ulEntryCnt; ulIndex++)
    {
        if (VOS_NULL != apfuncMatchEntry[ulIndex])
        {
            pResult = apfuncMatchEntry[ulIndex]((MsgBlock*)pMsg);
            if (pMsg != pResult)
            {
                break;
            }
        }
    }

    return pResult;
}


/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgFilterFuncReg
 ��������  : A��C ��ע��MsgMatch�ص��ӿ�
 �������  :��Ҫע���MsgFilterFunc����:
                PS_OM_LAYER_MSG_FILTER_PFUNC         pFunc,
            ��¼�Ѿ�ע���MsgFilterFunc�ĸ���:
                VOS_UINT32                          *pulRegCnt,
            ��¼�Ѿ�ע���MsgFilterFunc������:
                PS_OM_LAYER_MSG_FILTER_PFUNC         apfuncFilterEntry[],
            �洢MsgFilterFunc������������������:
                VOS_UINT32                           ulMsgFilterItemMaxCnt
            ��������ص��ӿڹ���:
             1.���ע��ص��ڲ�û�ж���Ϣ���д�������VOS_FALSE������
               ��ģ�鲻֪���Ƿ���Ҫ������Ϣ���ݸ���һ��ע��ص����д���
             2.���ע��ص��ڲ�����Ϣ�����˴�������VOS_TRUE��ʾ����Ϣ
               ��Ҫ���й��ˡ�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2016��11��3��
    ��    ��   : z00383822
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgFilterFuncCommReg
(
    PS_OM_LAYER_MSG_FILTER_PFUNC         pFunc,
    VOS_UINT32                          *pulRegCnt,
    PS_OM_LAYER_MSG_FILTER_PFUNC        *apfuncFilterEntry,
    VOS_UINT32                           ulMsgFilterItemMaxCnt
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMaxLoop;

    if ((VOS_NULL_PTR == pFunc)
        || (VOS_NULL_PTR == pulRegCnt)
        || (VOS_NULL_PTR == apfuncFilterEntry))
    {
        return VOS_ERR;
    }

    ulIndex     = *pulRegCnt;
    ulMaxLoop   = PS_MIN(ulIndex, ulMsgFilterItemMaxCnt);

    for (ulLoop = 0; ulLoop < ulMaxLoop; ulLoop++)
    {
        if (apfuncFilterEntry[ulLoop] == pFunc)
        {
            return VOS_OK;
        }
    }

    if (ulIndex < ulMsgFilterItemMaxCnt)
    {
        *pulRegCnt   += 1;
        apfuncFilterEntry[ulIndex] = pFunc;

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PS_OM_LayerMsgCommFilter
 ��������  : A��C �˲����Ϣ���˽ӿ�
 �������  : ��Ҫ�������Ϣ:
                const VOS_VOID                     *pMsg,
             ��¼�Ѿ�ע���MsgFilterFunc�ĸ���:
                VOS_UINT32                          ulRegCnt,
             ��¼�Ѿ�ע���MsgFilterFunc������:
                PS_OM_LAYER_MSG_MATCH_PFUNC         apfuncFilterEntry[],
             �洢MsgFilterFunc������������������:
                VOS_UINT32                          ulCount
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
VOS_UINT32 PS_OM_LayerMsgCommFilter
(
    const VOS_VOID                     *pMsg,
    VOS_UINT32                          ulRegCnt,
    PS_OM_LAYER_MSG_FILTER_PFUNC       *apfuncFilterEntry,
    VOS_UINT32                          ulMsgFilterItemMaxCnt
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulEntryCnt;
    VOS_UINT32                          ulResult    = VOS_FALSE;

    ulEntryCnt      = PS_MIN(ulRegCnt, ulMsgFilterItemMaxCnt);

    for (ulIndex = 0; ulIndex < ulEntryCnt; ulIndex++)
    {
        if (VOS_NULL != apfuncFilterEntry[ulIndex])
        {
            ulResult = apfuncFilterEntry[ulIndex](pMsg);
            if (VOS_FALSE != ulResult)
            {
                break;
            }
        }
    }

    return ulResult;

}


