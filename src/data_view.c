/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Aug 2000                                 */
/* @(#) Version : 2.1                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* インクルードファイル                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  データ表示関数 - data_view                                        */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   ウィンドウに、データを表示する。                                 */
/**********************************************************************/
vd  data_view( struct ifa_s *ifa )      /* データ表示関数             */
{
    li           cnt         ;          /* ループカウンタ             */
    li           pos_x[2]    ;          /* X座標                      */
    li           pos_y       ;          /* Y座標                      */
    li           cur_pos_x   ;          /* カーソル位置(X座標)        */
    li           cur_pos_y   ;          /* カーソル位置(Y座標)        */
    li           term_trgt   ;          /* 対象機能関数アドレス       */
    li           lang_trgt   ;          /* 対象機能関数アドレス       */
    ch           hex_data[2] ;          /* HEXデータ                  */
    uc           num_data    ;          /* 数値データ                 */
    vd        (*funcmtx[FUNC_T_MAX][FUNC_L_MAX])() ;
                                        /* 対象機能関数アドレス       */

    trace_start( ifa, "data_view" ) ;   /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    pos_x[0] = BASE_X1 ;                /* ベース座標(X1)の設定       */
    pos_x[1] = BASE_X2 ;                /* ベース座標(X2)の設定       */
    pos_y = BASE_Y ;                    /* ベース座標(Y)の設定        */

    cur_pos_x = ifa->cur_pos_x ;        /* カーソル位置(X座標)の退避  */
    cur_pos_y = ifa->cur_pos_y ;        /* カーソル位置(Y座標)の退避  */

    ifa->cur_pos_x = pos_x[1] ;         /* カーソル位置(X座標)の設定  */
    ifa->cur_pos_y = pos_y ;            /* カーソル位置(Y座標)の設定  */

    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* カーソルの移動             */
    clrtobot() ;                        /* ウィンドウのクリア         */

/* ------------------------------------------------------------------ */
/* 関数アドレス設定                                                   */
/* ------------------------------------------------------------------ */
    funcmtx[FUNC_T_A][FUNC_L_A] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_A][FUNC_L_E] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_A][FUNC_L_S] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_A][FUNC_L_J] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_A][FUNC_L_B] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_E][FUNC_L_A] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_E][FUNC_L_E] = lang_euc_euc ;
                                        /* EUC表示関数                */
    funcmtx[FUNC_T_E][FUNC_L_S] = lang_euc_sjis ;
                                        /* SJIS表示関数               */
    funcmtx[FUNC_T_E][FUNC_L_J] = lang_euc_jis ;
                                        /* JIS表示関数                */
    funcmtx[FUNC_T_E][FUNC_L_B] = lang_ascii_ebcdic ;
                                        /* EBCDIC表示関数             */
    funcmtx[FUNC_T_S][FUNC_L_A] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_S][FUNC_L_E] = lang_sjis_euc ;
                                        /* EUC表示関数                */
    funcmtx[FUNC_T_S][FUNC_L_S] = lang_sjis_sjis ;
                                        /* SJIS表示関数               */
    funcmtx[FUNC_T_S][FUNC_L_J] = lang_sjis_jis ;
                                        /* JIS表示関数                */
    funcmtx[FUNC_T_S][FUNC_L_B] = lang_ascii_ebcdic ;
                                        /* EBCDIC表示関数             */
    funcmtx[FUNC_T_O][FUNC_L_A] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_O][FUNC_L_E] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_O][FUNC_L_S] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_O][FUNC_L_J] = lang_ascii ;
                                        /* ASCII表示関数              */
    funcmtx[FUNC_T_O][FUNC_L_B] = lang_ascii ;
                                        /* ASCII表示関数              */
/* ------------------------------------------------------------------ */
/* オフセットの表示                                                   */
/* ------------------------------------------------------------------ */
    move(OFST_Y, OFST_X) ;              /* カーソル移動               */
    if ( ifa->data_offset == 0 ) {      /* カーソル位置が、先頭       */
        printw("%08x", ifa->data_offset) ;
                                        /* オフセットの表示           */
    }                                   /* end if                     */
    else {                              /* カーソル位置が、先頭以外   */
        printw("%08x", ifa->data_offset - 1) ;
                                        /* オフセットの表示           */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* データの表示                                                       */
/* ------------------------------------------------------------------ */
    move(pos_y, pos_x[0]) ; printw("%08x", 0) ;
                                        /* データ無し時のアドレス表示 */
    for ( cnt = ifa->view_offset ; cnt < ifa->size ; cnt++ ) {
                                        /* 全データの処理             */
        if ( pos_y == ( ifa->lines - 1 ) ) {
                                        /* 最終行                     */
            break ;                     /* データ表示の終了           */
        }                               /* end if                     */
        if ( ( cnt % 16 ) == 0 ) {      /* 1行の開始                  */
            move(pos_y, pos_x[0]) ; printw("%08x", cnt) ;
                                        /* アドレスの表示             */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* 数値をHEXデータに変換する                                          */
/* ------------------------------------------------------------------ */
        num_data = ( (uc)( ifa->workarea[cnt] ) >> 4 ) ;
                                        /* 上位バイトの取得           */
        NUM_TO_HEX( (hex_data[0]), (num_data) ) ;
                                        /* 数値データをHEXデータに変換*/

        num_data = ( (uc)( ifa->workarea[cnt] ) & MASK ) ;
                                        /* 下位バイトの取得           */
        NUM_TO_HEX( (hex_data[1]), (num_data) ) ;
                                        /* 数値データをHEXデータに変換*/
        if ( ifa->search_info != 0x00 ) {
                                        /* 検索後の表示               */
            if ( ( ifa->reverse == REVERSE )&&
                 ( STANDCHECK( cnt ) == 0x01 ) ) {
                                        /* 検索文字列                 */
                standout() ;            /* 強調モード開始             */
                move(pos_y, pos_x[1]) ; printw("%.2s", hex_data) ;
                                        /* 16進データの表示           */
                standend() ;            /* 強調モード終了             */
            }                           /* end if                     */
            else {                      /* 検索文字列以外             */
                move(pos_y, pos_x[1]) ; printw("%.2s", hex_data) ;
                                        /* 16進データの表示           */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 検索前の表示               */
            move(pos_y, pos_x[1]) ; printw("%.2s", hex_data) ;
                                        /* 16進データの表示           */
        }                               /* end else                   */
        pos_x[1] += 3 ;                 /* 16進データ表示位置の更新   */
        if ( ( cnt % 16 ) == 15 ) {     /* 1行の終了                  */
            pos_y++ ;                   /* 次の行へ                   */
            pos_x[1] = BASE_X2 ;        /* ベース座標(X2)の戻し       */
        }                               /* end if                     */
    }                                   /* end for                    */
    refresh() ;                         /* ウィンドウの再描画         */

/* ------------------------------------------------------------------ */
/* 言語に対応した文字表示を行う                                       */
/* ------------------------------------------------------------------ */
    switch ( ifa->term_lang ) {         /* 端末の言語属性チェック     */
        case LANG_ASCII :               /* 端末の言語属性:[ASCII]     */
            term_trgt = FUNC_T_A ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        case LANG_EUC :                 /* 端末の言語属性:[EUC]       */
            term_trgt = FUNC_T_E ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        case LANG_SJIS :                /* 端末の言語属性:[SJIS]      */
            term_trgt = FUNC_T_S ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        default :                       /* 端末の言語属性:その他      */
            term_trgt = FUNC_T_O ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
    }                                   /* end switch                 */

    switch ( ifa->lang ) {              /* 言語チェック               */
        case LANG_ASCII :               /* 言語:[ASCII]               */
            lang_trgt = FUNC_L_A ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        case LANG_EUC :                 /* 言語:[EUC]                 */
            lang_trgt = FUNC_L_E ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        case LANG_SJIS :                /* 言語:[SJIS]                */
            lang_trgt = FUNC_L_S ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        case LANG_JIS :                 /* 言語:[JIS]                 */
            lang_trgt = FUNC_L_J ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        case LANG_EBCDIC :              /* 言語:[EBCDIC]              */
            lang_trgt = FUNC_L_B ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
        default :                       /* 言語:その他                */
            lang_trgt = FUNC_L_A ;      /* 対象機能番号の設定         */
            break ;                     /* swtich break               */
    }                                   /* end switch                 */

    (*funcmtx[term_trgt][lang_trgt])( ifa ) ;
                                        /* 対象機能コール             */
    ifa->cur_pos_x = cur_pos_x ;        /* カーソル位置(X座標)の復元  */
    ifa->cur_pos_y = cur_pos_y ;        /* カーソル位置(Y座標)の復元  */
    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* カーソルを初期表示位置へ   */
    refresh() ;                         /* ウィンドウの再描画         */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - data_view         */
}                                       /* end (data_view)            */

/**********************************************************************/
