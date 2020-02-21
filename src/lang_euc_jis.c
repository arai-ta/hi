/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Oct 2000                                 */
/* @(#) Version : 2.2                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  JISɽ���ؿ� - lang_euc_jis                                        */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ʸ���ǡ������Ѵ� [ JIS �� EUC ] ���Ƥ���ɽ�����롣             */
/**********************************************************************/
vd  lang_euc_jis( struct ifa_s *ifa )   /* JISɽ���ؿ�                */
{
    li           cnt            ;       /* �롼�ץ�����             */
    li           pos_x          ;       /* X��ɸ                      */
    li           pos_y          ;       /* Y��ɸ                      */
    li           escp_size      ;       /* ���������ץ�����           */
    li           escp_disp_size ;       /* ���������׵���ɽ��������   */
    uc           escp_str[8]    ;       /* ����������ʸ����           */
    uc           check[6]       ;       /* �����å��ǡ���             */
    uc           char_data      ;       /* ʸ���ǡ���                 */
    ch           word_flg       ;       /* 2�Х���ʸ���ե饰          */
    ch           escp_flg       ;       /* ���������ץե饰           */

    trace_start( ifa, "lang_euc_jis" ) ;/* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �������                                                           */
/* ------------------------------------------------------------------ */
    pos_x = BASE_X3 ;                   /* �١�����ɸ(X)������        */
    pos_y = BASE_Y ;                    /* �١�����ɸ(Y)������        */
    word_flg = 0 ;                      /* 2�Х���ʸ���ե饰�ν����  */
    escp_flg = 0 ;                      /* ���������פν����         */
    char_data = 0x00 ;                  /* ʸ���ǡ����ν����         */
    escp_size = 0 ;
    escp_disp_size = 0 ;

/* ------------------------------------------------------------------ */
/* �ǡ��������å�                                                     */
/* ------------------------------------------------------------------ */
    if ( ifa->view_offset > 0 ) {       /* ��Ƭ�ʳ�                   */
        for ( cnt = ifa->view_offset ; cnt >= 0 ; cnt-- ) {
                                        /* ���ǡ��������å�           */
            memcpy(check, &ifa->workarea[cnt], 6) ;
                                        /* �����å��ǡ���(6�Х���)����*/
            if ( ( memcmp( check, JIS_ASCII, 3 ) == 0 )||
                 ( memcmp( check, JIS_ROMAN_SET, 3 ) == 0 )||
                 ( memcmp( check, JIS_HALF_KANA, 3 ) == 0 ) ) {
                                        /* 1�Х���ʸ��                */
                word_flg = 0 ;          /* 1�Х���ʸ��������          */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* ���������׾���μ���       */
                if ( ( ifa->view_offset - cnt ) < escp_size ) {
                                        /* ���������׾���ν�����     */
                    escp_flg = 1 ;      /* ���������פ�����           */
                    escp_disp_size = ( ifa->view_offset - cnt ) ;
                                        /* ���������׾���ν���       */
                }                       /* end if                     */
                else {                  /* �Ļ�ʸ���ν�����           */
                    escp_flg = 0 ;      /* ���������פβ��           */
                    escp_disp_size = 0 ;/* ���������׾���ν����     */
                                        /* ���������׾���ν���       */
                }                       /* end else                   */
                break ;                 /* break for                  */
            }                           /* end if                     */
            else if ( ( memcmp( check, JIS_X0208_OLD, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_NEW, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_ADD, 6 ) == 0 )||
                      ( memcmp( check, JIS_X0212, 3 ) == 0 ) ) {
                                        /* 2�Х���ʸ��                */
                word_flg = 1 ;          /* 2�Х���ʸ��������          */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* ���������׾���μ���       */
                if ( ( ifa->view_offset - cnt ) < escp_size ) {
                                        /* ���������׾���ν�����     */
                    escp_flg = 1 ;      /* ���������פ�����           */
                    escp_disp_size = ( ifa->view_offset - cnt ) ;
                                        /* ���������׾���ν���       */
                }                       /* end if                     */
                else {                  /* �Ļ�ʸ���ν�����           */
                    escp_flg = 0 ;      /* ���������פβ��           */
                    escp_disp_size = 0 ;/* ���������׾���ν����     */
                    if ( ( ( ifa->view_offset - cnt ) % 2 ) == 0 ) {
                                        /* 2�Х���ʸ����1�Х�����     */
                        word_flg = 2 ;  /* 2�Х���ʸ��������          */
                    }                   /* end else                   */
                }                       /* end else                   */
                break ;                 /* break for                  */
            }                           /* end else if                */
        }                               /* end for                    */
    }                                   /* end if                     */
    
/* ------------------------------------------------------------------ */
/* �ǡ�����ɽ��                                                       */
/* ------------------------------------------------------------------ */
    for ( cnt = ifa->view_offset ; cnt < ifa->size ; cnt++ ) {
                                        /* ���ǡ����ν���             */
        if ( pos_y == ( ifa->lines - 1 ) ) {
                                        /* �ǽ���                     */
            break ;                     /* �ǡ���ɽ���ν�λ           */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* ���������ץ����ɤ�����å�����                                     */
/* ------------------------------------------------------------------ */
        memcpy(check, &ifa->workarea[cnt], 6) ;
                                        /* �����å��ǡ���(6�Х���)����*/
        if ( escp_flg == 0 ) {          /* ���������ץ����å�ɬ��     */
            if ( ( memcmp( check, JIS_ASCII, 3 ) == 0 )||
                 ( memcmp( check, JIS_ROMAN_SET, 3 ) == 0 )||
                 ( memcmp( check, JIS_HALF_KANA, 3 ) == 0 ) ) {
                                        /* 1�Х���ʸ��                */
                word_flg = 0 ;          /* 1�Х���ʸ��������          */
                escp_flg = 1 ;          /* ���������פ�����           */
                escp_disp_size = 0 ;    /* ����ɽ���������ν����     */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* ���������׾���μ���       */
            }                           /* end if                     */
            else if ( ( memcmp( check, JIS_X0208_OLD, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_NEW, 3 ) == 0 )||
                      ( memcmp( check, JIS_X0208_ADD, 6 ) == 0 )||
                      ( memcmp( check, JIS_X0212, 3 ) == 0 ) ) {
                                        /* 2�Х���ʸ��                */
                word_flg = 1 ;          /* 2�Х���ʸ��������          */
                escp_flg = 1 ;          /* ���������פ�����           */
                escp_disp_size = 0 ;    /* ����ɽ���������ν����     */
                JIS_ESCAPE_GET( check, escp_size, escp_str ) ;
                                        /* ���������׾���μ���       */
            }                           /* end else if                */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* ���������ץ����ɽ���                                               */
/* ------------------------------------------------------------------ */
        if ( escp_flg == 1 ) {          /* ���������׽�����           */
            standout() ;                /* ��Ĵ�⡼�ɳ���             */
            move(pos_y, pos_x) ; printw("%c", escp_str[escp_disp_size]) ;
                                        /* ���������׵���ɽ����ɽ��   */
            standend() ;                /* ��Ĵ�⡼�ɽ�λ             */
            pos_x++ ;                   /* ����������ֹ���           */
            escp_disp_size++ ;          /* ����ɽ���������ι���       */
            if ( escp_disp_size >= escp_size ) {
                                        /* ���������׽�����λ         */
                escp_flg = 0 ;          /* ���������פβ��           */
            }                           /* end if                     */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* ʸ�������ɽ���                                                     */
/* ------------------------------------------------------------------ */
        else {                          /* ʸ���ǡ���������           */
            if ( word_flg == 0 ) {      /* 1�Х���ʸ��������          */
                if ((check[0] >= 0x20)&&(check[0] <= 0x7e)) {
                                        /* �Ļ�ʸ��(1�Х���ʸ��)      */
                    char_data = check[0] ;
                                        /* ���Τޤ�ɽ��               */
                }                       /* end if                     */
                else {                  /* �ԲĻ�ʸ��                 */
                    char_data = TEN ;   /* �ԲĻ�ʸ���ΰ�,(.)���Ѵ�   */
                }                       /* end else                   */
                move(pos_y, pos_x) ; printw("%c", char_data) ;
                                        /* 1�Х���ʸ����ɽ��          */
                pos_x++ ;               /* ����������ֹ���           */
            }                           /* end if                     */
            else if ( word_flg == 1 ) { /* 2�Х���ʸ����������        */
                JIS_TO_EUC( check[0], check[1] ) ;
                                        /* �Ѵ� [ JIS �� EUC ]        */
                move(pos_y, pos_x) ; printw("%.2s", check) ;
                                        /* 1�Х���ʸ����ɽ��          */
                word_flg = 2 ;          /* 2�Х���ʸ��������          */
                pos_x += 2 ;            /* ����������ֹ���           */
            }                           /* end else if                */
            else if ( word_flg == 2 ) { /* 2�Х���ʸ��������          */
                if ( cnt == ifa->view_offset ) {
                                        /* 2�Х���ʸ�������椫�鳫��  */
                    move(pos_y, BASE_X3) ; printw("%c", '@') ;
                                        /* �ü�ʸ����ɽ��             */
                    pos_x++ ;           /* ����������ֹ���           */
                }                       /* end if                     */
                word_flg = 1 ;          /* 2�Х���ʸ����������        */
            }                           /* end else                   */
        }                               /* end else                   */

        if ( ( cnt % 16 ) == 15 ) {     /* 1�Ԥν�λ                  */
            pos_y++ ;                   /* ���ιԤ�                   */
            if ( ( pos_x == ( BASE_X3 + 17 ) )&&
                 ( pos_y < ( ifa->lines - 1 ) ) ) {
                                        /* �Ը٤��2�Х���ʸ��        */
                move(pos_y, BASE_X3) ; printw("%c", '@') ;
                                        /* �ü�ʸ����ɽ��             */
                pos_x = BASE_X3 + 1 ;   /* �١�����ɸ(X)������        */
            }                           /* end if                     */
            else {                      /* �Ԥ���Ƭ����               */
                pos_x = BASE_X3 ;       /* �١�����ɸ(X)������        */
            }                           /* end else                   */
        }                               /* end if                     */
    }                                   /* end for                    */

    refresh() ;                         /* ������ɥ��κ�����         */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - lang_euc_jis      */
}                                       /* end (lang_euc_jis)         */

/**********************************************************************/