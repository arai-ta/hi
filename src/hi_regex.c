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
#include    <stdlib.h>
#include    <hi_std.h>

/**********************************************************************/
/*  正規表現解析関数 - hi_regex                                       */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定された正規表現の解析を行う。                                 */
/**********************************************************************/
vd  hi_regex( struct ifa_s *ifa, ch *regex, ul *anly, li siz )
                                        /* 指定アドレス出力関数       */
{
    li           offset      ;          /* 正規表現指定時のオフセット */
    li           stadr       ;          /* オフセット指定開始位置     */
    ch          *home        ;          /* ホームディレクトリ         */
    ch          *file        ;          /* 自ファイル名指定           */
    ch           wkfile[256] ;          /* ファイル名称(ワーク)       */

    trace_start( ifa, "hi_regex" ) ;    /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 正規表現の解析(アドレス指定編)                                     */
/* ------------------------------------------------------------------ */
    if (( regex[0] == CNTL_CMD_TOP ) ||( regex[0] == CNTL_CMD_CRNT )||
        ( regex[0] == CNTL_CMD_LAST )||( regex[0] == CNTL_CMD_PLUS )||
        ( regex[0] == CNTL_CMD_MINUS )) {/* アドレス変換               */

        stadr = 1 ;                      /* オフセット指定開始位置    */

        /* ---------------------------------------------------------- */
        /* ポジション解析                                             */
        /* ---------------------------------------------------------- */
        if ( regex[0] == CNTL_CMD_TOP ) {
                                        /* 先頭                       */
            *anly = 0 ;                 /* 指定アドレスは、先頭       */
        }                               /* end if                     */
        else if ( regex[0] == CNTL_CMD_CRNT ) {
                                        /* 現在位置                   */
            *anly = ifa->data_offset - 1 ;
                                        /* 終了アドレスは、現在位置   */
        }                               /* end else if                */
        else if ( regex[0] == CNTL_CMD_LAST ) {
                                        /* 最終                       */
            *anly = ifa->size - 1 ;     /* 終了アドレスは最終         */
        }                               /* end else if                */
        else {                          /* オフセット指定             */
            *anly = ifa->data_offset - 1 ;
                                        /* 終了アドレスは、先頭       */
            stadr = 0 ;                 /* オフセット指定開始位置    */
        }                               /* end else if                */

        /* ---------------------------------------------------------- */
        /* オフセット指定解析                                         */
        /* ---------------------------------------------------------- */
        if (( regex[stadr] == CNTL_CMD_MINUS )||
            ( regex[stadr] == CNTL_CMD_PLUS )) {
                                        /* オフセット指定             */
            if ( strncmp(&regex[stadr+1], "0x", 2) == 0 ) {
                                        /* 16進数指定                 */
                sscanf( &regex[stadr+1], "%x", &offset ) ;
                                        /* オフセットの取得           */
            }                           /* end if                     */
            else {                      /* 10進数指定                 */
                sscanf( &regex[stadr+1], "%d", &offset ) ;
                                        /* 終了アドレスの取得         */
            }                           /* end else                   */

            if ( regex[stadr] == CNTL_CMD_MINUS ) {
                                        /* オフセット指定             */
                *anly -= offset ;       /* 終了アドレスの変更         */
            }                           /* end if                     */
            else if ( regex[stadr] == CNTL_CMD_PLUS ) {
                                        /* オフセット指定             */
                *anly += offset ;       /* 終了アドレスの変更         */
            }                           /* end else if                */
        }                               /* end if                     */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 正規表現の解析(ファイル指定編)                                     */
/* ------------------------------------------------------------------ */
    else {                              /* ファイル指定変換           */
        strlcpy( (ch *)anly, regex, siz ) ;
                                        /* ファイル名設定             */

        /* ---------------------------------------------------------- */
        /* ディレクトリ解析                                           */
        /* ---------------------------------------------------------- */
        if ( regex[0] == CNTL_CMD_HOME ) {
                                        /* ホームディレクトリ指定     */
            home = getenv( "HOME" ) ;   /* ホームディレクトリの取得   */
            if ( home == NULL ) {       /* 取得失敗                   */
                snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                          "getenv[%s] error : errno = %d", "HOME", errno ) ;
                snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                          "getenv[%s]", "HOME" ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
                *anly = (ul)NULL ;      /* リターン値の設定           */
                trace_end( ifa ) ;      /* トレース取得               */
                return ;                /* return - hi_regex          */
            }                           /* end if                     */
            snprintf( (ch *)anly, 255, "%s%s", home, &regex[1] ) ;
                                        /* 指定されたファイル名の取得 */
        }                               /* end if                     */

        /* ---------------------------------------------------------- */
        /* ファイル名解析                                             */
        /* ---------------------------------------------------------- */
        file = strchr( (ch *)anly, CNTL_CMD_FILE ) ;
                                        /* 正規表現チェック           */
        if ( file != NULL ) {           /* ファイル名(正規表現)指定   */
            *file = 0x00 ;              /* 終端文字の設定             */
            strlcpy( wkfile, (ch *)anly, sizeof( wkfile ) ) ;
                                        /* ファイル名の退避           */
            strlcat( wkfile, ifa->file, sizeof( wkfile ) ) ;
                                        /* ファイル名称の変換         */
            strlcat( wkfile, &(file[1]), sizeof( wkfile ) ) ;
                                        /* '%'の後の文字列を連結      */
            strlcpy( (ch *)anly, wkfile, siz ) ;
                                        /* 正規表現解析後の文字列設定 */
        }                               /* end if                     */
    }                                   /* end else                   */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - hi_regex          */
}                                       /* end (hi_regex)             */

/**********************************************************************/
