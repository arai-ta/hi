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
/*  サーチコマンド関数 - search_cmd                                   */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   サーチコマンドを処理する。                                       */
/**********************************************************************/
vd  search_cmd( struct ifa_s *ifa )     /* サーチコマンド関数         */
{

    ch    search_str[64] ;              /* 検索文字列(退避用)         */
    ul    lpcnt          ;              /* コード変換用ループカウンタ */

#include    <hi_ebcdic.h>

    trace_start( ifa, "search_cmd" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    strlcpy( search_str, ifa->search_str, sizeof( search_str ) ) ;
                                        /* 検索文字列の退避           */
/* ------------------------------------------------------------------ */
/* サーチコマンド                                                     */
/* ------------------------------------------------------------------ */
    echo() ;                            /* エコー入力モード           */
    move( ifa->cur_cmd_y, ifa->cur_cmd_x ) ;
                                        /* カーソル位置をコマンド行へ */
    clrtoeol() ;                        /* コマンド行のクリア         */
    addch( (ch)ifa->cmd ) ;             /* サーチコマンド文字の表示   */
    refresh() ;                         /* 画面の再描画               */
    getnstr( ifa->search_str, 63 ) ;    /* サーチコマンドを取得       */
    move( ifa->cur_cmd_y, ifa->cur_cmd_x ) ;
                                        /* カーソル位置をコマンド行へ */
    clrtoeol() ;                        /* コマンド行のクリア         */
    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* カーソル位置を戻す         */
    noecho() ;                          /* エコー入力モード解除       */

    if ( ( ifa->search_str[0] < 0x20 )||
         ( ifa->search_str[0] > 0x7e ) ) {
                                        /* サーチ文字列指定無し       */
        strlcpy( ifa->search_str, search_str, sizeof( ifa->search_str ) ) ;
                                        /* 検索文字列の復元           */
    }                                   /* end if                     */

    if ( strlen( ifa->search_str ) != 0 ) {
                                        /* サーチ文字列指定有り       */
        ifa->search_size = strlen( ifa->search_str ) ;
                                        /* サーチコマンドサイズの設定 */
        if ( ( ifa->target == CHAR_DATA )&&
             ( ifa->lang == LANG_EBCDIC ) ) {
                                        /* EBCDIC(K)の時は変換が必要  */
            for ( lpcnt = 0 ; lpcnt < ifa->search_size ; lpcnt++ ) {
                                        /* サーチコマンドサイズループ */
                ASCII_TO_EBCDIC( ifa->search_str[lpcnt], ifa->ebcdic ) ;
                                        /* 変換 [ ASCII → EBCDIC ]   */
            }                           /* end for                    */
        }                               /* end if                     */
        exec_search_cmd( ifa ) ;        /* サーチコマンドの実行       */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - search_cmd        */
}                                       /* end (search_cmd)           */

/**********************************************************************/
