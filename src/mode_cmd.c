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
/*  コマンドモード関数 - mode_cmd                                     */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   各種コマンドを読み取り、対応機能に振り分ける。                   */
/**********************************************************************/
vd  mode_cmd( struct ifa_s *ifa )       /* コマンドモード関数         */
{
    li           target  ;              /* 対象機能番号               */
    vd        (*funcmtx[FUNC_MAX])() ;  /* 対象機能関数アドレス       */

    trace_start( ifa, "mode_cmd" ) ;    /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 関数アドレス設定                                                   */
/* ------------------------------------------------------------------ */
    funcmtx[FUNC_DMY] = dmy ;           /* ダミー関数                 */
    funcmtx[FUNC_HDN] = cur_move_h_j ;  /* カーソル下移動関数(HEX)    */
    funcmtx[FUNC_CDN] = cur_move_c_j ;  /* カーソル下移動関数(文字)   */
    funcmtx[FUNC_HUP] = cur_move_h_k ;  /* カーソル上移動関数(HEX)    */
    funcmtx[FUNC_CUP] = cur_move_c_k ;  /* カーソル上移動関数(文字)   */
    funcmtx[FUNC_HLF] = cur_move_h_h ;  /* カーソル左移動関数(HEX)    */
    funcmtx[FUNC_CLF] = cur_move_c_h ;  /* カーソル左移動関数(文字)   */
    funcmtx[FUNC_HRI] = cur_move_h_l ;  /* カーソル右移動関数(HEX)    */
    funcmtx[FUNC_CRI] = cur_move_c_l ;  /* カーソル右移動関数(文字)   */
    funcmtx[FUNC_GCM] = get_cmd ;       /* 制御コマンド関数           */
    funcmtx[FUNC_SCM] = search_cmd ;    /* サーチコマンド関数         */
    funcmtx[FUNC_SCE] = exec_search_cmd ;
                                        /* サーチコマンド実行関数     */
    funcmtx[FUNC_CMV] = cur_pos_move ;  /* カーソル位置切替関数       */
    funcmtx[FUNC_WRF] = win_refresh ;   /* 画面再描画関数             */
    funcmtx[FUNC_RPT] = report_dsp ;    /* レポート表示関数           */
    funcmtx[FUNC_HIN] = edit_h_input ;  /* データ挿入関数(HEX)        */
    funcmtx[FUNC_CIN] = edit_c_input ;  /* データ挿入関数(文字)       */
    funcmtx[FUNC_HHI] = head_h_input ;  /* データ挿入(先頭)関数(HEX)  */
    funcmtx[FUNC_CHI] = head_c_input ;  /* データ挿入(先頭)関数(文字) */
    funcmtx[FUNC_HAD] = edit_h_add ;    /* データ追加関数(HEX)        */
    funcmtx[FUNC_CAD] = edit_c_add ;    /* データ追加関数(文字)       */
    funcmtx[FUNC_HTA] = tail_h_add ;    /* データ追加(最終)関数(HEX)  */
    funcmtx[FUNC_CTA] = tail_c_add ;    /* データ追加(最終)関数(文字) */
    funcmtx[FUNC_HR1] = edit_h_rep_1 ;  /* データ変換関数(単一:HEX)   */
    funcmtx[FUNC_CR1] = edit_c_rep_1 ;  /* データ変換関数(単一:文字)  */
    funcmtx[FUNC_HR2] = edit_h_rep_2 ;  /* データ変換関数(複数:HEX)   */
    funcmtx[FUNC_CR2] = edit_c_rep_2 ;  /* データ変換関数(複数:文字)  */
    funcmtx[FUNC_HDL] = edit_h_del ;    /* データ削除関数(HEX)        */
    funcmtx[FUNC_CDL] = edit_c_del ;    /* データ削除関数(文字)       */
    funcmtx[FUNC_PRP] = page_up ;       /* ページスクロール関数(上)   */
    funcmtx[FUNC_NXP] = page_down ;     /* ページスクロール関数(下)   */
    funcmtx[FUNC_PHP] = half_page_up ;  /* 半ページスクロール関数(上) */
    funcmtx[FUNC_NHP] = half_page_down ;/* 半ページスクロール関数(下) */
    funcmtx[FUNC_HOM] = top_view ;      /* カーソル移動関数(先頭)     */
    funcmtx[FUNC_END] = tail_view ;     /* カーソル移動関数(最終)     */
    funcmtx[FUNC_LST] = move_line_start ;
                                        /* 行先頭に移動関数           */
    funcmtx[FUNC_LED] = move_line_end ; /* 行最終に移動関数           */
    funcmtx[FUNC_AGT] = address_get ;   /* アドレス取得関数           */
    funcmtx[FUNC_REP] = repeat_cmd ;    /* 繰り返しコマンド関数       */
    funcmtx[FUNC_CWQ] = exec_get_cmd ;  /* 制御コマンド実行関数       */

/* ------------------------------------------------------------------ */
/* コマンド読み取り                                                   */
/* ------------------------------------------------------------------ */
    ifa->before_cmd = ifa->cmd ;        /* 前回のコマンド退避         */
    ifa->cmd = wgetch( ifa->win ) ;     /* コマンド取得               */

/* ------------------------------------------------------------------ */
/* 繰り返し指定の判定                                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->cmd == CMD_REPEAT ) {     /* 前回のコマンド繰り返し     */
        if ( ifa->option == FIL ) {     /* 操作対象が、ファイル       */
            if ( ifa->before_cmd == CMD_DELETE ) {
                                        /* 繰り返し可能なコマンド     */
                ifa->cmd = ifa->before_cmd ;
                                        /* 前回のコマンド復元         */
            }                           /* end if                     */
            else {                      /* 繰り返し不可能なコマンド   */
                if ( ifa->before_cmd == 0x00 ) {
                                        /* 前回のコマンドが存在しない */
                    strlcpy( ifa->err_msg, "Before comannd nothing",
                             sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                }                       /* end if                     */
                else {                  /* 前回のコマンドが存在する   */
                    snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                              "[%c] is not repeat", ifa->before_cmd ) ;
                                        /* エラーメッセージ設定       */
                }                       /* end else                   */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 操作対象が、共有メモリ     */
            strlcpy( ifa->err_msg, "Shared memory is not support",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end else                   */
    }                                   /* end if                     */

    switch ( ifa->cmd ) {               /* コマンドチェック           */

/* ------------------------------------------------------------------ */
/* カーソル移動(下)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_DOWN :             /* [j]                        */
        case KEY_DOWN :                 /* [↓]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HDN ;     /* カーソル下移動関数(HEX)    */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CDN ;     /* カーソル下移動関数(文字)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* カーソル移動(上)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_UP :               /* [k]                        */
        case KEY_UP :                   /* [↑]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HUP ;     /* カーソル上移動関数(HEX)    */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CUP ;     /* カーソル上移動関数(文字)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* カーソル移動(左)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_LEFT :             /* [h]                        */
        case KEY_LEFT :                 /* [←]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HLF ;     /* カーソル左移動関数(HEX)    */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CLF ;     /* カーソル左移動関数(文字)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* カーソル移動(右)                                                   */
/* ------------------------------------------------------------------ */
        case CMD_CUR_RIGHT :            /* [l]                        */
        case KEY_RIGHT :                /* [→]                       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HRI ;     /* カーソル右移動関数(HEX)    */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CRI ;     /* カーソル右移動関数(文字)   */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ZZ = :wq                                                           */
/* ------------------------------------------------------------------ */
        case CMD_BIGZ :                 /* [Z]から始まる文字列        */
            if(wgetch( ifa->win ) == CMD_BIGZ){
                                        /* コマンド取得               */
                strlcpy(ifa->cmd_str, "wq", sizeof( ifa->cmd_str ) );
                                        /* :wq に置き換え             */
                ifa->cmd_size = strlen( ifa->cmd_str ) ;
                                        /* コマンドサイズの設定       */
                target = FUNC_CWQ ;     /* 制御コマンド実行関数       */
            } else {
                printf("\a");
                target = FUNC_DMY ;     /* ダミー関数                 */
            }
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 制御コマンド                                                       */
/* ------------------------------------------------------------------ */
        case CMD_CNTRL :                /* [:]から始まる文字列        */
            target = FUNC_GCM ;         /* 制御コマンド関数           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* サーチコマンド                                                     */
/* ------------------------------------------------------------------ */
        case CMD_SEARCH :               /* [/]から始まる文字列        */
            ifa->search = NEXT_SEARCH ; /* サーチ方向:順検索          */
            target = FUNC_SCM ;         /* サーチコマンド関数         */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 逆サーチコマンド                                                   */
/* ------------------------------------------------------------------ */
        case CMD_RSEARCH :              /* [?]から始まる文字列        */
            ifa->search = PREV_SEARCH ; /* サーチ方向:逆検索          */
            target = FUNC_SCM ;         /* サーチコマンド関数         */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 再検索コマンド                                                     */
/* ------------------------------------------------------------------ */
        case CMD_NEXT :                 /* [n]                        */
            target = FUNC_SCE ;         /* サーチコマンド実行関数     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 再逆検索コマンド                                                   */
/* ------------------------------------------------------------------ */
        case CMD_REVERSE :              /* [N]                        */
            target = FUNC_SCE ;         /* サーチコマンド実行関数     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* カーソル位置切替コマンド                                           */
/* ------------------------------------------------------------------ */
        case CMD_CPOS_MOVE :            /* [Ctrl] + [a]               */
        case CMD_CPOS_MOV2 :            /* [Tab]                      */
            target = FUNC_CMV ;         /* カーソル位置切替関数       */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 画面のリフレッシュ                                                 */
/* ------------------------------------------------------------------ */
        case CMD_REFRESH :              /* [Ctrl] + [l]               */
            target = FUNC_WRF ;         /* 画面再描画関数             */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 文字コード切り替え                                                 */
/* ------------------------------------------------------------------ */
        case CMD_CHG_CHAR :             /* [Ctrl] + [T]               */
            if ( ifa->lang == LANG_ASCII ){
                ifa->lang = LANG_EUC;
            } else if ( ifa->lang == LANG_EUC ){
                ifa->lang = LANG_SJIS;
            } else if ( ifa->lang == LANG_SJIS ){
                ifa->lang = LANG_JIS;
/*            } else if ( ifa->lang == LANG_JIS ){
                ifa->lang = LANG_EBCDIC;*/
            } else {
                ifa->lang = LANG_ASCII;
            }
            target = FUNC_WRF ;         /* 画面再描画関数             */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* レポート表示                                                       */
/* ------------------------------------------------------------------ */
        case CMD_REPORT :               /* [Ctrl] + [g]               */
            target = FUNC_RPT ;         /* レポート表示関数           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(データ挿入)                                     */
/* ------------------------------------------------------------------ */
        case CMD_INPUT :                /* [i]                        */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                    target = FUNC_HIN ; /* データ挿入関数(HEX)        */
                }                       /* end if                     */
                else {                  /* 文字データエリア           */
                    target = FUNC_CIN ; /* データ挿入関数(文字)       */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* 操作対象が、共有メモリ     */
                target = FUNC_DMY ;     /* ダミー関数                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(先頭からのデータ挿入)                           */
/* ------------------------------------------------------------------ */
        case CMD_TOP_INPUT :            /* [I]                        */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                    target = FUNC_HHI ; /* データ挿入(先頭)関数(HEX)  */
                }                       /* end if                     */
                else {                  /* 文字データエリア           */
                    target = FUNC_CHI ; /* データ挿入(先頭)関数(文字) */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* 操作対象が、共有メモリ     */
                target = FUNC_DMY ;     /* ダミー関数                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(データ追加)                                     */
/* ------------------------------------------------------------------ */
        case CMD_ADD :                  /* [a]                        */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                    target = FUNC_HAD ; /* データ追加関数(HEX)        */
                }                       /* end if                     */
                else {                  /* 文字データエリア           */
                    target = FUNC_CAD ; /* データ追加関数(文字)       */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* 操作対象が、共有メモリ     */
                target = FUNC_DMY ;     /* ダミー関数                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(最後からのデータ追加)                           */
/* ------------------------------------------------------------------ */
        case CMD_LAST_ADD :             /* [A]                        */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                    target = FUNC_HTA ; /* データ追加(最終)関数(HEX)  */
                }                       /* end if                     */
                else {                  /* 文字データエリア           */
                    target = FUNC_CTA ; /* データ追加(最終)関数(文字) */
                }                       /* end else                   */
            }                           /* end else                   */
            else {                      /* 操作対象が、共有メモリ     */
                target = FUNC_DMY ;     /* ダミー関数                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(データ置換:１文字)                              */
/* ------------------------------------------------------------------ */
        case CMD_REPLACE_1 :            /* [r]                        */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HR1 ;     /* データ変換関数(単一:HEX)   */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CR1 ;     /* データ変換関数(単一:文字)  */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(データ置換:複数文字)                            */
/* ------------------------------------------------------------------ */
        case CMD_REPLACE_2 :            /* [R]                        */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HR2 ;     /* データ変換関数(複数:HEX)   */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CR2 ;     /* データ変換関数(複数:文字)  */
            }                           /* end if                     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* データ編集コマンド(データ削除)                                     */
/* ------------------------------------------------------------------ */
        case CMD_DELETE :               /* [x]                        */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                    target = FUNC_HDL ; /* データ削除関数(HEX)        */
                }                       /* end if                     */
                else {                  /* 文字データエリア           */
                    target = FUNC_CDL ; /* データ削除関数(文字)       */
                }                       /* end if                     */
            }                           /* end else                   */
            else {                      /* 操作対象が、共有メモリ     */
                target = FUNC_DMY ;     /* ダミー関数                 */
                strlcpy( ifa->err_msg, "Shared memory is not support",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ページスクロール(上)                                               */
/* ------------------------------------------------------------------ */
        case CMD_PREV_PAGE :            /* [Ctrl] + [b]               */
        case KEY_PPAGE :                /* [PgUp]                     */
            target = FUNC_PRP ;         /* ページスクロール関数(上)   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ページスクロール(下)                                               */
/* ------------------------------------------------------------------ */
        case CMD_NEXT_PAGE :            /* [Ctrl] + [f]               */
        case KEY_NPAGE :                /* [PgUp]                     */
            target = FUNC_NXP ;         /* ページスクロール関数(下)   */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 半ページスクロール(上)                                             */
/* ------------------------------------------------------------------ */
        case CMD_PREV_HALF :            /* [Ctrl] + [u]               */
            target = FUNC_PHP ;         /* 半ページスクロール関数(上) */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 半ページスクロール(下)                                             */
/* ------------------------------------------------------------------ */
        case CMD_NEXT_HALF :            /* [Ctrl] + [d]               */
            target = FUNC_NHP ;         /* 半ページスクロール関数(下) */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ファイルの先頭位置に移動                                           */
/* ------------------------------------------------------------------ */
        case KEY_HOME :                 /* [Home]                     */
            target = FUNC_HOM ;         /* カーソル移動関数(先頭)     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* ファイルの最終位置に移動                                           */
/* ------------------------------------------------------------------ */
        case KEY_END :                  /* [End]                      */
        case CMD_TAIL :                 /* [G] ← [Shift] + [g]       */
            target = FUNC_END ;         /* カーソル移動関数(最終)     */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 行の先頭位置に移動                                                 */
/* ------------------------------------------------------------------ */
        case CMD_LINE_START :           /* [0]                        */
            target = FUNC_LST ;         /* 行移動関数(先頭)           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 行の最終位置に移動                                                 */
/* ------------------------------------------------------------------ */
        case CMD_LINE_END :             /* [$]                        */
            target = FUNC_LED ;         /* 行移動関数(最終)           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* アドレス読み込み移動                                               */
/* ------------------------------------------------------------------ */
        case CMD_ADRS_JMP :             /* [Ctrl] + [j]               */
            target = FUNC_AGT ;         /* アドレス取得関数           */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 繰り返しコマンド指定                                               */
/* ------------------------------------------------------------------ */
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
            target = FUNC_REP ;         /* 繰り返しコマンド関数       */
            break ;                     /* break switch               */

/* ------------------------------------------------------------------ */
/* 規定外のデータ                                                     */
/* ------------------------------------------------------------------ */
        default  :                      /* 規定外                     */
            target = FUNC_DMY ;         /* ダミー関数                 */
            break ;                     /* break switch               */
    }                                   /* end switch                 */
    (*funcmtx[target])( ifa ) ;         /* 対象機能コール             */
    refresh() ;                         /* ウィンドウの再描画         */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - mode_cmd          */
}                                       /* end (mode_cmd)             */

/**********************************************************************/
