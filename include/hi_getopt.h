/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/*    getopt_long ローカル対応 - hi_getopt.h                          */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998                                            */
/* @(#) Version : 2.0                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/* ------------------------------------------------------------------ */
/* ヘッダ概要                                                         */
/*   FreeBSD用にgetopt_long(ローカル対応)の手続きを定義する。         */
/**********************************************************************/
extern char *optarg ;                   /* getlong_optに引き渡す引数  */

struct option {
    const char   *name    ;             /* オプション名               */
    int           has_arg ;             /* 引数の有無                 */
    int          *flag    ;             /* 返り値の設定               */
    int           val     ;             /* 返り値                     */
} ;

extern int getopt_long ( int argc,
                         char **argv,
                         char *shortopts,
                         struct option *longopts,
                         int *longind);
                                        /* 関数型定義                 */

/**********************************************************************/
