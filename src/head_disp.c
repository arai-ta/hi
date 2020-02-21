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
#include    <unistd.h>
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  �إå�ɽ���ؿ� - head_disp                                        */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   �إå��ΰ��ɽ����Ԥ���                                         */
/**********************************************************************/
vd  head_disp( struct ifa_s *ifa )      /* �إå�ɽ���ؿ�             */
{
    ch            head_string_1_3[16] ; /* �إå�����1_3              */
    ch            version_string[8] ;   /* �С���������             */

    trace_start( ifa, "head_disp" ) ;   /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �إå�����1_3���Խ�                                                */
/* ------------------------------------------------------------------ */
    switch ( ifa->lang ) {              /* �����Ƚ��                 */
        case LANG_ASCII :               /* ����:ASCII                 */
            strlcpy( head_string_1_3, "[ASCII]", sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
            break ;                     /* break switch               */

        case LANG_EUC :                 /* ����:EUC                   */
            strlcpy( head_string_1_3, "[Japanese EUC]",
            sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
            break ;                     /* break switch               */

        case LANG_SJIS :                /* ����:Shift-JIS             */
            strlcpy( head_string_1_3, "[Shift-JIS]",
                     sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
            break ;                     /* break switch               */

        case LANG_JIS :                 /* ����:JIS                   */
            strlcpy( head_string_1_3, "[JIS]",
                     sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
            break ;                     /* break switch               */

        case LANG_EBCDIC :              /* ����:EBCDIC                */
            switch ( ifa->ebcdic ) {    /* EBCDIC(K)��Ƚ��            */
                case EBCDIC_IBM :       /* EBCDIC IBM                 */
                    strlcpy( head_string_1_3, "[EBCDIC IBM]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
                    break ;             /* break switch               */

                case EBCDIK_HITAC :     /* EBCDIK HITACHI             */
                    strlcpy( head_string_1_3, "[EBCDIK HITAC]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
                    break ;             /* break switch               */

                case EBCDIC_NEC :       /* EBCDIC NEC                 */
                    strlcpy( head_string_1_3, "[EBCDIC NEC]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
                    break ;             /* break switch               */

                case EBCDIC :           /* EBCDIC                     */
                    strlcpy( head_string_1_3, "[EBCDIC]",
                             sizeof( head_string_1_3 ) ) ;
                                        /* ɽ�����������             */
                    break ;             /* break switch               */

            }                           /* end switch                 */
            break ;                     /* break switch               */
    }                                   /* end switch                 */

/* ------------------------------------------------------------------ */
/* �إå���ɽ��                                                       */
/* ------------------------------------------------------------------ */
    mvaddstr(HEAD_Y1, HEAD_X1_1, HEAD_STRING_1_1) ;
                                        /* �إå�����1_1��ɽ��        */
    mvaddstr(HEAD_Y1, HEAD_X1_2, HEAD_STRING_1_2) ;
                                        /* �إå�����1_2��ɽ��        */
    mvaddstr(HEAD_Y1, HEAD_X1_3, head_string_1_3) ;
                                        /* �إå�����1_3��ɽ��        */
#ifdef DISP_LINE2
    mvaddstr(HEAD_Y2, HEAD_X2_1, HEAD_STRING_2_1) ;
                                        /* �إå�����2_1��ɽ��        */
    mvaddstr(HEAD_Y2, HEAD_X2_2, HEAD_STRING_2_2) ;
                                        /* �إå�����2_2��ɽ��        */
    mvaddstr(HEAD_Y2, HEAD_X2_3, HEAD_STRING_2_3) ;
                                        /* �إå�����2_3��ɽ��        */
#endif
/* ------------------------------------------------------------------ */
/* �С����������ɽ��                                               */
/* ------------------------------------------------------------------ */
    memset( version_string, 0x00, sizeof(version_string) ) ;
                                        /* �С���������ν����     */
    snprintf( version_string, sizeof( version_string ), "%s-%s",
              VERSION, RELEASE ) ;      /* �С��������������       */
    mvaddstr(VERSION_Y, VERSION_X, version_string) ;
                                        /* �С����������ɽ��       */
    refresh() ;                         /* ������ɥ��κ�����         */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - head_disp         */
}                                       /* end (head_disp)            */

/**********************************************************************/
