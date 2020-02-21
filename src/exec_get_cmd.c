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
/*  制御コマンド実行関数 - exec_get_cmd                               */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   制御コマンドを実行する。                                         */
/**********************************************************************/
vd  exec_get_cmd( struct ifa_s *ifa )   /* 制御コマンド関数           */
{

    trace_start( ifa, "exec_get_cmd" ) ;/* トレース取得               */
/* ------------------------------------------------------------------ */
/* 制御コマンド実行処理                                               */
/* ------------------------------------------------------------------ */
    /* -------------------------------------------------------------- */
    /* 終了                                                           */
    /* -------------------------------------------------------------- */
    if ( strcmp(ifa->cmd_str, CNTL_CMD_QUIT1) == 0 ) {
                                        /* 終了(q)                    */
        if ( ifa->entry >= ifa->maxent ) {
                                        /* 最終ファイル               */
            if ( ifa->modif == MOD_OFF ) {
                                        /* 修正していない             */
                ifa->endflg = N_END ;   /* 終了指示                   */
            }                           /* end if                     */
            else {                      /* 修正している               */
                if ( ifa->option == FIL ) {
                                        /* 操作対象が、ファイル       */
                    strlcpy( ifa->err_msg,
                             "File modified since last complete write.",
                             sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                    ERRINFO_SET( ifa ) ;/* 障害情報詳細設定           */
                    err_msg( ifa ) ;    /* エラーメッセージ表示       */
                }                       /* end if                     */
                else {                  /* 操作対象が、共有メモリ     */
                    ifa->endflg = N_END ;
                                        /* 終了指示                   */
                }                       /* end else                   */
            }                           /* end if                     */
        }                               /* end else                   */
        else {                          /* まだ、ファイルが存在する   */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "%d more files to edit.",
                      (ifa->maxent - ifa->entry) ) ;
                                        /* エラーメッセージ設定       */
                    ERRINFO_SET( ifa ) ;/* 障害情報詳細設定           */
                    err_msg( ifa ) ;    /* エラーメッセージ表示       */
        }                               /* end else                   */
    }                                   /* end if                     */

    /* -------------------------------------------------------------- */
    /* 強制終了                                                       */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_QUIT2) == 0 ) {
                                        /* 強制終了(q!)               */
        ifa->endflg = D_END ;           /* 強制終了指示               */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 書き込み終了                                                   */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_WQ) == 0 ) {
                                        /* 書き込み終了(wq)           */
        if ( ifa->entry == ifa->maxent ) {
                                        /* 最終ファイル               */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                file_write( ifa ) ;     /* ファイル書き込み関数       */
                ifa->endflg = N_END ;   /* 終了指示                   */
            }                           /* end if                     */
            else {                      /* 操作対象が、共有メモリ     */
                strlcpy( ifa->err_msg, "Shared memory is direct access.",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
        }                               /* end else                   */
        else {                          /* まだ、ファイルが存在する   */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "%d more files to edit.",
                      (ifa->maxent - ifa->entry) ) ;
                                        /* エラーメッセージ設定       */
                    ERRINFO_SET( ifa ) ;/* 障害情報詳細設定           */
                    err_msg( ifa ) ;    /* エラーメッセージ表示       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 上書き、又は別名保管                                           */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] ==  CNTL_CMD_WRITE ) {
                                        /* 上書き(w)、又は別名保管(w) */
        if ( ifa->cmd_size == 1 ) {     /* 上書き(w)                  */
            if ( ifa->option == FIL ) { /* 操作対象が、ファイル       */
                file_write( ifa ) ;     /* ファイル書き込み関数       */
            }                           /* end if                     */
            else {                      /* 操作対象が、共有メモリ     */
                strlcpy( ifa->err_msg,
                         "Shared memory is direct access.",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 別名保管                   */
            file_create( ifa ) ;        /* 新規ファイル作成関数       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 指定ファイルの挿入                                             */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] ==  CNTL_CMD_READ ) {
                                        /* ファイル読み込み(r)        */
        if ( ifa->option == FIL ) {     /* 操作対象が、ファイル       */
            if ( ifa->cmd_size == 1 ) { /* フォーマットエラー         */
                strlcpy( ifa->err_msg, "read command error : \"%s\"",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end if                     */
            else {                      /* 指定ファイルの挿入         */
                file_insert( ifa ) ;    /* 指定ファイル挿入関数       */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 操作対象が、共有メモリ     */
            strlcpy( ifa->err_msg, "Shared memory is not support",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 対象ファイル変更                                               */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_CHG01) == 0 ) {
                                        /* 対象ファイル変更(n)        */
        if ( ifa->entry < ifa->maxent ) {
                                        /* まだ、ファイルが存在する   */
            if ( ifa->modif == MOD_OFF ) {
                                        /* 修正していない             */
                ifa->endflg = CHANGE ;  /* 編集対象切り替え指示       */
            }                           /* end if                     */
            else {                      /* 修正している               */
                if ( ifa->option == FIL ) {
                                        /* 操作対象が、ファイル       */
                    strlcpy( ifa->err_msg,
                             "File modified since last complete write.",
                             sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                    ERRINFO_SET( ifa ) ;/* 障害情報詳細設定           */
                    err_msg( ifa ) ;    /* エラーメッセージ表示       */
                }                       /* end if                     */
                else {                  /* 操作対象が、共有メモリ     */
                    ifa->endflg = CHANGE ;
                                        /* 編集対象切り替え指示       */
                }                       /* end else                   */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* 最終ファイル               */
            strlcpy( ifa->err_msg, "No more files to edit.",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end else                   */
    }                                   /* end if                     */

    /* -------------------------------------------------------------- */
    /* 強制対象ファイル変更                                           */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_CHG02) == 0 ) {
                                        /* 強制対象ファイル変更(n!)   */
        if ( ifa->entry < ifa->maxent ) {
                                        /* まだ、ファイルが存在する   */
            ifa->endflg = CHANGE ;      /* 編集対象切り替え指示       */
        }                               /* end if                     */
        else {                          /* 最終ファイル               */
            strlcpy( ifa->err_msg, "No more files to edit.",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ヘルプ表示                                                     */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_HELP) == 0 ) {
                                        /* ヘルプ表示                 */
        help( ifa ) ;                   /* ヘルプ処理                 */
        win_refresh( ifa ) ;            /* 画面再描画関数             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 動作環境表示                                                   */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_ENV) == 0 ) {
                                        /* 動作環境表示               */
        env_output( ifa ) ;             /* 動作環境処理               */
        win_refresh( ifa ) ;            /* 画面再描画関数             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 動作環境表示                                                   */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_FNAME) == 0 ) {
                                        /* ファイル名表示             */
        report_dsp( ifa ) ;             /* 処理                       */
/*        win_refresh( ifa ) ;             画面再描画関数             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* シェルコマンド実行                                             */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] == CNTL_CMD_SHELL ) {
                                        /* シェルコマンド             */
        exec_shell( ifa ) ;             /* シェルコマンド実行関数     */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* アドレス指定(移動又は、出力) 又は、回数指定コマンド            */
    /* -------------------------------------------------------------- */
    else if (( strncmp(ifa->cmd_str, CNTL_CMD_ADRS, 2) == 0 )||
             (( ifa->cmd_str[0] == CNTL_CMD_TOP )||
              ( ifa->cmd_str[0] == CNTL_CMD_CRNT )||
              ( ifa->cmd_str[0] == CNTL_CMD_LAST )||
              ( ifa->cmd_str[0] == CNTL_CMD_PLUS )||
              ( ifa->cmd_str[0] == CNTL_CMD_MINUS ))||
             (( ifa->cmd_str[0] >= '0' )&&( ifa->cmd_str[0] <= '9' ))) {
                                        /* アドレス指定(正規表現有り) */
        if ( ifa->cmd_str[strlen(ifa->cmd_str)-1] == CMD_DELETE ) {
                                        /* アドレス指定削除           */
            area_delete( ifa ) ;        /* アドレス指定削除           */
        }                               /* end if                     */
        else if ( strchr( ifa->cmd_str, ((li)',') ) != NULL ) {
                                        /* アドレス指定出力           */
            area_write( ifa ) ;         /* アドレス指定出力           */
        }                               /* end else if                */
        else {                          /* 指定アドレス表示           */
            address_view( ifa ) ;       /* 指定アドレス表示処理       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 表示切替え                                                     */
    /* -------------------------------------------------------------- */
    else if ( strncmp(ifa->cmd_str, CNTL_CMD_TR, 2) == 0 ) {
                                        /* 表示切替え                 */
        tr_main( ifa ) ;                /* 言語設定関数               */
        win_refresh( ifa ) ;            /* 画面再描画関数             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 反転表示                                                       */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_SR_ON) == 0 ) {
                                        /* 反転表示                   */
        ifa->reverse = REVERSE ;        /* 検索文字列を反転表示する   */
        win_refresh( ifa ) ;            /* 画面再描画関数             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 反転表示しない                                                 */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_SR_OF) == 0 ) {
                                        /* 反転表示しない             */
        ifa->reverse = NOT_REVERSE ;    /* 検索文字列を反転表示しない */
        win_refresh( ifa ) ;            /* 画面再描画関数             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* データ変換表示                                                 */
    /* -------------------------------------------------------------- */
    else if ( strncmp(ifa->cmd_str, CNTL_CMD_PR, 2) == 0 ) {
                                        /* データ変換表示(pr)         */
        if ( ifa->cmd_size == 2 ) {     /* データ変換形式未指定       */
            strlcpy( ifa->err_msg, "Format error.", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
        else {                          /* データ変換表示             */
            print_conv_data( ifa ) ;    /* データ変換表示関数         */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 画面イメージ追加出力                                           */
    /* -------------------------------------------------------------- */
    else if ( strncmp(ifa->cmd_str, CNTL_CMD_PA, 2) == 0 ) {
                                        /* 画面イメージ追加出力(pa)   */
        if ( ifa->cmd_size == 2 ) {     /* ファイル名未指定           */
            strlcpy( ifa->err_msg, "Format error.", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
        else {                          /* 別名保管                   */
            ifa->image = ADD ;          /* 画面イメージ追加           */
            image_write( ifa ) ;        /* 画面イメージ出力関数       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* 画面イメージ出力                                               */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] ==  CNTL_CMD_P ) {
                                        /* 画面イメージ出力(p)        */
        if ( ifa->cmd_size == 1 ) {     /* ファイル名未指定           */
            strlcpy( ifa->err_msg, "Format error.", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
        else {                          /* 別名保管                   */
            ifa->image = CREATE ;       /* 画面イメージ新規作成       */
            image_write( ifa ) ;        /* 画面イメージ出力関数       */
        }                               /* end else                   */
    }                                   /* end else if                */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - exec_get_cmd      */
}                                       /* end (exec_get_cmd)         */

/**********************************************************************/
