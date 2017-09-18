/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_11k.c
  �� �� ��   : ����
  ��    ��   : y00196452
  ��������   : 2016��5��4��
  ����޸�   :
  ��������   : 11k Radio Resource Measurement���ܴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��5��4��
    ��    ��   : y00196452
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_11K

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_net.h"
#include "mac_frame.h"
#include "mac_resource.h"
#include "mac_ie.h"
#include "mac_vap.h"
#include "mac_user.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_resource.h"
#include "wlan_types.h"
#include "dmac_main.h"
#include "dmac_ext_if.h"
#include "dmac_chan_mgmt.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_scan.h"
#include "dmac_11k.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_11K_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_rrm_exit_quiet
 ��������  : �˳�Quietģʽ���ָ�Ӳ�����͹���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_exit_quiet(oal_void *para)
{
    dmac_vap_stru       *pst_dmac_vap;
    mac_rrm_info_stru   *pst_rrm_info;

    pst_dmac_vap = (dmac_vap_stru *)para;
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_exit_quiet::pst_dmac_vap null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    dmac_chan_enable_machw_tx(&pst_dmac_vap->st_vap_base_info);

    if (pst_rrm_info->uc_quiet_period)
    {
        pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_PRD_DEC;
    }
    else
    {
        pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_IDLE;
        if (pst_rrm_info->st_quiet_timer.en_is_registerd)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_rrm_info->st_quiet_timer);
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_enter_quiet
 ��������  : ����Quietģʽ���ر�Ӳ�����͹���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_enter_quiet(oal_void *para)
{
    mac_device_stru         *pst_mac_device;
    dmac_vap_stru           *pst_dmac_vap;
    mac_rrm_info_stru       *pst_rrm_info;

    pst_dmac_vap = (dmac_vap_stru *)para;
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_enter_quiet::pst_dmac_vap null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_enter_quiet::dev null, dev id[%d].}", pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    dmac_chan_disable_machw_tx(&(pst_dmac_vap->st_vap_base_info));
    if (0 == pst_rrm_info->uc_quiet_period && pst_rrm_info->st_quiet_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_rrm_info->st_quiet_timer);
    }

    pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_QUIET;
    FRW_TIMER_CREATE_TIMER(&pst_rrm_info->st_quiet_timer,
                               dmac_rrm_exit_quiet,
                               pst_rrm_info->us_quiet_duration,
                               pst_dmac_vap,
                               OAL_FALSE,
                               OAM_MODULE_ID_DMAC,
                               pst_mac_device->ul_core_id);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_handle_quiet
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_handle_quiet(dmac_vap_stru  *pst_dmac_vap)
{
    OAL_STATIC oal_uint8        uc_count = 0;
    OAL_STATIC oal_uint32       ul_tbtt_timer = 0;
    mac_device_stru             *pst_mac_device;
    mac_rrm_info_stru           *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_handle_quiet::pst_dmac_vap null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_handle_quiet::dev null, dev id[%d].}", pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    switch(pst_rrm_info->en_quiet_state)
    {
        case MAC_QUIET_STATE_INIT:
        case MAC_QUIET_STATE_IDLE:
            break;
        case MAC_QUIET_STATE_START:
            uc_count = pst_rrm_info->uc_quiet_count;
            ul_tbtt_timer = 0;
            if (pst_rrm_info->st_quiet_timer.en_is_registerd)
            {
                FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_rrm_info->st_quiet_timer);
            }

            if (0 != uc_count)
            {
                uc_count--;
                pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_COUNT;
            }
            else
            {
                if (pst_rrm_info->us_quiet_offset)
                {
                    FRW_TIMER_CREATE_TIMER(&pst_rrm_info->st_quiet_timer,
                           dmac_rrm_enter_quiet,
                           pst_rrm_info->us_quiet_offset,
                           pst_dmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_device->ul_core_id);
                    pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_OFFSET;
                }
                else
                {
                    dmac_rrm_enter_quiet((oal_void *)pst_dmac_vap);
                }
            }

            if (pst_rrm_info->uc_quiet_period)
            {
                ul_tbtt_timer++;
            }
            break;
        case MAC_QUIET_STATE_COUNT:
            if (0 != uc_count)
            {
                uc_count--;
                pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_COUNT;
            }
            else
            {
                if (pst_rrm_info->us_quiet_offset)
                {
                    FRW_TIMER_CREATE_TIMER(&pst_rrm_info->st_quiet_timer,
                           dmac_rrm_enter_quiet,
                           pst_rrm_info->us_quiet_offset,
                           pst_dmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_device->ul_core_id);
                    pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_OFFSET;
                }
                else
                {
                    dmac_rrm_enter_quiet((oal_void *)pst_dmac_vap);
                }
            }
            break;
        case MAC_QUIET_STATE_PRD_DEC:
            if(0 == (ul_tbtt_timer % pst_rrm_info->uc_quiet_period))
            {
                if (pst_rrm_info->us_quiet_offset)
                {
                    FRW_TIMER_CREATE_TIMER(&pst_rrm_info->st_quiet_timer,
                           dmac_rrm_enter_quiet,
                           pst_rrm_info->us_quiet_offset,
                           pst_dmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_device->ul_core_id);
                }
                else
                {
                    dmac_rrm_enter_quiet(pst_dmac_vap);
                }
                ul_tbtt_timer = 0;
            }
            else
            {
                ul_tbtt_timer++;
            }
            break;
        default:
            break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_parse_quiet
 ��������  : ����Quiet IE����¼֡���ݣ������б仯ʱ����Quiet����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_parse_quiet(dmac_vap_stru  *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_uint16                   us_frame_len;
    oal_bool_enum_uint8          en_is_update = OAL_FALSE;
    dmac_rx_ctl_stru            *pst_rx_ctrl;
    mac_rx_ctl_stru             *pst_rx_info;
    oal_uint8                   *puc_payload;
    mac_rrm_info_stru           *pst_rrm_info;
    mac_quiet_frm_stru          *pst_quiet_info;

    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    us_frame_len        = pst_rx_info->us_frame_len - pst_rx_info->bit_mac_header_len; /* ֡�峤�� */
    puc_payload         = OAL_NETBUF_PAYLOAD(pst_netbuf);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_parse_quiet::pst_dmac_vap null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    /* Quiet IE */
    pst_quiet_info = (mac_quiet_frm_stru *)mac_find_ie(MAC_EID_QUIET, puc_payload + MAC_DEVICE_BEACON_OFFSET, us_frame_len - MAC_DEVICE_BEACON_OFFSET);
    if (OAL_PTR_NULL == pst_quiet_info)
    {
        pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_IDLE;
        return OAL_ERR_CODE_PTR_NULL;
    }

    /***************************************************************************/
    /*                   Quiet IE                                              */
    /* ----------------------------------------------------------------------- */
    /* |Element ID|length|Quiet Count|Quiet Period|Quiet Duration|Quiet Offset|*/
    /* ----------------------------------------------------------------------- */
    /* |1         |1     |1          |1           |2             |2           |*/
    /* ----------------------------------------------------------------------- */
    /***************************************************************************/
    if (MAC_QUIET_IE_LEN != pst_quiet_info->uc_len)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RRM, "{dmac_rrm_parse_quiet::illegal quiet IE len[%d].", pst_quiet_info->uc_len);
        return OAL_FAIL;
    }

    if (pst_rrm_info->uc_quiet_count != pst_quiet_info->uc_quiet_count)
    {
        pst_rrm_info->uc_quiet_count = pst_quiet_info->uc_quiet_count;
        en_is_update = OAL_TRUE;
    }

    if (pst_rrm_info->uc_quiet_period != pst_quiet_info->uc_quiet_period)
    {
        pst_rrm_info->uc_quiet_period = pst_quiet_info->uc_quiet_period;
        en_is_update = OAL_TRUE;
    }

    if (pst_rrm_info->us_quiet_duration != pst_quiet_info->us_quiet_duration)
    {
        pst_rrm_info->us_quiet_duration = pst_quiet_info->us_quiet_duration;
        en_is_update = OAL_TRUE;
    }

    if (pst_rrm_info->us_quiet_offset != pst_quiet_info->us_quiet_offset)
    {
        pst_rrm_info->us_quiet_offset = pst_quiet_info->us_quiet_offset;
        en_is_update = OAL_TRUE;
    }

    if(en_is_update)
    {
        pst_rrm_info->en_quiet_state = MAC_QUIET_STATE_START;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_proc_pwr_constraint
 ��������  : ���ݹ���Լ���������������͵������ֵ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_proc_pwr_constraint(dmac_vap_stru  *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_uint16                   us_frame_len;
    oal_uint8                    uc_max_tx_pwr;
    OAL_STATIC oal_uint8         uc_local_pwr_constraint = 0;
    oal_uint8                   *puc_payload;
    dmac_rx_ctl_stru            *pst_rx_ctrl;
    mac_rx_ctl_stru             *pst_rx_info;
    mac_regclass_info_stru      *pst_regdom_info;
    mac_pwr_constraint_frm_stru *pst_pwr_constraint;

    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    us_frame_len        = pst_rx_info->us_frame_len - pst_rx_info->bit_mac_header_len; /* ֡�峤�� */
    puc_payload         = OAL_NETBUF_PAYLOAD(pst_netbuf);

    /* Power Constraint IE */
    pst_pwr_constraint = (mac_pwr_constraint_frm_stru *)mac_find_ie(MAC_EID_PWRCNSTR, puc_payload + MAC_DEVICE_BEACON_OFFSET, us_frame_len - MAC_DEVICE_BEACON_OFFSET);
    if (OAL_PTR_NULL == pst_pwr_constraint)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*************************************************************************/
    /*                   Power Constraint IE                                 */
    /* --------------------------------------------------------------------- */
    /* |Element ID         |   length            |Local Power Constraint    |*/
    /* --------------------------------------------------------------------- */
    /* |1                  |1                    |1                         |*/
    /* --------------------------------------------------------------------- */
    /*************************************************************************/
    if (MAC_PWR_CONSTRAINT_LEN != pst_pwr_constraint->uc_len)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RRM, "{dmac_rrm_proc_pwr_constraint::illegal pwr constraint IE len[%d].", pst_pwr_constraint->uc_len);
        return OAL_FAIL;
    }

    /* ֵ�仯ʱ�����ñ�������� */
    if (uc_local_pwr_constraint != pst_pwr_constraint->uc_local_pwr_constraint)
    {
        uc_local_pwr_constraint = pst_pwr_constraint->uc_local_pwr_constraint;

        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_parse_quiet::pst_dmac_vap null.");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* ���ù�����������Կ���TPC���������*/
        pst_regdom_info = mac_get_channel_num_rc_info(pst_dmac_vap->st_vap_base_info.st_channel.en_band, pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number);
        if (OAL_PTR_NULL == pst_regdom_info)
        {
            OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_proc_pwr_constraint::this channel isnot support by this country.freq_band = %d,cur_ch_num = %d}",
                                pst_dmac_vap->st_vap_base_info.st_channel.en_band, pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number);
        }
        else
        {
            if (pst_regdom_info->uc_max_reg_tx_pwr > uc_local_pwr_constraint)
            {
                uc_max_tx_pwr = pst_regdom_info->uc_max_reg_tx_pwr - uc_local_pwr_constraint;
                pst_regdom_info->uc_max_tx_pwr = uc_max_tx_pwr;
            }

            OAM_WARNING_LOG3(0, OAM_SF_RRM, "{dmac_rrm_proc_pwr_constraint::max_reg_tx_pwr[%d], constraint[%d], max_tx_pwr[%d]!}\r\n",
                            pst_regdom_info->uc_max_reg_tx_pwr, uc_local_pwr_constraint, pst_regdom_info->uc_max_tx_pwr);
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_gen_random16
 ��������  : ����16λ�����
 �������  : ul_val: �������
            us_rst_flag: �Ƿ�ʹ���������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  dmac_rrm_gen_random16(oal_uint32 ul_val, oal_uint8 us_rst_flag)
{
    OAL_STATIC oal_uint32 ul_rand = 0;
    if (0 != us_rst_flag)
    {
        ul_rand = ul_val;
    }
    ul_rand = ul_rand * 1664525L + 1013904223L;
    return (oal_uint16) (ul_rand >> 16);
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_get_link_req_info
 ��������  : ��ȡlink req֡����
 �������  : pst_dmac_vap: dmac vap�ṹ��
             puc_link_req_frame: link req֡��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rrm_get_link_req_info(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_link_req_frame)
{
    oal_uint8       uc_offset = 0;
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_get_link_req_info::pst_dmac_vap null.");
        return;
    }

    uc_offset += MAC_ACTION_OFFSET_ACTION + 1;
    pst_dmac_vap->pst_rrm_info->uc_link_dialog_token    = puc_link_req_frame[uc_offset++];
    pst_dmac_vap->pst_rrm_info->c_link_tx_pwr_used      = puc_link_req_frame[uc_offset++];
    pst_dmac_vap->pst_rrm_info->c_link_max_tx_pwr       = puc_link_req_frame[uc_offset++];
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_update_start_tsf
 ��������  : ����ʵ�ʲ�����ʼʱ��
 �������  : uc_vap_id: vap id
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rrm_update_start_tsf(oal_uint8 uc_vap_id)
{
    dmac_vap_stru                   *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_RRM, "{dmac_rrm_update_start_tsf::pst_dmac_vap null, vap id[%d].", uc_vap_id);
        return;
    }
    hal_vap_tsf_get_64bit(pst_dmac_vap->pst_hal_vap, (oal_uint32 *)&(pst_dmac_vap->pst_rrm_info->auc_act_meas_start_time[4]), (oal_uint32 *)&(pst_dmac_vap->pst_rrm_info->auc_act_meas_start_time[0]));
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_start_scan_for_bcn_req
 ��������  : ����ʵ�ʲ�����ʼʱ��
 �������  : uc_vap_id: vap id
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_start_scan_for_bcn_req(oal_void *p_arg)
{
    mac_device_stru     *pst_mac_device;
    dmac_vap_stru       *pst_dmac_vap;
    mac_scan_req_stru   *pst_scan_req;

    pst_dmac_vap = (dmac_vap_stru *)p_arg;
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_start_scan_for_bcn_req::pst_dmac_vap null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_start_scan_for_bcn_req::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_scan_req = (mac_scan_req_stru *)pst_dmac_vap->pst_rrm_info->p_scan_req;

    dmac_scan_handle_scan_req_entry(pst_mac_device, pst_dmac_vap, pst_scan_req);

    if (pst_mac_device->st_backoff_meas_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_mac_device->st_backoff_meas_timer));
    }
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_rrm_save_bss_info_event_process
 ��������  : ����hmac�·��������ѱ���BSS��Ϣ��䵽Beacon Report��, Tableģʽ��ʹ��
 �������  : pst_event_mem  �¼��ڴ�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_save_bss_info_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    mac_vap_rrm_trans_bss_info_stru     *pst_trans_bss_info;
    dmac_vap_stru                       *pst_dmac_vap;
    oal_uint8                            uc_bss_idx;
    mac_rrm_info_stru                   *pst_rrm_info;

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_save_bss_info_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);

    pst_trans_bss_info = (mac_vap_rrm_trans_bss_info_stru *)pst_event->auc_event_data;
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RRM, "{dmac_rrm_save_bss_info_event_process::cannot find vap [%d]!}", pst_event_hdr->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    for (uc_bss_idx = 0; uc_bss_idx < pst_trans_bss_info->uc_bss_num; uc_bss_idx++)
    {
        if (WLAN_MGMT_NETBUF_SIZE - pst_rrm_info->us_rm_rpt_action_len < MAC_MEASUREMENT_RPT_FIX_LEN + MAC_BEACON_RPT_FIX_LEN)
        {
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RRM, "{dmac_rrm_save_bss_info_event_process::rm rpt action too long[%d]!}", pst_rrm_info->us_rm_rpt_action_len);
            return OAL_FAIL;
        }

        dmac_rrm_encap_meas_rpt_basic(pst_dmac_vap);

        pst_rrm_info->us_rm_rpt_action_len          += MAC_MEASUREMENT_RPT_FIX_LEN;

        /* ����Beacon Report��ַ */
        pst_rrm_info->pst_bcn_rpt_item = (mac_bcn_rpt_stru *)pst_rrm_info->pst_meas_rpt_ie->auc_meas_rpt;

        /*************************************************************************/
        /*                   Beacon Report - Frame Body         */
        /* --------------------------------------------------------------------- */
        /* |oper class|chn num|Actual Meas Start Time|Meas Duration|Rpt Frm Info|*/
        /* --------------------------------------------------------------------- */
        /* |1         |1      |8                     |2            | 1          |*/
        /* --------------------------------------------------------------------- */
        /* --------------------------------------------------------------------- */
        /* | RCPI | RSNI | BSSID | Antenna ID | Parent TSF| Optional Subelements|*/
        /* --------------------------------------------------------------------- */
        /* |1     |1     |6      |1           |4          | Var                 |*/
        /* --------------------------------------------------------------------- */
        /*                                                                       */
        /*************************************************************************/
        OAL_MEMZERO(pst_rrm_info->pst_bcn_rpt_item, MAC_BEACON_RPT_FIX_LEN);
        pst_rrm_info->pst_bcn_rpt_item->uc_optclass    = pst_rrm_info->st_bcn_req_info.uc_opt_class;
        pst_rrm_info->pst_bcn_rpt_item->uc_channum      = pst_trans_bss_info->auc_chan_num[uc_bss_idx];
        oal_memcopy(pst_rrm_info->pst_bcn_rpt_item->auc_bssid, pst_trans_bss_info->auc_bssid[uc_bss_idx], WLAN_MAC_ADDR_LEN);
        pst_rrm_info->pst_bcn_rpt_item->uc_antenna_id = 1;
        pst_rrm_info->us_rm_rpt_action_len          += MAC_BEACON_RPT_FIX_LEN;
        pst_rrm_info->pst_meas_rpt_ie->uc_len       += MAC_BEACON_RPT_FIX_LEN;
        pst_rrm_info->pst_meas_rpt_ie = (mac_meas_rpt_ie_stru *)pst_rrm_info->pst_bcn_rpt_item->auc_subelm;
    }
    dmac_rrm_send_rm_rpt_action(pst_dmac_vap);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_encap_meas_rpt_basic
 ��������  : ��װMeasurement Report IE�Ĺ̶���
 �������  : pst_dmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rrm_encap_meas_rpt_basic(dmac_vap_stru *pst_dmac_vap)
{
    mac_rrm_info_stru   *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_encap_meas_rpt_basic::pst_dmac_vap null.");
        return;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    /*************************************************************************/
    /*                   Measurement Report IE - Frame Body         */
    /* --------------------------------------------------------------------- */
    /* |Element ID |Length |Meas Token| Meas Rpt Mode | Meas Type | Meas Rpt|*/
    /* --------------------------------------------------------------------- */
    /* |1          |1      | 1        |  1            | 1         | var      */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    pst_rrm_info->pst_meas_rpt_ie->uc_eid       = MAC_EID_MEASREP;
    pst_rrm_info->pst_meas_rpt_ie->uc_token     = pst_rrm_info->st_bcn_req_info.uc_meas_token;
    pst_rrm_info->pst_meas_rpt_ie->uc_rpttype   = pst_rrm_info->st_bcn_req_info.uc_meas_type;
    pst_rrm_info->pst_meas_rpt_ie->uc_len       = 3;
}
/*****************************************************************************
 �� �� ��  : dmac_rrm_set_bcn_rpt_frm_body
 ��������  : ����beacon req��Request�����ID�����beacon report��Report Frame Body
 �������  : pst_dmac_vap           : DMAC VAP�ṹ��ָ��
             puc_rpt_frm_body       : beacon report��Report Frame Body
             puc_rcv_frm            : ����Beacon/Probe rsp��֡��
             l_rcv_frm_len          : ����Beacon/Probe rsp��֡��

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��26��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_set_bcn_rpt_frm_body(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_rpt_frm_body, oal_uint8 *puc_rcv_frm, oal_int32 l_rcv_frm_len)
{
    oal_uint8       uc_element_num;
    oal_uint8      *puc_req_elements;
    oal_uint8       uc_element_idx;
    oal_uint8      *puc_frame_test = puc_rcv_frm;
    oal_uint8       uc_tmp_len;
    oal_uint8       uc_tmp_element_id;
    oal_bool_enum_uint8 en_is_eid_in_reqinfo = OAL_FALSE;
    mac_rrm_info_stru   *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_set_bcn_rpt_frm_body::pst_dmac_vap NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    if((1 != pst_rrm_info->st_bcn_req_info.uc_rpt_detail)
    && (2 != pst_rrm_info->st_bcn_req_info.uc_rpt_detail))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_set_bcn_rpt_frm_body::rpt detail invalid[%d].}", pst_rrm_info->st_bcn_req_info.uc_rpt_detail);
        return OAL_FAIL;
    }

    puc_req_elements = pst_rrm_info->st_bcn_req_info.puc_reqinfo_ieid;
    uc_element_num = pst_rrm_info->st_bcn_req_info.uc_req_ie_num;

    while (l_rcv_frm_len > 0)
    {
        uc_tmp_element_id = puc_frame_test[0];
        uc_tmp_len = puc_frame_test[1];

        if (1 == pst_rrm_info->st_bcn_req_info.uc_rpt_detail)
        {
            for (uc_element_idx = 0; uc_element_idx < uc_element_num; uc_element_idx++)
            {
                if (uc_tmp_element_id == puc_req_elements[uc_element_idx])
                {
                    en_is_eid_in_reqinfo = OAL_TRUE;
                    break;
                }
            }
        }

        if (((1 == pst_rrm_info->st_bcn_req_info.uc_rpt_detail) && (OAL_TRUE == en_is_eid_in_reqinfo))
        || (2 == pst_rrm_info->st_bcn_req_info.uc_rpt_detail))
        {
            switch(uc_tmp_element_id)
            {
                case MAC_EID_TIM:
                case MAC_EID_RSN:
                    if (pst_rrm_info->us_rm_rpt_action_len + 4 > WLAN_MGMT_NETBUF_SIZE)
                    {
                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{rpt frm[%d] is larger than max.}", pst_rrm_info->us_rm_rpt_action_len + 4);
                        return OAL_SUCC;
                    }
                    *puc_rpt_frm_body++ = *puc_frame_test; //EID
                    *puc_rpt_frm_body++ = 2; //new length
                    *puc_rpt_frm_body++ = *(puc_frame_test + 2);
                    *puc_rpt_frm_body++ = *(puc_frame_test + 3);
                    pst_rrm_info->us_rm_rpt_action_len += 4;
                    pst_rrm_info->pst_meas_rpt_ie->uc_len += 4;
                    break;
                case MAC_EID_IBSSDFS:
                    if (pst_rrm_info->us_rm_rpt_action_len + 13 > WLAN_MGMT_NETBUF_SIZE)
                    {
                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{rpt frm[%d] is larger than max.}", pst_rrm_info->us_rm_rpt_action_len + 13);
                        return OAL_SUCC;
                    }
                    /* ��������ŵ�map������ŵ�map */
                    *puc_rpt_frm_body++ = *puc_frame_test; //EID
                    *puc_rpt_frm_body++ = 11; //new length
                    oal_memcopy(puc_rpt_frm_body, puc_frame_test+2, 9);
                    puc_rpt_frm_body += 9;
                    oal_memcopy(puc_rpt_frm_body, puc_frame_test + *(puc_frame_test + 1) - 1, 2);
                    puc_rpt_frm_body += 2;
                    pst_rrm_info->us_rm_rpt_action_len += 13;
                    pst_rrm_info->pst_meas_rpt_ie->uc_len += 13;
                    break;
                default:
                    uc_tmp_len = *(puc_frame_test + 1);
                    if (pst_rrm_info->us_rm_rpt_action_len + uc_tmp_len + 2 > WLAN_MGMT_NETBUF_SIZE)
                    {
                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{rpt frm[%d] is larger than max.}", pst_rrm_info->us_rm_rpt_action_len + uc_tmp_len + 2);
                        return OAL_SUCC;
                    }
                    oal_memcopy(puc_rpt_frm_body, puc_frame_test, uc_tmp_len + 2);
                    puc_rpt_frm_body += uc_tmp_len + 2;
                    pst_rrm_info->us_rm_rpt_action_len += uc_tmp_len + 2;
                    pst_rrm_info->pst_meas_rpt_ie->uc_len += uc_tmp_len + 2;
                    break;
            }
         }

        puc_frame_test += 2 + puc_frame_test[1];
        l_rcv_frm_len -= 2 + puc_frame_test[1];

        en_is_eid_in_reqinfo = OAL_FALSE;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_get_bcn_info_from_rx
 ��������  : �ӽ��յ�Beacon/Probe Rsp�л�ȡBeacon Req������Ϣ, Active/Passiveģʽʹ��
 �������  : pst_dmac_vap : dmac vap�ṹ��
             pst_netbuf   : ����֡netbuf
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rrm_get_bcn_info_from_rx(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru  *pst_netbuf)
{
    oal_uint32                  ul_act_meas_lo;
    oal_uint8                  *puc_rpt_frm_body;
    oal_uint8                   uc_tmp_len;
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint8                  *puc_frame_body;
    oal_uint16                  us_frame_len;
    oal_uint8                  *puc_rpt_frm_len_field;
    mac_rrm_info_stru           *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_get_bcn_info_from_rx::pst_dmac_vap NULL!}");
        return;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    /* ��ȡ��buffer�Ŀ�����Ϣ */
    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ��ȡ֡��Ϣ */
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info));
    puc_frame_body = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctrl->st_rx_info), pst_netbuf);

    us_frame_len   = (oal_uint16)oal_netbuf_get_len(pst_netbuf);

    if (WLAN_MGMT_NETBUF_SIZE - pst_rrm_info->us_rm_rpt_action_len < MAC_MEASUREMENT_RPT_FIX_LEN + MAC_BEACON_RPT_FIX_LEN)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{rpt frm[%d] is larger than max.}", pst_rrm_info->us_rm_rpt_action_len);
        return;
    }

    dmac_rrm_encap_meas_rpt_basic(pst_dmac_vap);
    pst_rrm_info->us_rm_rpt_action_len          += MAC_MEASUREMENT_RPT_FIX_LEN;
    /* ����Beacon Report��ַ */
    pst_rrm_info->pst_bcn_rpt_item = (mac_bcn_rpt_stru *)pst_rrm_info->pst_meas_rpt_ie->auc_meas_rpt;

    /*************************************************************************/
    /*                   Beacon Report - Frame Body         */
    /* --------------------------------------------------------------------- */
    /* |oper class|chn num|Actual Meas Start Time|Meas Duration|Rpt Frm Info|*/
    /* --------------------------------------------------------------------- */
    /* |1         |1      |8                     |2            | 1          |*/
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | RCPI | RSNI | BSSID | Antenna ID | Parent TSF| Optional Subelements|*/
    /* --------------------------------------------------------------------- */
    /* |1     |1     |6      |1           |4          | Var                 |*/
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    pst_rrm_info->pst_bcn_rpt_item->uc_optclass    = pst_rrm_info->st_bcn_req_info.uc_opt_class;
    pst_rrm_info->pst_bcn_rpt_item->uc_channum      = pst_rx_ctrl->st_rx_info.uc_channel_number;
    /* Actual Meas Start Time */
    oal_memcopy(pst_rrm_info->pst_bcn_rpt_item->auc_act_meas_start_time, pst_rrm_info->auc_act_meas_start_time, 8);

    /* Meas Duration */
    if (1 == pst_rrm_info->st_bcn_req_info.st_mr_mode.bit_duration_mandatory)
    {
        pst_rrm_info->pst_bcn_rpt_item->us_duration = pst_rrm_info->st_bcn_req_info.us_meas_duration;
    }
    else
    {
        ul_act_meas_lo = *(oal_uint32 *)&(pst_rrm_info->pst_bcn_rpt_item->auc_act_meas_start_time);
        pst_rrm_info->pst_bcn_rpt_item->us_duration = (oal_uint16)((oal_uint32)(pst_rrm_info->pst_bcn_rpt_item->ul_parent_tsf + 1<<32 - ul_act_meas_lo) >> 10);
    }

    /* Rpt Frm Info */
    pst_rrm_info->pst_bcn_rpt_item->bit_rpt_frm_type        = 0;                /* Beacon/Probe rsp */
    pst_rrm_info->pst_bcn_rpt_item->bit_condensed_phy_type  = PHY_TYPE_OFDM;    /* need modify */

    pst_rrm_info->pst_bcn_rpt_item->uc_rcpi                 = 0;
    pst_rrm_info->pst_bcn_rpt_item->uc_rsni                 = 0;
    /* BSSID */
    oal_set_mac_addr(pst_rrm_info->pst_bcn_rpt_item->auc_bssid, pst_frame_hdr->auc_address3);
    pst_rrm_info->pst_bcn_rpt_item->uc_antenna_id           = 1;
    /* Parent TSF */
    hal_vap_tsf_get_32bit(pst_dmac_vap->pst_hal_vap, (oal_uint32 *)&(pst_rrm_info->pst_bcn_rpt_item->ul_parent_tsf));

    /* ����RM Report���� */
    pst_rrm_info->us_rm_rpt_action_len      += MAC_BEACON_RPT_FIX_LEN;
    pst_rrm_info->pst_meas_rpt_ie->uc_len   += MAC_BEACON_RPT_FIX_LEN;

    /* ���Report Frame Body */
    if (0 != pst_rrm_info->st_bcn_req_info.uc_rpt_detail)
    {
        puc_rpt_frm_body        = pst_rrm_info->pst_bcn_rpt_item->auc_subelm;
        *puc_rpt_frm_body++     = 1;  /* ID */
        puc_rpt_frm_len_field   = puc_rpt_frm_body++;/* Length */

        /* ����field���� */
        oal_memcopy(puc_rpt_frm_body, pst_frame_hdr, OAL_SIZEOF(mac_ieee80211_frame_stru));
        puc_rpt_frm_body += OAL_SIZEOF(mac_ieee80211_frame_stru);
        uc_tmp_len = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
        oal_memcopy(puc_rpt_frm_body, puc_frame_body, uc_tmp_len);
        puc_rpt_frm_body += uc_tmp_len;
        pst_rrm_info->us_rm_rpt_action_len += OAL_SIZEOF(mac_ieee80211_frame_stru) + uc_tmp_len;
        pst_rrm_info->pst_meas_rpt_ie->uc_len += OAL_SIZEOF(mac_ieee80211_frame_stru) + uc_tmp_len;

        /* IE���� */
        dmac_rrm_set_bcn_rpt_frm_body(pst_dmac_vap, puc_rpt_frm_body, puc_frame_body + uc_tmp_len, us_frame_len - MAC_80211_FRAME_LEN - uc_tmp_len);
        *puc_rpt_frm_len_field = puc_rpt_frm_body - pst_rrm_info->pst_bcn_rpt_item->auc_subelm - 1;

        /* ׼����һ�� */
        pst_rrm_info->pst_meas_rpt_ie = (mac_meas_rpt_ie_stru *)(puc_rpt_frm_body + 1);
    }
    else
    {
        pst_rrm_info->pst_meas_rpt_ie = (mac_meas_rpt_ie_stru *)pst_rrm_info->pst_bcn_rpt_item->auc_subelm;
    }

}

/*****************************************************************************
 �� �� ��  : dmac_rrm_meas_bcn
 ��������  : ���ݲ�ͬ����ģʽ��׼��ɨ�����������ɨ��
 �������  : pst_dmac_vap : dmac vap�ṹ��ָ��
             pst_bcn_req  : Beacon Req��Ϣָ��
             pst_scan_req : ����ɨ������ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_meas_bcn(dmac_vap_stru *pst_dmac_vap, mac_bcn_req_stru *pst_bcn_req, mac_scan_req_stru   *pst_scan_req)
{
    mac_device_stru                 *pst_mac_device;
    //oal_uint32                       ul_meas_duration;
    oal_uint16                      us_bcn_meas_backoff_time;
    oal_uint8                       uc_rst_flag = 0;
    oal_uint32                      ul_rand_seed = 32;
    mac_rrm_info_stru   *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_meas_bcn::pst_dmac_vap NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM,
                            "pst_mac_device is NULL,dev id[%d]", pst_dmac_vap->st_vap_base_info.uc_device_id);
    }
#if 0
    if (0 == pst_dmac_vap->st_bcn_req_info.st_mr_mode.bit_duration_mandatory)
    {
        if (0 == pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11RMMaxMeasurementDuration)
        {
            ul_meas_duration = pst_dmac_vap->st_bcn_req_info.us_meas_duration;
        }
        else
        {
            ul_meas_duration = OAL_MIN(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11RMMaxMeasurementDuration, pst_dmac_vap->st_bcn_req_info.us_meas_duration);
        }
    }
    else
    {
        if (pst_dmac_vap->st_bcn_req_info.us_meas_duration < pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11RMMaxMeasurementDuration)
        {
            ul_meas_duration = pst_dmac_vap->st_bcn_req_info.us_meas_duration;
        }
        else
        {
            return OAL_FAIL; //set refused
        }
    }
#endif
    /* ����ģʽ���в��� */
    switch (pst_bcn_req->en_mode)
    {
        /* Passive:����ɨ�裬����probe req�������յ���Beacon��probe rsp */
        case RM_BCN_REQ_MEAS_MODE_PASSIVE:
            if (OAL_FALSE == pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11RMBeaconPassiveMeasurementActivated)
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "passive measurement mode not enable");
                dmac_rrm_encap_meas_rpt_basic(pst_dmac_vap);
                pst_rrm_info->us_rm_rpt_action_len          += 5;
                pst_rrm_info->pst_meas_rpt_ie->st_rptmode.bit_incapable = 1;
                dmac_rrm_send_rm_rpt_action(pst_dmac_vap);
                return OAL_FAIL;
            }

            pst_scan_req->en_bss_type = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
            pst_scan_req->en_scan_type = WLAN_SCAN_TYPE_PASSIVE;
            pst_scan_req->en_scan_mode = WLAN_SCAN_MODE_RRM_BEACON_REQ;
            oal_set_mac_addr(pst_scan_req->auc_bssid[0], pst_bcn_req->auc_bssid);
            pst_scan_req->uc_bssid_num = 1;
            /* ����ʱ�� TBD */
            pst_scan_req->us_scan_time = 10;

            /* ��������˱�ʱ�� */
            us_bcn_meas_backoff_time = dmac_rrm_gen_random16(ul_rand_seed, uc_rst_flag);
            us_bcn_meas_backoff_time = (oal_uint16)((us_bcn_meas_backoff_time * pst_bcn_req->us_random_ivl) << 16);

            pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
            if (OAL_PTR_NULL == pst_mac_device)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM,
                                    "pst_mac_device is NULL,dev id[%d]", pst_dmac_vap->st_vap_base_info.uc_device_id);
            }

            pst_dmac_vap->pst_rrm_info->p_scan_req = (oal_void *)pst_scan_req;
            /* ����˱�һ�κ�ʼ���� */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_backoff_meas_timer,
                                   dmac_rrm_start_scan_for_bcn_req,
                                   us_bcn_meas_backoff_time,
                                   pst_dmac_vap,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);

            break;
        /* Active:����ɨ�裬��probe req�������յ���Beacon��probe rsp */
        case RM_BCN_REQ_MEAS_MODE_ACTIVE:
            if (OAL_FALSE == pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11RMBeaconActiveMeasurementActivated)
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "active measurement mode not enable");
                dmac_rrm_encap_meas_rpt_basic(pst_dmac_vap);
                pst_rrm_info->us_rm_rpt_action_len          += 5;
                pst_rrm_info->pst_meas_rpt_ie->st_rptmode.bit_incapable = 1;
                dmac_rrm_send_rm_rpt_action(pst_dmac_vap);
                return OAL_FAIL;
            }
            pst_scan_req->en_bss_type = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
            pst_scan_req->en_scan_type = WLAN_SCAN_TYPE_ACTIVE;
            pst_scan_req->en_scan_mode = WLAN_SCAN_MODE_RRM_BEACON_REQ;
            oal_set_mac_addr(pst_scan_req->auc_bssid[0], pst_bcn_req->auc_bssid);
            pst_scan_req->uc_bssid_num = 1;

            /* ����ʱ�� TBD*/
            pst_scan_req->us_scan_time = 10;

            /* ��������˱�ʱ�� */
            us_bcn_meas_backoff_time = dmac_rrm_gen_random16(ul_rand_seed, uc_rst_flag);
            us_bcn_meas_backoff_time = (oal_uint16)((us_bcn_meas_backoff_time * pst_bcn_req->us_random_ivl) << 16);

            pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
            if (OAL_PTR_NULL == pst_mac_device)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM,
                                    "pst_mac_device is NULL,dev id[%d]", pst_dmac_vap->st_vap_base_info.uc_device_id);
            }

            pst_dmac_vap->pst_rrm_info->p_scan_req = (oal_void *)pst_scan_req;

            /* ����˱�һ�κ�ʼ���� */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_backoff_meas_timer,
                                   dmac_rrm_start_scan_for_bcn_req,
                                   us_bcn_meas_backoff_time,
                                   pst_dmac_vap,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);

            break;
        /* Table:�ϱ������ɨ���� */
        case RM_BCN_REQ_MEAS_MODE_TABLE:
            if (OAL_FALSE == pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11RMBeaconTableMeasurementActivated)
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "table measurement mode not enable");
                dmac_rrm_encap_meas_rpt_basic(pst_dmac_vap);
                pst_rrm_info->us_rm_rpt_action_len          += 5;
                pst_rrm_info->pst_meas_rpt_ie->st_rptmode.bit_incapable = 1;
                dmac_rrm_send_rm_rpt_action(pst_dmac_vap);
                return OAL_FAIL;
            }
            dmac_send_sys_event(&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_REQ_SAVE_BSS_INFO, 0, OAL_PTR_NULL);

            break;
        default:
            break;

    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_get_bcn_rpt_channels
 ��������  : ����channel number��operating class��������������ŵ�
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
             ppst_ap_chn_rpt    : ָ��AP Channel Report��ָ������
             uc_ap_chn_rpt_num  : AP Channel Report����
             pst_scan_req       : ɨ����Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_get_bcn_rpt_channels(mac_bcn_req_stru *pst_bcn_req, mac_ap_chn_rpt_stru **ppst_ap_chn_rpt, oal_uint8 uc_ap_chn_rpt_num, mac_scan_req_stru *pst_scan_req)
{
    mac_regdomain_info_stru *pst_regdomain_info;
    mac_regclass_info_stru  *pst_regclass_info;
    oal_uint32              ul_channel_bitmap;
    oal_uint8               uc_chan_idx;
    oal_uint8               uc_chan_num;
    oal_uint8               uc_chan_avail_idx = 0;
    oal_uint8               uc_ap_chan_num;
    oal_uint8               uc_ap_chan_idx;
    oal_uint8               uc_ap_chan_rpt_count;

    /* ��ȡ��ǰ���ҵĹ����� */
    mac_get_regdomain_info(&pst_regdomain_info);
    if (pst_bcn_req->uc_optclass > WLAN_MAX_RC_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RRM, "dmac_rrm_get_bcn_rpt_channels: req optclass[%d] is larger than max", pst_bcn_req->uc_optclass);
        return OAL_FAIL;
    }

    pst_regclass_info = &(pst_regdomain_info->ast_regclass[pst_bcn_req->uc_optclass]);
    /* ��ȡ֧���ŵ�λͼ */
    ul_channel_bitmap = pst_regclass_info->ul_channel_bmap;

    /* ��ǰoperating class�µ�����chan */
    if (0 == pst_bcn_req->uc_channum)
    {
        /* ����channel_bitmap��������Ӧ���ŵ��ż��� */
        if (MAC_RC_START_FREQ_2 == pst_regclass_info->en_start_freq)
        {
            for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
            {
                if ((ul_channel_bitmap >> uc_chan_idx) & 0x1)
                {
                    mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_num);
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx].uc_chan_number = uc_chan_num;
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx].en_band        = WLAN_BAND_2G;
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx++].uc_idx       = uc_chan_idx;
                }
            }
            pst_scan_req->uc_channel_nums = uc_chan_avail_idx;
        }
        else if (MAC_RC_START_FREQ_5 == pst_regclass_info->en_start_freq)
        {
            for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
            {
                if ((ul_channel_bitmap >> uc_chan_idx) & 0x1)
                {
                    mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_num);
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx].uc_chan_number = uc_chan_num;
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx].en_band        = WLAN_BAND_5G;
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx++].uc_idx       = uc_chan_idx;
                }
            }
            pst_scan_req->uc_channel_nums = uc_chan_avail_idx;
        }
        else
        {
            OAM_WARNING_LOG1(0, OAM_SF_RRM, "dmac_rrm_get_bcn_rpt_channels: regclass band invalid[%d]", pst_regclass_info->en_start_freq);
            return OAL_FAIL;
        }
    }
    /* ��ǰoperating class��AP chan rpt�Ľ��� */
    else if (255 == pst_bcn_req->uc_channum)
    {
        if (0 == uc_ap_chn_rpt_num)
        {
            OAM_WARNING_LOG0(0, OAM_SF_RRM, "dmac_rrm_get_bcn_rpt_channels: channum is 255,but NO ap_chan_rpt ie");
            return OAL_FAIL;
        }

        for (uc_ap_chan_rpt_count = 0; uc_ap_chan_rpt_count < uc_ap_chn_rpt_num; uc_ap_chan_rpt_count++)
        {
            /* ������ŵ����������ݳ��ȼ��� */
            uc_ap_chan_num = ppst_ap_chn_rpt[uc_ap_chan_rpt_count]->uc_length - 1;

            pst_regclass_info = &(pst_regdomain_info->ast_regclass[ppst_ap_chn_rpt[uc_ap_chan_rpt_count]->uc_oper_class]);
            /* ��ȡ֧���ŵ�λͼ */
            ul_channel_bitmap = pst_regclass_info->ul_channel_bmap;

            for (uc_chan_idx = 0; uc_chan_idx < uc_ap_chan_num; uc_chan_idx++)
            {
                uc_chan_num = *(&(ppst_ap_chn_rpt[uc_ap_chan_rpt_count]->auc_chan[0]) + uc_chan_idx);
                mac_get_channel_idx_from_num(pst_regclass_info->en_start_freq, uc_chan_num, &uc_ap_chan_idx);
                if (ul_channel_bitmap >> uc_ap_chan_idx & 0x1)
                {
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx].uc_chan_number = uc_chan_num;
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx].en_band        = (wlan_channel_band_enum_uint8)(pst_regclass_info->en_start_freq);
                    pst_scan_req->ast_channel_list[uc_chan_avail_idx++].uc_idx         = uc_ap_chan_idx;
                }
                else
                {
                    OAM_WARNING_LOG2(0, OAM_SF_RRM, "dmac_rrm_get_bcn_rpt_channels: chan[%d] not in ap chan rpt regclass[%d]", uc_chan_num, ppst_ap_chn_rpt[uc_ap_chan_rpt_count]->uc_oper_class);
                }
            }
        }
        pst_scan_req->uc_channel_nums = uc_chan_avail_idx;
    }
    /* ��ǰchan num */
    else
    {
        uc_chan_num = pst_bcn_req->uc_channum;
        mac_get_channel_idx_from_num(pst_regclass_info->en_start_freq, uc_chan_num, &uc_ap_chan_idx);
        if (ul_channel_bitmap >> uc_ap_chan_idx & 0x1)
        {
            pst_scan_req->ast_channel_list[0].uc_chan_number = uc_chan_num;
            pst_scan_req->ast_channel_list[0].en_band        = (wlan_channel_band_enum_uint8)(pst_regclass_info->en_start_freq);
            pst_scan_req->ast_channel_list[0].uc_idx         = uc_ap_chan_idx;
            pst_scan_req->uc_channel_nums = 1;
        }
        else
        {
            OAM_WARNING_LOG2(0, OAM_SF_RRM, "dmac_rrm_get_bcn_rpt_channels: chan[%d] not in regclass[%d]", uc_chan_num, pst_bcn_req->uc_optclass);
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_fill_basic_rm_rpt_action
 ��������  : �������֡�ڴ棬������֡��Radio Measurement Report�Ĺ̶���
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_fill_basic_rm_rpt_action(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_mgmt_buf)
{
    oal_uint8                       *puc_buffer;
    mac_rrm_info_stru   *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_fill_basic_rm_rpt_action::pst_dmac_vap NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    /* �������֡�ڴ� */
    pst_mgmt_buf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_mgmt_buf)
    {
       OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_send_rm_bcn_rpt_action::pst_mgmt_buf null.}");

       return OAL_ERR_CODE_PTR_NULL;
    }

    oal_set_netbuf_prev(pst_mgmt_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_mgmt_buf,OAL_PTR_NULL);
    OAL_MEM_NETBUF_TRACE(pst_mgmt_buf, OAL_TRUE);

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    puc_buffer = (oal_uint8 *)pst_mgmt_buf;

    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* ���÷�Ƭ���Ϊ0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* ���õ�ַ1���㲥��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);

    /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /* ��ַ3��ΪVAP�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                    Radio Measurement Report Frame - Frame Body        */
    /* --------------------------------------------------------------------- */
    /* |Category |Action |Dialog Token| Measurement Report Elements         |*/
    /* --------------------------------------------------------------------- */
    /* |1        |1      | 1          |  var                                 */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_buffer                                      += MAC_80211_FRAME_LEN;
    pst_rrm_info->pst_rm_rpt_action                 = (mac_action_rm_rpt_stru *)puc_buffer;
    pst_rrm_info->pst_rm_rpt_action->uc_category    = MAC_ACTION_CATEGORY_RADIO_MEASURMENT;
    pst_rrm_info->pst_rm_rpt_action->uc_action_code = MAC_RM_ACTION_RADIO_MEASUREMENT_REPORT;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_parse_beacon_req
 ��������  : ����Beacon Request��Ϣ����׼������
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
             pst_meas_req_ie    : Measurement Request IEָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rrm_parse_beacon_req(dmac_vap_stru *pst_dmac_vap, mac_meas_req_ie_stru  *pst_meas_req_ie)
{
    mac_bcn_req_stru               *pst_bcn_req;
    mac_scan_req_stru               st_scan_req;
    mac_ap_chn_rpt_stru            *apst_ap_chn_rpt[MAC_11K_SUPPORT_AP_CHAN_RPT_NUM];
    oal_uint8                       uc_ap_chn_rpt_count = 0;
    oal_uint8                       uc_bcn_req_sub_len;
    oal_uint8                      *puc_ap_ch_rpt_search_addr;
    oal_int8                        c_ap_ch_rpt_search_len;
    oal_uint8                      *puc_rpt_detail_search_addr;
    oal_uint8                      *puc_reporting_detail;
    oal_uint8                      *puc_reqinfo_search_addr;
    oal_uint8                      *puc_reqinfo;
    mac_rrm_info_stru               *pst_rrm_info;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_parse_beacon_req::pst_dmac_vap NULL!}");
        return;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    pst_bcn_req = (mac_bcn_req_stru *)(pst_meas_req_ie->auc_meas_req[0]);

    /*************************************************************************/
    /*                    Beacon Request                                     */
    /* --------------------------------------------------------------------- */
    /* |Operating Class |Channel Number |Rand Interval| Meas Duration       |*/
    /* --------------------------------------------------------------------- */
    /* |1               |1              | 2           | 2                   |*/
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |Meas Mode       |BSSID          |Optional Subelements               |*/
    /* --------------------------------------------------------------------- */
    /* |1               |6              | var                               |*/
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    OAL_MEMZERO(&st_scan_req, OAL_SIZEOF(st_scan_req));

    /* ��Subelements�л�ȡ�����ŵ�����,AP Channel Report���ܻ��ж�� */
    uc_bcn_req_sub_len = pst_meas_req_ie->uc_len - 16;
    if (uc_bcn_req_sub_len <= 0)
    {
        dmac_rrm_get_bcn_rpt_channels(pst_bcn_req, apst_ap_chn_rpt,  uc_ap_chn_rpt_count, &st_scan_req);
    }
    else
    {
        puc_ap_ch_rpt_search_addr = pst_bcn_req->auc_subelm;
        c_ap_ch_rpt_search_len = (oal_int8)uc_bcn_req_sub_len;
        do {
            apst_ap_chn_rpt[uc_ap_chn_rpt_count] = (mac_ap_chn_rpt_stru *)mac_find_ie(MAC_EID_AP_CHAN_REPORT, puc_ap_ch_rpt_search_addr, c_ap_ch_rpt_search_len);
            if (OAL_PTR_NULL == apst_ap_chn_rpt[uc_ap_chn_rpt_count])
            {
                break;
            }
            puc_ap_ch_rpt_search_addr = (oal_uint8 *)apst_ap_chn_rpt[uc_ap_chn_rpt_count] + 2 + apst_ap_chn_rpt[uc_ap_chn_rpt_count]->uc_length;
            c_ap_ch_rpt_search_len = uc_bcn_req_sub_len - ((oal_uint8 *)apst_ap_chn_rpt[uc_ap_chn_rpt_count] - pst_bcn_req->auc_subelm) - (2 + apst_ap_chn_rpt[uc_ap_chn_rpt_count]->uc_length);
            uc_ap_chn_rpt_count++;
            if (MAC_11K_SUPPORT_AP_CHAN_RPT_NUM == uc_ap_chn_rpt_count)
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "ap chan rpt num is larger than 8, truncate the later ones");
                break;
            }
        }while (c_ap_ch_rpt_search_len > 0);

        dmac_rrm_get_bcn_rpt_channels(pst_bcn_req, apst_ap_chn_rpt,  uc_ap_chn_rpt_count, &st_scan_req);

        /* ��ȡReporting detail */
        puc_rpt_detail_search_addr = pst_bcn_req->auc_subelm;
        puc_reporting_detail = mac_find_ie(2, puc_rpt_detail_search_addr, uc_bcn_req_sub_len);
        if (OAL_PTR_NULL != puc_reporting_detail)
        {
            pst_rrm_info->st_bcn_req_info.uc_rpt_detail = *(puc_reporting_detail + 2);
        }

        /* ��ȡReqInfo */
        puc_reqinfo_search_addr = pst_bcn_req->auc_subelm;
        puc_reqinfo = mac_find_ie(MAC_EID_REQINFO, puc_reqinfo_search_addr, uc_bcn_req_sub_len);
        if (OAL_PTR_NULL != puc_reqinfo)
        {
            pst_rrm_info->st_bcn_req_info.uc_req_ie_num = *(puc_reqinfo + 1);
            pst_rrm_info->st_bcn_req_info.puc_reqinfo_ieid = puc_reqinfo + 2;
        }
    }

    pst_rrm_info->st_bcn_req_info.uc_opt_class = pst_bcn_req->uc_optclass;
    pst_rrm_info->st_bcn_req_info.us_meas_duration = pst_bcn_req->us_duration;

    dmac_rrm_meas_bcn(pst_dmac_vap, pst_bcn_req, &st_scan_req);

}

/*****************************************************************************
 �� �� ��  : dmac_rrm_send_rm_rpt_action
 ��������  : �����Ѿ���װ�õ�Radio Measurement Report֡
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_rrm_send_rm_rpt_action(dmac_vap_stru* pst_dmac_vap)
{
    mac_tx_ctl_stru                 *pst_tx_ctl;
    oal_netbuf_stru                 *pst_mgmt_buf;
    oal_uint32                      ul_ret = OAL_SUCC;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_send_rm_rpt_action::pst_dmac_vap NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mgmt_buf = pst_dmac_vap->pst_rrm_info->pst_rm_rpt_mgmt_buf;

    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_buf);

    OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)  =(oal_uint8)pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    /* ���÷��͹���֡�ӿ� */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_mgmt_buf, pst_dmac_vap->pst_rrm_info->us_rm_rpt_action_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_mgmt_buf);
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_send_link_meas_rpt_action::tx link meas rpt action failed.}");
        return ul_ret;
    }
    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_proc_rm_request
 ��������  : ����Radio Measurement Request��������Beacon Request
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
             pst_netbuf         : RM Request��netbuf
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 dmac_rrm_proc_rm_request(dmac_vap_stru* pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_action_rm_req_stru          *pst_rm_req;
    mac_meas_req_ie_stru            *pst_meas_req_ie;
    dmac_rx_ctl_stru                *pst_rx_ctrl;
    oal_uint16                      us_framebody_len;
    mac_rrm_info_stru   *pst_rrm_info;
    oal_netbuf_stru                 *pst_mgmt_buf = OAL_PTR_NULL;
    oal_uint8                      *puc_data;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_proc_rm_request::pst_dmac_vap NULL!}");
        return OAL_FALSE;
    }

    pst_rrm_info = pst_dmac_vap->pst_rrm_info;

    /* ��ȡ֡��ָ�� */
    puc_data = OAL_NETBUF_PAYLOAD(pst_netbuf);

    /* �������֡�ڴ沢���ͷ����Ϣ */
    dmac_rrm_fill_basic_rm_rpt_action(pst_dmac_vap, pst_mgmt_buf);

    pst_rrm_info->pst_rm_rpt_mgmt_buf = pst_mgmt_buf;
    pst_rx_ctrl      = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    us_framebody_len = pst_rx_ctrl->st_rx_info.us_frame_len - pst_rx_ctrl->st_rx_info.bit_mac_header_len;

    /*************************************************************************/
    /*                    Radio Measurement Request Frame - Frame Body       */
    /* --------------------------------------------------------------------- */
    /* |Category |Action |Dialog Token| Number of Repetitions|Meas Req Eles |*/
    /* --------------------------------------------------------------------- */
    /* |1        |1      | 1          | 2                    |var            */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    pst_rm_req = (mac_action_rm_req_stru *)(puc_data + MAC_ACTION_OFFSET_ACTION + 1);

    pst_rrm_info->pst_rm_rpt_action->uc_dialog_token = pst_rm_req->uc_dialog_token;
    pst_rrm_info->us_rm_rpt_action_len = 3 + MAC_80211_FRAME_LEN;

    /* �ظ����Դ����ݲ����� */

    /* �Ƿ���Meas Req */
    if (us_framebody_len <= 5)
    {
        /* ���û��MR IE��Ҳ��һ������Meas Rpt��Radio Meas Rpt */
        dmac_rrm_send_rm_rpt_action(pst_dmac_vap);
        return OAL_FALSE;
    }

    pst_meas_req_ie = (mac_meas_req_ie_stru *)&(pst_rm_req->auc_req_ies[0]);

    /*************************************************************************/
    /*                    Measurement Request IE                             */
    /* --------------------------------------------------------------------- */
    /* |Element ID |Length |Meas Token| Meas Req Mode|Meas Type  | Meas Req |*/
    /* --------------------------------------------------------------------- */
    /* |1          |1      | 1        | 1            |1          |var       |*/
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    /* TO BE DONE:�����ж��Measurement Req IEs */
    if (MAC_EID_MEASREQ == pst_meas_req_ie->uc_eid)
    {
        /* Req�в������Ͷ�Ӧ��report */
        if (1 == pst_meas_req_ie->st_reqmode.bit_enable && 0 == pst_meas_req_ie->st_reqmode.bit_rpt)
        {
            oal_netbuf_free(pst_mgmt_buf);
            pst_mgmt_buf = OAL_PTR_NULL;
            OAM_WARNING_LOG0(0, OAM_SF_RRM, "{rpt now allowed!}");
            return OAL_FALSE;
        }

        pst_rrm_info->pst_meas_rpt_ie               = (mac_meas_rpt_ie_stru *)pst_rrm_info->pst_rm_rpt_action->auc_rpt_ies;
        pst_rrm_info->st_bcn_req_info.uc_meas_token    = pst_meas_req_ie->uc_token;  //����meas token���Ա���rptʱʹ��
        pst_rrm_info->st_bcn_req_info.uc_meas_type     = pst_meas_req_ie->uc_reqtype;

        if (5 != pst_meas_req_ie->uc_reqtype)
        {

            pst_rrm_info->pst_meas_rpt_ie->st_rptmode.bit_incapable = 1;
            dmac_rrm_encap_meas_rpt_basic(pst_dmac_vap);
            pst_rrm_info->us_rm_rpt_action_len          += 5;
            dmac_rrm_send_rm_rpt_action(pst_dmac_vap);
            return OAL_FALSE;
        }

        /* ����Beacon req */
        dmac_rrm_parse_beacon_req(pst_dmac_vap, pst_meas_req_ie);
    }
    /* MR IE���󣬲��أ����� */
    else
    {
        oal_netbuf_free(pst_mgmt_buf);
        pst_mgmt_buf = OAL_PTR_NULL;
        OAM_WARNING_LOG1(0, OAM_SF_RRM, "{Error Request, Expect Measurement Request, but got EID[%d]!}", pst_meas_req_ie->uc_eid);
    }
    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_encap_link_meas_rpt
 ��������  : ��װLink Measurement Report
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
             puc_buffer         : link measurement report֡�ĵ�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32    dmac_rrm_encap_link_meas_rpt(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer)
{
    oal_uint8       uc_offset = 0;
    oal_uint8       uc_tpc_offset = 0;
    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_encap_link_meas_rpt::pst_dmac_vap NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* ���÷�Ƭ���Ϊ0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* ���õ�ַ1���㲥��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);

    /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /* ��ַ3��ΪVAP�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the fields in the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                    Link Measurement Report Frame - Frame Body         */
    /* --------------------------------------------------------------------- */
    /* |Category |Action |Dialog Token| TPC Report Element|Rx Antenna ID     */
    /* --------------------------------------------------------------------- */
    /* |1        |1      | 1          |  4                |1                 */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |Tx Antenna ID |RCPI |RSNI| Opt Subelement                            */
    /* --------------------------------------------------------------------- */
    /* |1             |1    | 1  |  Var                                      */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_buffer += MAC_80211_FRAME_LEN;

    /* ����Action��Category   */
    puc_buffer[uc_offset++] = MAC_ACTION_CATEGORY_RADIO_MEASURMENT;

    /* ����Link Measurement Report Action Field */
    puc_buffer[uc_offset++] = MAC_RM_ACTION_LINK_MEASUREMENT_REPORT;

    /* Dialog Token */
    puc_buffer[uc_offset++]= pst_dmac_vap->pst_rrm_info->uc_link_dialog_token;

    /* TPC Report */
    mac_set_tpc_report_ie(&(pst_dmac_vap->st_vap_base_info), puc_buffer + uc_offset, &uc_tpc_offset);
    uc_offset += uc_tpc_offset;

    /* Rx Antenna ID */
    puc_buffer[uc_offset++]= 1;

    /* Tx Antenna ID */
    puc_buffer[uc_offset++]= 1;

    /* RCPI */
    puc_buffer[uc_offset++]= 0;

    /* RSNI */
    puc_buffer[uc_offset++]= 0;

    return (oal_uint32)(uc_offset + MAC_80211_FRAME_LEN);
}

/*****************************************************************************
 �� �� ��  : dmac_rrm_send_link_meas_rpt_action
 ��������  : ����Link Measurement Report
 �������  : pst_dmac_vap       : dmac vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��29��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  dmac_rrm_send_link_meas_rpt_action(dmac_vap_stru *pst_dmac_vap)
{
    oal_netbuf_stru        *pst_mgmt_buf;
    oal_uint16              us_mgmt_len;
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint32              ul_ret;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RRM, "{dmac_rrm_send_link_meas_rpt_action::pst_dmac_vap null.}");
        return OAL_FALSE;
    }

    if (OAL_TRUE != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11RMLinkMeasurementActivated)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_send_link_meas_rpt_action::Link Meas not Activated.}");

        return OAL_FALSE;
    }

    /* �������֡�ڴ� */
    pst_mgmt_buf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_mgmt_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_send_link_meas_rpt_action::pst_mgmt_buf null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_set_netbuf_prev(pst_mgmt_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_mgmt_buf,OAL_PTR_NULL);
    OAL_MEM_NETBUF_TRACE(pst_mgmt_buf, OAL_TRUE);

    /* ��װ Link Measurement Report ֡ */
    us_mgmt_len = (oal_uint16)dmac_rrm_encap_link_meas_rpt(pst_dmac_vap, (oal_uint8 *)pst_mgmt_buf);
    if (0 == us_mgmt_len)
    {
        oal_netbuf_free(pst_mgmt_buf);
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_send_link_meas_rpt_action::encap link meas rpt action failed.}");
        return OAL_FALSE;
    }

    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_buf);

    OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)  =(oal_uint8)pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    /* ���÷��͹���֡�ӿ� */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_mgmt_buf, us_mgmt_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_mgmt_buf);
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RRM, "{dmac_rrm_send_link_meas_rpt_action::tx link meas rpt action failed.}");
        return OAL_FALSE;
    }
    return OAL_FALSE;
}

#endif//_PRE_WLAN_FEATURE_11K
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

