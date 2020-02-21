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
#include    <string.h>
#include    <sys/stat.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ファイル書き込み関数 - file_write                                 */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   作業領域の状態を、ファイルに出力する。                           */
/**********************************************************************/
vd  file_write( struct ifa_s *ifa )     /* ファイル書き込み関数       */
{
    FILE        *fpout    ;             /* 出力ファイル               */
    li           ret      ;             /* リターンコード(汎用)       */
    ch file[256];                       /* ファイル名                 */

    trace_start( ifa, "file_write" ) ;  /* トレース取得               */
    strlcpy(file, ifa->file, sizeof( file ) );
    if(strlen(file) > 64){
        snprintf( file, sizeof( file ) , "%s...", file);
    }
/* ------------------------------------------------------------------ */
/* ファイルのオープン                                                 */
/* ------------------------------------------------------------------ */
    fpout = fopen(ifa->file, "wb+") ;   /* ファイルオープン           */
    if ( fpout == NULL ) {              /* ファイルオープン失敗       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fopen[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fopen[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
    }                                   /* end if                     */
    else {                              /* ファイルオープン成功       */

/* ------------------------------------------------------------------ */
/* 作業領域の状態を、ファイルに書き込む                               */
/* ------------------------------------------------------------------ */
        if ( ifa->size != 0 ) {         /* 対象データが存在する       */
            ret = fwrite(ifa->workarea, ifa->size, 1, fpout) ;
                                        /* ファイルへ書き込む         */
            if ( ret != 1 ) {           /* ファイル読み込み失敗       */
                snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                          "fwrite[%s] error : errno = %d", file, errno ) ;
                snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                          "fwrite[%s]", file ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
            }                           /* end if                     */
            snprintf(ifa->inf_msg, sizeof( ifa->inf_msg ),
                  "\"%s\" wrote %d characters", file, ifa->size) ;
                                        /* インフォメーション設定     */
            inf_msg( ifa ) ;            /* インフォメーション表示     */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルのクローズ                                                 */
/* ------------------------------------------------------------------ */
        fclose( fpout ) ;               /* ファイルクローズ           */

        ifa->modif = MOD_OFF ;          /* 修正有無の初期化           */
    }                                   /* end else                   */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - file_write        */
}                                       /* end (file_write)           */

/**********************************************************************/
