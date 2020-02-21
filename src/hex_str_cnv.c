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
/*  HEX:文字列変換関数 - hex_str_cnv                                  */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   HEXデータを文字列に変換する。                                    */
/**********************************************************************/
vd  hex_str_cnv( struct ifa_s *ifa )    /* HEX:文字列変換関数         */
{
    li           cnt      ;             /* ループカウンタ             */
    li           size     ;             /* サーチデータサイズ         */
    ch           data[64] ;             /* サーチデータ               */

    trace_start( ifa, "hex_str_cnv" ) ; /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    size = 0 ;                          /* サーチデータサイズの初期化 */
    memset( data, 0x00, sizeof( data ) ) ;
                                        /* サーチデータの初期化       */
/* ------------------------------------------------------------------ */
/* サーチ文字列判定                                                   */
/* ------------------------------------------------------------------ */
    strlcpy( data, "0x", sizeof( data ) ) ;
                                        /* 固定文字列設定             */
    for ( cnt = 0 ; cnt < ifa->search_size ; cnt++ ) {
                                        /* HEXデータ:文字列変換       */
        snprintf( data, sizeof( data ), "%s%02x", data, 
                  (0xff & (ul)ifa->search_str[cnt])) ;
                                        /* quick hack by tatsu        */
    }                                   /* end for                    */
    size = strlen( data ) ;             /* サーチデータサイズの設定   */

/* ------------------------------------------------------------------ */
/* サーチデータ再設定                                                 */
/* ------------------------------------------------------------------ */
    memcpy( ifa->search_str, data, size + 1 ) ;
                                        /* サーチデータ再設定         */
    ifa->search_size = size ;           /* サーチデータサイズ再設定   */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - hex_str_cnv       */
}                                       /* end (hex_str_cnv)          */

/**********************************************************************/
