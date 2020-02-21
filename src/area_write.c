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
#include    <sys/stat.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  指定アドレス出力関数 - area_write                                 */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定されたアドレスの情報を、ファイルに出力する。                 */
/**********************************************************************/
vd  area_write( struct ifa_s *ifa )     /* 指定アドレス出力関数       */
{
    FILE        *fpout       ;          /* 出力ファイル               */
    li           ret         ;          /* リターンコード(汎用)       */
    li           size        ;          /* リターンコード(汎用)       */
    li           st_adr      ;          /* 開始アドレス数値           */
    li           ed_adr      ;          /* 終了アドレス数値           */
    ch           wkfile[256] ;          /* 出力ファイル名(ワーク)     */
    ch           file[256]   ;          /* 出力ファイル名             */
    ch           st_str[32]  ;          /* 開始アドレス文字列         */
    ch           ed_str[32]  ;          /* 終了アドレス文字列         */
    ch           cmd_str[32] ;          /* コマンド文字列(ワーク)     */

    trace_start( ifa, "area_write" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* コマンド文字列のフォーマット変換                                   */
/* ------------------------------------------------------------------ */
    strlcpy( cmd_str, ifa->cmd_str, sizeof( cmd_str ) ) ;
                                        /* コマンド文字列のコピー     */
    *strchr( cmd_str, ((li)',') ) = ' ' ;
                                        /* 区切り文字','を' 'に変換   */
    *strchr( cmd_str, ((li)'w') ) = ' ' ;
                                        /* 区切り文字'w'を' 'に変換   */

/* ------------------------------------------------------------------ */
/* フォーマット変換後文字列の分解                                     */
/* ------------------------------------------------------------------ */
    ret = sscanf( cmd_str, "%s %s %s", st_str, ed_str, wkfile ) ;
                                        /* 分解後文字列の取得         */
    if ( ret != 3 ) {                   /* ファイル名称未指定         */
        strlcpy( wkfile, ifa->file, sizeof( wkfile ) ) ;
                                        /* 現在のファイル名称を設定   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 開始アドレス取得                                                   */
/* ------------------------------------------------------------------ */
    if ( strncmp(st_str, CNTL_CMD_ADRS, 2) == 0 ) {
                                        /* 16進数指定                 */
        sscanf( st_str, "%x", &st_adr ) ;
                                        /* 開始アドレスの取得         */
    }                                   /* end if                     */
    else if (( st_str[0] == CNTL_CMD_TOP )||
             ( st_str[0] == CNTL_CMD_CRNT )||
             ( st_str[0] == CNTL_CMD_LAST )) {
                                        /* 正規表現指定               */
        hi_regex( ifa, st_str, (ul *)&st_adr, sizeof ( st_adr ) ) ;
                                        /* 正規表現解析関数           */
    }                                   /* end else if                */
    else {                              /* 10進数指定                 */
        sscanf( st_str, "%d", &st_adr ) ;
                                        /* 開始アドレスの取得         */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* 終了アドレス取得                                                   */
/* ------------------------------------------------------------------ */
    if ( strncmp(ed_str, CNTL_CMD_ADRS, 2) == 0 ) {
                                        /* 16進数指定                 */
        sscanf( ed_str, "%x", &ed_adr ) ;
                                        /* 終了アドレスの取得         */
    }                                   /* end if                     */
    else if (( ed_str[0] == CNTL_CMD_TOP )||
             ( ed_str[0] == CNTL_CMD_CRNT )||
             ( ed_str[0] == CNTL_CMD_LAST )) {
                                        /* 正規表現指定               */
        hi_regex( ifa, ed_str, (ul *)&ed_adr, sizeof ( ed_adr ) ) ;
                                        /* 正規表現解析関数           */
    }                                   /* end else if                */
    else {                              /* 10進数指定                 */
        sscanf( ed_str, "%d", &ed_adr ) ;
                                        /* 終了アドレスの取得         */
    }                                   /* end else                   */

    size = ed_adr - st_adr + 1 ;        /* 出力サイズの算出           */

/* ------------------------------------------------------------------ */
/* 出力サイズチェック                                                 */
/* ------------------------------------------------------------------ */
    if ( size <= 0 ) {                  /* 出力サイズ不正             */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "write command error : \"%s\" is output size <= 0",
                  ifa->cmd_str ) ;      /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - area_write        */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイル名称の取得                                                 */
/* ------------------------------------------------------------------ */
    strlcpy( file, wkfile, sizeof( wkfile ) ) ;
                                        /* 指定されたファイル名の取得 */
    hi_regex( ifa, wkfile, (ul *)file, sizeof ( file ) ) ;
                                        /* 正規表現の解析             */
    if ( file != NULL ) {               /* 正規表現の解析成功         */
/* ------------------------------------------------------------------ */
/* ファイルのオープン                                                 */
/* ------------------------------------------------------------------ */
        fpout = fopen(file, "wb+") ;    /* ファイルオープン           */
        if(strlen(file) > 64){
            snprintf( file, sizeof( file ), "%s...", file);
        }
        if ( fpout == NULL ) {          /* ファイルオープン失敗       */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "fopen[%s] error : errno = %d", file, errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fopen[%s]",
                      file ) ;          /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
            trace_end( ifa ) ;          /* トレース取得               */
            return ;                    /* return - area_write        */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* 作業領域の状態を、ファイルに書き込む                               */
/* ------------------------------------------------------------------ */
        ret = fwrite( &ifa->workarea[st_adr], size, 1, fpout ) ;
                                        /* ファイルへ書き込む         */
        if ( ret != 1 ) {               /* ファイル読み込み失敗       */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "fwrite[%s] error : errno = %d", file, errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fwrite[%s]",
                      file ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
            fclose( fpout ) ;           /* ファイルクローズ           */
            trace_end( ifa ) ;          /* トレース取得               */
            return ;                    /* return - area_write        */
        }                               /* end if                     */

        snprintf( ifa->inf_msg, sizeof( ifa->inf_msg ),
                  "\"%s\" wrote file %d characters", file, size ) ;
                                        /* インフォメーション設定     */
        inf_msg( ifa ) ;                /* インフォメーション表示     */

/* ------------------------------------------------------------------ */
/* ファイルのクローズ                                                 */
/* ------------------------------------------------------------------ */
        fclose( fpout ) ;               /* ファイルクローズ           */

        ifa->modif = MOD_OFF ;          /* 修正有無の初期化           */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - area_write        */
}                                       /* end (area_write)           */

/**********************************************************************/
