/**********************************************************************/
/*  hi - バイナリエディタ                                             */
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
/* インクルードファイル                                               */
/* ================================================================== */
#include    <stdlib.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  初期設定 - hi_init                                                */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーサスを使用する為の初期設定を行う。                           */
/**********************************************************************/
vd  hi_init( struct ifa_s *ifa )        /* 初期設定関数               */
{

    ch           *use_lang ;            /* 使用言語                   */

    trace_start( ifa, "hi_init" ) ;     /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ウィンドウの初期化                                                 */
/* ------------------------------------------------------------------ */
    ifa->win = initscr() ;              /* 編集ウィンドウの初期化     */
    cbreak();                           /* cbreakモードのセット       */
    noecho();                           /* エコ入力ーモード解除       */
    nonl();                             /* 復帰改行マップの解除       */
    crmode() ;                          /* 入力モード制御             */
    intrflush( ifa->win, FALSE );       /* 割り込みキーを制限         */
    keypad( ifa->win, TRUE ) ;          /* キーマップの割り当て       */
    ifa->curses = INIT ;                /* カーサス初期化済み         */

/* ------------------------------------------------------------------ */
/* ウィンドウサイズのチェック                                         */
/* ------------------------------------------------------------------ */
    win_size( ifa ) ;                   /* サイズチェック関数         */

/* ------------------------------------------------------------------ */
/* 使用言語の取得                                                     */
/* ------------------------------------------------------------------ */
#ifdef CYGWIN
    ifa->term_lang = LANG_SJIS ;        /* [Shift-JIS]を設定          */
#else
    use_lang = getenv( "LANG" ) ;       /* 言語の取得                 */
    if ( use_lang == NULL ) {           /* 言語の取得失敗             */
        ifa->term_lang = LANG_ASCII ;   /* [C]を設定                  */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 端末の言語属性の決定                                               */
/* ------------------------------------------------------------------ */
    else {                              /* 言語の取得成功             */
        if ( ( strcmp( use_lang, "ja_JP.EUC" ) == 0 )||
             ( strcmp( use_lang, "ja_JP.eucJP" ) == 0 )||
             ( strcmp( use_lang, "ja_JP.ujis" ) == 0 ) ) {
                                        /* 使用言語が、[EUC]          */
            ifa->term_lang = LANG_EUC ; /* [Japanese EUC]を設定       */
        }                               /* end if                     */
        else if ( strcmp( use_lang, "ja_JP.SJIS" ) == 0 ) {
                                        /* 使用言語が、[SJIS]         */
            ifa->term_lang = LANG_SJIS ;/* [Shift-JIS]を設定          */
        }                               /* end else if                */
        else {                          /* 使用言語が、[C]か[C]以外?  */
            ifa->term_lang = LANG_ASCII ;
                                        /* [C]を設定                  */
        }                               /* end else if                */
    }                                   /* end else                   */
#endif /* ifdef CYGWIN */

/* ------------------------------------------------------------------ */
/* 環境ファイルの読み込み                                             */
/* ------------------------------------------------------------------ */
    hi_config( ifa ) ;                  /* 環境ファイル読み込み関数   */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - hi_init           */
}                                       /* end (hi_init)              */

/**********************************************************************/
