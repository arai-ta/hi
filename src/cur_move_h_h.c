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
#include    <hi_std.h>

/**********************************************************************/
/*  �������뺸��ư�ؿ�(HEX) - cur_move_h_h                            */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ��������򺸰�ư����������ɥ�������褹�롣(HEX�ǡ�����)        */
/**********************************************************************/
vd  cur_move_h_h( struct ifa_s *ifa )   /* �������뺸��ư�ؿ�(HEX)    */
{
    li           pos_top  ;             /* �ǡ���ɽ���ΰ�ξ�         */
    li           pos_left ;             /* �ǡ���ɽ���ΰ�κ�         */
    li           pos_right ;            /* �ǡ���ɽ���ΰ�α�         */

    trace_start( ifa, "cur_move_h_h" ) ;/* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ��������򺸤˰�ư                                                 */
/* ------------------------------------------------------------------ */
    pos_top   = 1 ;                     /* ��Ƭ�Ԥ�����               */
    pos_left  = BASE_X2 ;               /* ��ü������                 */
    pos_right = pos_left + ( 3 * 15 ) + 1 ;
                                        /* ��ü������                 */

    if ( ifa->hex_pos == CUR_RIGHT ) {  /* ���̥Х��Ȥ�ݥ������     */
        ifa->cur_pos_x-- ;              /* ����������̥Х��Ȥذ�ư */
        ifa->hex_pos = CUR_LEFT ;       /* ��̥Х��Ȥ�ݥ���Ȥ����� */
                                        /* ��Ф���                   */
    }                                   /* end if                     */
    else {                              /* ���̥Х��Ȥ�ݥ������     */
        if ( ifa->data_offset > 1 ) {   /* ̤ɽ���ǡ���ͭ��           */
            if ( ifa->cur_pos_x <= pos_left ) {
                                        /* ����������֤������ֺ�     */
                if ( ifa->cur_pos_y > pos_top ) {
                                        /* ����������֤�����Ƭ�԰ʳ� */
                    ifa->data_offset-- ;/* �ǡ������ե��åȤι���     */
                    ifa->cur_pos_x = pos_right ;
                                        /* �����������(X��ɸ)�ι���  */
                    ifa->cur_pos_y-- ;  /* �����������(Y��ɸ)�ι���  */
                }                       /* end if                     */
                else if ( ifa->view_offset > 0 ) {
                                        /* �������뤬��Ƭ�Ԥǡ�̤ɽ�� */
                                        /* �ǡ���ͭ��                 */
                    ifa->cur_pos_x = pos_right ;
                                        /* �����������(X)������      */
                    ifa->data_offset-- ;/* �ǡ������ե��åȤι���     */
                    ifa->view_offset -= 16 ;
                                        /* ɽ�����ե��åȤι���       */
                    data_view( ifa ) ;  /* �ǡ���ɽ��                 */
                }                       /* end else if                */
            }                           /* end if                     */
            else {                      /* ����������֤������ֺ��ʳ� */
                ifa->data_offset-- ;    /* �ǡ������ե��åȤι���     */
                ifa->cur_pos_x -= 2 ;   /* �����������(X��ɸ)�ι���  */
            }                           /* end else                   */
            ifa->hex_pos = CUR_RIGHT ;  /* ���̥Х��Ȥ�ݥ���Ȥ����� */
                                        /* ��Ф���                   */
        }                               /* end if                     */
        move(OFST_Y, OFST_X) ;          /* ���������ư               */
        printw("%08x", ifa->data_offset - 1) ;
                                        /* ���ե��åȤ�ɽ��           */
        move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* ���������ư               */
        refresh() ;                     /* ������ɥ�������           */
    }                                   /* end else                   */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - cur_move_h        */
}                                       /* end (cur_move_h)           */

/**********************************************************************/