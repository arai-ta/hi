/**********************************************************************/
/*  hi - �Х��ʥꥨ�ǥ���                                             */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Aug 2000                                 */
/* @(#) Version : 2.1                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/**********************************************************************/
/* ================================================================== */
/* ���󥯥롼�ɥե�����                                               */
/* ================================================================== */
#include    <hi_std.h>

/**********************************************************************/
/*  �ǡ���ɽ���ؿ� - data_view                                        */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ������ɥ��ˡ��ǡ�����ɽ�����롣                                 */
/**********************************************************************/
vd  data_view( struct ifa_s *ifa )      /* �ǡ���ɽ���ؿ�             */
{
    li           cnt         ;          /* �롼�ץ�����             */
    li           pos_x[2]    ;          /* X��ɸ                      */
    li           pos_y       ;          /* Y��ɸ                      */
    li           cur_pos_x   ;          /* �����������(X��ɸ)        */
    li           cur_pos_y   ;          /* �����������(Y��ɸ)        */
    li           term_trgt   ;          /* �оݵ�ǽ�ؿ����ɥ쥹       */
    li           lang_trgt   ;          /* �оݵ�ǽ�ؿ����ɥ쥹       */
    ch           hex_data[2] ;          /* HEX�ǡ���                  */
    uc           num_data    ;          /* ���ͥǡ���                 */
    vd        (*funcmtx[FUNC_T_MAX][FUNC_L_MAX])() ;
                                        /* �оݵ�ǽ�ؿ����ɥ쥹       */

    trace_start( ifa, "data_view" ) ;   /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �������                                                           */
/* ------------------------------------------------------------------ */
    pos_x[0] = BASE_X1 ;                /* �١�����ɸ(X1)������       */
    pos_x[1] = BASE_X2 ;                /* �١�����ɸ(X2)������       */
    pos_y = BASE_Y ;                    /* �١�����ɸ(Y)������        */

    cur_pos_x = ifa->cur_pos_x ;        /* �����������(X��ɸ)������  */
    cur_pos_y = ifa->cur_pos_y ;        /* �����������(Y��ɸ)������  */

    ifa->cur_pos_x = pos_x[1] ;         /* �����������(X��ɸ)������  */
    ifa->cur_pos_y = pos_y ;            /* �����������(Y��ɸ)������  */

    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* ��������ΰ�ư             */
    clrtobot() ;                        /* ������ɥ��Υ��ꥢ         */

/* ------------------------------------------------------------------ */
/* �ؿ����ɥ쥹����                                                   */
/* ------------------------------------------------------------------ */
    funcmtx[FUNC_T_A][FUNC_L_A] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_A][FUNC_L_E] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_A][FUNC_L_S] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_A][FUNC_L_J] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_A][FUNC_L_B] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_E][FUNC_L_A] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_E][FUNC_L_E] = lang_euc_euc ;
                                        /* EUCɽ���ؿ�                */
    funcmtx[FUNC_T_E][FUNC_L_S] = lang_euc_sjis ;
                                        /* SJISɽ���ؿ�               */
    funcmtx[FUNC_T_E][FUNC_L_J] = lang_euc_jis ;
                                        /* JISɽ���ؿ�                */
    funcmtx[FUNC_T_E][FUNC_L_B] = lang_ascii_ebcdic ;
                                        /* EBCDICɽ���ؿ�             */
    funcmtx[FUNC_T_S][FUNC_L_A] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_S][FUNC_L_E] = lang_sjis_euc ;
                                        /* EUCɽ���ؿ�                */
    funcmtx[FUNC_T_S][FUNC_L_S] = lang_sjis_sjis ;
                                        /* SJISɽ���ؿ�               */
    funcmtx[FUNC_T_S][FUNC_L_J] = lang_sjis_jis ;
                                        /* JISɽ���ؿ�                */
    funcmtx[FUNC_T_S][FUNC_L_B] = lang_ascii_ebcdic ;
                                        /* EBCDICɽ���ؿ�             */
    funcmtx[FUNC_T_O][FUNC_L_A] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_O][FUNC_L_E] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_O][FUNC_L_S] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_O][FUNC_L_J] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
    funcmtx[FUNC_T_O][FUNC_L_B] = lang_ascii ;
                                        /* ASCIIɽ���ؿ�              */
/* ------------------------------------------------------------------ */
/* ���ե��åȤ�ɽ��                                                   */
/* ------------------------------------------------------------------ */
    move(OFST_Y, OFST_X) ;              /* ���������ư               */
    if ( ifa->data_offset == 0 ) {      /* ����������֤�����Ƭ       */
        printw("%08x", ifa->data_offset) ;
                                        /* ���ե��åȤ�ɽ��           */
    }                                   /* end if                     */
    else {                              /* ����������֤�����Ƭ�ʳ�   */
        printw("%08x", ifa->data_offset - 1) ;
                                        /* ���ե��åȤ�ɽ��           */
    }                                   /* end else                   */

/* ------------------------------------------------------------------ */
/* �ǡ�����ɽ��                                                       */
/* ------------------------------------------------------------------ */
    move(pos_y, pos_x[0]) ; printw("%08x", 0) ;
                                        /* �ǡ���̵�����Υ��ɥ쥹ɽ�� */
    for ( cnt = ifa->view_offset ; cnt < ifa->size ; cnt++ ) {
                                        /* ���ǡ����ν���             */
        if ( pos_y == ( ifa->lines - 1 ) ) {
                                        /* �ǽ���                     */
            break ;                     /* �ǡ���ɽ���ν�λ           */
        }                               /* end if                     */
        if ( ( cnt % 16 ) == 0 ) {      /* 1�Ԥγ���                  */
            move(pos_y, pos_x[0]) ; printw("%08x", cnt) ;
                                        /* ���ɥ쥹��ɽ��             */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* ���ͤ�HEX�ǡ������Ѵ�����                                          */
/* ------------------------------------------------------------------ */
        num_data = ( (uc)( ifa->workarea[cnt] ) >> 4 ) ;
                                        /* ��̥Х��Ȥμ���           */
        NUM_TO_HEX( (hex_data[0]), (num_data) ) ;
                                        /* ���ͥǡ�����HEX�ǡ������Ѵ�*/

        num_data = ( (uc)( ifa->workarea[cnt] ) & MASK ) ;
                                        /* ���̥Х��Ȥμ���           */
        NUM_TO_HEX( (hex_data[1]), (num_data) ) ;
                                        /* ���ͥǡ�����HEX�ǡ������Ѵ�*/
        if ( ifa->search_info != 0x00 ) {
                                        /* �������ɽ��               */
            if ( ( ifa->reverse == REVERSE )&&
                 ( STANDCHECK( cnt ) == 0x01 ) ) {
                                        /* ����ʸ����                 */
                standout() ;            /* ��Ĵ�⡼�ɳ���             */
                move(pos_y, pos_x[1]) ; printw("%.2s", hex_data) ;
                                        /* 16�ʥǡ�����ɽ��           */
                standend() ;            /* ��Ĵ�⡼�ɽ�λ             */
            }                           /* end if                     */
            else {                      /* ����ʸ����ʳ�             */
                move(pos_y, pos_x[1]) ; printw("%.2s", hex_data) ;
                                        /* 16�ʥǡ�����ɽ��           */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* ��������ɽ��               */
            move(pos_y, pos_x[1]) ; printw("%.2s", hex_data) ;
                                        /* 16�ʥǡ�����ɽ��           */
        }                               /* end else                   */
        pos_x[1] += 3 ;                 /* 16�ʥǡ���ɽ�����֤ι���   */
        if ( ( cnt % 16 ) == 15 ) {     /* 1�Ԥν�λ                  */
            pos_y++ ;                   /* ���ιԤ�                   */
            pos_x[1] = BASE_X2 ;        /* �١�����ɸ(X2)���ᤷ       */
        }                               /* end if                     */
    }                                   /* end for                    */
    refresh() ;                         /* ������ɥ��κ�����         */

/* ------------------------------------------------------------------ */
/* ������б�����ʸ��ɽ����Ԥ�                                       */
/* ------------------------------------------------------------------ */
    switch ( ifa->term_lang ) {         /* ü���θ���°�������å�     */
        case LANG_ASCII :               /* ü���θ���°��:[ASCII]     */
            term_trgt = FUNC_T_A ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        case LANG_EUC :                 /* ü���θ���°��:[EUC]       */
            term_trgt = FUNC_T_E ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        case LANG_SJIS :                /* ü���θ���°��:[SJIS]      */
            term_trgt = FUNC_T_S ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        default :                       /* ü���θ���°��:����¾      */
            term_trgt = FUNC_T_O ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
    }                                   /* end switch                 */

    switch ( ifa->lang ) {              /* ��������å�               */
        case LANG_ASCII :               /* ����:[ASCII]               */
            lang_trgt = FUNC_L_A ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        case LANG_EUC :                 /* ����:[EUC]                 */
            lang_trgt = FUNC_L_E ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        case LANG_SJIS :                /* ����:[SJIS]                */
            lang_trgt = FUNC_L_S ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        case LANG_JIS :                 /* ����:[JIS]                 */
            lang_trgt = FUNC_L_J ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        case LANG_EBCDIC :              /* ����:[EBCDIC]              */
            lang_trgt = FUNC_L_B ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
        default :                       /* ����:����¾                */
            lang_trgt = FUNC_L_A ;      /* �оݵ�ǽ�ֹ������         */
            break ;                     /* swtich break               */
    }                                   /* end switch                 */

    (*funcmtx[term_trgt][lang_trgt])( ifa ) ;
                                        /* �оݵ�ǽ������             */
    ifa->cur_pos_x = cur_pos_x ;        /* �����������(X��ɸ)������  */
    ifa->cur_pos_y = cur_pos_y ;        /* �����������(Y��ɸ)������  */
    move(ifa->cur_pos_y, ifa->cur_pos_x) ;
                                        /* �����������ɽ�����֤�   */
    refresh() ;                         /* ������ɥ��κ�����         */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - data_view         */
}                                       /* end (data_view)            */

/**********************************************************************/
