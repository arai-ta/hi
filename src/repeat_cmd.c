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
#include    <ctype.h>
#include    <hi_std.h>

/**********************************************************************/
/*  繰り返しコマンド実行関数 - repeat_cmd                             */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定回数分、指定されたコマンドを繰り返す。                       */
/**********************************************************************/
vd  repeat_cmd( struct ifa_s *ifa )     /* 繰り返しコマンド実行関数   */
{

    li           cnt         ;          /* ループカウンタ             */
    li           number      ;          /* 繰り返し回数               */
    li           target      ;          /* 対象機能番号               */
    uc           cmd_str[32] ;          /* コマンド文字列             */
    uc           cmd         ;          /* コマンド                   */
    vd        (*funcmtx[FUNC_MAX])() ;  /* 対象機能関数アドレス       */

    trace_start( ifa, "repeat_cmd" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* 関数アドレス設定                                                   */
/* ------------------------------------------------------------------ */
    funcmtx[FUNC_DMY] = repeat_dmy ;    /* ダミー関数                 */
    funcmtx[FUNC_HDL] = repeat_h_del ;  /* 連続データ削除関数(HEX)    */
    funcmtx[FUNC_CDL] = repeat_c_del ;  /* 連続データ削除関数(文字)   */
    funcmtx[FUNC_HDN] = repeat_move_j ; /* 連続カーソル下移動関数     */
    funcmtx[FUNC_HUP] = repeat_move_k ; /* 連続カーソル上移動関数     */
/* ------------------------------------------------------------------ */
/* コマンド取得とパターン解析                                         */
/* ------------------------------------------------------------------ */
    memset( cmd_str, 0x00, sizeof( cmd_str ) ) ;
                                        /* コマンド文字列の初期化     */
    cnt = 1 ;                           /* ループカウンタの初期化     */
    cmd_str[0] = (uc)ifa->cmd ;         /* 1文字目設定                */
    while ( 1 ) {                       /* 無限ループに突入           */
        cmd_str[cnt] = getch() ;        /* 入力データ(１文字)取得     */
        if ( cmd_str[cnt] == ESCAPE ) { /* キャンセル                 */
            trace_end( ifa ) ;          /* トレース取得               */
            return ;                    /* return - repeat_cmd        */
        }                               /* end if                     */
        else if ( !isdigit(cmd_str[cnt]) ) {
                                        /* 数字以外                   */
            break ;                     /* break while                */
        }                               /* end if                     */
        cnt++ ;                         /* ループカウンタの更新       */
    }                                   /* end while                  */
    sscanf( (ch *)cmd_str, "%d%c",&number, &cmd ) ;

    if ( number == 0 ) {                /* 繰り返し回数 0             */
        target = FUNC_DMY ;             /* ダミー関数                 */
    }
/* ------------------------------------------------------------------ */
/* データの削除                                                       */
/* ------------------------------------------------------------------ */
    else if ( cmd == (uc)CMD_DELETE ) { /* データの削除               */
        if ( ifa->option == FIL ) {     /* 操作対象が、ファイル       */
            if ( ifa->target == HEX_DATA ) {
                                        /* HEXデータエリア            */
                target = FUNC_HDL ;     /* データ削除関数(HEX)        */
            }                           /* end if                     */
            else {                      /* 文字データエリア           */
                target = FUNC_CDL ;     /* データ削除関数(文字)       */
            }                           /* end if                     */
        }                               /* end else                   */
        else {                          /* 操作対象が、共有メモリ     */
            target = FUNC_DMY ;         /* ダミー関数                 */
            strlcpy( ifa->err_msg, "Shared memory is not support", 
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }
    }                                   /* end else if                */
/* ------------------------------------------------------------------ */
/* カーソル下移動                                                     */
/* ------------------------------------------------------------------ */
    else if ( cmd == (uc)CMD_CUR_DOWN ) { 
                                        /* カーソル下移動             */
        if ( ifa->option == FIL ) {     /* 操作対象が、ファイル       */
            target = FUNC_HDN ;         /* カーソル下移動関数(HEX)    */
        }                               /* end else                   */
        else {                          /* 操作対象が、共有メモリ     */
            target = FUNC_DMY ;         /* ダミー関数                 */
            strlcpy( ifa->err_msg, "Shared memory is not support",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }
    }                                   /* end else if                */
/* ------------------------------------------------------------------ */
/* カーソル上移動                                                     */
/* ------------------------------------------------------------------ */
    else if ( cmd == (uc)CMD_CUR_UP ) { 
                                        /* カーソル下移動             */
        if ( ifa->option == FIL ) {     /* 操作対象が、ファイル       */
            target = FUNC_HUP ;         /* カーソル下移動関数(HEX)    */
        }                               /* end else                   */
        else {                          /* 操作対象が、共有メモリ     */
            target = FUNC_DMY ;         /* ダミー関数                 */
            strlcpy( ifa->err_msg, "Shared memory is not support",
                     sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }
    }                                   /* end else if                */
/* ------------------------------------------------------------------ */
/* 規定外                                                             */
/* ------------------------------------------------------------------ */
    else {                              /* 規定外                     */
        number = 0 ;                    /* 回数の初期化               */
        target = FUNC_DMY ;             /* 関数の初期化               */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* 繰り返しコマンドの実行                                             */
/* ------------------------------------------------------------------ */
    (*funcmtx[target])( ifa, number ) ; /* 対象機能コール             */
    refresh() ;                         /* ウィンドウの再描画         */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - repeat_cmd        */
}                                       /* end (repeat_cmd)           */

/**********************************************************************/
