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
#include    <errno.h>
#include    <stdlib.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ���������ޥ�ɼ¹Դؿ� - exec_search_cmd                          */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ���������ޥ�ɤ�¹Ԥ��롣                                       */
/**********************************************************************/
vd  exec_search_cmd( struct ifa_s *ifa )/* ���������ޥ�ɴؿ�         */
{
    li         ret   ;                  /* �꥿���󥳡���(����)       */
    li         cnt1  ;                  /* �롼�ץ�����1            */
    li         cnt2  ;                  /* �롼�ץ�����2            */
    ch         found ;                  /* ʸ�����Υե饰           */
    ch         cnv   ;                  /* ʸ����:HEX�Ѵ��ե饰       */

    trace_start( ifa, "exec_search_cmd" ) ;
                                        /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ������ʸ����Ƚ��                                                   */
/* ------------------------------------------------------------------ */
    cnv = 0 ;                           /* ʸ����:HEX�Ѵ��ե饰����� */
    if ( ifa->target == HEX_DATA ) {    /* �Х��ʥ�ǡ�������         */
        if ( memcmp( ifa->search_str, "0x", 2 ) == 0 ) {
                                        /* HEX����Ƚ��                */
            if ( ( ifa->search_size < 4 ) || 
                 ( ( ifa->search_size % 2 ) != 0 ) ){
                                        /* HEX�ǡ�����������          */
                strlcpy( ifa->err_msg, "Search-string error",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
                trace_end( ifa ) ;      /* �ȥ졼������               */
                return ;                /* return - exec_search_cmd   */
            }                           /* end if                     */
            str_hex_cnv( ifa ) ;        /* ʸ����:HEX�Ѵ�             */
            cnv = 1 ;                   /* ʸ����:HEX�Ѵ��ե饰����   */
        }                               /* end if                     */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ����ʸ��������ΰ�γ���                                           */
/* ------------------------------------------------------------------ */
    if ( ifa->search_info == NULL ) {   /* �ΰ�̤����                 */
        ifa->search_info = (ch *)malloc( ( ifa->size / 8 ) );
                                        /* ����ʸ��������ΰ�γ���   */
        if ( ifa->search_info == NULL ) {
                                        /* �ΰ�γ��ݼ���             */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "malloc error : errno = %d", errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* ���顼��å���������       */
            ifa->endflg = ABORT ;       /* ������λ�ؼ�               */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end if                     */
    }                                   /* end if                     */
    memset( ifa->search_info, 0x00, ( ifa->size / 8 ) ) ;
                                        /* ����ʸ��������ΰ�ν���� */
/* ------------------------------------------------------------------ */
/* ���������ޥ��������                                               */
/* ------------------------------------------------------------------ */
    if ( ifa->cmd == CMD_NEXT ) {       /* ������                     */
        if ( ifa->search == NEXT_SEARCH ) {
                                        /* �����������ϡ��縡��       */
            ifa->cmd = CMD_SEARCH ;     /* ���ޥ�ɤ��ִ�             */
        }                               /* end if                     */
        else {                          /* �����������ϡ��ո���       */
            ifa->cmd = CMD_RSEARCH ;    /* ���ޥ�ɤ��ִ�             */
        }                               /* end else                   */
    }                                   /* end if                     */
    else if ( ifa->cmd == CMD_REVERSE) {
                                        /* �ռ�����                   */
        if ( ifa->search == NEXT_SEARCH ) {
                                        /* �����������ϡ��ո���       */
            ifa->cmd = CMD_RSEARCH ;    /* ���ޥ�ɤ��ִ�             */
        }                               /* end if                     */
        else {                          /* �����������ϡ��縡��       */
            ifa->cmd = CMD_SEARCH ;     /* ���ޥ�ɤ��ִ�             */
        }                               /* end else                   */
    }                                   /* end if                     */
    else {                              /* �������                   */
        if ( ifa->reverse == REVERSE ) {/* ����ʸ�����ȿžɽ������   */
            cnt1 = 0 ;                  /* �롼�ץ����󥿤ν����     */
            while ( cnt1 < ifa->size ) {/* ��Ƭ���֤��顢��������     */
                ret = memcmp( &ifa->workarea[cnt1], ifa->search_str,
                              ifa->search_size ) ;
                if ( ret == 0 ) {       /* ʸ������                 */
                    for ( cnt2 = cnt1 ; cnt2 < ( cnt1 + ifa->search_size ) ;
                          cnt2++ ) {    /* ����ʸ���󥵥����Υ롼��   */
                        STANDON( cnt2 ) ;
                                        /* ����ʸ������������       */
                    }                   /* end for                    */
                    cnt1 += ifa->search_size ;
                                        /* �������֤ι���             */
                    continue ;          /* continue while             */
                }                       /* end if                     */
                cnt1++ ;                /* �롼�ץ����󥿤ι���       */
            }                           /* end while                  */
        }                               /* end if                     */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* ���������ޥ�ɼ¹Խ���                                             */
/* ------------------------------------------------------------------ */
    if ( ifa->cmd == CMD_SEARCH ) {     /* �祵����                   */
        found = 0 ;                     /* ʸ�����Υե饰�ν����   */
        for ( cnt2 = ifa->data_offset+1 ; cnt2 < ifa->size ; cnt2++ ) {
                                        /* ���߰��֤��顢��������     */
            ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                          ifa->search_size ) ;
            if ( ret == 0 ) {           /* ʸ������                 */
                found = 1 ;             /* ʸ�����Υե饰����       */
                break ;                 /* break for                  */
            }                           /* end if                     */
        }                               /* end for                    */
#ifdef SEARCH_WRAP
        if ( found == 0 ) {             /* ʸ����¸�ߤ���             */
            for ( cnt2 = 0 ; cnt2 <= ifa->data_offset ; cnt2++ ) {
                                        /* �ǽ���֤��顢��������     */
                ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                              ifa->search_size ) ;
                if ( ret == 0 ) {       /* ʸ������                 */
                    found = 2 ;         /* ʸ�����Υե饰����       */
                    break ;             /* break for                  */
                }                       /* end if                     */
            }                           /* end for                    */
        }                               /* end if                     */
#endif
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե��������ޥ�ɼ¹Խ���                                           */
/* ------------------------------------------------------------------ */
    else {                              /* �ե�����                   */
        found = 0 ;                     /* ʸ�����Υե饰�ν����   */
        for ( cnt2 = ifa->data_offset-2 ; cnt2 >= 0 ; cnt2-- ) {
                                        /* ���߰��֤��顢��������     */
            ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                          ifa->search_size ) ;
            if ( ret == 0 ) {           /* ʸ������                 */
                found = 1 ;             /* ʸ�����Υե饰����       */
                break ;                 /* break for                  */
            }                           /* end if                     */
        }                               /* end for                    */
#ifdef SEARCH_WRAP
        if ( found == 0 ) {             /* ʸ����¸�ߤ���             */
            for ( cnt2 = ifa->size ; cnt2 >= ifa->data_offset-1 ; cnt2-- ) {
                                        /* �ǽ����֤��顢��������     */
                ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                              ifa->search_size ) ;
                if ( ret == 0 ) {       /* ʸ������                 */
                    found = 2 ;         /* ʸ�����Υե饰����       */
                    break ;             /* break for                  */
                }                       /* end if                     */
            }                           /* end for                    */
        }                               /* end if                     */
#endif
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ��������̤β��̺�����                                             */
/* ------------------------------------------------------------------ */
    if ( found != 0 ) {                 /* ʸ����¸�ߤ���           */
        ifa->data_offset = cnt2 + 1 ;   /* �ǡ������ե��åȤι���     */
        ifa->view_offset = cnt2 - ( cnt2 % 16 ) ;
                                        /* ɽ�����ե��åȤι���       */
        data_view( ifa ) ;              /* �ǡ���ɽ��                 */
        if ( ifa->target == HEX_DATA ) {/* HEX�ǡ������ꥢ            */
            if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* ����������֤����ֱ�       */
                ifa->cur_pos_x = BASE_X2 + 15 * 3 ;
                                        /* �����������(X)������      */
            }                           /* end if                     */
            else {                      /* ����������֤����ֱ��ʳ�   */
                ifa->cur_pos_x = BASE_X2 +
                                 ( ifa->data_offset % 16 ) * 3 - 3 ;
                                        /* �����������(X)������      */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* ʸ���ǡ������ꥢ           */
            if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* ����������֤����ֱ�       */
                ifa->cur_pos_x = BASE_X3 + 15 ;
                                        /* �����������(X)������      */
            }                           /* end if                     */
            else {                      /* ����������֤����ֱ��ʳ�   */
                ifa->cur_pos_x = BASE_X3 +
                                 ( ifa->data_offset % 16 ) - 1 ;
                                        /* �����������(X)������      */
            }                           /* end else                   */
        }                               /* end else                   */
        ifa->cur_pos_y = BASE_Y ;       /* �����������(Y)������      */
        move( ifa->cur_pos_y, ifa->cur_pos_x ) ;
                                        /* ���������ư               */
        ifa->hex_pos = CUR_LEFT ;       /* ��̥Х��Ȥ�ݥ���Ȥ����� */
                                        /* ��Ф���                   */
#ifdef SEARCH_WRAP
        if ( found == 2 ) {             /* ��åפ��Ƹ���             */
            strlcpy( ifa->err_msg, "Search wrapped", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
#endif
    }                                   /* end else                   */
    else {                              /* ʸ����¸�ߤ��ʤ�         */
        strlcpy( ifa->err_msg, "Pattern not found", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
    }                                   /* end else                   */
    refresh() ;                         /* ������ɥ�������           */

    if ( cnv == 1 ) {                   /* ʸ����:HEX�Ѵ�����         */
        hex_str_cnv( ifa ) ;            /* HEX:ʸ�����Ѵ�             */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - exec_search_cmd   */
}                                       /* end (exec_search_cmd)      */

/**********************************************************************/
