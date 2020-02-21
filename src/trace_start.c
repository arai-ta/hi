/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Sep 2000                                 */
/* @(#) Version : 2.2                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  関数開始関数 - trace_start                                        */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   トレース情報(開始)を取得する。                                   */
/**********************************************************************/
vd  trace_start( struct ifa_s *ifa, ch *func )
{                                       /* 関数開始関数               */

    ifa->func_trace[ifa->func_dep] = func ;
                                        /* 関数名称を設定する         */
    ifa->func_dep++ ;                   /* 関数トレースの深さを設定   */

#ifdef TRACE
{
    ul    cnt ;                         /* ループカウンタ             */

    memset( ifa->debug_msg, 0x00, sizeof( ifa->debug_msg ) ) ;
                                        /* デバッグメッセージエリアの */
                                        /* 初期化                     */
    for ( cnt = 0 ; cnt < ifa->func_dep ; cnt++ ) {
                                        /* ネスト分ループ             */
        strlcat( ifa->debug_msg, "  ", sizeof( ifa->debug_msg ) ) 
                                       ;/* ネスト分スペースを挿入     */
    }                                   /* end for                    */
    strlcat( ifa->debug_msg, "[S] ", sizeof( ifa->debug_msg ) ) ;
                                        /* 標識を設定                 */
    strlcat( ifa->debug_msg, func, sizeof( ifa->debug_msg ) ) ;
                                        /* 関数名称を設定             */

    debug( ifa ) ;                      /* デバッグ関数               */
}
#endif

    return ;                            /* return - trace_start       */
}                                       /* end (trace_start)          */

/**********************************************************************/
