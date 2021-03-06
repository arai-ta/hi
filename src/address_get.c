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
#include    <hi_std.h>
#include    <stdio.h>

/**********************************************************************/
/*  アドレス取得関数 - address_get                                    */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーソル位置から4バイトのデータをアドレスとし、そのアドレスに    */
/*   移動する。                                                       */
/**********************************************************************/
vd  address_get( struct ifa_s *ifa )    /* アドレス取得関数           */
{
    ch           *data ;                /* 変換前データ               */

    trace_start( ifa, "address_get" ) ; /* トレース取得               */
/* ------------------------------------------------------------------ */
/* アドレスを取得し、コマンド入力エリアに設定する                     */
/* ------------------------------------------------------------------ */
    data = &(ifa->workarea[(ifa->data_offset-1)]) ;
                                        /* 変換対象データアドレス設定 */
    DEC_TO_UDCSTR( data, 4, ifa->cmd_str ) ;
                                        /* 指定アドレスの取得         */

/* ------------------------------------------------------------------ */
/* 指定アドレス表示関数をコール                                       */
/* ------------------------------------------------------------------ */
    address_view( ifa ) ;               /* 指定アドレス表示関数       */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - address_get       */
}                                       /* end (address_get)          */

/**********************************************************************/
