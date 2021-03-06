/**********************************************************************/
/*  hi - バイナリエディタ                                             */
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
/* インクルードファイル                                               */
/* ================================================================== */
#include    <sys/types.h>
#include    <signal.h>
#include    <stdlib.h>
#include    <hi_std.h>

extern struct ifa_s *ext_ifa[MAX_EDIT] ;/* インターフェースエリア     */
extern li            ext_entry ;        /* エントリ番号               */

/**********************************************************************/
/*  シグナル受信関数 - hi_signal                                      */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   シグナルを受信したら、カーサスの終了処理を行う。                 */
/**********************************************************************/
vd  hi_signal( li signo )               /* シグナル受信関数           */
{
    ch            message[64] ;         /* 異常終了メッセージエリア   */

/* ------------------------------------------------------------------ */
/* シグナルの再登録                                                   */
/* ------------------------------------------------------------------ */
    signal( SIGBUS,  SIG_IGN ) ;        /* シグナル(10)の無視         */
    signal( SIGSEGV, SIG_IGN ) ;        /* シグナル(11)の無視         */

/* ------------------------------------------------------------------ */
/* 異常終了メッセージの表示                                           */
/* ------------------------------------------------------------------ */
    snprintf( message, sizeof( message ), 
              "Signal [%d] caught. Hit return key to abort...",
              signo ) ;                 /* 異常終了メッセージの編集   */
    echo() ;                            /* エコー入力モード           */
    clear() ;                           /* ウィンドウ全体のクリア     */
    mvaddstr( 0, 0, message ) ;         /* 異常終了メッセージの表示   */
    refresh() ;                         /* 画面の再描画               */
    noecho() ;                          /* エコー入力モード解除       */
    (vd)getch() ;                       /* 表示解除の契機を待つ       */

/* ------------------------------------------------------------------ */
/* 動作環境の表示                                                     */
/* ------------------------------------------------------------------ */
    snprintf( (ext_ifa[ext_entry])->err_msg,
              sizeof( (ext_ifa[ext_entry])->err_msg ),
              "Signal [%d] caught. Hit return key to abort...", signo ) ;
                                        /* 異常終了メッセージの編集   */
    if ( (ext_ifa[ext_entry])->envout == ENVOUT ) {
                                        /* 動作環境表示指示           */
        env_output( ext_ifa[ext_entry] ) ;
                                        /* 動作環境表示               */
    }                                   /* end if                     */
    clear() ;                           /* ウィンドウ全体のクリア     */
    refresh() ;                         /* 画面の再描画               */

/* ------------------------------------------------------------------ */
/* ウィンドウの終了                                                   */
/* ------------------------------------------------------------------ */
    keypad( stdscr, FALSE ) ;           /* キーマップの割り当てを解除 */
    intrflush( stdscr, TRUE ) ;         /* 割り込みキーを解除         */
    nocrmode() ;                        /* 入力モード制御の終了       */
    nl() ;                              /* 復帰改行モードのセット     */
    echo() ;                            /* エコー入力モード           */
    nocbreak() ;                        /* cbreakモードの解除         */
    endwin() ;                          /* 編集ウィンドウの終了       */

/* ------------------------------------------------------------------ */
/* 異常終了処理                                                       */
/* ------------------------------------------------------------------ */
    abort() ;                           /* end program                */
}                                       /* end (hi_signal)            */

/**********************************************************************/
