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
/*  連続データ削除関数(文字) - repeat_c_del                           */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーソル位置の、連続データ削除を行う。                           */
/**********************************************************************/
vd  repeat_c_del( struct ifa_s *ifa, li number )
                                        /* 連続データ削除関数(文字)   */
{
    li           del_size ;             /* 削除サイズ                 */

    trace_start( ifa, "repeat_c_del" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* データサイズチェック                                               */
/* ------------------------------------------------------------------ */
    if ( ifa->size == 0 ) {             /* 削除するデータが存在しない */
        strlcpy( ifa->err_msg, "Delete-data nothing",
                 sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - repeat_c_del      */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* モード表示                                                         */
/* ------------------------------------------------------------------ */
    strlcpy( ifa->mode_msg, MODE_STR_DEL, sizeof( ifa->mode_msg ) ) ;
                                        /* モード設定                 */
    mode_dsp( ifa ) ;                   /* モード表示                 */

/* ------------------------------------------------------------------ */
/* カーソル位置の連続データ削除                                       */
/* ------------------------------------------------------------------ */
    if ( ifa->data_offset > ( ifa->size - number ) ) {
                                        /* 指定サイズ分のデータ無し   */
        del_size = ifa->size - ifa->data_offset + 1 ;
                                        /* 削除サイズの設定           */
        ifa->size = ifa->data_offset - 1 ;
                                        /* データサイズの更新         */
        if ( ifa->data_offset > 1 ) {   /* カーソル位置が先頭以外     */
            ifa->data_offset-- ;        /* データオフセットの更新     */
        }                               /* end if                     */

        if ( ( ifa->size % 16 ) == 0 ) {/* 行の最終位置               */
            if ( ifa->cur_pos_y != BASE_Y ) {
                                        /* 先頭行じゃない             */
                ifa->cur_pos_x = BASE_X3 + 15 ;
                                        /* カーソル位置(X)の設定      */
                ifa->cur_pos_y-- ;      /* カーソル位置(Y)の設定      */
            }                           /* end if                     */
        }                               /* end if                     */
        else {                          /* 行の最終位置以外           */
            ifa->cur_pos_x = BASE_X3 + ( ifa->size % 16 ) - 1 ;
                                        /* カーソル位置(X)の設定      */
        }                               /* end else                   */
    }                                   /* end if                     */
    else {                              /* 最終データ以外             */
        del_size = number ;             /* 削除サイズの設定           */
        memcpy(&ifa->workarea[(ifa->data_offset-1)],
               &ifa->workarea[(ifa->data_offset+number-1)],
                (ifa->size - (ifa->data_offset+number-1))) ;
                                        /* カーソル位置のデータ削除   */
        ifa->size -= number ;           /* データサイズの更新         */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* データの再表示                                                     */
/* ------------------------------------------------------------------ */
    data_view( ifa ) ;                  /* データ表示関数             */

/* ------------------------------------------------------------------ */
/* インフォメーション表示                                             */
/* ------------------------------------------------------------------ */
    snprintf( ifa->inf_msg, sizeof( ifa->inf_msg ), 
              "%d byte data deleted", del_size ) ;
                                        /* インフォメーション設定     */
    inf_msg( ifa ) ;                    /* インフォメーション表示処理 */

    ifa->modif = MOD_ON ;               /* 修正した事を覚える         */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - repeat_c_del      */
}                                       /* end (repeat_c_del)         */

/**********************************************************************/
