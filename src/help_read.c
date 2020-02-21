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
#include    <sys/stat.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ヘルプファイル読み込み関数 - help_read                            */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   使用言語に対応したヘルプファイルを読み込み、ヘルプ情報エリアに   */
/*   展開する。                                                       */
/**********************************************************************/
vd  help_read( struct ifa_s *ifa )      /* ヘルプファイル読み込み関数 */
{
    FILE               *fpin      ;     /* 入力ファイル               */
    li                  ret       ;     /* リターンコード(汎用)       */
    li                  cnt       ;     /* ループカウンタ             */
    li                  offset    ;     /* オフセット値               */
    ch                  file[64]  ;     /* ヘルプファイル名称         */
    ch                 *workarea  ;     /* 作業領域                   */
    struct stat         st        ;     /* ファイルステータス         */
    struct help_info_s *help_info ;     /* ファイルステータス         */

    trace_start( ifa, "help_read" ) ;   /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ヘルプファイルの決定                                               */
/* ------------------------------------------------------------------ */
    if ( ifa->term_lang == LANG_EUC ) { /* 使用言語が、[EUC]          */
        snprintf( file, 64, "%s/MANUAL.EUC", HELP_PATH ) ;
                                        /* EUC用マニュアル            */
    }                                   /* end if                     */
    else if ( ifa->term_lang == LANG_SJIS ) {
                                        /* 使用言語が、[SJIS]         */
        snprintf( file, 64, "%s/MANUAL.SJIS", HELP_PATH ) ;
                                        /* SJIS用マニュアル           */
    }                                   /* end else if                */
    else {                              /* 使用言語が、[C]か[C]以外?  */
        snprintf( file, 64, "%s/MANUAL.C", HELP_PATH ) ;
                                        /* C用マニュアル              */
    }                                   /* end else if                */

/* ------------------------------------------------------------------ */
/* ファイルステータスの取得                                           */
/* ------------------------------------------------------------------ */
    ret = stat( file, &st ) ;           /* ファイルステータス取得     */
    if ( ret != 0 ) {                   /* ファイルが存在しない       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "stat[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "stat[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        ifa->help_area = ifa->err_msg ; /* ヘルプ情報の設定           */
        ifa->help_line = 1 ;            /* ヘルプ行数の設定           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - help_read         */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* ファイル読み込み領域の確保                                         */
/* ------------------------------------------------------------------ */
    workarea = (ch *)malloc( st.st_size ) ;
                                        /* 作業領域の確保             */
    if ( workarea == NULL ) {           /* 作業領域の確保失敗         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        ifa->help_area = ifa->err_msg ; /* ヘルプ情報の設定           */
        ifa->help_line = 1 ;            /* ヘルプ行数の設定           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルのオープン                                                 */
/* ------------------------------------------------------------------ */
    fpin = fopen( file, "rb" ) ;        /* ファイルオープン           */
    if ( fpin == NULL ) {               /* ファイルオープン失敗       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fopen[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fopen[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        ifa->help_area = ifa->err_msg ; /* ヘルプ情報の設定           */
        ifa->help_line = 1 ;            /* ヘルプ行数の設定           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルの読み込み                                                 */
/* ------------------------------------------------------------------ */
    ret = fread( workarea, st.st_size, 1, fpin) ;
                                        /* ファイルの読み込み         */
    if ( ret != 1 ) {                   /* ファイル読み込み失敗       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                "fread[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fread[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        ifa->help_area = ifa->err_msg ; /* ヘルプ情報の設定           */
        ifa->help_line = 1 ;            /* ヘルプ行数の設定           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 行数の取得                                                         */
/* ------------------------------------------------------------------ */
    for ( cnt = 0 ; cnt < st.st_size ; cnt++ ) {
                                        /* 改行コードの検索ループ     */
        if ( workarea[cnt] == 0x0a ) {  /* 改行コード検知             */
            ifa->help_line++ ;          /* ヘルプの行数の更新         */
        }                               /* end if                     */
    }                                   /* end for                    */

/* ------------------------------------------------------------------ */
/* ヘルプファイル読み込み領域の再確保                                 */
/* ------------------------------------------------------------------ */
    ifa->help_area = (ch *)malloc( sizeof(struct help_info_s) *
                                   ifa->help_line );
                                        /* ヘルプ情報エリアの確保     */
    if ( ifa->help_area == NULL ) {     /* ヘルプ情報エリアの確保失敗 */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        ifa->help_area = ifa->err_msg ; /* ヘルプ情報の設定           */
        ifa->help_line = 1 ;            /* ヘルプ行数の設定           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - help_read         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ヘルプ情報の設定                                                   */
/* ------------------------------------------------------------------ */
    offset = 0 ;                        /* オフセット値の初期化       */
    help_info = (struct help_info_s *)ifa->help_area ;
                                        /* ヘルプ情報アドレスの変換   */
    for ( cnt = 0 ; cnt < st.st_size ; cnt++ ) {
                                        /* 改行コードの検索ループ     */
        if ( ( workarea[cnt] != 0x0a ) && ( workarea[cnt] != 0x0d ) ) {
                                        /* CR/LF以外                  */
            help_info->help_msg[offset] = workarea[cnt] ;
                                        /* ヘルプ情報の設定           */
            offset++ ;                  /* オフセット値の更新         */
        }                               /* end if                     */

        if ( workarea[cnt] == 0x0a ) {  /* 改行コード検知             */
            if ( ( help_info->help_msg[0] != ' ' ) &&
                 ( help_info->help_msg[0] != 0x00 ) ) {
                                        /* 見出し行                   */
                help_info->stand = '1' ;/* 強調表示モード             */
            }                           /* end if                     */
            else {                      /* 見出し行以外               */
                help_info->stand = '0' ;/* 通常表示モード             */
            }                           /* end else                   */
            help_info++ ;               /* ヘルプ行の更新             */
            offset = 0 ;                /* オフセット値の初期化       */
        }                               /* end if                     */
    }                                   /* end for                    */

/* ------------------------------------------------------------------ */
/* ファイルのクローズ                                                 */
/* ------------------------------------------------------------------ */
    free( workarea ) ;                  /* 作業領域の解放             */
    fclose( fpin ) ;                    /* ファイルクローズ           */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - help_read         */
}                                       /* end (help_read)            */

/**********************************************************************/
