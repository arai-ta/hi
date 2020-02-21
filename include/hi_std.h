/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/*    標準ヘッダ - hi_std.h                                           */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : May 2004                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 0t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004 Tatsuyoshi                                   */
/* ------------------------------------------------------------------ */
/* ヘッダ概要                                                         */
/*   バイナリエディタが必要とするヘッダファイルをインクルードする。   */
/**********************************************************************/
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#else
#include <hi_getopt.h>
#endif

#ifdef HAVE_NCURSES_NCURSES_H
#  include <ncurses/ncurses.h>
#else
#  ifdef HAVE_NCURSES_CURSES_H
#    include <ncurses/curses.h>
#  else
#    ifdef HAVE_NCURSES_H
#      include <ncurses.h>
#    else
#      ifdef HAVE_CURSES_H
#        include <curses.h>
#      endif
#    endif
#  endif
#endif

#include    <hi_keymap.h>
#include    <hi_def.h>
#include    <hi_str.h>
#include    <hi_func.h>
#include    <hi_macro.h>

/**********************************************************************/
