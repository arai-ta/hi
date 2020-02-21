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
/*  ファイル読み込み関数 - file_read                                  */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   ファイルを読み込み、作業領域に展開する。                         */
/**********************************************************************/
vd  file_read( struct ifa_s *ifa )      /* ファイル読み込み関数       */
{
    FILE        *fpin     ;             /* 入力ファイル               */
    li           ret      ;             /* リターンコード(汎用)       */
    struct stat  st       ;             /* ファイルステータス         */
    ch file[256];                       /* ファイル名                 */

    trace_start( ifa, "file_read" ) ;   /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ファイルポインタの初期化                                           */
/* ------------------------------------------------------------------ */
    fpin = NULL ;                       /* ファイルポインタの初期化   */
    strlcpy(file, ifa->file, sizeof( file ));
    if(strlen(file) > 64){
        snprintf( file, sizeof( file ), "%s...", file);
    }

/* ------------------------------------------------------------------ */
/* ファイルステータスの取得                                           */
/* ------------------------------------------------------------------ */
    ret = stat( ifa->file, &st ) ;      /* ファイルステータス取得     */
    if ( ret == 0 ) {                   /* ファイルが存在する         */
        ifa->size = st.st_size ;        /* データサイズの取得         */
        ifa->exist = EXIST ;            /* ファイルが存在する         */
    }                                   /* end if                     */
    else {                              /* ファイルが存在しない       */
        ifa->size = 0 ;                 /* データサイズの初期化       */
        ifa->exist = NOT_EXIST ;        /* ファイルが存在しない       */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* ファイル読み込み領域の確保                                         */
/* ------------------------------------------------------------------ */
    ifa->area_size = ifa->size + ( 16 - ( ifa->size % 16 ) ) ;
                                        /* 作業領域の計算(境界調整)   */
    if ( ifa->area_size >= ifa->max_size ) {
                                        /* 最大サイズに到達した       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
            "workarea size is greater than max size" ) ;
        ifa->endflg = ABORT ;           /* 強制終了指示               */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
    }                                   /* end if                     */

    ifa->workarea = (ch *)malloc( ifa->area_size ) ;
                                        /* 作業領域の確保             */
    if ( ifa->workarea == NULL ) {      /* 作業領域の確保失敗         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* エラーメッセージ設定       */
        ifa->endflg = ABORT ;           /* 強制終了指示               */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルのオープン                                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->exist == EXIST ) {        /* ファイルが存在する         */
        fpin = fopen(ifa->file, "rb") ; /* ファイルオープン           */
        if ( fpin == NULL ) {           /* ファイルオープン失敗       */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "fopen[%s] error : errno = %d", file, errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                      "fopen[%s]", file ) ;
                                        /* エラーメッセージ設定       */
            ifa->endflg = ABORT ;       /* 強制終了指示               */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルポインタを先頭に移動                                       */
/* ------------------------------------------------------------------ */
    if ( ifa->exist == EXIST ) {        /* ファイルが存在する         */
        ret = fseek(fpin, 0L, SEEK_SET) ;
                                        /* ファイルポインタを先頭に   */
                                        /* 移動する                   */
        if ( ret != 0 ) {               /* ファイルポインタの移動失敗 */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                    "fseek[%s] error : errno = %d", file, errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                      "fseek[%s]", file ) ;
                                        /* エラーメッセージ設定       */
            ifa->endflg = ABORT ;       /* 強制終了指示               */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
    }                                   /* end if                     */


/* ------------------------------------------------------------------ */
/* ファイルの読み込み                                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->size != 0 ) {             /* 既存ファイルの処理         */
        ret = fread(ifa->workarea, ifa->size, 1, fpin) ;
                                        /* ファイルの読み込み         */
        if ( ret != 1 ) {               /* ファイル読み込み失敗       */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "fread[%s] error : errno = %d", file, errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                      "fread[%s]", file ) ;
                                        /* エラーメッセージ設定       */
            ifa->endflg = ABORT ;       /* 強制終了指示               */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルのクローズ                                                 */
/* ------------------------------------------------------------------ */
    if ( ifa->exist == EXIST ) {        /* ファイルが存在する         */
        fclose( fpin ) ;                /* ファイルクローズ           */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - file_read         */
}                                       /* end (file_read)            */

/**********************************************************************/
