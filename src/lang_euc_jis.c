/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Oct 2000                                 */
/* @(#) Version : 2.2                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  JIS表示関数 - lang_euc_jis                                        */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   文字データを、変換 [ JIS → EUC ] してから表示する。             */
/**********************************************************************/
vd  lang_euc_jis( struct ifa_s *ifa )   /* JIS表示関数                */
{
    li           cnt            ;       /* ループカウンタ             */
    li           pos_x          ;       /* X座標                      */
    li           pos_y          ;       /* Y座標                      */
    li           escp_size      ;       /* エスケープサイズ           */
    li           escp_disp_size ;       /* エスケープ記号表記サイズ   */
    uc           escp_str[8]    ;       /* エスケープ文字列           */
    uc           check[6]       ;       /* チェックデータ             */
    uc           char_data      ;       /* 文字データ                 */
    ch           word_flg       ;       /* 2バイト文字フラグ          */
    ch           escp_flg       ;       /* エスケープフラグ           */

    trace_start( ifa, "lang_euc_jis" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    pos_x = BASE_X3 ;                   /* ベース座標(X)の設定        */
    pos_y = BASE_Y ;                    /* ベース座標(Y)の設定        */
    word_flg = 0 ;                      /* 2バイト文字フラグの初期化  */
    escp_flg = 0 ;                      /* エスケープの初期化         */
    char_data = 0x00 ;                  /* 文字データの初期化         */
    escp_size = 0 ;
    escp_disp_size = 0 ;

/* ------------------------------------------------------------------ */
/* データチェック                                                     */
/* ------------------------------------------------------------------ */
    if ( ifa->view_offset > 0 ) {       /* 先頭以外                   */
        for ( cnt = ifa->view_offset ; cnt >= 0 ; cnt-- ) {
                                        /* 前データチェック           */
            memcpy(check, &ifa->workarea[cnt], 6) ;
                                        /* チェックデータ(6バイト)取得*/
            if ( ( memcmp( check, JIS_ASCII, 3 ) == 0 )||
                 ( memcmp( check, JIS_ROMAN_SET, 3 ) == 0 )||
                 ( memcmp( check, JIS_HALF_KANA, 3 ) == 0 ) ) {
                                        /* 1バイト文字                */
                word_flg = 0 ;          /* 1バイト文字の設定          */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* エスケープ情報の取得       */
                if ( ( ifa->view_offset - cnt ) < escp_size ) {
                                        /* エスケープ情報の処理中     */
                    escp_flg = 1 ;      /* エスケープの設定           */
                    escp_disp_size = ( ifa->view_offset - cnt ) ;
                                        /* エスケープ情報の修正       */
                }                       /* end if                     */
                else {                  /* 可視文字の処理中           */
                    escp_flg = 0 ;      /* エスケープの解除           */
                    escp_disp_size = 0 ;/* エスケープ情報の初期化     */
                                        /* エスケープ情報の修正       */
                }                       /* end else                   */
                break ;                 /* break for                  */
            }                           /* end if                     */
            else if ( ( memcmp( check, JIS_X0208_OLD, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_NEW, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_ADD, 6 ) == 0 )||
                      ( memcmp( check, JIS_X0212, 3 ) == 0 ) ) {
                                        /* 2バイト文字                */
                word_flg = 1 ;          /* 2バイト文字の設定          */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* エスケープ情報の取得       */
                if ( ( ifa->view_offset - cnt ) < escp_size ) {
                                        /* エスケープ情報の処理中     */
                    escp_flg = 1 ;      /* エスケープの設定           */
                    escp_disp_size = ( ifa->view_offset - cnt ) ;
                                        /* エスケープ情報の修正       */
                }                       /* end if                     */
                else {                  /* 可視文字の処理中           */
                    escp_flg = 0 ;      /* エスケープの解除           */
                    escp_disp_size = 0 ;/* エスケープ情報の初期化     */
                    if ( ( ( ifa->view_offset - cnt ) % 2 ) == 0 ) {
                                        /* 2バイト文字の1バイト目     */
                        word_flg = 2 ;  /* 2バイト文字処理中          */
                    }                   /* end else                   */
                }                       /* end else                   */
                break ;                 /* break for                  */
            }                           /* end else if                */
        }                               /* end for                    */
    }                                   /* end if                     */
    
/* ------------------------------------------------------------------ */
/* データの表示                                                       */
/* ------------------------------------------------------------------ */
    for ( cnt = ifa->view_offset ; cnt < ifa->size ; cnt++ ) {
                                        /* 全データの処理             */
        if ( pos_y == ( ifa->lines - 1 ) ) {
                                        /* 最終行                     */
            break ;                     /* データ表示の終了           */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* エスケープコードをチェックする                                     */
/* ------------------------------------------------------------------ */
        memcpy(check, &ifa->workarea[cnt], 6) ;
                                        /* チェックデータ(6バイト)取得*/
        if ( escp_flg == 0 ) {          /* エスケープチェック必要     */
            if ( ( memcmp( check, JIS_ASCII, 3 ) == 0 )||
                 ( memcmp( check, JIS_ROMAN_SET, 3 ) == 0 )||
                 ( memcmp( check, JIS_HALF_KANA, 3 ) == 0 ) ) {
                                        /* 1バイト文字                */
                word_flg = 0 ;          /* 1バイト文字の設定          */
                escp_flg = 1 ;          /* エスケープの設定           */
                escp_disp_size = 0 ;    /* 記号表記サイズの初期化     */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* エスケープ情報の取得       */
            }                           /* end if                     */
            else if ( ( memcmp( check, JIS_X0208_OLD, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_NEW, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_ADD, 6 ) == 0 )||
                      ( memcmp( check, JIS_X0212, 3 ) == 0 ) ) {
                                        /* 2バイト文字                */
                word_flg = 1 ;          /* 2バイト文字の設定          */
                escp_flg = 1 ;          /* エスケープの設定           */
                escp_disp_size = 0 ;    /* 記号表記サイズの初期化     */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* エスケープ情報の取得       */
            }                           /* end else if                */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* エスケープコード処理                                               */
/* ------------------------------------------------------------------ */
        if ( escp_flg == 1 ) {          /* エスケープ処理中           */
            standout() ;                /* 強調モード開始             */
            move(pos_y, pos_x) ; printw("%c", escp_str[escp_disp_size]) ;
                                        /* エスケープ記号表記の表示   */
            standend() ;                /* 強調モード終了             */
            pos_x++ ;                   /* カーソル位置更新           */
            escp_disp_size++ ;          /* 記号表記サイズの更新       */
            if ( escp_disp_size >= escp_size ) {
                                        /* エスケープ処理終了         */
                escp_flg = 0 ;          /* エスケープの解除           */
            }                           /* end if                     */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* 文字コード処理                                                     */
/* ------------------------------------------------------------------ */
        else {                          /* 文字データ処理中           */
            if ( word_flg == 0 ) {      /* 1バイト文字処理中          */
                if ((check[0] >= 0x20)&&(check[0] <= 0x7e)) {
                                        /* 可視文字(1バイト文字)      */
                    char_data = check[0] ;
                                        /* そのまま表示               */
                }                       /* end if                     */
                else {                  /* 不可視文字                 */
                    char_data = TEN ;   /* 不可視文字の為,(.)に変換   */
                }                       /* end else                   */
                move(pos_y, pos_x) ; printw("%c", char_data) ;
                                        /* 1バイト文字の表示          */
                pos_x++ ;               /* カーソル位置更新           */
            }                           /* end if                     */
            else if ( word_flg == 1 ) { /* 2バイト文字処理開始        */
                JIS_TO_EUC( check[0], check[1] ) ;
                                        /* 変換 [ JIS → EUC ]        */
                move(pos_y, pos_x) ; printw("%.2s", check) ;
                                        /* 1バイト文字の表示          */
                word_flg = 2 ;          /* 2バイト文字処理中          */
                pos_x += 2 ;            /* カーソル位置更新           */
            }                           /* end else if                */
            else if ( word_flg == 2 ) { /* 2バイト文字処理中          */
                if ( cnt == ifa->view_offset ) {
                                        /* 2バイト文字処理中から開始  */
                    move(pos_y, BASE_X3) ; printw("%c", '@') ;
                                        /* 特殊文字の表示             */
                    pos_x++ ;           /* カーソル位置更新           */
                }                       /* end if                     */
                word_flg = 1 ;          /* 2バイト文字処理開始        */
            }                           /* end else                   */
        }                               /* end else                   */

        if ( ( cnt % 16 ) == 15 ) {     /* 1行の終了                  */
            pos_y++ ;                   /* 次の行へ                   */
            if ( ( pos_x == ( BASE_X3 + 17 ) )&&
                 ( pos_y < ( ifa->lines - 1 ) ) ) {
                                        /* 行跨りの2バイト文字        */
                move(pos_y, BASE_X3) ; printw("%c", '@') ;
                                        /* 特殊文字の表示             */
                pos_x = BASE_X3 + 1 ;   /* ベース座標(X)の設定        */
            }                           /* end if                     */
            else {                      /* 行の先頭から               */
                pos_x = BASE_X3 ;       /* ベース座標(X)の設定        */
            }                           /* end else                   */
        }                               /* end if                     */
    }                                   /* end for                    */

    refresh() ;                         /* ウィンドウの再描画         */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - lang_euc_jis      */
}                                       /* end (lang_euc_jis)         */

/**********************************************************************/
