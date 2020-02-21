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
/*  サーチコマンド実行関数 - exec_search_cmd                          */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   サーチコマンドを実行する。                                       */
/**********************************************************************/
vd  exec_search_cmd( struct ifa_s *ifa )/* サーチコマンド関数         */
{
    li         ret   ;                  /* リターンコード(汎用)       */
    li         cnt1  ;                  /* ループカウンタ1            */
    li         cnt2  ;                  /* ループカウンタ2            */
    ch         found ;                  /* 文字列検知フラグ           */
    ch         cnv   ;                  /* 文字列:HEX変換フラグ       */

    trace_start( ifa, "exec_search_cmd" ) ;
                                        /* トレース取得               */
/* ------------------------------------------------------------------ */
/* サーチ文字列判定                                                   */
/* ------------------------------------------------------------------ */
    cnv = 0 ;                           /* 文字列:HEX変換フラグ初期化 */
    if ( ifa->target == HEX_DATA ) {    /* バイナリデータ検索         */
        if ( memcmp( ifa->search_str, "0x", 2 ) == 0 ) {
                                        /* HEX検索判定                */
            if ( ( ifa->search_size < 4 ) || 
                 ( ( ifa->search_size % 2 ) != 0 ) ){
                                        /* HEXデータ指定不正          */
                strlcpy( ifa->err_msg, "Search-string error",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
                trace_end( ifa ) ;      /* トレース取得               */
                return ;                /* return - exec_search_cmd   */
            }                           /* end if                     */
            str_hex_cnv( ifa ) ;        /* 文字列:HEX変換             */
            cnv = 1 ;                   /* 文字列:HEX変換フラグ設定   */
        }                               /* end if                     */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 検索文字列情報領域の確保                                           */
/* ------------------------------------------------------------------ */
    if ( ifa->search_info == NULL ) {   /* 領域未確保                 */
        ifa->search_info = (ch *)malloc( ( ifa->size / 8 ) );
                                        /* 検索文字列情報領域の確保   */
        if ( ifa->search_info == NULL ) {
                                        /* 領域の確保失敗             */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "malloc error : errno = %d", errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* エラーメッセージ設定       */
            ifa->endflg = ABORT ;       /* 強制終了指示               */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
    }                                   /* end if                     */
    memset( ifa->search_info, 0x00, ( ifa->size / 8 ) ) ;
                                        /* 検索文字列情報領域の初期化 */
/* ------------------------------------------------------------------ */
/* サーチコマンド前処理                                               */
/* ------------------------------------------------------------------ */
    if ( ifa->cmd == CMD_NEXT ) {       /* 次検索                     */
        if ( ifa->search == NEXT_SEARCH ) {
                                        /* サーチ方向は、順検索       */
            ifa->cmd = CMD_SEARCH ;     /* コマンドの置換             */
        }                               /* end if                     */
        else {                          /* サーチ方向は、逆検索       */
            ifa->cmd = CMD_RSEARCH ;    /* コマンドの置換             */
        }                               /* end else                   */
    }                                   /* end if                     */
    else if ( ifa->cmd == CMD_REVERSE) {
                                        /* 逆次検索                   */
        if ( ifa->search == NEXT_SEARCH ) {
                                        /* サーチ方向は、逆検索       */
            ifa->cmd = CMD_RSEARCH ;    /* コマンドの置換             */
        }                               /* end if                     */
        else {                          /* サーチ方向は、順検索       */
            ifa->cmd = CMD_SEARCH ;     /* コマンドの置換             */
        }                               /* end else                   */
    }                                   /* end if                     */
    else {                              /* 初期検索                   */
        if ( ifa->reverse == REVERSE ) {/* 検索文字列の反転表示指定   */
            cnt1 = 0 ;                  /* ループカウンタの初期化     */
            while ( cnt1 < ifa->size ) {/* 先頭位置から、検索開始     */
                ret = memcmp( &ifa->workarea[cnt1], ifa->search_str,
                              ifa->search_size ) ;
                if ( ret == 0 ) {       /* 文字列検知                 */
                    for ( cnt2 = cnt1 ; cnt2 < ( cnt1 + ifa->search_size ) ;
                          cnt2++ ) {    /* 検索文字列サイズのループ   */
                        STANDON( cnt2 ) ;
                                        /* 検索文字列情報の設定       */
                    }                   /* end for                    */
                    cnt1 += ifa->search_size ;
                                        /* 検索位置の更新             */
                    continue ;          /* continue while             */
                }                       /* end if                     */
                cnt1++ ;                /* ループカウンタの更新       */
            }                           /* end while                  */
        }                               /* end if                     */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* サーチコマンド実行処理                                             */
/* ------------------------------------------------------------------ */
    if ( ifa->cmd == CMD_SEARCH ) {     /* 順サーチ                   */
        found = 0 ;                     /* 文字列検知フラグの初期化   */
        for ( cnt2 = ifa->data_offset+1 ; cnt2 < ifa->size ; cnt2++ ) {
                                        /* 現在位置から、検索開始     */
            ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                          ifa->search_size ) ;
            if ( ret == 0 ) {           /* 文字列検知                 */
                found = 1 ;             /* 文字列検知フラグ設定       */
                break ;                 /* break for                  */
            }                           /* end if                     */
        }                               /* end for                    */
#ifdef SEARCH_WRAP
        if ( found == 0 ) {             /* 文字列存在せず             */
            for ( cnt2 = 0 ; cnt2 <= ifa->data_offset ; cnt2++ ) {
                                        /* 最初位置から、検索開始     */
                ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                              ifa->search_size ) ;
                if ( ret == 0 ) {       /* 文字列検知                 */
                    found = 2 ;         /* 文字列検知フラグ設定       */
                    break ;             /* break for                  */
                }                       /* end if                     */
            }                           /* end for                    */
        }                               /* end if                     */
#endif
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 逆サーチコマンド実行処理                                           */
/* ------------------------------------------------------------------ */
    else {                              /* 逆サーチ                   */
        found = 0 ;                     /* 文字列検知フラグの初期化   */
        for ( cnt2 = ifa->data_offset-2 ; cnt2 >= 0 ; cnt2-- ) {
                                        /* 現在位置から、検索開始     */
            ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                          ifa->search_size ) ;
            if ( ret == 0 ) {           /* 文字列検知                 */
                found = 1 ;             /* 文字列検知フラグ設定       */
                break ;                 /* break for                  */
            }                           /* end if                     */
        }                               /* end for                    */
#ifdef SEARCH_WRAP
        if ( found == 0 ) {             /* 文字列存在せず             */
            for ( cnt2 = ifa->size ; cnt2 >= ifa->data_offset-1 ; cnt2-- ) {
                                        /* 最終位置から、検索開始     */
                ret = memcmp( &ifa->workarea[cnt2], ifa->search_str,
                              ifa->search_size ) ;
                if ( ret == 0 ) {       /* 文字列検知                 */
                    found = 2 ;         /* 文字列検知フラグ設定       */
                    break ;             /* break for                  */
                }                       /* end if                     */
            }                           /* end for                    */
        }                               /* end if                     */
#endif
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* サーチ結果の画面再描画                                             */
/* ------------------------------------------------------------------ */
    if ( found != 0 ) {                 /* 文字列が存在した           */
        ifa->data_offset = cnt2 + 1 ;   /* データオフセットの更新     */
        ifa->view_offset = cnt2 - ( cnt2 % 16 ) ;
                                        /* 表示オフセットの更新       */
        data_view( ifa ) ;              /* データ表示                 */
        if ( ifa->target == HEX_DATA ) {/* HEXデータエリア            */
            if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* カーソル位置が一番右       */
                ifa->cur_pos_x = BASE_X2 + 15 * 3 ;
                                        /* カーソル位置(X)の設定      */
            }                           /* end if                     */
            else {                      /* カーソル位置が一番右以外   */
                ifa->cur_pos_x = BASE_X2 +
                                 ( ifa->data_offset % 16 ) * 3 - 3 ;
                                        /* カーソル位置(X)の設定      */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 文字データエリア           */
            if ( ( ifa->data_offset % 16 ) == 0 ) {
                                        /* カーソル位置が一番右       */
                ifa->cur_pos_x = BASE_X3 + 15 ;
                                        /* カーソル位置(X)の設定      */
            }                           /* end if                     */
            else {                      /* カーソル位置が一番右以外   */
                ifa->cur_pos_x = BASE_X3 +
                                 ( ifa->data_offset % 16 ) - 1 ;
                                        /* カーソル位置(X)の設定      */
            }                           /* end else                   */
        }                               /* end else                   */
        ifa->cur_pos_y = BASE_Y ;       /* カーソル位置(Y)の設定      */
        move( ifa->cur_pos_y, ifa->cur_pos_x ) ;
                                        /* カーソル移動               */
        ifa->hex_pos = CUR_LEFT ;       /* 上位バイトをポイントした事 */
                                        /* を覚える                   */
#ifdef SEARCH_WRAP
        if ( found == 2 ) {             /* ラップして検知             */
            strlcpy( ifa->err_msg, "Search wrapped", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end else                   */
#endif
    }                                   /* end else                   */
    else {                              /* 文字列が存在しない         */
        strlcpy( ifa->err_msg, "Pattern not found", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
    }                                   /* end else                   */
    refresh() ;                         /* ウィンドウ再描画           */

    if ( cnv == 1 ) {                   /* 文字列:HEX変換した         */
        hex_str_cnv( ifa ) ;            /* HEX:文字列変換             */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - exec_search_cmd   */
}                                       /* end (exec_search_cmd)      */

/**********************************************************************/
