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
#include    <errno.h>
#include    <stdlib.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  作業領域チェック関数 - area_check                                 */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   作業領域をチェックし、全エリアを使用中であれば、再取得する。     */
/**********************************************************************/
vd  area_check( struct ifa_s *ifa )     /* 作業領域チェック関数       */
{

    trace_start( ifa, "area_check" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 作業領域のチェック                                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->area_size == ifa->size ) {/* 全領域を使用済             */

/* ------------------------------------------------------------------ */
/* 作業領域の再確保                                                   */
/* ------------------------------------------------------------------ */
        ifa->area_size += ifa->alloc_size ;
                                        /* 作業領域の再計算           */
        if ( ifa->area_size >= ifa->max_size ) {
                                        /* 最大サイズに到達した       */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "workarea size is greater than max size" ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
        else {                          /* 最大サイズに未到達         */
            ifa->workarea = (ch *)realloc( ifa->workarea, ifa->area_size ) ;
                                        /* 作業領域の再確保           */
            if ( ifa->workarea == NULL ) {
                                        /* 作業領域の再確保失敗       */
                snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                          "realloc error : errno = %d", errno ) ;
                snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "realloc" ) ;
                                        /* エラーメッセージ設定       */
                ifa->endflg = ABORT ;   /* 強制終了指示               */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end if                     */
        }                               /* end else                   */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - area_check        */
}                                       /* end (area_check)           */

/**********************************************************************/
