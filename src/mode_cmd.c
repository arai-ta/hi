/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : Nov 2006                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 3t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004-2006 Tatsuyoshi                              */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ���ޥ�ɥ⡼�ɴؿ� - mode_cmd                                     */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   �Ƽ拾�ޥ�ɤ��ɤ߼�ꡢ�б���ǽ�˿���ʬ���롣                   */
/**********************************************************************/
vd  mode_cmd( struct ifa_s *ifa )       /* ���ޥ�ɥ⡼�ɴؿ�         */
{
    li           target  ;              /* �оݵ�ǽ�ֹ�               */
    vd        (*funcmtx[FUNC_MAX])() ;  /* �оݵ�ǽ�ؿ����ɥ쥹       */

    trace_start( ifa, "mode_cmd" ) ;    /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �ؿ����ɥ쥹����                                                   */
/* ------------------------------------------------------------------ */
    funcmtx[FUNC_DMY] = dmy ;           /* ���ߡ��ؿ�                 */
    funcmtx[FUNC_HDN] = cur_move_h_j ;  /* �������벼��ư�ؿ�(HEX)    */
    funcmtx[FUNC_CDN] = cur_move_c_j ;  /* �������벼��ư�ؿ�(ʸ��)   */
    funcmtx[FUNC_HUP] = cur_move_h_k ;  /* ����������ư�ؿ�(HEX)    */
    funcmtx[FUNC_CUP] = cur_move_c_k ;  /* ����������ư�ؿ�(ʸ��)   */
    funcmtx[FUNC_HLF] = cur_move_h_h ;  /* �������뺸��ư�ؿ�(HEX)    */
    funcmtx[FUNC_CLF] = cur_move_c_h ;  /* �������뺸��ư�ؿ�(ʸ��)   */
    funcmtx[FUNC_HRI] = cur_move_h_l ;  /* �������뱦��ư�ؿ�(HEX)    */
    funcmtx[FUNC_CRI] = cur_move_c_l ;  /* �������뱦��ư�ؿ�(ʸ��)   */
    funcmtx[FUNC_GCM] = get_cmd ;       /* ���楳�ޥ�ɴؿ�           */
    funcmtx[FUNC_SCM] = search_cmd ;    /* ���������ޥ�ɴؿ�         */
    funcmtx[FUNC_SCE] = exec_search_cmd ;
                                        /* ���������ޥ�ɼ¹Դؿ�     */
    funcmtx[FUNC_CMV] = cur_pos_move ;  /* ��������������شؿ�       */
    funcmtx[FUNC_WRF] = win_refresh ;   /* ���̺�����ؿ�             */
    funcmtx[FUNC_RPT] = report_dsp ;    /* ��ݡ���ɽ���ؿ�           */
    funcmtx[FUNC_HIN] = edit_h_input ;  /* �ǡ��������ؿ�(HEX)        */
    funcmtx[FUNC_CIN] = edit_c_input ;  /* �ǡ��������ؿ�(ʸ��)       */
    funcmtx[FUNC_HHI] = head_h_input ;  /* �ǡ�������(��Ƭ)�ؿ�(HEX)  */
    funcmtx[FUNC_CHI] = head_c_input ;  /* �ǡ�������(��Ƭ)�ؿ�(ʸ��) */
    funcmtx[FUNC_HAD] = edit_h_add ;    /* �ǡ����ɲôؿ�(HEX)        */
    funcmtx[FUNC_CAD] = edit_c_add ;    /* �ǡ����ɲôؿ�(ʸ��)       */
    funcmtx[FUNC_HTA] = tail_h_add ;    /* �ǡ����ɲ�(�ǽ�)�ؿ�(HEX)  */
    funcmtx[FUNC_CTA] = tail_c_add ;    /* �ǡ����ɲ�(�ǽ�)�ؿ�(ʸ��) */
    funcmtx[FUNC_HR1] = edit_h_rep_1 ;  /* �ǡ����Ѵ��ؿ�(ñ��:HEX)   */
    funcmtx[FUNC_CR1] = edit_c_rep_1 ;  /* �ǡ����Ѵ��ؿ�(ñ��:ʸ��)  */
    funcmtx[FUNC_HR2] = edit_h_rep_2 ;  /* �ǡ����Ѵ��ؿ�(ʣ��:HEX)   */
    funcmtx[FUNC_CR2] = edit_c_rep_2 ;  /* �ǡ����Ѵ��ؿ�(ʣ��:ʸ��)  */
    funcmtx[FUNC_HDL] = edit_h_del ;    /* �ǡ�������ؿ�(HEX)        */
    funcmtx[FUNC_CDL] = edit_c_del ;    /* �ǡ�������ؿ�(ʸ��)       */
    funcmtx[FUNC_PRP] = page_up ;       /* �ڡ�������������ؿ�(��)   */
    funcmtx[FUNC_NXP] = page_down ;     /* �ڡ�������������ؿ�(��)   */
    funcmtx[FUNC_PHP] = half_page_up ;  /* Ⱦ�ڡ�������������ؿ�(��) */
    funcmtx[FUNC_NHP] = half_page_down ;/* Ⱦ�ڡ�������������ؿ�(��) */
    funcmtx[FUNC_HOM] = top_view ;      /* ���������ư�ؿ�(��Ƭ)     */
    funcmtx[FUNC_END] = tail_view ;     /* ���������ư�ؿ�(�ǽ�)     */
    funcmtx[FUNC_LST] = move_line_start ;
                                        /* ����Ƭ�˰�ư�ؿ�           */
    funcmtx[FUNC_LED] = move_line_end ; /* �Ժǽ��˰�ư�ؿ�           */
    funcmtx[FUNC_AGT] = address_get ;   /* ���ɥ쥹�����ؿ�           */
    funcmtx[FUNC_REP] = repeat_cmd ;    /* �����֤����ޥ�ɴؿ�       */
    funcmtx[FUNC_CWQ] = exec_get_cmd ;  /* ���楳�ޥ�ɼ¹Դؿ�       */

/* ------------------------------------------------------------------ */
/* ���ޥ���ɤ߼��                                                   */
/* ------------------------------------------------------------------ */
    ifa->before_cmd = ifa->cmd ;        /* ����Υ��ޥ������         */
    ifa->cmd = wgetch( ifa->win ) ;     /* ���ޥ�ɼ���               */

/* ------------------------------------------------------------------ */
/* �����֤������Ƚ��                                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->cmd == CMD_REPEAT ) {     /* ����Υ��ޥ�ɷ����֤�     */
        if ( ifa->option == FIL ) {     /* ����оݤ����ե�����       */
            if ( ifa->before_cmd == CMD_DELETE ) {
                                        /* �����֤���ǽ�ʥ��ޥ��     */
                ifa->cmd = ifa->before_cmd ;
                                        /* ����Υ��ޥ������         */
            }                           /* end if                     */
            else {                      /* �����֤��Բ�ǽ�ʥ��ޥ��   */
                if ( ifa->before_cmd == 0x00 ) {
                                        /* ����Υ��ޥ�ɤ�¸�ߤ��ʤ� */
                    strlcpy( ifa->err_msg, "Before comannd nothing",
                             sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                }                       /* end if                     */
                else {                  /* ����Υ��ޥ�ɤ�¸�ߤ���   */
                    snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                              "[%c] is not repeat", ifa->before_cmd ) ;
                                        /* ���顼��å���������       */
                }                       /* end else                   */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* ����оݤ�����ͭ����     */
            strlcpy( ifa->err_msg, "Shared memory is not support",
                     sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
    }                                   /* end if                     */

    switch ( ifa->cmd ) {               /* ���ޥ�ɥ����å�           */

/* ------------------------------------------------------------------ */
/* ���������ư(��)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_DOWN :             /* [j]                        */
        case KEY_DOWN :                 /* [��]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                target = FUNC_HDN ;     /* �������벼��ư�ؿ�(HEX)    */
            }                           /* end if                     */
            else {                      /* ʸ���ǡ������ꥢ           */
                target = FUNC_CDN ;     /* �������벼��ư�ؿ�(ʸ��)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���������ư(��)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_UP :               /* [k]                        */
        case KEY_UP :                   /* [��]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                target = FUNC_HUP ;     /* ����������ư�ؿ�(HEX)    */
            }                           /* end if                     */
            else {                      /* ʸ���ǡ������ꥢ           */
                target = FUNC_CUP ;     /* ����������ư�ؿ�(ʸ��)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���������ư(��)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_LEFT :             /* [h]                        */
        case KEY_LEFT :                 /* [��]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                target = FUNC_HLF ;     /* �������뺸��ư�ؿ�(HEX)    */
            }                           /* end if                     */
            else {                      /* ʸ���ǡ������ꥢ           */
                target = FUNC_CLF ;     /* �������뺸��ư�ؿ�(ʸ��)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���������ư(��)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_RIGHT :            /* [l]                        */
        case KEY_RIGHT :                /* [��]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                target = FUNC_HRI ;     /* �������뱦��ư�ؿ�(HEX)    */
            }                           /* end if                     */
            else {                      /* ʸ���ǡ������ꥢ           */
                target = FUNC_CRI ;     /* �������뱦��ư�ؿ�(ʸ��)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ZZ = :wq                                                           */
/* ------------------------------------------------------------------ */
        case CMD_BIGZ :                 /* [Z]����Ϥޤ�ʸ����        */
            if(wgetch( ifa->win ) == CMD_BIGZ){
                                        /* ���ޥ�ɼ���               */
                strlcpy(ifa->cmd_str, "wq", sizeof( ifa->cmd_str ) );
                                        /* :wq ���֤�����             */
                ifa->cmd_size = strlen( ifa->cmd_str ) ;
                                        /* ���ޥ�ɥ�����������       */
                target = FUNC_CWQ ;     /* ���楳�ޥ�ɼ¹Դؿ�       */
            } else {
                printf("\a");
                target = FUNC_DMY ;     /* ���ߡ��ؿ�                 */
            }
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���楳�ޥ��                                                       */
/* ------------------------------------------------------------------ */
        case CMD_CNTRL :                /* [:]����Ϥޤ�ʸ����        */
            target = FUNC_GCM ;         /* ���楳�ޥ�ɴؿ�           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���������ޥ��                                                     */
/* ------------------------------------------------------------------ */
        case CMD_SEARCH :               /* [/]����Ϥޤ�ʸ����        */
            ifa->search = NEXT_SEARCH ; /* ����������:�縡��          */
            target = FUNC_SCM ;         /* ���������ޥ�ɴؿ�         */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ե��������ޥ��                                                   */
/* ------------------------------------------------------------------ */
        case CMD_RSEARCH :              /* [?]����Ϥޤ�ʸ����        */
            ifa->search = PREV_SEARCH ; /* ����������:�ո���          */
            target = FUNC_SCM ;         /* ���������ޥ�ɴؿ�         */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �Ƹ������ޥ��                                                     */
/* ------------------------------------------------------------------ */
        case CMD_NEXT :                 /* [n]                        */
            target = FUNC_SCE ;         /* ���������ޥ�ɼ¹Դؿ�     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �Ƶո������ޥ��                                                   */
/* ------------------------------------------------------------------ */
        case CMD_REVERSE :              /* [N]                        */
            target = FUNC_SCE ;         /* ���������ޥ�ɼ¹Դؿ�     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ��������������إ��ޥ��                                           */
/* ------------------------------------------------------------------ */
        case CMD_CPOS_MOVE :            /* [Ctrl] + [a]               */
        case CMD_CPOS_MOV2 :            /* [Tab]                      */
            target = FUNC_CMV ;         /* ��������������شؿ�       */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���̤Υ�ե�å���                                                 */
/* ------------------------------------------------------------------ */
        case CMD_REFRESH :              /* [Ctrl] + [l]               */
            target = FUNC_WRF ;         /* ���̺�����ؿ�             */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ʸ���������ڤ��ؤ�                                                 */
/* ------------------------------------------------------------------ */
        case CMD_CHG_CHAR :             /* [Ctrl] + [T]               */
            if ( ifa->lang == LANG_ASCII ){
                ifa->lang = LANG_EUC;
            } else if ( ifa->lang == LANG_EUC ){
                ifa->lang = LANG_SJIS;
            } else if ( ifa->lang == LANG_SJIS ){
                ifa->lang = LANG_JIS;
/*            } else if ( ifa->lang == LANG_JIS ){
                ifa->lang = LANG_EBCDIC;*/
            } else {
                ifa->lang = LANG_ASCII;
            }
            target = FUNC_WRF ;         /* ���̺�����ؿ�             */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ��ݡ���ɽ��                                                       */
/* ------------------------------------------------------------------ */
        case CMD_REPORT :               /* [Ctrl] + [g]               */
            target = FUNC_RPT ;         /* ��ݡ���ɽ���ؿ�           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(�ǡ�������)                                     */
/* ------------------------------------------------------------------ */
        case CMD_INPUT :                /* [i]                        */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                    target = FUNC_HIN ; /* �ǡ��������ؿ�(HEX)        */
                }                       /* end if                     */
                else {                  /* ʸ���ǡ������ꥢ           */
                    target = FUNC_CIN ; /* �ǡ��������ؿ�(ʸ��)       */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* ����оݤ�����ͭ����     */
                target = FUNC_DMY ;     /* ���ߡ��ؿ�                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(��Ƭ����Υǡ�������)                           */
/* ------------------------------------------------------------------ */
        case CMD_TOP_INPUT :            /* [I]                        */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                    target = FUNC_HHI ; /* �ǡ�������(��Ƭ)�ؿ�(HEX)  */
                }                       /* end if                     */
                else {                  /* ʸ���ǡ������ꥢ           */
                    target = FUNC_CHI ; /* �ǡ�������(��Ƭ)�ؿ�(ʸ��) */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* ����оݤ�����ͭ����     */
                target = FUNC_DMY ;     /* ���ߡ��ؿ�                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(�ǡ����ɲ�)                                     */
/* ------------------------------------------------------------------ */
        case CMD_ADD :                  /* [a]                        */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                    target = FUNC_HAD ; /* �ǡ����ɲôؿ�(HEX)        */
                }                       /* end if                     */
                else {                  /* ʸ���ǡ������ꥢ           */
                    target = FUNC_CAD ; /* �ǡ����ɲôؿ�(ʸ��)       */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* ����оݤ�����ͭ����     */
                target = FUNC_DMY ;     /* ���ߡ��ؿ�                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(�Ǹ夫��Υǡ����ɲ�)                           */
/* ------------------------------------------------------------------ */
        case CMD_LAST_ADD :             /* [A]                        */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                    target = FUNC_HTA ; /* �ǡ����ɲ�(�ǽ�)�ؿ�(HEX)  */
                }                       /* end if                     */
                else {                  /* ʸ���ǡ������ꥢ           */
                    target = FUNC_CTA ; /* �ǡ����ɲ�(�ǽ�)�ؿ�(ʸ��) */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* ����оݤ�����ͭ����     */
                target = FUNC_DMY ;     /* ���ߡ��ؿ�                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(�ǡ����ִ�:��ʸ��)                              */
/* ------------------------------------------------------------------ */
        case CMD_REPLACE_1 :            /* [r]                        */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                target = FUNC_HR1 ;     /* �ǡ����Ѵ��ؿ�(ñ��:HEX)   */
            }                           /* end if                     */
            else {                      /* ʸ���ǡ������ꥢ           */
                target = FUNC_CR1 ;     /* �ǡ����Ѵ��ؿ�(ñ��:ʸ��)  */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(�ǡ����ִ�:ʣ��ʸ��)                            */
/* ------------------------------------------------------------------ */
        case CMD_REPLACE_2 :            /* [R]                        */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                target = FUNC_HR2 ;     /* �ǡ����Ѵ��ؿ�(ʣ��:HEX)   */
            }                           /* end if                     */
            else {                      /* ʸ���ǡ������ꥢ           */
                target = FUNC_CR2 ;     /* �ǡ����Ѵ��ؿ�(ʣ��:ʸ��)  */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ǡ����Խ����ޥ��(�ǡ������)                                     */
/* ------------------------------------------------------------------ */
        case CMD_DELETE :               /* [x]                        */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEX�ǡ������ꥢ            */
                    target = FUNC_HDL ; /* �ǡ�������ؿ�(HEX)        */
                }                       /* end if                     */
                else {                  /* ʸ���ǡ������ꥢ           */
                    target = FUNC_CDL ; /* �ǡ�������ؿ�(ʸ��)       */
                }                       /* end if                     */
            }                           /* end else                   */
            else {                      /* ����оݤ�����ͭ����     */
                target = FUNC_DMY ;     /* ���ߡ��ؿ�                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ڡ�������������(��)                                               */
/* ------------------------------------------------------------------ */
        case CMD_PREV_PAGE :            /* [Ctrl] + [b]               */
        case KEY_PPAGE :                /* [PgUp]                     */
            target = FUNC_PRP ;         /* �ڡ�������������ؿ�(��)   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ڡ�������������(��)                                               */
/* ------------------------------------------------------------------ */
        case CMD_NEXT_PAGE :            /* [Ctrl] + [f]               */
        case KEY_NPAGE :                /* [PgUp]                     */
            target = FUNC_NXP ;         /* �ڡ�������������ؿ�(��)   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* Ⱦ�ڡ�������������(��)                                             */
/* ------------------------------------------------------------------ */
        case CMD_PREV_HALF :            /* [Ctrl] + [u]               */
            target = FUNC_PHP ;         /* Ⱦ�ڡ�������������ؿ�(��) */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* Ⱦ�ڡ�������������(��)                                             */
/* ------------------------------------------------------------------ */
        case CMD_NEXT_HALF :            /* [Ctrl] + [d]               */
            target = FUNC_NHP ;         /* Ⱦ�ڡ�������������ؿ�(��) */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ե��������Ƭ���֤˰�ư                                           */
/* ------------------------------------------------------------------ */
        case KEY_HOME :                 /* [Home]                     */
            target = FUNC_HOM ;         /* ���������ư�ؿ�(��Ƭ)     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �ե�����κǽ����֤˰�ư                                           */
/* ------------------------------------------------------------------ */
        case KEY_END :                  /* [End]                      */
        case CMD_TAIL :                 /* [G] �� [Shift] + [g]       */
            target = FUNC_END ;         /* ���������ư�ؿ�(�ǽ�)     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �Ԥ���Ƭ���֤˰�ư                                                 */
/* ------------------------------------------------------------------ */
        case CMD_LINE_START :           /* [0]                        */
            target = FUNC_LST ;         /* �԰�ư�ؿ�(��Ƭ)           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �Ԥκǽ����֤˰�ư                                                 */
/* ------------------------------------------------------------------ */
        case CMD_LINE_END :             /* [$]                        */
            target = FUNC_LED ;         /* �԰�ư�ؿ�(�ǽ�)           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���ɥ쥹�ɤ߹��߰�ư                                               */
/* ------------------------------------------------------------------ */
        case CMD_ADRS_JMP :             /* [Ctrl] + [j]               */
            target = FUNC_AGT ;         /* ���ɥ쥹�����ؿ�           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* �����֤����ޥ�ɻ���                                               */
/* ------------------------------------------------------------------ */
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
            target = FUNC_REP ;         /* �����֤����ޥ�ɴؿ�       */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ���곰�Υǡ���                                                     */
/* ------------------------------------------------------------------ */
        default  :                      /* ���곰                     */
            target = FUNC_DMY ;         /* ���ߡ��ؿ�                 */
            break ;                     /* break switch               */
    }                                   /* end switch                 */
    (*funcmtx[target])( ifa ) ;         /* �оݵ�ǽ������             */
    refresh() ;                         /* ������ɥ��κ�����         */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - mode_cmd          */
}                                       /* end (mode_cmd)             */

/**********************************************************************/