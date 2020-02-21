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
#include    <errno.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>
#include    <hi_std.h>

/**********************************************************************/
/*  �ե������ɤ߹��ߴؿ� - hi_config                                  */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   �Ķ��ե�������ɤ߹��ߡ���������Ԥ���                         */
/**********************************************************************/
vd  hi_config( struct ifa_s *ifa )      /* �Ķ��ե������ɤ߹��ߴؿ�   */
{
    FILE        *fpin     ;             /* �Ķ��ե�����               */
    li           ret      ;             /* �꥿���󥳡���(����)       */
    ch          *fgets_ret;             /* fgets()�꥿���󥳡���      */
    ch          *home     ;             /* �ۡ���ǥ��쥯�ȥ�         */
    ch          *equal    ;             /* '='����                    */
    ch           conf[128];             /* �Ķ��ե�����(�ե�ѥ�)     */
    ch           area[128];             /* �Ķ��������               */
    ch           _set[32] ;             /* :set��Ǽ���ꥢ             */
    ch           dinf[32] ;             /* ��������Ǽ���ꥢ         */
    ch           dval[32] ;             /* ����ͳ�Ǽ���ꥢ           */
    struct stat  st       ;             /* �ե����륹�ơ�����         */

    trace_start( ifa, "hi_config" ) ;   /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �ե�����ݥ��󥿤ν����                                           */
/* ------------------------------------------------------------------ */
    fpin = NULL ;                       /* �ե�����ݥ��󥿤ν����   */

/* ------------------------------------------------------------------ */
/* �ۡ���ǥ��쥯�ȥ�μ���                                           */
/* ------------------------------------------------------------------ */
    home = getenv( "HOME" ) ;           /* �ۡ���ǥ��쥯�ȥ�μ���   */
    if ( home == NULL ) {               /* ��������                   */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - hi_config         */
    }                                   /* end if                     */
    snprintf( conf, 127, "%s/%s", home, HI_CONFIG ) ;
                                        /* �Ķ��ե�����(�ե�ѥ�)���� */
/* ------------------------------------------------------------------ */
/* �ե����륹�ơ������μ���                                           */
/* ------------------------------------------------------------------ */
    ret = stat( conf, &st ) ;           /* �ե����륹�ơ���������     */
    if ( ret == (-1) ) {                /* �ե����뤬¸�ߤ��ʤ�       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - hi_config         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե�����Υ����ץ�                                                 */
/* ------------------------------------------------------------------ */
    fpin = fopen( conf, "rb" ) ;        /* �ե����륪���ץ�           */
    if ( fpin == NULL ) {               /* �ե����륪���ץ���       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - hi_config         */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �����������ɤ߹���                                               */
/* ------------------------------------------------------------------ */
    while ( 1 ) {                       /* �����������ɤ߹���       */

        fgets_ret = fgets( area, 127, fpin ) ;
                                        /* �ե�������ɤ߹���         */
        if ( fgets_ret == NULL ) {      /* �ե������ɤ߹��߼�������   */
                                        /* �ե�����ν�ü����       */
            break ;                     /* break while                */
        }                               /* end if                     */

        if ( area[0] == '#' ) {         /* �����ȹ�                 */
            continue ;                  /* continue while             */
        }                               /* end if                     */

        equal = strchr( area, ((li)'=') ) ;
                                        /* '='���֤μ���              */
        *equal = ' ' ;                  /* '=' �� ' ' ���Ѵ�          */
        /* I think this sscanf is dengerous. */
        sscanf( area, "%s %s %s", _set, dinf, dval ) ;
                                        /* ����Ԥμ���               */
        if ( strncmp( dinf, "TR", 2 ) == 0 ) {
                                        /* ʸ��ɽ�����ꥢ�θ������   */
            switch ( (li)dval[0] ) {    /* ��������å�               */
                case (li)'a' : ifa->lang = LANG_ASCII  ; break ;
                case (li)'e' : ifa->lang = LANG_EUC    ; break ;
                case (li)'s' : ifa->lang = LANG_SJIS   ; break ;
                case (li)'j' : ifa->lang = LANG_JIS    ; break ;
                case (li)'b' : ifa->lang = LANG_EBCDIC ;
                    switch ( (li)dval[1] ) {
                                        /* EBCDIC(K)�����å�          */
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
                                        /* ��������ݥ������λ���   */
            switch ( (li)dval[0] ) {    /* ��������ݥ����������å� */
                case (li)'h' : ifa->target = HEX_DATA  ; break ;
                case (li)'c' : ifa->target = CHAR_DATA ; break ;
                default      : ifa->target = HEX_DATA  ; break ;
            }                           /* end switch                 */
        }                               /* end else if                */
        else if ( strncmp( dinf, "SR", 2 ) == 0 ) {
                                        /* ����ʸ�����ȿžɽ������   */
            if ( strncmp( dval, "on", 2 ) == 0 ) {
                ifa->reverse = REVERSE ;/* ȿžɽ������               */
            }                           /* end if                     */
            else if ( strncmp( dval, "off", 3 ) == 0 ) {
                ifa->reverse = NOT_REVERSE ;
                                        /* ȿžɽ�����ʤ�             */
            }                           /* end else if                */
            else {                      /* �����Ͱʳ�                 */
                ifa->reverse = REVERSE ;/* ȿžɽ������               */
            }                           /* end else                   */
        }                               /* end else if                */
        else if ( strncmp( dinf, "EO", 2 ) == 0 ) {
                                        /* ư��Ķ�ɽ���λ���         */
            if ( strncmp( dval, "on", 2 ) == 0 ) {
                ifa->envout = ENVOUT ;  /* ư��Ķ���ɽ������         */
            }                           /* end if                     */
            else if ( strncmp( dval, "off", 3 ) == 0 ) {
                ifa->envout = NOT_ENVOUT ;
                                        /* ư��Ķ���ɽ�����ʤ�       */
            }                           /* end else if                */
            else {                      /* �����Ͱʳ�                 */
                ifa->reverse = ENVOUT ; /* ư��Ķ���ɽ������         */
            }                           /* end else                   */
        }                               /* end else if                */
        else if ( strncmp( dinf, "AS", 2 ) == 0 ) {
                                        /* �ɲú���ΰ�Υ���������   */
            sscanf( dval, "%d", &ifa->alloc_size ) ;
                                        /* �ɲú���ΰ襵�����μ���   */
        }                               /* end else if                */
        else if ( strncmp( dinf, "MS", 2 ) == 0 ) {
                                        /* �������ΰ�Υ���������   */
            sscanf( dval, "%d", &ifa->max_size ) ;
                                        /* �������ΰ襵�����μ���   */
        }                               /* end else if                */

    }                                   /* end while                  */

/* ------------------------------------------------------------------ */
/* �ե�����Υ�����                                                 */
/* ------------------------------------------------------------------ */
    fclose( fpin ) ;                    /* �ե����륯����           */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - hi_config         */
}                                       /* end (hi_config)            */

/**********************************************************************/
