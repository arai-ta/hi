/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Oct 2000                                 */
/* @(#) Version : 2.2                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <hi_std.h>
#include    <errno.h>
#include    <stdlib.h>

/**********************************************************************/
/*  ���顼��å�����ɽ���ؿ� - err_msg                                */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ���ꤵ�줿��å�������ɽ�����롣�ޤ������ܡ��Ȼؼ��ξ��ϡ�     */
/*   �Х��ʥꥨ�ǥ���������λ����                                   */
/**********************************************************************/
vd  err_msg( struct ifa_s *ifa )        /* ���顼��å�����ɽ���ؿ�   */
{

    trace_start( ifa, "err_msg" ) ;     /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ���顼��å�����ɽ������                                           */
/* ------------------------------------------------------------------ */
    if ( ifa->curses == INIT ) {        /* ��������������Ѥ�         */
        echo() ;                        /* ���������ϥ⡼��           */
        move(ifa->err_msg_y, ifa->err_msg_x) ;
                                        /* ���顼��å�����ɽ�����ꥢ */
                                        /* �˰�ư                     */
        clrtobot() ;                    /* ���顼��å�����ɽ�����ꥢ */
                                        /* �Υ��ꥢ                   */
        standout() ;                    /* ��Ĵɽ������               */
        printw( ifa->err_msg ) ;        /* ���顼��å�������ɽ��     */
        standend() ;                    /* ��Ĵɽ����λ               */
        flash() ;                       /* ���դ�¥��                 */
        refresh() ;                     /* ���̤κ�����               */
        noecho() ;                      /* ���������ϥ⡼�ɲ��       */
    }                                   /* end if                     */
    else {                              /* ��������̤�����           */
        if ( errno != 0 ) {             /* �����ƥม�ξ㳲           */
            perror( ifa->perr_msg ) ;   /* ɸ�२�顼���Ϥˡ��㳲���� */
        }                               /* end if                     */
        else {                          /* �桼�����ξ㳲             */
            fprintf( stderr, "%s\n", ifa->err_msg ) ;
                                        /* ���顼��å�������ɽ��     */
        }                               /* end else                   */
        fflush( stderr ) ;              /* �Хåե��Υե�å���       */
                                        /* ɽ������                   */
        printf( "\033[7mPlease hit Return-key\033[m" ) ;
        getchar() ;                     /* �������ϼ���               */
    }                                   /* end else                   */

    if ( ifa->endflg == ABORT ) {       /* ������λ�ؼ�               */
        if ( ifa->envout == ENVOUT ) {  /* ư��Ķ�ɽ���ؼ�           */
            env_output( ifa ) ;         /* ư��Ķ�ɽ��               */
        }                               /* end if                     */
        hi_end( ifa ) ;                 /* ��λ�����ؿ�               */
        printf("\n") ;                  /* ����                       */
        exit(1) ;                       /* abort program              */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - err_msg           */
}                                       /* end (err_msg)              */

/**********************************************************************/