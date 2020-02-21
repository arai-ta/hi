/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/*    �ޥ�������إå� - hi_macro.h                                   */
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
/* �إå�����                                                         */
/*   �Х��ʥꥨ�ǥ����ǻ��Ѥ���ޥ����������롣                     */
/**********************************************************************/
/**********************************************************************/
/* �ޥ���̾ : ERRINFO_SET( ifa )                                      */
/*   ifa�ˡ��㳲����ܺ٤����ꤹ�롣                                  */
/* ------------------------------------------------------------------ */
/* ����     : ifa    = ifa��¤��                                      */
/**********************************************************************/
#define     ERRINFO_SET( ifa )                                         \
            strlcpy( (ifa)->err_func, __FILE__, sizeof((ifa)->err_func) ) ; \
            snprintf( (ifa)->err_line, sizeof( (ifa)->err_line), "%d", \
                     __LINE__ ) ;

/**********************************************************************/
/* �ޥ���̾ : LEFT_DATA_SET( target, data )                           */
/*   ��̥Х��Ȥˡ����ꤵ�줿�ǡ��������ꤹ�롣                       */
/* ------------------------------------------------------------------ */
/* ����     : target = �ǡ������ꥨ�ꥢ                               */
/*          : data   = �ǡ���                                         */
/**********************************************************************/
#define     LEFT_DATA_SET( target, data )                              \
            if (((data) >= 'a')&&((data) <= 'f')) {                    \
                (data) -= 0x57 ;                                       \
            }                                                          \
            ((target) = ((target) & 0x0f) | (((data) << 4) & 0xf0))

/**********************************************************************/
/* �ޥ���̾ : RIGHT_DATA_SET( target, data )                          */
/*   ���̥Х��Ȥˡ����ꤵ�줿�ǡ��������ꤹ�롣                       */
/* ------------------------------------------------------------------ */
/* ����     : target = �ǡ������ꥨ�ꥢ                               */
/*          : data   = �ǡ���                                         */
/**********************************************************************/
#define     RIGHT_DATA_SET( target, data )                             \
            if (((data) >= 'a')&&((data) <= 'f')) {                    \
                (data) -= 0x57 ;                                       \
            }                                                          \
            ((target) = ((target) & 0xf0) | ((data) & 0x0f))

/**********************************************************************/
/* �ޥ���̾ : NUM_TO_HEX( hex, num )                                  */
/*   ���ꤵ�줿���ͥǡ�����HEX�ǡ������Ѵ����롣                    */
/* ------------------------------------------------------------------ */
/* ����     : hex = HEX�ǡ������ꥨ�ꥢ                               */
/*          : num = ���ͥǡ���                                        */
/**********************************************************************/
#define     NUM_TO_HEX( hex, num )                                     \
            (hex) = ((num) < 10) ? ((num) + 0x30) : ((num) + 0x57)

/**********************************************************************/
/* �ޥ���̾ : CHAR_TO_HEX( hex, char, offset )                        */
/*   ���ꤵ�줿ʸ���ǡ�����HEX�ǡ������Ѵ����롣                    */
/* ------------------------------------------------------------------ */
/* ����     : hex    = HEX�ǡ������ꥨ�ꥢ                            */
/*          : char   = ʸ���ǡ���                                     */
/**********************************************************************/
#define     CHAR_TO_HEX( hex, char )                                   \
            (hex) = (((char) >= '0')&&((char) <= '9')) ?               \
                    ((char) - '0') : ((char) - 'a' + 0x0a) ;

/**********************************************************************/
/* �ޥ���̾ : CHAR_TO_DEC( dec, char, len )                           */
/*   ���ꤵ�줿ʸ���ǡ�����10�ʥǡ������Ѵ����롣                   */
/* ------------------------------------------------------------------ */
/* ����     : dec    = 10�ʥǡ������ꥨ�ꥢ                           */
/*          : char   = ʸ���ǡ���                                     */
/*          : len    = ʸ���ǡ���Ĺ                                   */
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
/* �ޥ���̾ : DEC_TO_BINSTR( dec, size, output )                      */
/*   ���ꤵ�줿10�ʿ��ǡ�����2�ʿ��ǡ���(ʸ��)���Ѵ����롣          */
/* ------------------------------------------------------------------ */
/* ����     : dec    = 10�ʿ��ǡ���                                   */
/*          : size   = �Ѵ��оݥǡ���Ĺ                               */
/*          : output = �Ѵ���ʸ���ǡ���                               */
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
/* �ޥ���̾ : DEC_TO_OCTSTR( dec, size, output )                      */
/*   ���ꤵ�줿10�ʿ��ǡ�����8�ʿ��ǡ���(ʸ��)���Ѵ����롣          */
/* ------------------------------------------------------------------ */
/* ����     : dec    = 10�ʿ��ǡ���                                   */
/*          : size   = �Ѵ��оݥǡ���Ĺ                               */
/*          : output = �Ѵ���ʸ���ǡ���                               */
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
/* �ޥ���̾ : DEC_TO_UDCSTR( dec, size, output )                      */
/*   ���ꤵ�줿10�ʿ��ǡ��������̵��10�ʿ��ǡ���(ʸ��)���Ѵ����롣 */
/* ------------------------------------------------------------------ */
/* ����     : dec    = 10�ʿ��ǡ���                                   */
/*          : size   = �Ѵ��оݥǡ���Ĺ                               */
/*          : output = �Ѵ���ʸ���ǡ���                               */
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
/* �ޥ���̾ : DEC_TO_DECSTR( dec, size, output )                      */
/*   ���ꤵ�줿10�ʿ��ǡ��������ͭ��10�ʿ��ǡ���(ʸ��)���Ѵ����롣 */
/* ------------------------------------------------------------------ */
/* ����     : dec    = 10�ʿ��ǡ���                                   */
/*          : size   = �Ѵ��оݥǡ���Ĺ                               */
/*          : output = �Ѵ���ʸ���ǡ���                               */
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
/* �ޥ���̾ : DEC_TO_PACSTR( dec, size, output )                      */
/*   ���ꤵ�줿�ѥå��ǡ��������ͭ��10�ʿ��ǡ���(ʸ��)���Ѵ����롣 */
/* ------------------------------------------------------------------ */
/* ����     : dec    = 10�ʿ��ǡ���                                   */
/*          : size   = �Ѵ��оݥǡ���Ĺ                               */
/*          : output = �Ѵ���ʸ���ǡ���                               */
/*          : check  = �����å����                                   */
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
/* �ޥ���̾ : STANDON( offset )                                       */
/*   ���ꤵ�줿�ӥåȰ��֤ˡ�1(=standout)�򥻥åȤ��롣               */
/* ------------------------------------------------------------------ */
/* ����     : offset = �ե饰���ꥨ�ꥢ���ե��å�                     */
/**********************************************************************/
#define     STANDON( offset )                                          \
            ifa->search_info[((offset)/8)] |= (0x01 << ((offset)%8))

/**********************************************************************/
/* �ޥ���̾ : STANDCHECK( offset )                                    */
/*   ���ꤵ�줿�ӥåȰ��֤ξ�����֤���                               */
/* ------------------------------------------------------------------ */
/* ����     : offset = �ե饰���ꥨ�ꥢ���ե��å�                     */
/**********************************************************************/
#define     STANDCHECK( offset )                                       \
            ((ifa->search_info[((offset)/8)] >> ((offset)%8)) & 0x01)

/**********************************************************************/
/* �ޥ���̾ : SJIS_TO_EUC( check1, check2 )                           */
/*   ���ꤵ�줿ʸ��[Shift-JIS]��EUC���Ѵ����롣                     */
/* ------------------------------------------------------------------ */
/* ����     : check1 = ʸ���ǡ�����1�Х�����                          */
/*          : check2 = ʸ���ǡ�����2�Х�����                          */
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
/* �ޥ���̾ : EUC_TO_SJIS( check1, check2 )                           */
/*   ���ꤵ�줿ʸ��[EUC]��Shift-JIS���Ѵ����롣                     */
/* ------------------------------------------------------------------ */
/* ����     : check1 = ʸ���ǡ�����1�Х�����                          */
/*          : check2 = ʸ���ǡ�����2�Х�����                          */
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
/* �ޥ���̾ : JIS_TO_EUC( check1, check2 )                            */
/*   ���ꤵ�줿ʸ��[JIS]��EUC���Ѵ����롣                           */
/* ------------------------------------------------------------------ */
/* ����     : check1 = ʸ���ǡ�����1�Х�����                          */
/*          : check2 = ʸ���ǡ�����2�Х�����                          */
/**********************************************************************/
#define     JIS_TO_EUC( check1, check2 )                               \
{                                                                      \
    (check1) = (check1) + 0x80 ;                                       \
    (check2) = (check2) + 0x80 ;                                       \
}

/**********************************************************************/
/* �ޥ���̾ : JIS_TO_SJIS( check1, check2 )                           */
/*   ���ꤵ�줿ʸ��[JIS]��Shift-JIS���Ѵ����롣                     */
/* ------------------------------------------------------------------ */
/* ����     : check1 = ʸ���ǡ�����1�Х�����                          */
/*          : check2 = ʸ���ǡ�����2�Х�����                          */
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
/* �ޥ���̾ : EBCDIC_TO_ASCII( check )                                */
/*   ���ꤵ�줿ʸ��[EBCDIC]��ASCII���Ѵ����롣                      */
/*   * �ܥޥ������Ѥ��륽�����ϡ�[ hi_ebcdic.h ] ������ळ��     */
/* ------------------------------------------------------------------ */
/* ����     : check  = ʸ���ǡ���                                     */
/*          : kind   = EBCDIC(K)�μ���                                */
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
/* �ޥ���̾ : ASCII_TO_EBCDIC( check )                                */
/*   ���ꤵ�줿ʸ��[ASCII]��EBCDIC���Ѵ����롣                      */
/*   * �ܥޥ������Ѥ��륽�����ϡ�[ hi_ebcdic.h ] ������ळ��     */
/* ------------------------------------------------------------------ */
/* ����     : check  = ʸ���ǡ���                                     */
/*          : kind   = EBCDIC(K)�μ���                                */
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
/* �ޥ���̾ : JIS_ESCAPE_GET( check, size, str )                      */
/*   ���ꤵ�줿���������ץ������󥹤Υ������ڤӡ�����ɽ�����᤹��     */
/* ------------------------------------------------------------------ */
/* ����     : check  = ���������ץ�������                           */
/*          : size   = ���������ץ������󥹤ε���ɽ��������           */
/*          : str    = ����ɽ��                                       */
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
