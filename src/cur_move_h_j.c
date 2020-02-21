/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998                                            */
/* @(#) Version : 2.0                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  カーソル下移動関数(HEX) - cur_move_h_j                            */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーソルを下移動し、ウィンドウを再描画する。(HEXデータ用)        */
/**********************************************************************/
vd  cur_move_h_j( struct ifa_s *ifa )   /* カーソル下移動関数(HEX)    */
{
    li           pos_tail ;             /* データ表示領域の下         */

    trace_start( ifa, "cur_move_h_j" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* カーソルを下に移動                                                 */
/* ------------------------------------------------------------------ */
    pos_tail = ifa->lines - 2 ;         /* 最終行の設定               */

    if ( ( ifa->data_offset + 15 ) < ifa->size ) {
                                        /* 未表示データ有り           */
        if ( ifa->cur_pos_y < pos_tail ) {
                                        /* カーソル位置が、最終行以外 */
            ifa->data_offset += 16 ;    /* データオフセットの更新     */
            ifa->cur_pos_y++ ;          /* カーソル位置(Y座標)の更新  */
        }                               /* end if                     */
        else if ( ifa->size > ( ifa->view_offset + 16 ) ) {
                                        /* カーソルが最終行で、未表示 */
                                        /* データ有り                 */
            ifa->data_offset += 16 ;    /* データオフセットの更新     */
            ifa->view_offset += 16 ;    /* 表示オフセットの更新       */
            data_view( ifa ) ;          /* データ表示                 */
        }                               /* end else if                */
        move(OFST_Y, OFST_X) ;          /* カーソル移動               */
        printw("%08x", ifa->data_offset - 1) ;
                                        /* オフセットの表示           */
        move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* カーソル移動               */
        refresh() ;                     /* ウィンドウ再描画           */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - cur_move_j        */
}                                       /* end (cur_move_j)           */

/**********************************************************************/
