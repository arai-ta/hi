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
/*    Copyright (c) 2006 Tatsuyoshi                                   */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <string.h>
#include    <stdio.h>
#include    <hi_std.h>

/**********************************************************************/
/*  指定アドレス表示関数 - address_view                               */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   データ表示位置を指定されたアドレスに位置付け、カーソルを最終位置 */
/*   に移動する。                                                     */
/**********************************************************************/
vd  address_view( struct ifa_s *ifa )   /* 指定アドレス表示関数       */
{
    ul            data_offset ;         /* データオフセット(ワーク)   */

    trace_start( ifa, "address_view" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* 指定アドレスを取得し、10進数に変換する                             */
/* ------------------------------------------------------------------ */
    if ( strncmp(ifa->cmd_str, CNTL_CMD_ADRS, 2) == 0 ) {      
                                        /* 16進数指定                 */
        sscanf( ifa->cmd_str, "%x", &data_offset ) ; 
                                        /* 指定アドレスの取得         */
    }                                   /* end if                     */
    else if (( ifa->cmd_str[0] == CNTL_CMD_TOP )||              
             ( ifa->cmd_str[0] == CNTL_CMD_CRNT )||
             ( ifa->cmd_str[0] == CNTL_CMD_LAST )||
             ( ifa->cmd_str[0] == CNTL_CMD_PLUS )||
             ( ifa->cmd_str[0] == CNTL_CMD_MINUS )) {
                                        /* 正規表現指定               */
        hi_regex( ifa, ifa->cmd_str, &data_offset, sizeof( data_offset ) ) ;        
                                        /* 正規表現解析関数           */
    }                                   /* else if end                */
    else {                              /* 10進数指定                 */
        sscanf( ifa->cmd_str, "%d", &data_offset ) ;
                                        /* 指定アドレスの取得         */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* 指定アドレスの妥当性チェックを行う                                 */
/* ------------------------------------------------------------------ */
    data_offset++ ;                     /* ずれの調整                 */
    if ( data_offset > ifa->size ) {    /* 領域を超えて指定           */
        strlcpy( ifa->err_msg, "Input address error",
                 sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - address_view      */
    }                                   /* end if                     */

    ifa->data_offset = data_offset ;    /* データオフセットの更新     */

/* ------------------------------------------------------------------ */
/* データ表示位置を指定アドレス行の先頭に位置付ける                   */
/* ------------------------------------------------------------------ */
    if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* 行の最終位置               */
        ifa->view_offset = ifa->data_offset - 16 ;
                                        /* 表示オフセットの更新       */
    }                                   /* end if                     */
    else {                              /* 行の最終位置以外           */
        ifa->view_offset = ifa->data_offset -
                           ( ifa->data_offset % 16 ) ;
                                        /* 表示オフセットの更新       */
    }                                   /* end else                   */
    data_view( ifa ) ;                  /* データ表示                 */

/* ------------------------------------------------------------------ */
/* カーソル表示位置を末尾に位置付ける                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->target == HEX_DATA ) {    /* HEXデータエリア            */
        if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* 行の最終位置               */
            ifa->cur_pos_x = BASE_X2 + ( 15 * 3 ) ;
                                        /* カーソル位置(X)の設定      */
        }                               /* end if                     */
        else {                          /* 行の最終位置以外           */
            ifa->cur_pos_x = BASE_X2 +
                             ( ifa->data_offset % 16 ) * 3 - 3 ;
                                        /* カーソル位置(X)の設定      */
        }                               /* end if                     */
    }                                   /* end if                     */
    else {                              /* 文字データエリア           */
        if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* 行の最終位置               */
            ifa->cur_pos_x = BASE_X3 + 15 ;
                                        /* カーソル位置(X)の設定      */
        }                               /* end if                     */
        else {                          /* 行の最終位置以外           */
            ifa->cur_pos_x = BASE_X3 + ( ifa->data_offset % 16 ) - 1 ;
                                        /* カーソル位置(X)の設定      */
        }                               /* end if                     */
    }                                   /* end else                   */
    ifa->cur_pos_y = BASE_Y ;           /* カーソル位置(Y)の設定      */
    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* カーソル移動               */
    ifa->hex_pos = CUR_LEFT ;           /* 上位バイトをポイントした事 */
                                        /* を覚える                   */
    refresh() ;                         /* ウィンドウ再描画           */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - address_view      */
}                                       /* end (address_view)         */

/**********************************************************************/
