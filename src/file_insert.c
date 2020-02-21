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
/*  指定ファイル挿入関数 - file_insert                                */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   ファイルを読み込み、カレントに挿入する。                         */
/**********************************************************************/
vd  file_insert( struct ifa_s *ifa )    /* 指定ファイル挿入関数       */
{
    FILE        *fpin     ;             /* 入力ファイル               */
    li           ret      ;             /* リターンコード(汎用)       */
    li           alloc    ;             /* 確保サイズ(malloc用)       */
    ch          *sep      ;             /* セパレータ                 */
    ch           file[64] ;             /* 入力ファイル名称           */
                                        /* cmd_str からなので 64 文字 */
    ch          *work_tmp ;             /* 一時作業領域               */
    struct stat  st       ;             /* ファイルステータス         */

    trace_start( ifa, "file_insert" ) ; /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ファイル名称の取得                                                 */
/* ------------------------------------------------------------------ */
    sep = strchr( ifa->cmd_str,' ' ) ;  /* セパレータ位置の取得       */
    strlcpy( file, ( sep + 1 ), sizeof( file ) ) ;
                                        /* 指定されたファイル名の取得 */
    hi_regex( ifa, ( sep + 1 ), (ul *)file, sizeof( file ) ) ;
                                        /* 正規表現の解析             */
    if ( file == NULL ) {               /* 正規表現の解析成功         */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルステータスの取得                                           */
/* ------------------------------------------------------------------ */
    ret = stat( file, &st ) ;           /* ファイルステータス取得     */
    if ( ret != 0 ) {                   /* ファイルが存在する         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "\"%s\": No such file or directory.", file ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "stat[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

    if ( st.st_size == 0 ) {            /* ファイルサイズが0バイト    */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "\"%s\" is 0 byte file.", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 作業領域の再確保                                                   */
/* ------------------------------------------------------------------ */
    ifa->area_size += ( st.st_size + ( 16 - ( st.st_size % 16 ) ) ) ;
                                        /* 作業領域の再計算(境界調整) */
    if ( ifa->area_size >= ifa->max_size ) {
                                        /* 最大サイズに到達した       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "workarea size is greater than max size" ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

    ifa->workarea = (ch *)realloc( ifa->workarea, ifa->area_size ) ;
                                        /* 作業領域の確保             */
    if ( ifa->workarea == NULL ) {      /* 作業領域の確保失敗         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "realloc error : errno = %d", errno ) ;
                                        /* エラーメッセージ設定       */
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "realloc" ) ;
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 一時作業領域の確保                                                 */
/* ------------------------------------------------------------------ */
    alloc = ifa->size - ifa->data_offset + 1 +
            ( 16 - ( (ifa->size - ifa->data_offset + 1) % 16 ) ) ;
                                        /* 確保サイズの計算(境界調整) */
    work_tmp = (ch *)malloc( alloc ) ;  /* 一時作業領域の確保         */
    if ( work_tmp == NULL ) {           /* 一時作業領域の確保失敗     */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
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
        free( work_tmp ) ;              /* 一時作業領域の解放         */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルポインタを先頭に移動                                       */
/* ------------------------------------------------------------------ */
    ret = fseek( fpin, 0L, SEEK_SET ) ; /* ファイルポインタを先頭に   */
                                        /* 移動する                   */
    if ( ret != 0 ) {                   /* ファイルポインタの移動失敗 */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fseek[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fseek[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        free( work_tmp ) ;              /* 一時作業領域の解放         */
        fclose( fpin ) ;                /* ファイルクローズ           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* カーソル以降のデータ退避                                           */
/* ------------------------------------------------------------------ */
    memcpy( work_tmp, &ifa->workarea[(ifa->data_offset-1)],
            (ifa->size - ifa->data_offset + 1) ) ;
                                        /* カーソル以降のデータ退避   */
/* ------------------------------------------------------------------ */
/* ファイルの読み込み                                                 */
/* ------------------------------------------------------------------ */
    ret = fread( &ifa->workarea[(ifa->data_offset-1)],
                 st.st_size, 1, fpin) ; /* ファイルの読み込み         */
    if ( ret != 1 ) {                   /* ファイル読み込み失敗       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fread[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fread[%s]", file ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        free( work_tmp ) ;              /* 一時作業領域の解放         */
        fclose( fpin ) ;                /* ファイルクローズ           */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 退避したデータの復元                                               */
/* ------------------------------------------------------------------ */
    memcpy( &ifa->workarea[(ifa->data_offset-1+st.st_size)],
            work_tmp, (ifa->size - ifa->data_offset + 1) ) ;
                                        /* 退避したデータの復元       */
/* ------------------------------------------------------------------ */
/* 関数の後始末                                                       */
/* ------------------------------------------------------------------ */
    ifa->size += st.st_size ;           /* データサイズの追加         */
    data_view( ifa ) ;                  /* データ表示関数             */

    ifa->modif = MOD_ON ;               /* 修正した事を覚える         */
    snprintf( ifa->inf_msg, sizeof( ifa->inf_msg ),
              "\"%s\" inserted file %d characters",
              file, (li)st.st_size ) ;  /* インフォメーション設定     */
    inf_msg( ifa ) ;                    /* インフォメーション表示     */

    free( work_tmp ) ;                  /* 一時作業領域の解放         */
    fclose( fpin ) ;                    /* ファイルクローズ           */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - file_insert       */
}                                       /* end (file_insert)          */

/**********************************************************************/
