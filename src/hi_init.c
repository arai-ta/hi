/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : Jun 2004                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 2t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004 Tatsuyoshi                                   */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <stdlib.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ������� - hi_init                                                */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ������������Ѥ���٤ν�������Ԥ���                           */
/**********************************************************************/
vd  hi_init( struct ifa_s *ifa )        /* �������ؿ�               */
{

    ch           *use_lang ;            /* ���Ѹ���                   */

    trace_start( ifa, "hi_init" ) ;     /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ������ɥ��ν����                                                 */
/* ------------------------------------------------------------------ */
    ifa->win = initscr() ;              /* �Խ�������ɥ��ν����     */
    cbreak();                           /* cbreak�⡼�ɤΥ��å�       */
    noecho();                           /* �������ϡ��⡼�ɲ��       */
    nonl();                             /* �������ԥޥåפβ��       */
    crmode() ;                          /* ���ϥ⡼������             */
    intrflush( ifa->win, FALSE );       /* �����ߥ���������         */
    keypad( ifa->win, TRUE ) ;          /* �����ޥåפγ������       */
    ifa->curses = INIT ;                /* ��������������Ѥ�         */

/* ------------------------------------------------------------------ */
/* ������ɥ��������Υ����å�                                         */
/* ------------------------------------------------------------------ */
    win_size( ifa ) ;                   /* �����������å��ؿ�         */

/* ------------------------------------------------------------------ */
/* ���Ѹ���μ���                                                     */
/* ------------------------------------------------------------------ */
#ifdef CYGWIN
    ifa->term_lang = LANG_SJIS ;        /* [Shift-JIS]������          */
#else
    use_lang = getenv( "LANG" ) ;       /* ����μ���                 */
    if ( use_lang == NULL ) {           /* ����μ�������             */
        ifa->term_lang = LANG_ASCII ;   /* [C]������                  */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ü���θ���°���η���                                               */
/* ------------------------------------------------------------------ */
    else {                              /* ����μ�������             */
        if ( ( strcmp( use_lang, "ja_JP.EUC" ) == 0 )||
             ( strcmp( use_lang, "ja_JP.eucJP" ) == 0 )||
             ( strcmp( use_lang, "ja_JP.ujis" ) == 0 ) ) {
                                        /* ���Ѹ��줬��[EUC]          */
            ifa->term_lang = LANG_EUC ; /* [Japanese EUC]������       */
        }                               /* end if                     */
        else if ( strcmp( use_lang, "ja_JP.SJIS" ) == 0 ) {
                                        /* ���Ѹ��줬��[SJIS]         */
            ifa->term_lang = LANG_SJIS ;/* [Shift-JIS]������          */
        }                               /* end else if                */
        else {                          /* ���Ѹ��줬��[C]��[C]�ʳ�?  */
            ifa->term_lang = LANG_ASCII ;
                                        /* [C]������                  */
        }                               /* end else if                */
    }                                   /* end else                   */
#endif /* ifdef CYGWIN */

/* ------------------------------------------------------------------ */
/* �Ķ��ե�������ɤ߹���                                             */
/* ------------------------------------------------------------------ */
    hi_config( ifa ) ;                  /* �Ķ��ե������ɤ߹��ߴؿ�   */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - hi_init           */
}                                       /* end (hi_init)              */

/**********************************************************************/