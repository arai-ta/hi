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
/*  データ変換関数(複数:HEX) - edit_h_rep_2                           */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーソル位置から、連続したデータの変換を行う。                   */
/**********************************************************************/
vd  edit_h_rep_2( struct ifa_s *ifa )   /* データ変換関数(複数:HEX)   */
{
    li           data ;                 /* 入力データ領域             */
    li           pos_tail ;             /* データ表示領域の下         */
    li           pos_left ;             /* データ表示領域の左         */
    li           pos_right ;            /* データ表示領域の右         */

    trace_start( ifa, "edit_h_rep_2" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    pos_tail  = ifa->lines - 2 ;        /* 最終行の設定               */
    pos_left  = BASE_X2 ;               /* 左端の設定                 */
    pos_right = pos_left + ( 3 * 15 ) ; /* 右端の設定                 */

/* ------------------------------------------------------------------ */
/* インフォメーション表示                                             */
/* ------------------------------------------------------------------ */
    strlcpy( ifa->mode_msg, MODE_STR_REP, sizeof( ifa->mode_msg ) ) ;
                                        /* モード設定                 */
    mode_dsp( ifa ) ;                   /* モード表示                 */

/* ------------------------------------------------------------------ */
/* 変更データの判定                                                   */
/* ------------------------------------------------------------------ */
    if ( ifa->size == 0 ) {             /* 変更データが、存在しない   */
        strlcpy( ifa->err_msg, "Replace data nothing",
                 sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - edit_h_rep_2      */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 入力データの取得と判定                                             */
/* ------------------------------------------------------------------ */
    while ( 1 ) {                       /* 無限ループに突入           */
        if ( ifa->hex_pos == CUR_LEFT ) {
                                        /* カーソル位置が、上位バイト */
            data = getch() ;            /* 入力データ(上位バイト)取得 */
            if ( data == ESCAPE ) {     /* 編集モード終了             */
                cur_move_h_h( ifa ) ;   /* カーソル左移動関数(文字)   */
                break ;                 /* break while                */
            }                           /* end if                     */

            if ( ( ( (ch)data < '0' ) || ( (ch)data > '9' ) ) &&
                 ( ( (ch)data < 'a' ) || ( (ch)data > 'f' ) ) ) {
                                        /* 16進データ以外             */
                strlcpy( ifa->err_msg, "Input data error",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
                break ;                 /* break while                */
            }                           /* end if                     */
            else {                      /* 可視文字の入力             */
                ifa->modif = MOD_ON ;   /* 修正した事を覚える         */
                LEFT_DATA_SET((ifa->workarea[(ifa->data_offset-1)]),
                              (data)) ;
                                        /* 取得したデータの格納       */
            }                           /* end else                   */
            ifa->cur_pos_x++ ;          /* カーソルを、下位バイトへ   */
            ifa->hex_pos = CUR_RIGHT ;  /* カーソルを、下位バイトへ   */
            data_view( ifa ) ;          /* データ表示関数             */
        }                               /* end if                     */

        data = getch() ;                /* 入力データ(下位バイト)取得 */
        if ( data == ESCAPE ) {         /* 編集モード終了             */
            cur_move_h_h( ifa ) ;       /* カーソル左移動関数(文字)   */
            break ;                     /* break while                */
        }                               /* end if                     */

        if ( ( ( (ch)data < '0' ) || ( (ch)data > '9' ) ) &&
             ( ( (ch)data < 'a' ) || ( (ch)data > 'f' ) ) ) {
                                        /* 16進データ以外             */
            strlcpy( ifa->err_msg, "Input data error",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
            break ;                     /* break while                */
        }                               /* end if                     */
        else {                          /* 可視文字の入力             */
            RIGHT_DATA_SET((ifa->workarea[(ifa->data_offset-1)]),
                           (data)) ;    /* 取得したデータの格納       */
        }                               /* end else                   */

/* ------------------------------------------------------------------ */
/* カーソル位置の判定                                                 */
/* ------------------------------------------------------------------ */
        if ( ifa->size != ifa->data_offset ) {
                                        /* 作業領域内                 */
            ifa->data_offset++ ;        /* データオフセット値の更新   */
            if ( ifa->cur_pos_x > pos_right ) {
                                        /* カーソル位置が、一番右     */
                ifa->cur_pos_x = pos_left ;
                                        /* カーソル位置(X)の設定      */
                if ( ifa->cur_pos_y < pos_tail ) {
                                        /* カーソル位置が、最終行以外 */
                    ifa->cur_pos_y++ ;  /* カーソル位置(Y)の設定      */
                }                       /* end if                     */
                else {                  /* カーソル位置が、最終行     */
                    ifa->view_offset += 16 ;
                                        /* ウィンドウのスクロール     */
                }                       /* end else                   */
            }                           /* end if                     */
            else {                      /* 行の最終位置以外           */
                ifa->cur_pos_x += 2 ;   /* カーソル位置(X)の設定      */
            }                           /* end else                   */
            ifa->hex_pos = CUR_LEFT ;   /* 下位バイトをポイントした事 */
                                        /* を覚える                   */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* データの再表示                                                     */
/* ------------------------------------------------------------------ */
        data_view( ifa ) ;              /* データ表示関数             */

    }                                   /* end while                  */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - edit_h_rep_2      */
}                                       /* end (edit_h_rep_2)         */

/**********************************************************************/
