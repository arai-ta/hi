/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : May 2004                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 0t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004 Tatsuyoshi                                   */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  ページスクロール関数(下) - page_down                              */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   ページ単位のスクロール(下)を行う。                               */
/**********************************************************************/
vd  page_down( struct ifa_s *ifa )      /* ページスクロール関数(下)   */
{
    li scr_end = 0;

    trace_start( ifa, "page_down" ) ;   /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ページのスクロール                                                 */
/* ------------------------------------------------------------------ */
    ifa->data_offset += ( ( ifa->lines - (BASE_Y + 2) ) * 16 ) ;
                                        /* データオフセットの更新     */
    if ( ifa->data_offset < ifa->size ) {
                                        /* ページスクロール(下)可能   */
        if ( ( ifa->size % 16 ) == 0 ) {
            scr_end = ifa->size - ( ( ifa->lines - (BASE_Y + 1) ) * 16 )
                                + ( ( ifa->cur_pos_y - 1 ) * 16 );
        } else {
            scr_end = ifa->size - ( ( ifa->lines - (BASE_Y + 2) ) * 16 )
                                + ( ( ifa->cur_pos_y - 1 ) * 16 )
                                - ( ifa->size % 16 );
        }
        if ( ifa->data_offset >= scr_end) {
            if ( ( ifa->size % 16 ) == 0 ) {
                                        /* 行の最終位置               */
                ifa->view_offset = ifa->size - 16
                                             - (ifa->lines - BASE_Y - 2 ) * 16;
                                        /* 表示オフセットの更新       */
                ifa->cur_pos_y = ifa->lines 
                                 - ((ifa->size - ifa->data_offset) / 16) 
                                 - BASE_Y - 1;
            } else {                    /* 行の最終位置以外           */
                ifa->view_offset = ifa->size - ( ifa->size % 16 )
                                             - (ifa->lines - BASE_Y - 2 ) * 16;
                                        /* 表示オフセットの更新       */
                ifa->cur_pos_y = ifa->lines - ( ( ifa->size / 16 )
                                 - ( ifa->data_offset / 16 ) )
                                 - BASE_Y - 1;
            }                           /* end else                   */
        } else {
            ifa->view_offset += ( ( ifa->lines - (BASE_Y + 2) ) * 16 ) ;
                                        /* 表示オフセットの更新       */
        }
        data_view( ifa ) ;              /* データ表示                 */
    }                                   /* end if                     */
    else {                              /* 末尾データへ移動           */
        tail_view( ifa ) ;              /* 末尾表示関数               */
    }                                   /* end else                   */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - page_down         */
}                                       /* end (page_down)            */

/**********************************************************************/
