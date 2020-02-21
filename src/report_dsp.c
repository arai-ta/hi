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
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  レポート表示関数 - report_dsp                                     */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   インフォメーションエリアに、現在の状態を表示する。               */
/**********************************************************************/
vd  report_dsp( struct ifa_s *ifa )     /* レポート表示関数           */
{
    ch           name[256] ;            /* 操作対象名称               */
    ch           kind[32] ;             /* 操作対象種別               */
    ch           aces[32] ;             /* アクセスモード             */
    ch           status[32] ;           /* ファイル修正状態           */
    ch           crnt[32] ;             /* カーソル位置(%)            */

    trace_start( ifa, "report_dsp" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* レポート情報編集                                                   */
/* ------------------------------------------------------------------ */
    if ( ifa->modif == MOD_ON ) {       /* 編集した                   */
        strlcpy( status, "modified", sizeof( status ) ) ;
                                        /* メッセージ設定             */
    }                                   /* end if                     */
    else {                              /* 編集していない             */
        strlcpy( status, "unmodified", sizeof( status ) ) ;
                                        /* メッセージ設定             */
    }                                   /* end else                   */

    if ( ifa->option == FIL ) {         /* 操作対象が、ファイル       */
        strlcpy( name, ifa->file, sizeof( name ) ) ;
        strlcpy( kind, "ordinary file", sizeof( kind ) ) ;
        strlcpy( aces, "indirect access", sizeof( aces ) ) ;
                                        /* メッセージ設定             */
    }                                   /* end if                     */
    else {                              /* 編集していない             */
        strlcpy( name, ifa->shmid, sizeof( name ) ) ;
        strlcpy( kind, "shared memory", sizeof( kind ) ) ;
        strlcpy( aces, "direct access", sizeof( aces ) ) ;
                                        /* メッセージ設定             */
    }                                   /* end else                   */

    if ( ifa->size == 0 ) {             /* ファイルサイズが0          */
        strlcpy( crnt, "0%", sizeof( crnt ) ) ;
                                        /* 0%                         */
    }                                   /* end if                     */
    else {                              /* カーソル位置が先頭以外     */
        snprintf( crnt, sizeof( crnt ), "%d%%",
                  ((ifa->data_offset * 100) / ifa->size) ) ;
    }                                   /* else if                    */

    snprintf( ifa->inf_msg, 127, "\"%s\" is %s, %s, %d of %d [%s], %s",
             name, kind, aces, (ifa->data_offset - 1), ifa->size,
             crnt, status ) ;           /* レポート情報の編集         */

    inf_msg( ifa ) ;                    /* インフォメーション表示処理 */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - report_dsp        */
}                                       /* end (report_dsp)           */

/**********************************************************************/
