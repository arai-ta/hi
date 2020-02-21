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
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  �Ķ�������ϴؿ� - env_output                                     */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   �Ķ�����򡢴Ķ����ϥե�����˽��Ϥ��롣                         */
/**********************************************************************/
vd  env_output( struct ifa_s *ifa )     /* �Ķ�������ϴؿ�           */
{
    FILE              *fp            ;  /* �ե�����ݥ���           */
    li                 line_cnt      ;  /* �оݥإ�׹�               */
    li                 top[256]      ;  /* �оݥڡ�������Ƭ��         */
    li                 page          ;  /* �оݥڡ���                 */
    li                 last_page     ;  /* �ǽ��ڡ���                 */
    ul                 cnt           ;  /* �롼�ץ�����             */
    li                 hed1_pos_x    ;  /* �إå�1ɽ��(X)             */
    li                 hed1_pos_y    ;  /* �إå�1ɽ��(Y)             */
    li                 hed2_pos_x    ;  /* �إå�2ɽ��(X)             */
    li                 hed2_pos_y    ;  /* �إå�2ɽ��(Y)             */
    li                 inf_pos_x     ;  /* ����ե��᡼�����ɽ��(X)  */
    li                 inf_pos_y     ;  /* ����ե��᡼�����ɽ��(Y)  */
    li                 pos_x         ;  /* ɽ����ɸ(X)                */
    li                 pos_y         ;  /* ɽ����ɸ(Y)                */
    ch                 end_flg       ;  /* ��λ�ե饰                 */
    ch                 check_flg     ;  /* �����å��ե饰             */
    ch                 head_str[80]  ;  /* �إå�1ʸ����              */
    struct env_info_s  env[ENV_LINE] ;  /* ư��Ķ����󥨥ꥢ         */

    ch                 msg_status    [32] ;
    ch                 msg_endflg    [32] ;
    ch                 msg_option    [32] ;
    ch                 msg_curses    [32] ;
    ch                 msg_modif     [32] ;
    ch                 msg_target    [32] ;
    ch                 msg_shmid     [32] ;
    ch                 msg_exist     [32] ;
    ch                 msg_lang      [32] ;
    ch                 msg_term_lang [32] ;
    ch                 msg_cmd       [32] ;
    ch                 msg_before_cmd[32] ;
    ch                 msg_mode      [32] ;
    ch                 msg_hex_pos   [32] ;
    ch                 msg_image     [32] ;
    ch                 msg_reverse   [32] ;
    ch                 msg_search    [32] ;
    ch                 msg_helpfile  [32] ;

    trace_start( ifa, "env_output" ) ;  /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �������                                                           */
/* ------------------------------------------------------------------ */
    memset( env, 0x00, sizeof(env) ) ;  /* ư��Ķ����󥨥ꥢ�ν���� */
    snprintf( head_str, sizeof( head_str ),
              " environment information " ) ;
                                        /* �إå�1ʸ��������          */
    page = 0 ;                          /* �оݥڡ����ν����         */
    last_page = -1 ;                    /* �ǽ��ڡ����ν����         */
    for ( cnt = 0 ; cnt < ENV_LINE ; cnt += ( ifa->lines - 4 ) ) {
        top[++last_page] = cnt ;        /* �оݥڡ�������Ƭ�Ԥν���� */
    }                                   /* end if                     */
    end_flg = 0 ;                       /* ��λ�ե饰�ν����         */
    hed1_pos_x = ( ifa->columns - strlen( head_str ) ) / 2 ;
                                        /* �إå�1��ɸ(X)             */
    hed1_pos_y = 0 ;                    /* �إå�1��ɸ(Y)             */
    hed2_pos_x = ifa->columns - 16 ;    /* �إå�2��ɸ(X)             */
    hed2_pos_y = 0 ;                    /* �إå�2��ɸ(Y)             */
    inf_pos_x = ifa->columns - 54 ;     /* ����ե��᡼������ɸ(X)  */
    inf_pos_y = ifa->lines - 1 ;        /* ����ե��᡼������ɸ(Y)  */
    pos_x = 0 ;                         /* ɽ����ɸ(X)                */

/* ------------------------------------------------------------------ */
/* ��������ʸ������Ѵ����롣                                     */
/* ------------------------------------------------------------------ */
    if ( ifa->status == NON_SERVICE ) {
        strlcpy( msg_status, "not service", sizeof( msg_status ) ) ;
    }
    else if ( ifa->status == SERVICE ) {
        strlcpy( msg_status, "service", sizeof( msg_status ) ) ;
    }
    else {
        strlcpy( msg_status, "<null>", sizeof( msg_status ) ) ;
    }

    if ( ifa->endflg == N_END ) {
        strlcpy( msg_endflg, "quit", sizeof( msg_endflg ) ) ;
    }
    else if ( ifa->endflg == D_END ) {
        strlcpy( msg_endflg, "quit, discard", sizeof( msg_endflg ) ) ;
    }
    else if ( ifa->endflg == ABORT ) {
        strlcpy( msg_endflg, "abort", sizeof( msg_endflg ) ) ;
    }
    else if ( ifa->endflg == CONTINUE ) {
        strlcpy( msg_endflg, "continue", sizeof( msg_endflg ) ) ;
    }
    else if ( ifa->endflg == CHANGE ) {
        strlcpy( msg_endflg, "file change", sizeof( msg_endflg ) ) ;
    }
    else {
        strlcpy( msg_endflg, "<null>", sizeof( msg_endflg ) ) ;
    }

    if ( ifa->option == FIL ) {
        strlcpy( msg_option, "ordinary file", sizeof( msg_option ) ) ;
    }
    else if ( ifa->option == SHM ) {
        strlcpy( msg_option, "shared memory", sizeof( msg_option ) ) ;
    }
    else {
        strlcpy( msg_option, "<null>", sizeof( msg_option ) ) ;
    }

    if ( ifa->curses == INIT ) {
        strlcpy( msg_curses, "initialized", sizeof( msg_curses ) ) ;
    }
    else if ( ifa->curses == NOT_INIT ) {
        strlcpy( msg_curses, "uninitialized", sizeof( msg_curses ) ) ;
    }
    else {
        strlcpy( msg_curses, "<null>", sizeof( msg_curses ) ) ;
    }

    if ( ifa->modif == MOD_ON ) {
        strlcpy( msg_modif, "modified", sizeof( msg_modif ) ) ;
    }
    else if ( ifa->modif == MOD_OFF ) {
        strlcpy( msg_modif, "unmodified", sizeof( msg_modif ) ) ;
    }
    else {
        strlcpy( msg_modif, "<null>", sizeof( msg_modif ) ) ;
    }

    if ( ifa->target == HEX_DATA ) {
        strlcpy( msg_target, "hex", sizeof( msg_target ) ) ;
    }
    else if ( ifa->target == CHAR_DATA ) {
        strlcpy( msg_target, "char", sizeof( msg_target ) ) ;
    }
    else {
        strlcpy( msg_target, "<null>", sizeof( msg_target ) ) ;
    }

    if ( strlen( ifa->shmid ) != 0 ) {
        strlcpy( msg_shmid, ifa->shmid, sizeof( msg_shmid ) ) ;
    }
    else {
        strlcpy( msg_shmid, "<null>", sizeof( msg_shmid ) ) ;
    }

    if ( ifa->exist == EXIST ) {
        strlcpy( msg_exist, "exist", sizeof( msg_exist ) ) ;
    }
    else if ( ifa->exist == NOT_EXIST ) {
        strlcpy( msg_exist, "not exist", sizeof( msg_exist ) ) ;
    }
    if ( ifa->lang == LANG_ASCII ) {
        strlcpy( msg_lang, "ASCII", sizeof( msg_lang ) ) ;
    }
    else if ( ifa->lang == LANG_EUC ) {
        strlcpy( msg_lang, "Japanese EUC", sizeof( msg_lang ) ) ;
    }
    else if ( ifa->lang == LANG_SJIS ) {
        strlcpy( msg_lang, "Shift-JIS", sizeof( msg_lang ) ) ;
    }
    else if ( ifa->lang == LANG_JIS ) {
        strlcpy( msg_lang, "JIS", sizeof( msg_lang ) ) ;
    }
    else if ( ifa->lang == LANG_EBCDIC ) {
        if ( ifa->ebcdic == EBCDIC_IBM ) {
            strlcpy( msg_lang, "EBCDIC IBM", sizeof( msg_lang ) ) ;
        }
        else if ( ifa->ebcdic == EBCDIK_HITAC ) {
            strlcpy( msg_lang, "EBCDIK HITACHI", sizeof( msg_lang ) ) ;
        }
        else if ( ifa->ebcdic == EBCDIC_NEC ) {
            strlcpy( msg_lang, "EBCDIC NEC", sizeof( msg_lang ) ) ;
        }
        else if ( ifa->ebcdic == EBCDIC ) {
            strlcpy( msg_lang, "EBCDIC", sizeof( msg_lang ) ) ;
        }
        else {
            strlcpy( msg_lang, "<null>", sizeof( msg_lang ) ) ;
        }
    }
    else {
        strlcpy( msg_lang, "<null>", sizeof( msg_lang ) ) ;
    }

    if ( ifa->term_lang == LANG_ASCII ) {
        strlcpy( msg_term_lang, "ASCII", sizeof( msg_term_lang ) ) ;
        strlcpy( msg_helpfile, "MANUAL.C", sizeof( msg_helpfile ) ) ;
    }
    else if ( ifa->term_lang == LANG_EUC ) {
        strlcpy( msg_term_lang, "Japanese EUC", sizeof( msg_term_lang ) ) ;
        strlcpy( msg_helpfile, "MANUAL.EUC", sizeof( msg_helpfile ) ) ;
    }
    else if ( ifa->term_lang == LANG_SJIS ) {
        strlcpy( msg_term_lang, "Shift-JIS", sizeof( msg_term_lang ) ) ;
        strlcpy( msg_helpfile, "MANUAL.SJIS", sizeof( msg_helpfile ) ) ;
    }
    else {
        strlcpy( msg_term_lang, "<null>", sizeof( msg_term_lang ) ) ;
    }

    if ( ifa->cmd == CMD_CUR_DOWN ) {
        strlcpy( msg_cmd, "cursor down", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_CUR_UP ) {
        strlcpy( msg_cmd, "cursor up", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_CUR_LEFT ) {
        strlcpy( msg_cmd, "cursor left", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_CUR_RIGHT ) {
        strlcpy( msg_cmd, "cursor right", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_PREV_PAGE ) {
        strlcpy( msg_cmd, "scroll up(page)", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_NEXT_PAGE ) {
        strlcpy( msg_cmd, "scroll down(page)", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_PREV_HALF ) {
        strlcpy( msg_cmd, "scroll up(half-page)", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_NEXT_HALF ) {
        strlcpy( msg_cmd, "scroll down(half-page)", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_TAIL ) {
        strlcpy( msg_cmd, "move to end of file", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_CPOS_MOVE ) {
        strlcpy( msg_cmd, "move to cursor area", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_CPOS_MOV2 ) {
        strlcpy( msg_cmd, "move to cursor area", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_REPEAT ) {
        strlcpy( msg_cmd, "repeat", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_INPUT ) {
        strlcpy( msg_cmd, "data insert", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_TOP_INPUT ) {
        strlcpy( msg_cmd, "data insert to top of file", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_ADD ) {
        strlcpy( msg_cmd, "data append", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_LAST_ADD ) {
        strlcpy( msg_cmd, "data append to end of file", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_REPLACE_1 ) {
        strlcpy( msg_cmd, "data replace only 1byte", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_REPLACE_2 ) {
        strlcpy( msg_cmd, "data replace more 1byte", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_DELETE ) {
        strlcpy( msg_cmd, "data delete", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_REFRESH ) {
        strlcpy( msg_cmd, "refresh", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_REPORT ) {
        strlcpy( msg_cmd, "report", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_SEARCH ) {
        strlcpy( msg_cmd, "search", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_NEXT ) {
        strlcpy( msg_cmd, "research", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_REVERSE ) {
        strlcpy( msg_cmd, "reverse research", sizeof( msg_cmd ) ) ;
    }
    else if ( ifa->cmd == CMD_CNTRL ) {
        strlcpy( msg_cmd, "control command", sizeof( msg_cmd ) ) ;
    }
    else {
        strlcpy( msg_cmd, "<null>", sizeof( msg_cmd ) ) ;
    }

    if ( ifa->before_cmd == CMD_DELETE ) {
        strlcpy( msg_before_cmd, "data delete", sizeof( msg_before_cmd ) ) ;
    }
    else {
        strlcpy( msg_before_cmd, "<null>", sizeof( msg_before_cmd ) ) ;
    }

    if ( ifa->mode == MODE_CMD ) {
        strlcpy( msg_mode, "command mode", sizeof( msg_mode ) ) ;
    }
    else if ( ifa->mode == MODE_EDT ) {
        strlcpy( msg_mode, "edit mode", sizeof( msg_mode ) ) ;
    }
    else {
        strlcpy( msg_mode, "<null>", sizeof( msg_mode ) ) ;
    }

    if ( ifa->hex_pos == CUR_LEFT ) {
        strlcpy( msg_hex_pos, "left of byte", sizeof( msg_hex_pos ) ) ;
    }
    else if ( ifa->hex_pos == CUR_RIGHT ) {
        strlcpy( msg_hex_pos, "right of byte", sizeof( msg_hex_pos ) ) ;
    }
    else {
        strlcpy( msg_hex_pos, "<null>", sizeof( msg_hex_pos ) ) ;
    }

    if ( ifa->image == CREATE ) {
        strlcpy( msg_image, "create", sizeof( msg_image ) ) ;
    }
    else if ( ifa->image == ADD ) {
        strlcpy( msg_image, "append", sizeof( msg_image ) ) ;
    }
    else {
        strlcpy( msg_image, "<null>", sizeof( msg_image ) ) ;
    }

    if ( ifa->reverse == REVERSE ) {
        strlcpy( msg_reverse, "reverse", sizeof( msg_reverse ) ) ;
    }
    else if ( ifa->reverse == NOT_REVERSE ) {
        strlcpy( msg_reverse, "not reverse", sizeof( msg_reverse ) ) ;
    }
    else {
        strlcpy( msg_reverse, "<null>", sizeof( msg_reverse ) ) ;
    }

    if ( ifa->search == NEXT_SEARCH ) {
        strlcpy( msg_search, "next search", sizeof( msg_search ) ) ;
    }
    else if ( ifa->search == PREV_SEARCH ) {
        strlcpy( msg_search, "prev search", sizeof( msg_search ) ) ;
    }
    else {
        strlcpy( msg_search, "<null>", sizeof( msg_search ) ) ;
    }

/* ------------------------------------------------------------------ */
/* ư��Ķ���������ꤹ�롣                                           */
/* ------------------------------------------------------------------ */
    env[0].stand = '1' ;
    snprintf( env [0].env_msg, sizeof( env [0].env_msg ), 
              " <<< Global information >>> " ) ;
    snprintf( env [1].env_msg, sizeof( env [1].env_msg ),
              "entry                   : %d", ifa->entry ) ;
    snprintf( env [2].env_msg, sizeof( env [2].env_msg ),
              "total entry             : %d", ifa->maxent ) ;
    snprintf( env [3].env_msg, sizeof( env [3].env_msg ),
              "status                  : %s", msg_status ) ;
    snprintf( env [4].env_msg, sizeof( env [4].env_msg ),
              "end status              : %s", msg_endflg ) ;
    snprintf( env [5].env_msg, sizeof( env [5].env_msg ),
              "curses status           : %s", msg_curses ) ;
    snprintf( env [6].env_msg, sizeof( env [6].env_msg ),
              "kind                    : %s", msg_option ) ;
    snprintf( env [7].env_msg, sizeof( env [7].env_msg ),
              "modification            : %s", msg_modif ) ;
    snprintf( env [8].env_msg, sizeof( env [8].env_msg ),
              "language                : %s", msg_lang ) ;
    snprintf( env [9].env_msg, 255, 
              "filename                : %s", ifa->file ) ;
    snprintf( env[10].env_msg, sizeof( env [10].env_msg ),
              "shared memory ID        : %s", msg_shmid ) ;
    snprintf( env[11].env_msg, sizeof( env [11].env_msg ),
              "file exist              : %s", msg_exist ) ;
    snprintf( env[12].env_msg, sizeof( env [12].env_msg ),
              "image write file        : %s", msg_image ) ;
    snprintf( env[13].env_msg, sizeof( env [13].env_msg ),
              "command                 : %s", msg_cmd ) ;
    snprintf( env[14].env_msg, sizeof( env [14].env_msg ),
              "prev command            : %s", msg_before_cmd ) ;
    snprintf( env[15].env_msg, sizeof( env [15].env_msg ),
              "mode                    : %s", msg_mode ) ;
    snprintf( env[16].env_msg, sizeof( env [16].env_msg ),
              "mode message            : %s", ifa->mode_msg ) ;
    snprintf( env[17].env_msg, sizeof( env [17].env_msg ),
              "reverse                 : %s", msg_reverse ) ;
    snprintf( env[18].env_msg, sizeof( env [18].env_msg ),
              "view offset             : %d", ifa->view_offset ) ;
    snprintf( env[19].env_msg, sizeof( env [19].env_msg ),
              "data offset             : %d", ifa->data_offset ) ;

    env[21].stand = '1' ;
    snprintf( env[21].env_msg, sizeof( env [21].env_msg ),
              " <<< Area information >>> " ) ;
    snprintf( env[22].env_msg, sizeof( env [22].env_msg ),
              "data size               : %d", ifa->size ) ;
    snprintf( env[23].env_msg, sizeof( env [23].env_msg ),
              "area size               : %d", ifa->area_size ) ;
    snprintf( env[24].env_msg, sizeof( env [24].env_msg ),
              "append area size        : %d", ifa->alloc_size ) ;
    snprintf( env[25].env_msg, sizeof( env [25].env_msg ),
              "max area size           : %d", ifa->max_size ) ;

    env[27].stand = '1' ;
    snprintf( env[27].env_msg, sizeof( env [27].env_msg ),
              " <<< Window information >>> " ) ;
    snprintf( env[28].env_msg, sizeof( env [28].env_msg ),
              "columns                 : %d", ifa->columns ) ;
    snprintf( env[29].env_msg, sizeof( env [29].env_msg ),
              "lines                   : %d", ifa->lines ) ;
    snprintf( env[30].env_msg, sizeof( env [30].env_msg ),
              "VT language             : %s", msg_term_lang ) ;

    env[32].stand = '1' ;
    snprintf( env[32].env_msg, sizeof( env [32].env_msg ),
              " <<< Position information >>> " ) ;
    snprintf( env[33].env_msg, sizeof( env [33].env_msg ),
              "area position           : %s", msg_target ) ;
    snprintf( env[34].env_msg, sizeof( env [34].env_msg ),
              "cursor position         : %s", msg_hex_pos ) ;
    snprintf( env[35].env_msg, sizeof( env [35].env_msg ),
              "cursor position(X)      : %d", ifa->cur_pos_x ) ;
    snprintf( env[36].env_msg, sizeof( env [36].env_msg ),
              "cursor position(Y)      : %d", ifa->cur_pos_y ) ;
    snprintf( env[37].env_msg, sizeof( env [37].env_msg ),
              "command position(X)     : %d", ifa->cur_cmd_x ) ;
    snprintf( env[38].env_msg, sizeof( env [38].env_msg ),
              "command position(Y)     : %d", ifa->cur_cmd_y ) ;
    snprintf( env[39].env_msg, sizeof( env [39].env_msg ),
              "information position(X) : %d", ifa->inf_msg_x ) ;
    snprintf( env[40].env_msg, sizeof( env [40].env_msg ),
              "information position(Y) : %d", ifa->inf_msg_y ) ;
    snprintf( env[41].env_msg, sizeof( env [41].env_msg ),
              "error position(X)       : %d", ifa->err_msg_x ) ;
    snprintf( env[42].env_msg, sizeof( env [42].env_msg ),
              "error position(Y)       : %d", ifa->err_msg_y ) ;

    env[44].stand = '1' ;
    snprintf( env[44].env_msg, sizeof( env [44].env_msg ),
              " <<< Any message information >>> " ) ;
    snprintf( env[45].env_msg, sizeof( env [45].env_msg ),
              "command string          : %s", ifa->cmd_str ) ;
    snprintf( env[46].env_msg, sizeof( env [46].env_msg ),
              "size of command string  : %d", ifa->cmd_size ) ;
    snprintf( env[47].env_msg, sizeof( env [47].env_msg ),
              "search command          : %s", ifa->search_str ) ;
    snprintf( env[48].env_msg, sizeof( env [48].env_msg ),
              "size of search command  : %d", ifa->search_size ) ;
    snprintf( env[49].env_msg, sizeof( env [49].env_msg ),
              "search next or prev     : %s", msg_search ) ;
    snprintf( env[50].env_msg, 255, 
              "information message     : %s", ifa->inf_msg ) ;
    snprintf( env[51].env_msg, 255, 
              "system error message    : %s", ifa->perr_msg ) ;

    env[53].stand = '1' ;
    snprintf( env[53].env_msg, sizeof( env [53].env_msg ),
              " <<< Stack trace information >>> " ) ;
    snprintf( env[54].env_msg, sizeof( env [54].env_msg ),
              "trace depth             : %d", ifa->func_dep ) ;
    for ( cnt = 0 ; cnt < 16 ; cnt ++ ) {
        if ( cnt < ifa->func_dep ) {
            snprintf( env[55+cnt].env_msg, sizeof( env [55+cnt].env_msg ),
                      "trace[%2d]               : %s",
                     cnt, ifa->func_trace[cnt] ) ;
        }
        else {
            snprintf( env[55+cnt].env_msg, sizeof( env [55+cnt].env_msg ),
                      "trace[%2d]               : <null>", cnt ) ;
        }
    }

    env[72].stand = '1' ;
    snprintf( env[72].env_msg, sizeof( env [72].env_msg ),
              " <<< Error information >>> " ) ;
    snprintf( env[73].env_msg, 255, 
              "error message           : %s", ifa->err_msg ) ;
    snprintf( env[74].env_msg, 255, 
              "error function          : %s", ifa->err_func ) ;
    snprintf( env[75].env_msg, 255, 
              "error line              : %s", ifa->err_line ) ;

    env[77].stand = '1' ;
    snprintf( env[77].env_msg, sizeof( env [77].env_msg ),
              " <<< Help information >>> " ) ;
    snprintf( env[78].env_msg, 255, 
              "help file path          : %s", HELP_PATH ) ;
    snprintf( env[79].env_msg, 255, 
              "help file               : %s", msg_helpfile ) ;
    snprintf( env[80].env_msg, 255, 
              "line of help file       : %d", ifa->help_line ) ;

/* ------------------------------------------------------------------ */
/* ư��Ķ����ϼ¹Խ���                                               */
/* ------------------------------------------------------------------ */
    while ( end_flg != 1 ) {            /* ��λ�ؼ��ޤǥ롼��         */

        clear() ;                       /* ������ɥ��Υ��ꥢ         */

/* ------------------------------------------------------------------ */
/* �إå�����ɽ��                                                     */
/* ------------------------------------------------------------------ */
        standout() ;                    /* ��Ĵ�⡼�ɳ���             */
        move( hed1_pos_y, hed1_pos_x ) ;/* �إå�1���֤ˡ����������ư*/
        printw( "%s", head_str ) ;      /* �إå�1ɽ��                */
        standend() ;                    /* ��Ĵ�⡼�ɽ�λ             */
        move( hed2_pos_y, hed2_pos_x ) ;/* �إå�2���֤ˡ����������ư*/
        printw( "[ %2d / %2d ] page", (page+1), (last_page+1) ) ;
                                        /* �إå�ɽ��                 */
        for ( cnt = 0 ; cnt < ifa->columns ; cnt++ ) {
                                        /* ���ʬ�Υ롼��             */
            mvaddch( ( hed1_pos_y + 1 ) , cnt, '-' ) ;
                                        /* ��ʿ��������               */
        }                               /* end for                    */

/* ------------------------------------------------------------------ */
/* ư��Ķ������ɽ��                                                 */
/* ------------------------------------------------------------------ */
        for ( line_cnt = top[page], cnt = 0, pos_y = 2 ;
              cnt < ( ifa->lines - 4 ) ;
              cnt++, pos_y++, line_cnt++ ) {
                                        /* ư��Ķ������ɽ��         */
            if ( line_cnt >= ENV_LINE ) {
                                        /* ư��Ķ�����κǸ�         */
                break ;                 /* break for                  */
            }                           /* end if                     */
            move( pos_y, pos_x ) ;      /* ��������ΰ�ư             */
            if ( env[line_cnt].stand == '1' ) {
                                        /* ��Ĵ�⡼�ɻ���             */
                standout() ;            /* ��Ĵ�⡼�ɳ���             */
                printw( "%s", env[line_cnt].env_msg ) ;
                                        /* �оݹԤ�ɽ��               */
                standend() ;            /* ��Ĵ�⡼�ɽ�λ             */
            }                           /* end if                     */
            else {                      /* ��Ĵ�⡼��̤����           */
                printw( "%s", env[line_cnt].env_msg ) ;
                                        /* �оݹԤ�ɽ��               */
            }                           /* end else                   */
        }                               /* end for                    */

/* ------------------------------------------------------------------ */
/* ����ե��᡼���������ɽ��                                       */
/* ------------------------------------------------------------------ */
        for ( cnt = 0 ; cnt < ifa->columns ; cnt++ ) {
                                        /* ���ʬ�Υ롼��             */
            mvaddch( ( inf_pos_y - 1 ) , cnt, '-' ) ;
        }                               /* end for                    */
        mvaddstr( inf_pos_y, inf_pos_x, ENV_INFO ) ;
                                        /* ����ե��᡼�����ɽ��     */
        refresh() ;                     /* ������ɥ��κ�����         */

/* ------------------------------------------------------------------ */
/* ���ޥ�ɼ��դ�Ƚ��                                                 */
/* ------------------------------------------------------------------ */
        check_flg = 0 ;                 /* �����å��ե饰�ν����     */
        while ( check_flg != 1 ) {      /* �����å�OK�ޤǥ롼��       */
            switch ( getch() ) {        /* ���ޥ�ɤμ����ȿ���ʬ��   */
                case ENV_CMD_NEXT :     /* ���ڡ���ɽ��               */
                case ENV_CMD_NEXT2 :    /* ' '                        */
                    if ( page < last_page ) {
                                        /* ���ڡ���ͭ��               */
                        page++ ;        /* �оݥڡ����ι���           */
                        check_flg = 1 ; /* �����å�OK                 */
                    }                   /* end if                     */
                    break ;             /* break switch               */

                case ENV_CMD_PREV :     /* ���ڡ���ɽ��               */
                case ENV_CMD_PREV2 :    /* B                          */
                    if ( page > 0 ) {   /* ���ڡ���ͭ��               */
                        page-- ;        /* �оݥڡ����ι���           */
                        check_flg = 1 ; /* �����å�OK                 */
                    }                   /* end if                     */
                    break ;             /* break switch               */

                case ENV_CMD_WRITE :    /* ư��Ķ�����               */
                    fp = fopen( ENV_OUT_FILE, "wb+" ) ;
                                        /* ���ϥե����륪���ץ�       */
                    if ( fp != NULL ) { /* �ե����륪���ץ�����       */
                        for ( cnt = 0 ; cnt < ENV_LINE ; cnt ++ ) {
                            fprintf( fp, "%s\n", env[cnt].env_msg ) ;
                                        /* �оݥڡ�������Ƭ�Ԥν���� */
                        }               /* end if                     */
                        fclose( fp ) ;  /* ���ϥե����륯����       */
                        snprintf( ifa->inf_msg, sizeof( ifa->inf_msg ),
                                  "\"%s\" wrote. ", ENV_OUT_FILE ) ;
                                        /* ����ե��᡼���������     */
                        inf_msg( ifa ) ;/* ����ե��᡼�����ɽ������ */
                    }                   /* end if                     */
                    else {              /* �ե����륪���ץ���       */
                        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                                  "fopen[%s] error : errno = %d, ",
                                  ENV_OUT_FILE, errno ) ;
                        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                                  "fopen[%s]", ENV_OUT_FILE ) ;
                                        /* ���顼��å���������       */
                        ERRINFO_SET( ifa ) ;
                                        /* �㳲����ܺ�����           */
                        err_msg( ifa ) ;/* ���顼��å�����ɽ��       */
                    }                   /* end else                   */
                    mvaddstr( inf_pos_y, 25,
                              "please hit return-key to continue..." ) ;
                    refresh() ;         /* ������ɥ��κ�����         */
                    getchar() ;         /* �������ϼ���               */
                    check_flg = 1 ;     /* �����å�OK                 */
                    break ;             /* break switch               */

                case ENV_CMD_QUIT :     /* ư��Ķ�ɽ����λ           */
                    end_flg = 1 ;       /* ��λ�ե饰�ι���           */
                    check_flg = 1 ;     /* �����å�OK                 */
                    break ;             /* break switch               */

                default :               /* ���ϥ��ޥ������           */
                    break ;             /* break switch               */
            }                           /* end switch                 */
        }                               /* end while                  */
    }                                   /* end while                  */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - env_output        */
}                                       /* end (env_output)           */

/**********************************************************************/
