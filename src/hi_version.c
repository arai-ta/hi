/**********************************************************************/
/*  hi - バイナリエディタ                                             */
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
/* インクルードファイル                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  バージョン表示関数 - hi_version                                   */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   バージョン表示を行う。                                           */
/**********************************************************************/
vd  hi_version( struct ifa_s *ifa )     /* バージョン表示関数         */
{

    trace_start( ifa, "hi_version" ) ;  /* トレース取得               */
/* ------------------------------------------------------------------ */
/* コマンド受付と判定                                                 */
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

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - hi_version        */
}                                       /* end (hi_version)           */

/**********************************************************************/
