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
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  データ追加関数(文字) - edit_c_add                                 */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーソル位置の次から、データの追加を行う。                       */
/**********************************************************************/
vd  edit_c_add( struct ifa_s *ifa )     /* データ追加関数(文字)       */
{
    li           pos_tail ;             /* データ表示領域の下         */
    li           pos_left ;             /* データ表示領域の左         */
    li           pos_right ;            /* データ表示領域の右         */

    trace_start( ifa, "edit_c_add" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    pos_tail  = ifa->lines - 2 ;        /* 最終行の設定               */
    pos_left  = BASE_X3 ;               /* 左端の設定                 */
    pos_right = pos_left + 14 ;         /* 右端の設定                 */

/* ------------------------------------------------------------------ */
/* インフォメーション表示                                             */
/* ------------------------------------------------------------------ */
    strlcpy( ifa->mode_msg, MODE_STR_INS, sizeof( ifa->mode_msg ) ) ;
                                        /* モード設定                 */
    mode_dsp( ifa ) ;                   /* モード表示                 */

/* ------------------------------------------------------------------ */
/* 初期カーソル位置の設定                                             */
/* ------------------------------------------------------------------ */
    if ( ifa->size != 0 ) {             /* データの途中に、挿入       */
        ifa->data_offset++ ;            /* データオフセットの更新     */
        if ( ifa->cur_pos_x > pos_right ) {
                                        /* カーソル位置が、一番右     */
            ifa->cur_pos_x = pos_left ; /* カーソル位置(X)の設定      */
            if ( ifa->cur_pos_y < pos_tail ) {
                                        /* カーソル位置が、最終行以外 */
                ifa->cur_pos_y++ ;      /* カーソル位置(Y)の設定      */
            }                           /* end if                     */
            else {                      /* カーソル位置が、最終行     */
                ifa->view_offset += 16 ;/* ウィンドウのスクロール     */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 行の最終位置以外           */
            ifa->cur_pos_x++ ;          /* カーソル位置(X)の設定      */
        }                               /* end else                   */
        data_view( ifa ) ;              /* データ表示関数             */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 以降の処理は、データ挿入関数(文字)に任せる                         */
/* ------------------------------------------------------------------ */
    edit_c_input( ifa ) ;               /* データ挿入関数(文字)       */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - edit_c_add        */
}                                       /* end (edit_c_add)           */

/**********************************************************************/
