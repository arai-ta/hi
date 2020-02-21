/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
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
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  �ǡ����Ѵ�ɽ���ؿ� - print_conv_data                              */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ���ꤵ�줿�ǡ����򡢻��ꤵ�줿�������Ѵ�������ɽ�����롣         */
/**********************************************************************/
vd  print_conv_data( struct ifa_s *ifa )/* �ǡ����Ѵ�ɽ���ؿ�         */
{
    ch           *sep       ;           /* ���ѥ졼��                 */
    ch           *data      ;           /* �Ѵ����ǡ���               */
    ch            format[8] ;           /* �ե����ޥå�               */
    ch            inf[128]  ;           /* ����ե��᡼�����ǡ���   */
    ch            cnv[64]   ;           /* �Ѵ���ǡ���               */
    ch            ope       ;           /* ��                         */
    ch            check     ;           /* �����å�                   */
    ul            len       ;           /* �Ѵ��ǡ���Ĺ               */
    ul            cnt       ;           /* �롼�ץ�����             */

    trace_start( ifa, "print_conv_data" ) ;
                                        /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �ե����ޥåȼ���                                                   */
/* ------------------------------------------------------------------ */
    sep = strchr( ifa->cmd_str, ' ' ) ; /* ���ѥ졼�����֤μ���       */
    strlcpy( format, ( sep + 1 ), sizeof( format ) ) ;
                                        /* �ե����ޥåȤμ���         */

/* ------------------------------------------------------------------ */
/* �񼰥����å�                                                       */
/* ------------------------------------------------------------------ */
    for ( cnt = 0 ; cnt < strlen( format ) ; cnt++ ) {
                                        /* �������η������           */
        if ( ( format[cnt] < '0' )||
             ( format[cnt] > '9' ) ) {  /* ���Ͱʳ���ʸ������       */
            break ;                     /* break for                  */
        }                               /* end if                     */
    }                                   /* end for                    */
    if ( cnt > strlen( format ) ) {     /* �����꤬���Ĥ���ʤ�       */
        strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - print_conv_data   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �������å�                                                         */
/* ------------------------------------------------------------------ */
    ope = format[cnt] ;                 /* ������                     */
    if ( ( ope != CONV_BIN )&&
         ( ope != CONV_OCT )&&
         ( ope != CONV_UDC )&&
         ( ope != CONV_DEC )&&
         ( ope != CONV_PAC ) ) {        /* ����������                 */
        strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - print_conv_data   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ��������å�                                                       */
/* ------------------------------------------------------------------ */
    sscanf( format, "%d%c", &len, &ope ) ;
                                        /* �������ο����Ѵ�           */
    if ( ( ( ope == CONV_BIN )||
           ( ope == CONV_OCT )||
           ( ope == CONV_UDC )||
           ( ope == CONV_DEC ) )&&
         ( ( len != 1 )&&( len != 2 )&&( len != 4 ) ) ) {
                                        /* �Ѵ��ǡ���Ĺ����           */
        strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - print_conv_data   */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �����������                                                       */
/* ------------------------------------------------------------------ */
    memset( cnv, 0x00, sizeof( cnv ) ) ;/* �Ѵ���ǡ������ꥢ�ν���� */
    data = &(ifa->workarea[(ifa->data_offset-1)]) ;
                                        /* �Ѵ��оݥǡ������ɥ쥹���� */
    switch ( ope ) {                    /* �Ѵ�������Ƚ��             */
        case CONV_BIN :                 /* 2�ʿ�����                  */
            DEC_TO_BINSTR( data, len, cnv ) ;
                                        /* 2�ʿ��Ѵ�                  */
            snprintf( inf, sizeof( inf ), "%d byte data is (%s)binnary", len,
                      cnv ) ;           /* ɽ��ʸ��������             */
            break ;                     /* break switch               */

        case CONV_OCT :                 /* 8�ʿ�����                  */
            DEC_TO_OCTSTR( data, len, cnv ) ;
                                        /* 8�ʿ��Ѵ�                  */
            snprintf( inf, sizeof( inf ), "%d byte data is (%s)octal", len,
                      cnv ) ;           /* ɽ��ʸ��������             */
            break ;                     /* break switch               */

        case CONV_UDC :                 /* ���̵��10�ʿ�����         */
            DEC_TO_UDCSTR( data, len, cnv ) ;
                                        /* ���̵��10�ʿ��Ѵ�         */
            snprintf( inf, sizeof( inf ),
                      "%d byte data is (%s)unsigned decimal", len, cnv ) ;
                                        /* ɽ��ʸ��������             */
            break ;                     /* break switch               */

        case CONV_DEC :                 /* ���ͭ��10�ʿ�����         */
            DEC_TO_DECSTR( data, len, cnv ) ;
                                        /* ���ͭ��10�ʿ��Ѵ�         */
            snprintf( inf, sizeof( inf ), "%d byte data is (%s)signed decimal",
                      len, cnv ) ;      /* ɽ��ʸ��������             */
            break ;                     /* break switch               */

        case CONV_PAC :                 /* �ѥå�����                 */
            DEC_TO_PACSTR( data, len, cnv, check ) ;
            if ( check != (-1) ) {      /* �����å�OK                 */
                snprintf( inf, sizeof( inf ), "%d byte data is (%s)pack", len,
                          cnv ) ;       /* ɽ��ʸ��������             */
            }                           /* end if                     */
            else {                      /* �����å����顼             */
                strlcpy( ifa->err_msg, "pack data error",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
                trace_end( ifa ) ;      /* �ȥ졼������               */
                return ;                /* return - print_conv_data   */
            }                           /* end else                   */
            break ;                     /* break switch               */

        default       :                 /* ���ͭ��10�ʿ�����         */
            strlcpy( ifa->err_msg, "Format error", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
            trace_end( ifa ) ;          /* �ȥ졼������               */
            return ;                    /* return - print_conv_data   */
    }                                   /* end switch                 */

/* ------------------------------------------------------------------ */
/* �ǡ���ɽ������                                                     */
/* ------------------------------------------------------------------ */
    echo() ;                            /* ���������ϥ⡼��           */
    move(ifa->inf_msg_y, ifa->inf_msg_x) ;
                                        /* ����ե��᡼����󥨥ꥢ�� */
                                        /* ��ư                       */
    clrtobot() ;                        /* ����ե��᡼����󥨥ꥢ�� */
                                        /* ���ꥢ                     */
    addstr( inf ) ;                     /* ����ե��᡼������ɽ��   */
    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* ����������֤��᤹         */
    refresh() ;                         /* ���̤κ�����               */
    noecho() ;                          /* ���������ϥ⡼�ɲ��       */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - print_conv_data   */
}                                       /* end (print_conv_data)      */

/**********************************************************************/
