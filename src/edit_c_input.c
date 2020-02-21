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
/*  データ挿入関数(文字) - edit_c_input                               */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーソル位置から、データの挿入を行う。                           */
/**********************************************************************/
vd  edit_c_input( struct ifa_s *ifa )   /* データ挿入関数(文字)       */
{
    li           data ;                 /* 入力データ領域             */
    li           pos_tail ;             /* データ表示領域の下         */
    li           pos_left ;             /* データ表示領域の左         */
    li           pos_right ;            /* データ表示領域の右         */
    ch          *work_tmp ;             /* 一時作業領域               */

#include    <hi_ebcdic.h>

    trace_start( ifa, "edit_c_input" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    pos_tail  = ifa->lines - 2 ;        /* 最終行の設定               */
    pos_left  = BASE_X3 ;               /* 左端の設定                 */
    pos_right = pos_left + 14 ;         /* 右端の設定                 */

/* ------------------------------------------------------------------ */
/* インフォメーション表示                                             */
/* ------------------------------------------------------------------ */
    strlcpy( ifa->mode_msg, MODE_STR_INS, sizeof( ifa->mode_msg) ) ;
                                        /* モード設定                 */
    mode_dsp( ifa ) ;                   /* モード表示                 */

/* ------------------------------------------------------------------ */
/* 入力データの取得と判定                                             */
/* ------------------------------------------------------------------ */
    while ( 1 ) {                       /* 無限ループに突入           */
        data = getch() ;                /* 入力データ(１文字)取得     */
        if ( data == ESCAPE ) {         /* 編集モード終了             */
            cur_move_c_h( ifa ) ;       /* カーソル左移動関数(文字)   */
            break ;                     /* break while                */
        }                               /* end if                     */

        if ( ifa->lang == LANG_EBCDIC ) {
                                        /* EBCDIC(K)の時は変換が必要  */
            ASCII_TO_EBCDIC( data, ifa->ebcdic ) ;
                                        /* 変換 [ ASCII → EBCDIC ]   */
        }                               /* end if                     */

        area_check( ifa ) ;             /* 作業領域チェック関数       */
        if ( ifa->area_size >= ifa->max_size ) {
                                        /* 最大サイズに到達           */
            cur_move_c_h( ifa ) ;       /* カーソル左移動関数(文字)   */
            break ;                     /* break while                */
        }                               /* end if                     */

        if ( ifa->size == 0 ) {         /* データ無し時に、先頭から   */
            ifa->workarea[(ifa->data_offset-1)] = (uc)data ;
                                        /* 取得したデータの格納       */
        }                               /* end if                     */
        else {                          /* データの途中に、挿入       */
            work_tmp = (ch *)malloc( ifa->area_size + ifa->alloc_size ) ;
                                        /* 一時作業領域確保           */
            if ( work_tmp == NULL ) {   /* 一時作業領域の確保失敗     */
                snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                          "malloc error : errno = %d", errno ) ;
                strlcpy( ifa->perr_msg, "malloc", sizeof( ifa->perr_msg) ) ;
                                        /* エラーメッセージ設定       */
                ifa->endflg = ABORT ;   /* 強制終了指示               */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end if                     */

            memcpy(work_tmp, &ifa->workarea[(ifa->data_offset-1)],
                   (ifa->size - ifa->data_offset + 1)) ;
                                        /* カーソル以降のデータ退避   */
            ifa->workarea[(ifa->data_offset-1)] = (uc)data ;
                                        /* 取得したデータの格納       */
            memcpy(&ifa->workarea[(ifa->data_offset)], work_tmp,
                   (ifa->size - ifa->data_offset + 1)) ;
                                        /* 退避したデータの復元       */
            free( work_tmp ) ;          /* 一時作業領域の解放         */
        }                               /* end else                   */

        ifa->data_offset++ ;            /* データオフセットの更新     */
        ifa->size++ ;                   /* データサイズの更新         */

/* ------------------------------------------------------------------ */
/* カーソル位置の判定                                                 */
/* ------------------------------------------------------------------ */
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

/* ------------------------------------------------------------------ */
/* データの再表示                                                     */
/* ------------------------------------------------------------------ */
        data_view( ifa ) ;              /* データ表示関数             */

        ifa->modif = MOD_ON ;           /* 修正した事を覚える         */
    }                                   /* end while                  */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - edit_c_input      */
}                                       /* end (edit_c_input)         */

/**********************************************************************/
