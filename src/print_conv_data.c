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
/*  データ変換表示関数 - print_conv_data                              */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定されたデータを、指定された形式に変換し、を表示する。         */
/**********************************************************************/
vd  print_conv_data( struct ifa_s *ifa )/* データ変換表示関数         */
{
    ch           *sep       ;           /* セパレータ                 */
    ch           *data      ;           /* 変換前データ               */
    ch            format[8] ;           /* フォーマット               */
    ch            inf[128]  ;           /* インフォメーションデータ   */
    ch            cnv[64]   ;           /* 変換後データ               */
    ch            ope       ;           /* 型                         */
    ch            check     ;           /* チェック                   */
    ul            len       ;           /* 変換データ長               */
    ul            cnt       ;           /* ループカウンタ             */

    trace_start( ifa, "print_conv_data" ) ;
                                        /* トレース取得               */
/* ------------------------------------------------------------------ */
/* フォーマット取得                                                   */
/* ------------------------------------------------------------------ */
    sep = strchr( ifa->cmd_str, ' ' ) ; /* セパレータ位置の取得       */
    strlcpy( format, ( sep + 1 ), sizeof( format ) ) ;
                                        /* フォーマットの取得         */

/* ------------------------------------------------------------------ */
/* 書式チェック                                                       */
/* ------------------------------------------------------------------ */
    for ( cnt = 0 ; cnt < strlen( format ) ; cnt++ ) {
                                        /* サイズの桁数取得           */
        if ( ( format[cnt] < '0' )||
             ( format[cnt] > '9' ) ) {  /* 数値以外の文字を検知       */
            break ;                     /* break for                  */
        }                               /* end if                     */
    }                                   /* end for                    */
    if ( cnt > strlen( format ) ) {     /* 型指定が見つからない       */
        strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - print_conv_data   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 型チェック                                                         */
/* ------------------------------------------------------------------ */
    ope = format[cnt] ;                 /* 型取得                     */
    if ( ( ope != CONV_BIN )&&
         ( ope != CONV_OCT )&&
         ( ope != CONV_UDC )&&
         ( ope != CONV_DEC )&&
         ( ope != CONV_PAC ) ) {        /* 型指定不正                 */
        strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - print_conv_data   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 桁数チェック                                                       */
/* ------------------------------------------------------------------ */
    sscanf( format, "%d%c", &len, &ope ) ;
                                        /* サイズの数値変換           */
    if ( ( ( ope == CONV_BIN )||
           ( ope == CONV_OCT )||
           ( ope == CONV_UDC )||
           ( ope == CONV_DEC ) )&&
         ( ( len != 1 )&&( len != 2 )&&( len != 4 ) ) ) {
                                        /* 変換データ長不正           */
        strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
        ERRINFO_SET( ifa ) ;            /* 障害情報詳細設定           */
        err_msg( ifa ) ;                /* エラーメッセージ表示       */
        trace_end( ifa ) ;              /* トレース取得               */
        return ;                        /* return - print_conv_data   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 桁数取得処理                                                       */
/* ------------------------------------------------------------------ */
    memset( cnv, 0x00, sizeof( cnv ) ) ;/* 変換後データエリアの初期化 */
    data = &(ifa->workarea[(ifa->data_offset-1)]) ;
                                        /* 変換対象データアドレス設定 */
    switch ( ope ) {                    /* 変換方式の判定             */
        case CONV_BIN :                 /* 2進数指定                  */
            DEC_TO_BINSTR( data, len, cnv ) ;
                                        /* 2進数変換                  */
            snprintf( inf, sizeof( inf ), "%d byte data is (%s)binnary", len,
                      cnv ) ;           /* 表示文字列生成             */
            break ;                     /* break switch               */

        case CONV_OCT :                 /* 8進数指定                  */
            DEC_TO_OCTSTR( data, len, cnv ) ;
                                        /* 8進数変換                  */
            snprintf( inf, sizeof( inf ), "%d byte data is (%s)octal", len,
                      cnv ) ;           /* 表示文字列生成             */
            break ;                     /* break switch               */

        case CONV_UDC :                 /* 符号無し10進数指定         */
            DEC_TO_UDCSTR( data, len, cnv ) ;
                                        /* 符号無し10進数変換         */
            snprintf( inf, sizeof( inf ),
                      "%d byte data is (%s)unsigned decimal", len, cnv ) ;
                                        /* 表示文字列生成             */
            break ;                     /* break switch               */

        case CONV_DEC :                 /* 符号有り10進数指定         */
            DEC_TO_DECSTR( data, len, cnv ) ;
                                        /* 符号有り10進数変換         */
            snprintf( inf, sizeof( inf ), "%d byte data is (%s)signed decimal",
                      len, cnv ) ;      /* 表示文字列生成             */
            break ;                     /* break switch               */

        case CONV_PAC :                 /* パック指定                 */
            DEC_TO_PACSTR( data, len, cnv, check ) ;
            if ( check != (-1) ) {      /* チェックOK                 */
                snprintf( inf, sizeof( inf ), "%d byte data is (%s)pack", len,
                          cnv ) ;       /* 表示文字列生成             */
            }                           /* end if                     */
            else {                      /* チェックエラー             */
                strlcpy( ifa->err_msg, "pack data error",
                         sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
                ERRINFO_SET( ifa ) ;    /* 障害情報詳細設定           */
                err_msg( ifa ) ;        /* エラーメッセージ表示       */
                trace_end( ifa ) ;      /* トレース取得               */
                return ;                /* return - print_conv_data   */
            }                           /* end else                   */
            break ;                     /* break switch               */

        default       :                 /* 符号有り10進数指定         */
            strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* エラーメッセージ設定       */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
            trace_end( ifa ) ;          /* トレース取得               */
            return ;                    /* return - print_conv_data   */
    }                                   /* end switch                 */

/* ------------------------------------------------------------------ */
/* データ表示処理                                                     */
/* ------------------------------------------------------------------ */
    echo() ;                            /* エコー入力モード           */
    move(ifa->inf_msg_y, ifa->inf_msg_x) ;
                                        /* インフォメーションエリアに */
                                        /* 移動                       */
    clrtobot() ;                        /* インフォメーションエリアの */
                                        /* クリア                     */
    addstr( inf ) ;                     /* インフォメーションの表示   */
    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* カーソル位置を戻す         */
    refresh() ;                         /* 画面の再描画               */
    noecho() ;                          /* エコー入力モード解除       */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - print_conv_data   */
}                                       /* end (print_conv_data)      */

/**********************************************************************/
