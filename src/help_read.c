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
#include    <sys/stat.h>
#include    <hi_std.h>

/**********************************************************************/
/*  �إ�ץե������ɤ߹��ߴؿ� - help_read                            */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ���Ѹ�����б������إ�ץե�������ɤ߹��ߡ��إ�׾��󥨥ꥢ��   */
/*   Ÿ�����롣                                                       */
/**********************************************************************/
vd  help_read( struct ifa_s *ifa )      /* �إ�ץե������ɤ߹��ߴؿ� */
{
    FILE               *fpin      ;     /* ���ϥե�����               */
    li                  ret       ;     /* �꥿���󥳡���(����)       */
    li                  cnt       ;     /* �롼�ץ�����             */
    li                  offset    ;     /* ���ե��å���               */
    ch                  file[64]  ;     /* �إ�ץե�����̾��         */
    ch                 *workarea  ;     /* ����ΰ�                   */
    struct stat         st        ;     /* �ե����륹�ơ�����         */
    struct help_info_s *help_info ;     /* �ե����륹�ơ�����         */

    trace_start( ifa, "help_read" ) ;   /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �إ�ץե�����η���                                               */
/* ------------------------------------------------------------------ */
    if ( ifa->term_lang == LANG_EUC ) { /* ���Ѹ��줬��[EUC]          */
        snprintf( file, 64, "%s/MANUAL.EUC", HELP_PATH ) ;
                                        /* EUC�ѥޥ˥奢��            */
    }                                   /* end if                     */
    else if ( ifa->term_lang == LANG_SJIS ) {
                                        /* ���Ѹ��줬��[SJIS]         */
        snprintf( file, 64, "%s/MANUAL.SJIS", HELP_PATH ) ;
                                        /* SJIS�ѥޥ˥奢��           */
    }                                   /* end else if                */
    else {                              /* ���Ѹ��줬��[C]��[C]�ʳ�?  */
        snprintf( file, 64, "%s/MANUAL.C", HELP_PATH ) ;
                                        /* C�ѥޥ˥奢��              */
    }                                   /* end else if                */

/* ------------------------------------------------------------------ */
/* �ե����륹�ơ������μ���                                           */
/* ------------------------------------------------------------------ */
    ret = stat( file, &st ) ;           /* �ե����륹�ơ���������     */
    if ( ret != 0 ) {                   /* �ե����뤬¸�ߤ��ʤ�       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "stat[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "stat[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        ifa->help_area = ifa->err_msg ; /* �إ�׾��������           */
        ifa->help_line = 1 ;            /* �إ�׹Կ�������           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - help_read         */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* �ե������ɤ߹����ΰ�γ���                                         */
/* ------------------------------------------------------------------ */
    workarea = (ch *)malloc( st.st_size ) ;
                                        /* ����ΰ�γ���             */
    if ( workarea == NULL ) {           /* ����ΰ�γ��ݼ���         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        ifa->help_area = ifa->err_msg ; /* �إ�׾��������           */
        ifa->help_line = 1 ;            /* �إ�׹Կ�������           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե�����Υ����ץ�                                                 */
/* ------------------------------------------------------------------ */
    fpin = fopen( file, "rb" ) ;        /* �ե����륪���ץ�           */
    if ( fpin == NULL ) {               /* �ե����륪���ץ���       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fopen[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fopen[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        ifa->help_area = ifa->err_msg ; /* �إ�׾��������           */
        ifa->help_line = 1 ;            /* �إ�׹Կ�������           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե�������ɤ߹���                                                 */
/* ------------------------------------------------------------------ */
    ret = fread( workarea, st.st_size, 1, fpin) ;
                                        /* �ե�������ɤ߹���         */
    if ( ret != 1 ) {                   /* �ե������ɤ߹��߼���       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                "fread[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fread[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        ifa->help_area = ifa->err_msg ; /* �إ�׾��������           */
        ifa->help_line = 1 ;            /* �إ�׹Կ�������           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �Կ��μ���                                                         */
/* ------------------------------------------------------------------ */
    for ( cnt = 0 ; cnt < st.st_size ; cnt++ ) {
                                        /* ���ԥ����ɤθ����롼��     */
        if ( workarea[cnt] == 0x0a ) {  /* ���ԥ����ɸ���             */
            ifa->help_line++ ;          /* �إ�פιԿ��ι���         */
        }                               /* end if                     */
    }                                   /* end for                    */

/* ------------------------------------------------------------------ */
/* �إ�ץե������ɤ߹����ΰ�κƳ���                                 */
/* ------------------------------------------------------------------ */
    ifa->help_area = (ch *)malloc( sizeof(struct help_info_s) *
                                   ifa->help_line );
                                        /* �إ�׾��󥨥ꥢ�γ���     */
    if ( ifa->help_area == NULL ) {     /* �إ�׾��󥨥ꥢ�γ��ݼ��� */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        ifa->help_area = ifa->err_msg ; /* �إ�׾��������           */
        ifa->help_line = 1 ;            /* �إ�׹Կ�������           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �إ�׾��������                                                   */
/* ------------------------------------------------------------------ */
    offset = 0 ;                        /* ���ե��å��ͤν����       */
    help_info = (struct help_info_s *)ifa->help_area ;
                                        /* �إ�׾��󥢥ɥ쥹���Ѵ�   */
    for ( cnt = 0 ; cnt < st.st_size ; cnt++ ) {
                                        /* ���ԥ����ɤθ����롼��     */
        if ( ( workarea[cnt] != 0x0a ) && ( workarea[cnt] != 0x0d ) ) {
                                        /* CR/LF�ʳ�                  */
            help_info->help_msg[offset] = workarea[cnt] ;
                                        /* �إ�׾��������           */
            offset++ ;                  /* ���ե��å��ͤι���         */
        }                               /* end if                     */

        if ( workarea[cnt] == 0x0a ) {  /* ���ԥ����ɸ���             */
            if ( ( help_info->help_msg[0] != ' ' ) &&
                 ( help_info->help_msg[0] != 0x00 ) ) {
                                        /* ���Ф���                   */
                help_info->stand = '1' ;/* ��Ĵɽ���⡼��             */
            }                           /* end if                     */
            else {                      /* ���Ф��԰ʳ�               */
                help_info->stand = '0' ;/* �̾�ɽ���⡼��             */
            }                           /* end else                   */
            help_info++ ;               /* �إ�׹Ԥι���             */
            offset = 0 ;                /* ���ե��å��ͤν����       */
        }                               /* end if                     */
    }                                   /* end for                    */

/* ------------------------------------------------------------------ */
/* �ե�����Υ�����                                                 */
/* ------------------------------------------------------------------ */
    free( workarea ) ;                  /* ����ΰ�β���             */
    fclose( fpin ) ;                    /* �ե����륯����           */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - help_read         */
}                                       /* end (help_read)            */

/**********************************************************************/
