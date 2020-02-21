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
#include    <string.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ���楳�ޥ�ɼ¹Դؿ� - exec_get_cmd                               */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ���楳�ޥ�ɤ�¹Ԥ��롣                                         */
/**********************************************************************/
vd  exec_get_cmd( struct ifa_s *ifa )   /* ���楳�ޥ�ɴؿ�           */
{

    trace_start( ifa, "exec_get_cmd" ) ;/* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* ���楳�ޥ�ɼ¹Խ���                                               */
/* ------------------------------------------------------------------ */
    /* -------------------------------------------------------------- */
    /* ��λ                                                           */
    /* -------------------------------------------------------------- */
    if ( strcmp(ifa->cmd_str, CNTL_CMD_QUIT1) == 0 ) {
                                        /* ��λ(q)                    */
        if ( ifa->entry >= ifa->maxent ) {
                                        /* �ǽ��ե�����               */
            if ( ifa->modif == MOD_OFF ) {
                                        /* �������Ƥ��ʤ�             */
                ifa->endflg = N_END ;   /* ��λ�ؼ�                   */
            }                           /* end if                     */
            else {                      /* �������Ƥ���               */
                if ( ifa->option == FIL ) {
                                        /* ����оݤ����ե�����       */
                    strlcpy( ifa->err_msg,
                             "File modified since last complete write.",
                             sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                    ERRINFO_SET( ifa ) ;/* �㳲����ܺ�����           */
                    err_msg( ifa ) ;    /* ���顼��å�����ɽ��       */
                }                       /* end if                     */
                else {                  /* ����оݤ�����ͭ����     */
                    ifa->endflg = N_END ;
                                        /* ��λ�ؼ�                   */
                }                       /* end else                   */
            }                           /* end if                     */
        }                               /* end else                   */
        else {                          /* �ޤ����ե����뤬¸�ߤ���   */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "%d more files to edit.",
                      (ifa->maxent - ifa->entry) ) ;
                                        /* ���顼��å���������       */
                    ERRINFO_SET( ifa ) ;/* �㳲����ܺ�����           */
                    err_msg( ifa ) ;    /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
    }                                   /* end if                     */

    /* -------------------------------------------------------------- */
    /* ������λ                                                       */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_QUIT2) == 0 ) {
                                        /* ������λ(q!)               */
        ifa->endflg = D_END ;           /* ������λ�ؼ�               */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* �񤭹��߽�λ                                                   */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_WQ) == 0 ) {
                                        /* �񤭹��߽�λ(wq)           */
        if ( ifa->entry == ifa->maxent ) {
                                        /* �ǽ��ե�����               */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                file_write( ifa ) ;     /* �ե�����񤭹��ߴؿ�       */
                ifa->endflg = N_END ;   /* ��λ�ؼ�                   */
            }                           /* end if                     */
            else {                      /* ����оݤ�����ͭ����     */
                strlcpy( ifa->err_msg, "Shared memory is direct access.",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
        }                               /* end else                   */
        else {                          /* �ޤ����ե����뤬¸�ߤ���   */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "%d more files to edit.",
                      (ifa->maxent - ifa->entry) ) ;
                                        /* ���顼��å���������       */
                    ERRINFO_SET( ifa ) ;/* �㳲����ܺ�����           */
                    err_msg( ifa ) ;    /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ��񤭡�������̾�ݴ�                                           */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] ==  CNTL_CMD_WRITE ) {
                                        /* ���(w)��������̾�ݴ�(w) */
        if ( ifa->cmd_size == 1 ) {     /* ���(w)                  */
            if ( ifa->option == FIL ) { /* ����оݤ����ե�����       */
                file_write( ifa ) ;     /* �ե�����񤭹��ߴؿ�       */
            }                           /* end if                     */
            else {                      /* ����оݤ�����ͭ����     */
                strlcpy( ifa->err_msg,
                         "Shared memory is direct access.",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* ��̾�ݴ�                   */
            file_create( ifa ) ;        /* �����ե���������ؿ�       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ����ե����������                                             */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] ==  CNTL_CMD_READ ) {
                                        /* �ե������ɤ߹���(r)        */
        if ( ifa->option == FIL ) {     /* ����оݤ����ե�����       */
            if ( ifa->cmd_size == 1 ) { /* �ե����ޥåȥ��顼         */
                strlcpy( ifa->err_msg, "read command error : \"%s\"",
                         sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end if                     */
            else {                      /* ����ե����������         */
                file_insert( ifa ) ;    /* ����ե����������ؿ�       */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* ����оݤ�����ͭ����     */
            strlcpy( ifa->err_msg, "Shared memory is not support",
                     sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* �оݥե������ѹ�                                               */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_CHG01) == 0 ) {
                                        /* �оݥե������ѹ�(n)        */
        if ( ifa->entry < ifa->maxent ) {
                                        /* �ޤ����ե����뤬¸�ߤ���   */
            if ( ifa->modif == MOD_OFF ) {
                                        /* �������Ƥ��ʤ�             */
                ifa->endflg = CHANGE ;  /* �Խ��о��ڤ��ؤ��ؼ�       */
            }                           /* end if                     */
            else {                      /* �������Ƥ���               */
                if ( ifa->option == FIL ) {
                                        /* ����оݤ����ե�����       */
                    strlcpy( ifa->err_msg,
                             "File modified since last complete write.",
                             sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
                    ERRINFO_SET( ifa ) ;/* �㳲����ܺ�����           */
                    err_msg( ifa ) ;    /* ���顼��å�����ɽ��       */
                }                       /* end if                     */
                else {                  /* ����оݤ�����ͭ����     */
                    ifa->endflg = CHANGE ;
                                        /* �Խ��о��ڤ��ؤ��ؼ�       */
                }                       /* end else                   */
            }                           /* end else                   */
        }                               /* end if                     */
        else {                          /* �ǽ��ե�����               */
            strlcpy( ifa->err_msg, "No more files to edit.",
                     sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
    }                                   /* end if                     */

    /* -------------------------------------------------------------- */
    /* �����оݥե������ѹ�                                           */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_CHG02) == 0 ) {
                                        /* �����оݥե������ѹ�(n!)   */
        if ( ifa->entry < ifa->maxent ) {
                                        /* �ޤ����ե����뤬¸�ߤ���   */
            ifa->endflg = CHANGE ;      /* �Խ��о��ڤ��ؤ��ؼ�       */
        }                               /* end if                     */
        else {                          /* �ǽ��ե�����               */
            strlcpy( ifa->err_msg, "No more files to edit.",
                     sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* �إ��ɽ��                                                     */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_HELP) == 0 ) {
                                        /* �إ��ɽ��                 */
        help( ifa ) ;                   /* �إ�׽���                 */
        win_refresh( ifa ) ;            /* ���̺�����ؿ�             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ư��Ķ�ɽ��                                                   */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_ENV) == 0 ) {
                                        /* ư��Ķ�ɽ��               */
        env_output( ifa ) ;             /* ư��Ķ�����               */
        win_refresh( ifa ) ;            /* ���̺�����ؿ�             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ư��Ķ�ɽ��                                                   */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_FNAME) == 0 ) {
                                        /* �ե�����̾ɽ��             */
        report_dsp( ifa ) ;             /* ����                       */
/*        win_refresh( ifa ) ;             ���̺�����ؿ�             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* �����륳�ޥ�ɼ¹�                                             */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] == CNTL_CMD_SHELL ) {
                                        /* �����륳�ޥ��             */
        exec_shell( ifa ) ;             /* �����륳�ޥ�ɼ¹Դؿ�     */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ���ɥ쥹����(��ư���ϡ�����) ���ϡ�������ꥳ�ޥ��            */
    /* -------------------------------------------------------------- */
    else if (( strncmp(ifa->cmd_str, CNTL_CMD_ADRS, 2) == 0 )||
             (( ifa->cmd_str[0] == CNTL_CMD_TOP )||
              ( ifa->cmd_str[0] == CNTL_CMD_CRNT )||
              ( ifa->cmd_str[0] == CNTL_CMD_LAST )||
              ( ifa->cmd_str[0] == CNTL_CMD_PLUS )||
              ( ifa->cmd_str[0] == CNTL_CMD_MINUS ))||
             (( ifa->cmd_str[0] >= '0' )&&( ifa->cmd_str[0] <= '9' ))) {
                                        /* ���ɥ쥹����(����ɽ��ͭ��) */
        if ( ifa->cmd_str[strlen(ifa->cmd_str)-1] == CMD_DELETE ) {
                                        /* ���ɥ쥹������           */
            area_delete( ifa ) ;        /* ���ɥ쥹������           */
        }                               /* end if                     */
        else if ( strchr( ifa->cmd_str, ((li)',') ) != NULL ) {
                                        /* ���ɥ쥹�������           */
            area_write( ifa ) ;         /* ���ɥ쥹�������           */
        }                               /* end else if                */
        else {                          /* ���ꥢ�ɥ쥹ɽ��           */
            address_view( ifa ) ;       /* ���ꥢ�ɥ쥹ɽ������       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ɽ�����ؤ�                                                     */
    /* -------------------------------------------------------------- */
    else if ( strncmp(ifa->cmd_str, CNTL_CMD_TR, 2) == 0 ) {
                                        /* ɽ�����ؤ�                 */
        tr_main( ifa ) ;                /* ��������ؿ�               */
        win_refresh( ifa ) ;            /* ���̺�����ؿ�             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ȿžɽ��                                                       */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_SR_ON) == 0 ) {
                                        /* ȿžɽ��                   */
        ifa->reverse = REVERSE ;        /* ����ʸ�����ȿžɽ������   */
        win_refresh( ifa ) ;            /* ���̺�����ؿ�             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ȿžɽ�����ʤ�                                                 */
    /* -------------------------------------------------------------- */
    else if ( strcmp(ifa->cmd_str, CNTL_CMD_SR_OF) == 0 ) {
                                        /* ȿžɽ�����ʤ�             */
        ifa->reverse = NOT_REVERSE ;    /* ����ʸ�����ȿžɽ�����ʤ� */
        win_refresh( ifa ) ;            /* ���̺�����ؿ�             */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* �ǡ����Ѵ�ɽ��                                                 */
    /* -------------------------------------------------------------- */
    else if ( strncmp(ifa->cmd_str, CNTL_CMD_PR, 2) == 0 ) {
                                        /* �ǡ����Ѵ�ɽ��(pr)         */
        if ( ifa->cmd_size == 2 ) {     /* �ǡ����Ѵ�����̤����       */
            strlcpy( ifa->err_msg, "Format error.", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end if                     */
        else {                          /* �ǡ����Ѵ�ɽ��             */
            print_conv_data( ifa ) ;    /* �ǡ����Ѵ�ɽ���ؿ�         */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ���̥��᡼���ɲý���                                           */
    /* -------------------------------------------------------------- */
    else if ( strncmp(ifa->cmd_str, CNTL_CMD_PA, 2) == 0 ) {
                                        /* ���̥��᡼���ɲý���(pa)   */
        if ( ifa->cmd_size == 2 ) {     /* �ե�����̤̾����           */
            strlcpy( ifa->err_msg, "Format error.", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end if                     */
        else {                          /* ��̾�ݴ�                   */
            ifa->image = ADD ;          /* ���̥��᡼���ɲ�           */
            image_write( ifa ) ;        /* ���̥��᡼�����ϴؿ�       */
        }                               /* end else                   */
    }                                   /* end else if                */

    /* -------------------------------------------------------------- */
    /* ���̥��᡼������                                               */
    /* -------------------------------------------------------------- */
    else if ( ifa->cmd_str[0] ==  CNTL_CMD_P ) {
                                        /* ���̥��᡼������(p)        */
        if ( ifa->cmd_size == 1 ) {     /* �ե�����̤̾����           */
            strlcpy( ifa->err_msg, "Format error.", sizeof( ifa->err_msg ) ) ;
                                        /* ���顼��å���������       */
            ERRINFO_SET( ifa ) ;        /* �㳲����ܺ�����           */
            err_msg( ifa ) ;            /* ���顼��å�����ɽ��       */
        }                               /* end if                     */
        else {                          /* ��̾�ݴ�                   */
            ifa->image = CREATE ;       /* ���̥��᡼����������       */
            image_write( ifa ) ;        /* ���̥��᡼�����ϴؿ�       */
        }                               /* end else                   */
    }                                   /* end else if                */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - exec_get_cmd      */
}                                       /* end (exec_get_cmd)         */

/**********************************************************************/
