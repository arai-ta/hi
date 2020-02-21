/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/*    �����ޥå�����إå� - hi_keymap.h                              */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : Jun 2004                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 2t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004 Tatsuyoshi                                   */
/* ------------------------------------------------------------------ */
/* �إå�����                                                         */
/*   �Х��ʥꥨ�ǥ����ǻ��Ѥ��륭���ޥåפ�������롣                 */
/**********************************************************************/
/* ------------------------------------------------------------------ */
/* ����ʸ��                                                           */
/* ------------------------------------------------------------------ */
#if defined(KEY_BACKSPACE)
#undef      KEY_BACKSPACE               /* ���������ɤ��ʤ� by curses */
#define     KEY_BACKSPACE  0x08         /* [Backspace]                */
#endif
#define     KEY_CTRL_A     0x01         /* [Ctrl] + [a]               */
#define     KEY_CTRL_B     0x02         /* [Ctrl] + [b]               */
#define     KEY_CTRL_D     0x04         /* [Ctrl] + [d]               */
#define     KEY_CTRL_F     0x06         /* [Ctrl] + [f]               */
#define     KEY_CTRL_G     0x07         /* [Ctrl] + [g]               */
#define     KEY_CTRL_J     0x0a         /* [Ctrl] + [j]               */
#define     KEY_CTRL_L     0x0c         /* [Ctrl] + [l]               */
#define     KEY_CTRL_T     0x14         /* [Ctrl] + [t]               */
#define     KEY_CTRL_U     0x15         /* [Ctrl] + [u]               */
#define     KEY_ESCAPE     0x1b         /* [Esc]                      */

/**********************************************************************/
