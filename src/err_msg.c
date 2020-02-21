/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Oct 2000                                 */
/* @(#) Version : 2.2                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <hi_std.h>
#include    <errno.h>
#include    <stdlib.h>

/**********************************************************************/
/*  エラーメッセージ表示関数 - err_msg                                */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定されたメッセージを表示する。また、アボート指示の場合は、     */
/*   バイナリエディタを強制終了する                                   */
/**********************************************************************/
vd  err_msg( struct ifa_s *ifa )        /* エラーメッセージ表示関数   */
{

    trace_start( ifa, "err_msg" ) ;     /* トレース取得               */
/* ------------------------------------------------------------------ */
/* エラーメッセージ表示処理                                           */
/* ------------------------------------------------------------------ */
    if ( ifa->curses == INIT ) {        /* カーサス初期化済み         */
        echo() ;                        /* エコー入力モード           */
        move(ifa->err_msg_y, ifa->err_msg_x) ;
                                        /* エラーメッセージ表示エリア */
                                        /* に移動                     */
        clrtobot() ;                    /* エラーメッセージ表示エリア */
                                        /* のクリア                   */
        standout() ;                    /* 強調表示開始               */
        printw( ifa->err_msg ) ;        /* エラーメッセージの表示     */
        standend() ;                    /* 強調表示終了               */
        flash() ;                       /* 注意を促す                 */
        refresh() ;                     /* 画面の再描画               */
        noecho() ;                      /* エコー入力モード解除       */
    }                                   /* end if                     */
    else {                              /* カーサス未初期化           */
        if ( errno != 0 ) {             /* システム検知障害           */
            perror( ifa->perr_msg ) ;   /* 標準エラー出力に、障害情報 */
        }                               /* end if                     */
        else {                          /* ユーザ検知障害             */
            fprintf( stderr, "%s\n", ifa->err_msg ) ;
                                        /* エラーメッセージの表示     */
        }                               /* end else                   */
        fflush( stderr ) ;              /* バッファのフラッシュ       */
                                        /* 表示する                   */
        printf( "\033[7mPlease hit Return-key\033[m" ) ;
        getchar() ;                     /* キー入力取得               */
    }                                   /* end else                   */

    if ( ifa->endflg == ABORT ) {       /* 強制終了指示               */
        if ( ifa->envout == ENVOUT ) {  /* 動作環境表示指示           */
            env_output( ifa ) ;         /* 動作環境表示               */
        }                               /* end if                     */
        hi_end( ifa ) ;                 /* 終了処理関数               */
        printf("\n") ;                  /* 改行                       */
        exit(1) ;                       /* abort program              */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - err_msg           */
}                                       /* end (err_msg)              */

/**********************************************************************/
