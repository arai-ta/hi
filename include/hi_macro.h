/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/*    マクロ定義ヘッダ - hi_macro.h                                   */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : Nov 2006                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 3t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004-2006 Tatsuyoshi                              */
/* ------------------------------------------------------------------ */
/* ヘッダ概要                                                         */
/*   バイナリエディタで使用するマクロを定義する。                     */
/**********************************************************************/
/**********************************************************************/
/* マクロ名 : ERRINFO_SET( ifa )                                      */
/*   ifaに、障害情報詳細を設定する。                                  */
/* ------------------------------------------------------------------ */
/* 引数     : ifa    = ifa構造体                                      */
/**********************************************************************/
#define     ERRINFO_SET( ifa )                                         \
            strlcpy( (ifa)->err_func, __FILE__, sizeof((ifa)->err_func) ) ; \
            snprintf( (ifa)->err_line, sizeof( (ifa)->err_line), "%d", \
                     __LINE__ ) ;

/**********************************************************************/
/* マクロ名 : LEFT_DATA_SET( target, data )                           */
/*   上位バイトに、指定されたデータを設定する。                       */
/* ------------------------------------------------------------------ */
/* 引数     : target = データ設定エリア                               */
/*          : data   = データ                                         */
/**********************************************************************/
#define     LEFT_DATA_SET( target, data )                              \
            if (((data) >= 'a')&&((data) <= 'f')) {                    \
                (data) -= 0x57 ;                                       \
            }                                                          \
            ((target) = ((target) & 0x0f) | (((data) << 4) & 0xf0))

/**********************************************************************/
/* マクロ名 : RIGHT_DATA_SET( target, data )                          */
/*   下位バイトに、指定されたデータを設定する。                       */
/* ------------------------------------------------------------------ */
/* 引数     : target = データ設定エリア                               */
/*          : data   = データ                                         */
/**********************************************************************/
#define     RIGHT_DATA_SET( target, data )                             \
            if (((data) >= 'a')&&((data) <= 'f')) {                    \
                (data) -= 0x57 ;                                       \
            }                                                          \
            ((target) = ((target) & 0xf0) | ((data) & 0x0f))

/**********************************************************************/
/* マクロ名 : NUM_TO_HEX( hex, num )                                  */
/*   指定された数値データを、HEXデータに変換する。                    */
/* ------------------------------------------------------------------ */
/* 引数     : hex = HEXデータ設定エリア                               */
/*          : num = 数値データ                                        */
/**********************************************************************/
#define     NUM_TO_HEX( hex, num )                                     \
            (hex) = ((num) < 10) ? ((num) + 0x30) : ((num) + 0x57)

/**********************************************************************/
/* マクロ名 : CHAR_TO_HEX( hex, char, offset )                        */
/*   指定された文字データを、HEXデータに変換する。                    */
/* ------------------------------------------------------------------ */
/* 引数     : hex    = HEXデータ設定エリア                            */
/*          : char   = 文字データ                                     */
/**********************************************************************/
#define     CHAR_TO_HEX( hex, char )                                   \
            (hex) = (((char) >= '0')&&((char) <= '9')) ?               \
                    ((char) - '0') : ((char) - 'a' + 0x0a) ;

/**********************************************************************/
/* マクロ名 : CHAR_TO_DEC( dec, char, len )                           */
/*   指定された文字データを、10進データに変換する。                   */
/* ------------------------------------------------------------------ */
/* 引数     : dec    = 10進データ設定エリア                           */
/*          : char   = 文字データ                                     */
/*          : len    = 文字データ長                                   */
/**********************************************************************/
#define     CHAR_TO_DEC( dec, char, len )                              \
{                                                                      \
    ul counter ;                                                       \
    (dec) = 0 ;                                                        \
    for ( counter = 0 ; counter < (len) ; counter++ ) {                \
        (dec) += ( (char[counter]) - '0' ) ;                           \
        (dec) *= 10 ;                                                  \
    }                                                                  \
    (dec) /= 10 ;                                                      \
}

/**********************************************************************/
/* マクロ名 : DEC_TO_BINSTR( dec, size, output )                      */
/*   指定された10進数データを、2進数データ(文字)に変換する。          */
/* ------------------------------------------------------------------ */
/* 引数     : dec    = 10進数データ                                   */
/*          : size   = 変換対象データ長                               */
/*          : output = 変換後文字データ                               */
/**********************************************************************/
#define     DEC_TO_BINSTR( dec, size, output )                         \
{                                                                      \
    ul counter ;                                                       \
    ul sft_cnt ;                                                       \
    ul ary_cnt = 0 ;                                                   \
    for ( counter = 0 ; counter < (size) ; counter++ ) {               \
        for ( sft_cnt = 0 ; sft_cnt < 8 ; sft_cnt++ ) {                \
            (output)[ary_cnt++] =                                      \
                ((dec[counter] >> (7 - sft_cnt)) & 0x01) + 0x30 ;      \
        }                                                              \
    }                                                                  \
    (output)[ary_cnt] = 0x00 ;                                         \
}

/**********************************************************************/
/* マクロ名 : DEC_TO_OCTSTR( dec, size, output )                      */
/*   指定された10進数データを、8進数データ(文字)に変換する。          */
/* ------------------------------------------------------------------ */
/* 引数     : dec    = 10進数データ                                   */
/*          : size   = 変換対象データ長                               */
/*          : output = 変換後文字データ                               */
/**********************************************************************/
#define     DEC_TO_OCTSTR( dec, size, output )                         \
{                                                                      \
    ul counter ;                                                       \
    db num = 0 ;                                                       \
    uc n_1 ;                                                           \
    us n_2 ;                                                           \
    ul n_4 ;                                                           \
    for ( counter = 0 ; counter < (size) ; counter++ ) {               \
        num += dec[counter] ;                                          \
        num *= 256 ;                                                   \
    }                                                                  \
    num /= 256 ;                                                       \
    switch ( (size) ) {                                                \
        case 1 :                                                       \
            n_1 = num ;                                                \
            snprintf( (output), sizeof(output), "%o", n_1 ) ;          \
            break ;                                                    \
        case 2 :                                                       \
            n_2 = num ;                                                \
            snprintf( (output), sizeof(output), "%o", n_2 ) ;          \
            break ;                                                    \
        case 4 :                                                       \
            n_4 = num ;                                                \
            snprintf( (output), sizeof(output), "%o", n_4 ) ;          \
            break ;                                                    \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : DEC_TO_UDCSTR( dec, size, output )                      */
/*   指定された10進数データを、符号無し10進数データ(文字)に変換する。 */
/* ------------------------------------------------------------------ */
/* 引数     : dec    = 10進数データ                                   */
/*          : size   = 変換対象データ長                               */
/*          : output = 変換後文字データ                               */
/**********************************************************************/
#define     DEC_TO_UDCSTR( dec, size, output )                         \
{                                                                      \
    ul counter ;                                                       \
    db num = 0 ;                                                       \
    uc n_1 ;                                                           \
    us n_2 ;                                                           \
    ul n_4 ;                                                           \
    for ( counter = 0 ; counter < (size) ; counter++ ) {               \
        num += dec[counter] ;                                          \
        num *= 256 ;                                                   \
    }                                                                  \
    num /= 256 ;                                                       \
    switch ( (size) ) {                                                \
        case 1 :                                                       \
            n_1 = num ;                                                \
            snprintf( (output), sizeof(output), "%u", n_1 ) ;          \
            break ;                                                    \
        case 2 :                                                       \
            n_2 = num ;                                                \
            snprintf( (output), sizeof(output), "%u", n_2 ) ;          \
            break ;                                                    \
        case 4 :                                                       \
            n_4 = num ;                                                \
            snprintf( (output), sizeof(output), "%u", n_4 ) ;          \
            break ;                                                    \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : DEC_TO_DECSTR( dec, size, output )                      */
/*   指定された10進数データを、符号有り10進数データ(文字)に変換する。 */
/* ------------------------------------------------------------------ */
/* 引数     : dec    = 10進数データ                                   */
/*          : size   = 変換対象データ長                               */
/*          : output = 変換後文字データ                               */
/**********************************************************************/
#define     DEC_TO_DECSTR( dec, size, output )                         \
{                                                                      \
    ul counter ;                                                       \
    db num = 0 ;                                                       \
    ch n_1 ;                                                           \
    si n_2 ;                                                           \
    li n_4 ;                                                           \
    for ( counter = 0 ; counter < (size) ; counter++ ) {               \
        num += dec[counter] ;                                          \
        num *= 256 ;                                                   \
    }                                                                  \
    num /= 256 ;                                                       \
    switch ( (size) ) {                                                \
        case 1 :                                                       \
            n_1 = num ;                                                \
            snprintf( (output), sizeof(output), "%d", n_1 ) ;          \
            break ;                                                    \
        case 2 :                                                       \
            n_2 = num ;                                                \
            snprintf( (output), sizeof(output), "%d", n_2 ) ;          \
            break ;                                                    \
        case 4 :                                                       \
            n_4 = num ;                                                \
            snprintf( (output), sizeof(output), "%d", n_4 ) ;          \
            break ;                                                    \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : DEC_TO_PACSTR( dec, size, output )                      */
/*   指定されたパックデータを、符号有り10進数データ(文字)に変換する。 */
/* ------------------------------------------------------------------ */
/* 引数     : dec    = 10進数データ                                   */
/*          : size   = 変換対象データ長                               */
/*          : output = 変換後文字データ                               */
/*          : check  = チェック結果                                   */
/**********************************************************************/
#define     DEC_TO_PACSTR( dec, size, output, check )                  \
{                                                                      \
    ul cnt  ;                                                          \
    ul ofst ;                                                          \
                                                                       \
    ofst = 1 ;                                                         \
    (check) = 0 ;                                                      \
    for ( cnt = 0 ; cnt < (size) ; cnt++ ) {                           \
        (output)[ofst] = ( ( dec[cnt] >> 4 ) & 0x0f ) + 0x30 ;         \
        if ( ( (output)[ofst] < '0' )||                                \
             ( (output)[ofst] > '9' ) ) {                              \
            (check) = (-1) ;                                           \
        }                                                              \
        ofst++ ;                                                       \
        if ( cnt < ( (size) - 1 ) ) {                                  \
            (output)[ofst] = ( dec[cnt] & 0x0f ) + 0x30 ;              \
            if ( ( (output)[ofst] < '0' )||                            \
                 ( (output)[ofst] > '9' ) ) {                          \
                (check) = (-1) ;                                       \
            }                                                          \
            ofst++ ;                                                   \
        }                                                              \
        else {                                                         \
            if ( ( dec[cnt] & 0x0f ) == 0x0c ) {                       \
                (output)[0] = '+' ;                                    \
            }                                                          \
            else if ( ( dec[cnt] & 0x0f ) == 0x0d ) {                  \
                (output)[0] = '-' ;                                    \
            }                                                          \
            else if ( ( dec[cnt] & 0x0f ) == 0x0f ) {                  \
                (output)[0] = ' ' ;                                    \
            }                                                          \
            else {                                                     \
                (check) = (-1) ;                                       \
            }                                                          \
        }                                                              \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : STANDON( offset )                                       */
/*   指定されたビット位置に、1(=standout)をセットする。               */
/* ------------------------------------------------------------------ */
/* 引数     : offset = フラグ設定エリアオフセット                     */
/**********************************************************************/
#define     STANDON( offset )                                          \
            ifa->search_info[((offset)/8)] |= (0x01 << ((offset)%8))

/**********************************************************************/
/* マクロ名 : STANDCHECK( offset )                                    */
/*   指定されたビット位置の情報を返す。                               */
/* ------------------------------------------------------------------ */
/* 引数     : offset = フラグ設定エリアオフセット                     */
/**********************************************************************/
#define     STANDCHECK( offset )                                       \
            ((ifa->search_info[((offset)/8)] >> ((offset)%8)) & 0x01)

/**********************************************************************/
/* マクロ名 : SJIS_TO_EUC( check1, check2 )                           */
/*   指定された文字[Shift-JIS]を、EUCに変換する。                     */
/* ------------------------------------------------------------------ */
/* 引数     : check1 = 文字データの1バイト目                          */
/*          : check2 = 文字データの2バイト目                          */
/**********************************************************************/
#define     SJIS_TO_EUC( check1, check2 )                              \
{                                                                      \
    if ((check1) <= 0x9F) {                                            \
        (check1) = (check1) * 2 - (0x81 * 2 - 0x21) ;                  \
    }                                                                  \
    else {                                                             \
        (check1) = (check1) * 2 - (0xE0 * 2 - 0x5F) ;                  \
    }                                                                  \
    if ((check2) <= 0x7E) {                                            \
        (check2) = (check2) - (0x40 - 0x21) ;                          \
    }                                                                  \
    else if ((check2) <= 0x9e) {                                       \
        (check2) = (check2) - (0x80 - 0x60) ;                          \
    }                                                                  \
    else {                                                             \
        (check2) = (check2) - (0x9F - 0x21) ;                          \
        (check1) = (check1) + 1 ;                                      \
    }                                                                  \
    (check1) = (check1) + 0x80 ;                                       \
    (check2) = (check2) + 0x80 ;                                       \
}

/**********************************************************************/
/* マクロ名 : EUC_TO_SJIS( check1, check2 )                           */
/*   指定された文字[EUC]を、Shift-JISに変換する。                     */
/* ------------------------------------------------------------------ */
/* 引数     : check1 = 文字データの1バイト目                          */
/*          : check2 = 文字データの2バイト目                          */
/**********************************************************************/
#define     EUC_TO_SJIS( check1, check2 )                              \
{                                                                      \
    (check1) = (check1) - 0x80 ;                                       \
    (check2) = (check2) - 0x80 ;                                       \
    if ((check1) & 0x01) {                                             \
        (check1) = (((check1) + 1) / 2) + 0x70 ;                       \
        (check2) = (check2) + 0x1F ;                                   \
    }                                                                  \
    else {                                                             \
        (check1) = ((check1) / 2) + 0x70 ;                             \
        (check2) = (check2) + 0x7D ;                                   \
    }                                                                  \
    if ((check1) >= 0xA0) {                                            \
        (check1) = (check1) + 0x40 ;                                   \
    }                                                                  \
    if ((check2) >= 0x7F) {                                            \
        (check2) = (check2) + 0x01 ;                                   \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : JIS_TO_EUC( check1, check2 )                            */
/*   指定された文字[JIS]を、EUCに変換する。                           */
/* ------------------------------------------------------------------ */
/* 引数     : check1 = 文字データの1バイト目                          */
/*          : check2 = 文字データの2バイト目                          */
/**********************************************************************/
#define     JIS_TO_EUC( check1, check2 )                               \
{                                                                      \
    (check1) = (check1) + 0x80 ;                                       \
    (check2) = (check2) + 0x80 ;                                       \
}

/**********************************************************************/
/* マクロ名 : JIS_TO_SJIS( check1, check2 )                           */
/*   指定された文字[JIS]を、Shift-JISに変換する。                     */
/* ------------------------------------------------------------------ */
/* 引数     : check1 = 文字データの1バイト目                          */
/*          : check2 = 文字データの2バイト目                          */
/**********************************************************************/
#define     JIS_TO_SJIS( check1, check2 )                              \
{                                                                      \
    if ((check1) & 0x01) {                                             \
        (check1) = (((check1) + 1) / 2) + 0x70 ;                       \
        (check2) = (check2) + 0x1F ;                                   \
    }                                                                  \
    else {                                                             \
        (check1) = ((check1) / 2) + 0x70 ;                             \
        (check2) = (check2) + 0x7D ;                                   \
    }                                                                  \
    if ((check1) >= 0xA0) {                                            \
        (check1) = (check1) + 0x40 ;                                   \
    }                                                                  \
    if ((check2) >= 0x7F) {                                            \
        (check2) = (check2) + 0x01 ;                                   \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : EBCDIC_TO_ASCII( check )                                */
/*   指定された文字[EBCDIC]を、ASCIIに変換する。                      */
/*   * 本マクロを使用するソースは、[ hi_ebcdic.h ] を取り込むこと     */
/* ------------------------------------------------------------------ */
/* 引数     : check  = 文字データ                                     */
/*          : kind   = EBCDIC(K)の種類                                */
/**********************************************************************/
#define     EBCDIC_TO_ASCII( check, kind )                             \
{                                                                      \
    ul counter ;                                                       \
    if ( (kind) == EBCDIC_IBM ) {                                      \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_EBCDIC_IBM ) {           \
                (check) = ebcdic[counter].C_ASCII ;                    \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
    else if ( (kind) == EBCDIK_HITAC ) {                               \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_EBCDIK_HITAC ) {         \
                (check) = ebcdic[counter].C_ASCII ;                    \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
    else if ( (kind) == EBCDIC_NEC ) {                                 \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_EBCDIC_NEC ) {           \
                (check) = ebcdic[counter].C_ASCII ;                    \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
    else {                                                             \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_EBCDIC ) {               \
                (check) = ebcdic[counter].C_ASCII ;                    \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : ASCII_TO_EBCDIC( check )                                */
/*   指定された文字[ASCII]を、EBCDICに変換する。                      */
/*   * 本マクロを使用するソースは、[ hi_ebcdic.h ] を取り込むこと     */
/* ------------------------------------------------------------------ */
/* 引数     : check  = 文字データ                                     */
/*          : kind   = EBCDIC(K)の種類                                */
/**********************************************************************/
#define     ASCII_TO_EBCDIC( check, kind )                             \
{                                                                      \
    ul counter ;                                                       \
    if ( (kind) == EBCDIC_IBM ) {                                      \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_ASCII ) {                \
                (check) = ebcdic[counter].C_EBCDIC_IBM ;               \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
    else if ( (kind) == EBCDIK_HITAC ) {                               \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_ASCII ) {                \
                (check) = ebcdic[counter].C_EBCDIK_HITAC ;             \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
    else if ( (kind) == EBCDIC_NEC ) {                                 \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_ASCII ) {                \
                (check) = ebcdic[counter].C_EBCDIC_NEC ;               \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
    else {                                                             \
        for ( counter = 0 ; counter <= 255 ; counter++ ) {             \
            if ( (check) == ebcdic[counter].C_ASCII ) {                \
                (check) = ebcdic[counter].C_EBCDIC ;                   \
                break ;                                                \
            }                                                          \
        }                                                              \
    }                                                                  \
}

/**********************************************************************/
/* マクロ名 : JIS_ESCAPE_GET( check, size, str )                      */
/*   指定されたエスケープシーケンスのサイズ及び、記号表記を戻す。     */
/* ------------------------------------------------------------------ */
/* 引数     : check  = エスケープシーケンス                           */
/*          : size   = エスケープシーケンスの記号表記サイズ           */
/*          : str    = 記号表記                                       */
/**********************************************************************/
#define     JIS_ESCAPE_GET( check, size, str )                         \
{                                                                      \
    if ( memcmp( (check), JIS_ASCII, 3 ) == 0 ) {                      \
        strlcpy( (ch *)(str), "[(B", sizeof( str ) ) ;                 \
    }                                                                  \
    else if ( memcmp( (check), JIS_ROMAN_SET, 3 ) == 0 ) {             \
        strlcpy( (ch *)(str), "[(J", sizeof( str ) ) ;                 \
    }                                                                  \
    else if ( memcmp( (check), JIS_HALF_KANA, 3 ) == 0 ) {             \
        strlcpy( (ch *)(str), "[(I", sizeof( str ) ) ;                 \
    }                                                                  \
    else if ( memcmp( (check), JIS_X0208_OLD, 3 ) == 0 ) {             \
        strlcpy( (ch *)(str), "[$@", sizeof( str ) ) ;                 \
    }                                                                  \
    else if ( memcmp( (check), JIS_X0208_NEW, 3 ) == 0 ) {             \
        strlcpy( (ch *)(str), "[$B", sizeof( str ) ) ;                 \
    }                                                                  \
    else if ( memcmp( (check), JIS_X0208_ADD, 6 ) == 0 ) {             \
        strlcpy( (ch *)(str), "[&@[$B", sizeof( str ) ) ;              \
    }                                                                  \
    else if ( memcmp( (check), JIS_X0212, 3 ) == 0 ) {                 \
        strlcpy( (ch *)(str), "[$(D", sizeof( str ) ) ;                \
    }                                                                  \
    (size) = strlen( (ch *)(str) ) ;                                   \
}

/**********************************************************************/
