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
/*  ファイル読み込み関数 - hi_config                                  */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   環境ファイルを読み込み、初期設定を行う。                         */
/**********************************************************************/
vd  hi_config( struct ifa_s *ifa )      /* 環境ファイル読み込み関数   */
{
    FILE        *fpin     ;             /* 環境ファイル               */
    li           ret      ;             /* リターンコード(汎用)       */
    ch          *fgets_ret;             /* fgets()リターンコード      */
    ch          *home     ;             /* ホームディレクトリ         */
    ch          *equal    ;             /* '='位置                    */
    ch           conf[128];             /* 環境ファイル(フルパス)     */
    ch           area[128];             /* 環境定義情報               */
    ch           _set[32] ;             /* :set格納エリア             */
    ch           dinf[32] ;             /* 定義情報格納エリア         */
    ch           dval[32] ;             /* 定義値格納エリア           */
    struct stat  st       ;             /* ファイルステータス         */

    trace_start( ifa, "hi_config" ) ;   /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ファイルポインタの初期化                                           */
/* ------------------------------------------------------------------ */
    fpin = NULL ;                       /* ファイルポインタの初期化   */

/* ------------------------------------------------------------------ */
/* ホームディレクトリの取得                                           */
/* ------------------------------------------------------------------ */
    home = getenv( "HOME" ) ;           /* ホームディレクトリの取得   */
    if ( home == NULL ) {               /* 取得失敗                   */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - hi_config         */
    }                                   /* end if                     */
    snprintf( conf, 127, "%s/%s", home, HI_CONFIG ) ;
                                        /* 環境ファイル(フルパス)設定 */
/* ------------------------------------------------------------------ */
/* ファイルステータスの取得                                           */
/* ------------------------------------------------------------------ */
    ret = stat( conf, &st ) ;           /* ファイルステータス取得     */
    if ( ret == (-1) ) {                /* ファイルが存在しない       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - hi_config         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ファイルのオープン                                                 */
/* ------------------------------------------------------------------ */
    fpin = fopen( conf, "rb" ) ;        /* ファイルオープン           */
    if ( fpin == NULL ) {               /* ファイルオープン失敗       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - hi_config         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 全定義情報の読み込み                                               */
/* ------------------------------------------------------------------ */
    while ( 1 ) {                       /* 全定義情報を読み込む       */

        fgets_ret = fgets( area, 127, fpin ) ;
                                        /* ファイルの読み込み         */
        if ( fgets_ret == NULL ) {      /* ファイル読み込み失敗又は   */
                                        /* ファイルの終端を検知       */
            break ;                     /* break while                */
        }                               /* end if                     */

        if ( area[0] == '#' ) {         /* コメント行                 */
            continue ;                  /* continue while             */
        }                               /* end if                     */

        equal = strchr( area, ((li)'=') ) ;
                                        /* '='位置の取得              */
        *equal = ' ' ;                  /* '=' を ' ' に変換          */
        /* I think this sscanf is dengerous. */
        sscanf( area, "%s %s %s", _set, dinf, dval ) ;
                                        /* 定義行の取得               */
        if ( strncmp( dinf, "TR", 2 ) == 0 ) {
                                        /* 文字表示エリアの言語指定   */
            switch ( (li)dval[0] ) {    /* 言語チェック               */
                case (li)'a' : ifa->lang = LANG_ASCII  ; break ;
                case (li)'e' : ifa->lang = LANG_EUC    ; break ;
                case (li)'s' : ifa->lang = LANG_SJIS   ; break ;
                case (li)'j' : ifa->lang = LANG_JIS    ; break ;
                case (li)'b' : ifa->lang = LANG_EBCDIC ;
                    switch ( (li)dval[1] ) {
                                        /* EBCDIC(K)チェック          */
                        case (li)'i' : ifa->ebcdic = EBCDIC_IBM   ; break ;
                        case (li)'h' : ifa->ebcdic = EBCDIK_HITAC ; break ;
                        case (li)'n' : ifa->ebcdic = EBCDIC_NEC   ; break ;
                        case (li)'o' : ifa->ebcdic = EBCDIC       ; break ;
                        default      : ifa->ebcdic = EBCDIC       ; break ;
                    }                   /* end switch                 */
                    break ;
                default      : ifa->lang = LANG_ASCII  ; break ;
            }                           /* end switch                 */
        }                               /* end if                     */
        else if ( strncmp( dinf, "CP", 2 ) == 0 ) {
                                        /* カーソルポジションの指定   */
            switch ( (li)dval[0] ) {    /* カーソルポジションチェック */
                case (li)'h' : ifa->target = HEX_DATA  ; break ;
                case (li)'c' : ifa->target = CHAR_DATA ; break ;
                default      : ifa->target = HEX_DATA  ; break ;
            }                           /* end switch                 */
        }                               /* end else if                */
        else if ( strncmp( dinf, "SR", 2 ) == 0 ) {
                                        /* 検索文字列の反転表示指定   */
            if ( strncmp( dval, "on", 2 ) == 0 ) {
                ifa->reverse = REVERSE ;/* 反転表示する               */
            }                           /* end if                     */
            else if ( strncmp( dval, "off", 3 ) == 0 ) {
                ifa->reverse = NOT_REVERSE ;
                                        /* 反転表示しない             */
            }                           /* end else if                */
            else {                      /* 規定値以外                 */
                ifa->reverse = REVERSE ;/* 反転表示する               */
            }                           /* end else                   */
        }                               /* end else if                */
        else if ( strncmp( dinf, "EO", 2 ) == 0 ) {
                                        /* 動作環境表示の指定         */
            if ( strncmp( dval, "on", 2 ) == 0 ) {
                ifa->envout = ENVOUT ;  /* 動作環境を表示する         */
            }                           /* end if                     */
            else if ( strncmp( dval, "off", 3 ) == 0 ) {
                ifa->envout = NOT_ENVOUT ;
                                        /* 動作環境を表示しない       */
            }                           /* end else if                */
            else {                      /* 規定値以外                 */
                ifa->reverse = ENVOUT ; /* 動作環境を表示する         */
            }                           /* end else                   */
        }                               /* end else if                */
        else if ( strncmp( dinf, "AS", 2 ) == 0 ) {
                                        /* 追加作業領域のサイズ指定   */
            sscanf( dval, "%d", &ifa->alloc_size ) ;
                                        /* 追加作業領域サイズの取得   */
        }                               /* end else if                */
        else if ( strncmp( dinf, "MS", 2 ) == 0 ) {
                                        /* 最大作業領域のサイズ指定   */
            sscanf( dval, "%d", &ifa->max_size ) ;
                                        /* 最大作業領域サイズの取得   */
        }                               /* end else if                */

    }                                   /* end while                  */

/* ------------------------------------------------------------------ */
/* ファイルのクローズ                                                 */
/* ------------------------------------------------------------------ */
    fclose( fpin ) ;                    /* ファイルクローズ           */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - hi_config         */
}                                       /* end (hi_config)            */

/**********************************************************************/
