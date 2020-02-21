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
#include    <unistd.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ヘッダ表示関数 - head_disp                                        */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   ヘッダ領域の表示を行う。                                         */
/**********************************************************************/
vd  head_disp( struct ifa_s *ifa )      /* ヘッダ表示関数             */
{
    ch            head_string_1_3[16] ; /* ヘッダ情報1_3              */
    ch            version_string[8] ;   /* バージョン情報             */

    trace_start( ifa, "head_disp" ) ;   /* トレース取得               */
/* ------------------------------------------------------------------ */
/* ヘッダ情報1_3の編集                                                */
/* ------------------------------------------------------------------ */
    switch ( ifa->lang ) {              /* 言語の判定                 */
        case LANG_ASCII :               /* 言語:ASCII                 */
            strlcpy( head_string_1_3, "[ASCII]", sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
            break ;                     /* break switch               */

        case LANG_EUC :                 /* 言語:EUC                   */
            strlcpy( head_string_1_3, "[Japanese EUC]",
            sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
            break ;                     /* break switch               */

        case LANG_SJIS :                /* 言語:Shift-JIS             */
            strlcpy( head_string_1_3, "[Shift-JIS]",
                     sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
            break ;                     /* break switch               */

        case LANG_JIS :                 /* 言語:JIS                   */
            strlcpy( head_string_1_3, "[JIS]",
                     sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
            break ;                     /* break switch               */

        case LANG_EBCDIC :              /* 言語:EBCDIC                */
            switch ( ifa->ebcdic ) {    /* EBCDIC(K)の判定            */
                case EBCDIC_IBM :       /* EBCDIC IBM                 */
                    strlcpy( head_string_1_3, "[EBCDIC IBM]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
                    break ;             /* break switch               */

                case EBCDIK_HITAC :     /* EBCDIK HITACHI             */
                    strlcpy( head_string_1_3, "[EBCDIK HITAC]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
                    break ;             /* break switch               */

                case EBCDIC_NEC :       /* EBCDIC NEC                 */
                    strlcpy( head_string_1_3, "[EBCDIC NEC]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
                    break ;             /* break switch               */

                case EBCDIC :           /* EBCDIC                     */
                    strlcpy( head_string_1_3, "[EBCDIC]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* 表示言語の設定             */
                    break ;             /* break switch               */

            }                           /* end switch                 */
            break ;                     /* break switch               */
    }                                   /* end switch                 */

/* ------------------------------------------------------------------ */
/* ヘッダの表示                                                       */
/* ------------------------------------------------------------------ */
    mvaddstr(HEAD_Y1, HEAD_X1_1, HEAD_STRING_1_1) ;
                                        /* ヘッダ情報1_1の表示        */
    mvaddstr(HEAD_Y1, HEAD_X1_2, HEAD_STRING_1_2) ;
                                        /* ヘッダ情報1_2の表示        */
    mvaddstr(HEAD_Y1, HEAD_X1_3, head_string_1_3) ;
                                        /* ヘッダ情報1_3の表示        */
#ifdef DISP_LINE2
    mvaddstr(HEAD_Y2, HEAD_X2_1, HEAD_STRING_2_1) ;
                                        /* ヘッダ情報2_1の表示        */
    mvaddstr(HEAD_Y2, HEAD_X2_2, HEAD_STRING_2_2) ;
                                        /* ヘッダ情報2_2の表示        */
    mvaddstr(HEAD_Y2, HEAD_X2_3, HEAD_STRING_2_3) ;
                                        /* ヘッダ情報2_3の表示        */
#endif
/* ------------------------------------------------------------------ */
/* バージョン情報の表示                                               */
/* ------------------------------------------------------------------ */
    memset( version_string, 0x00, sizeof(version_string) ) ;
                                        /* バージョン情報の初期化     */
    snprintf( version_string, sizeof( version_string ), "%s-%s",
              VERSION, RELEASE ) ;      /* バージョン情報の設定       */
    mvaddstr(VERSION_Y, VERSION_X, version_string) ;
                                        /* バージョン情報の表示       */
    refresh() ;                         /* ウィンドウの再描画         */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - head_disp         */
}                                       /* end (head_disp)            */

/**********************************************************************/
