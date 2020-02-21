/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : May 2004                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 0t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004 Tatsuyoshi                                   */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  �С������ɽ���ؿ� - hi_version                                   */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   �С������ɽ����Ԥ���                                           */
/**********************************************************************/
vd  hi_version( struct ifa_s *ifa )     /* �С������ɽ���ؿ�         */
{

    trace_start( ifa, "hi_version" ) ;  /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ���ޥ�ɼ��դ�Ƚ��                                                 */
/* ------------------------------------------------------------------ */
/*    printf("\n") ;*/
    printf("Binary editor(hi) version %s release %s\n",
            VERSION,RELEASE) ;
    printf("Copyright (c) 1998-2000 Kazunori Mita.\n") ;
    printf("Copyright (c) 2004 Tatsuyoshi\n") ;
/*    printf("\n") ;
    printf("The latest version is located at\n") ;
    printf("    Japanese version : ") ;
    printf("<http://www2.plala.or.jp/mita/download/hi/info.html>.\n") ;
    printf("    English version  : ") ;
    printf("<http://www2.plala.or.jp/mita/download/hi/info_en.html>.\n") ;
    printf("\n") ;
    printf("Report bugs to <mita@maroon.plala.or.jp>.\n") ;*/
    printf("\n") ;

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - hi_version        */
}                                       /* end (hi_version)           */

/**********************************************************************/
