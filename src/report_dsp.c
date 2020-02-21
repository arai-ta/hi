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
/*  ��ݡ���ɽ���ؿ� - report_dsp                                     */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ����ե��᡼����󥨥ꥢ�ˡ����ߤξ��֤�ɽ�����롣               */
/**********************************************************************/
vd  report_dsp( struct ifa_s *ifa )     /* ��ݡ���ɽ���ؿ�           */
{
    ch           name[256] ;            /* ����о�̾��               */
    ch           kind[32] ;             /* ����оݼ���               */
    ch           aces[32] ;             /* ���������⡼��             */
    ch           status[32] ;           /* �ե����뽤������           */
    ch           crnt[32] ;             /* �����������(%)            */

    trace_start( ifa, "report_dsp" ) ;  /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ��ݡ��Ⱦ����Խ�                                                   */
/* ------------------------------------------------------------------ */
    if ( ifa->modif == MOD_ON ) {       /* �Խ�����                   */
        strlcpy( status, "modified", sizeof( status ) ) ;
                                        /* ��å���������             */
    }                                   /* end if                     */
    else {                              /* �Խ����Ƥ��ʤ�             */
        strlcpy( status, "unmodified", sizeof( status ) ) ;
                                        /* ��å���������             */
    }                                   /* end else                   */

    if ( ifa->option == FIL ) {         /* ����оݤ����ե�����       */
        strlcpy( name, ifa->file, sizeof( name ) ) ;
        strlcpy( kind, "ordinary file", sizeof( kind ) ) ;
        strlcpy( aces, "indirect access", sizeof( aces ) ) ;
                                        /* ��å���������             */
    }                                   /* end if                     */
    else {                              /* �Խ����Ƥ��ʤ�             */
        strlcpy( name, ifa->shmid, sizeof( name ) ) ;
        strlcpy( kind, "shared memory", sizeof( kind ) ) ;
        strlcpy( aces, "direct access", sizeof( aces ) ) ;
                                        /* ��å���������             */
    }                                   /* end else                   */

    if ( ifa->size == 0 ) {             /* �ե����륵������0          */
        strlcpy( crnt, "0%", sizeof( crnt ) ) ;
                                        /* 0%                         */
    }                                   /* end if                     */
    else {                              /* ����������֤���Ƭ�ʳ�     */
        snprintf( crnt, sizeof( crnt ), "%d%%",
                  ((ifa->data_offset * 100) / ifa->size) ) ;
    }                                   /* else if                    */

    snprintf( ifa->inf_msg, 127, "\"%s\" is %s, %s, %d of %d [%s], %s",
             name, kind, aces, (ifa->data_offset - 1), ifa->size,
             crnt, status ) ;           /* ��ݡ��Ⱦ�����Խ�         */

    inf_msg( ifa ) ;                    /* ����ե��᡼�����ɽ������ */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - report_dsp        */
}                                       /* end (report_dsp)           */

/**********************************************************************/
