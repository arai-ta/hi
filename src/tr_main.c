/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Jul 2000                                 */
/* @(#) Version : 2.1                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <unistd.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  言語設定関数 - tr_main                                            */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定された言語に切替える。                                       */
/**********************************************************************/
vd  tr_main( struct ifa_s *ifa )        /* 言語設定関数               */
{
    ch          *lang ;                 /* 指定言語                   */

    trace_start( ifa, "tr_main" ) ;     /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 指定言語取得 & チェック                                            */
/* ------------------------------------------------------------------ */
    lang = strchr( (ch *)ifa->cmd_str, ((li)' ') );
                                        /* 指定言語取得               */
    if ( lang == NULL ) {               /* 指定方法不正               */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - tr_main           */
    }                                   /* end if                     */

    switch ( (li)(lang[1]) ) {          /* 指定言語チェック           */
        case (li)LANG_ASCII :           /* 言語 : ASCII               */
        case (li)LANG_EUC :             /* 言語 : EUC                 */
        case (li)LANG_SJIS :            /* 言語 : Shift-JIS           */
        case (li)LANG_JIS :             /* 言語 : JIS                 */
        case (li)LANG_EBCDIC :          /* 言語 : EBCDIC              */
            break ;                     /* break switch               */

        default :                       /* 指定言語不正               */
            trace_end( ifa ) ;          /* トレース取得               */
            return ;                    /* return - tr_main           */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 切替え言語の設定                                                   */
/* ------------------------------------------------------------------ */
    if ( lang[1] == LANG_EBCDIC ) {     /* 言語は[EBCDIC(K)]          */
        switch ( (li)(lang[2]) ) {      /* 指定言語チェック           */
            case (li)EBCDIC_IBM :       /* EBCDIC IBM                 */
            case (li)EBCDIK_HITAC :     /* EBCDIK HITAC               */
            case (li)EBCDIC_NEC :       /* EBCDIC NEC                 */
            case (li)EBCDIC :           /* EBCDIC                     */
                break ;                 /* break switch               */

            default :                   /* 指定言語不正               */
                trace_end( ifa ) ;      /* トレース取得               */
                return ;                /* return - tr_main           */
        }                               /* end if                     */
        ifa->ebcdic = lang[2] ;         /* EBCDIC(K)の種類を取得      */
    }                                   /* end if                     */
    ifa->lang = lang[1] ;               /* 言語を指定言語に設定       */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - tr_main           */
}                                       /* end (tr_main)              */

/**********************************************************************/
