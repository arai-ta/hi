/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998                                            */
/* @(#) Version : 2.0                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  �������벼��ư�ؿ�(HEX) - cur_move_h_j                            */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ��������򲼰�ư����������ɥ�������褹�롣(HEX�ǡ�����)        */
/**********************************************************************/
vd  cur_move_h_j( struct ifa_s *ifa )   /* �������벼��ư�ؿ�(HEX)    */
{
    li           pos_tail ;             /* �ǡ���ɽ���ΰ�β�         */

    trace_start( ifa, "cur_move_h_j" ) ;/* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ��������򲼤˰�ư                                                 */
/* ------------------------------------------------------------------ */
    pos_tail = ifa->lines - 2 ;         /* �ǽ��Ԥ�����               */

    if ( ( ifa->data_offset + 15 ) < ifa->size ) {
                                        /* ̤ɽ���ǡ���ͭ��           */
        if ( ifa->cur_pos_y < pos_tail ) {
                                        /* ����������֤����ǽ��԰ʳ� */
            ifa->data_offset += 16 ;    /* �ǡ������ե��åȤι���     */
            ifa->cur_pos_y++ ;          /* �����������(Y��ɸ)�ι���  */
        }                               /* end if                     */
        else if ( ifa->size > ( ifa->view_offset + 16 ) ) {
                                        /* �������뤬�ǽ��Ԥǡ�̤ɽ�� */
                                        /* �ǡ���ͭ��                 */
            ifa->data_offset += 16 ;    /* �ǡ������ե��åȤι���     */
            ifa->view_offset += 16 ;    /* ɽ�����ե��åȤι���       */
            data_view( ifa ) ;          /* �ǡ���ɽ��                 */
        }                               /* end else if                */
        move(OFST_Y, OFST_X) ;          /* ���������ư               */
        printw("%08x", ifa->data_offset - 1) ;
                                        /* ���ե��åȤ�ɽ��           */
        move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* ���������ư               */
        refresh() ;                     /* ������ɥ�������           */
    }                                   /* end if                     */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - cur_move_j        */
}                                       /* end (cur_move_j)           */

/**********************************************************************/