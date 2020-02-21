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
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>
#include    <hi_std.h>

/**********************************************************************/
/*  ����ե����������ؿ� - file_insert                                */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   �ե�������ɤ߹��ߡ������Ȥ��������롣                         */
/**********************************************************************/
vd  file_insert( struct ifa_s *ifa )    /* ����ե����������ؿ�       */
{
    FILE        *fpin     ;             /* ���ϥե�����               */
    li           ret      ;             /* �꥿���󥳡���(����)       */
    li           alloc    ;             /* ���ݥ�����(malloc��)       */
    ch          *sep      ;             /* ���ѥ졼��                 */
    ch           file[64] ;             /* ���ϥե�����̾��           */
                                        /* cmd_str ����ʤΤ� 64 ʸ�� */
    ch          *work_tmp ;             /* �������ΰ�               */
    struct stat  st       ;             /* �ե����륹�ơ�����         */

    trace_start( ifa, "file_insert" ) ; /* �ȥ졼������               */
/* ------------------------------------------------------------------ */
/* �ե�����̾�Τμ���                                                 */
/* ------------------------------------------------------------------ */
    sep = strchr( ifa->cmd_str,' ' ) ;  /* ���ѥ졼�����֤μ���       */
    strlcpy( file, ( sep + 1 ), sizeof( file ) ) ;
                                        /* ���ꤵ�줿�ե�����̾�μ��� */
    hi_regex( ifa, ( sep + 1 ), (ul *)file, sizeof( file ) ) ;
                                        /* ����ɽ���β���             */
    if ( file == NULL ) {               /* ����ɽ���β�������         */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե����륹�ơ������μ���                                           */
/* ------------------------------------------------------------------ */
    ret = stat( file, &st ) ;           /* �ե����륹�ơ���������     */
    if ( ret != 0 ) {                   /* �ե����뤬¸�ߤ���         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "\"%s\": No such file or directory.", file ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "stat[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

    if ( st.st_size == 0 ) {            /* �ե����륵������0�Х���    */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "\"%s\" is 0 byte file.", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ����ΰ�κƳ���                                                   */
/* ------------------------------------------------------------------ */
    ifa->area_size += ( st.st_size + ( 16 - ( st.st_size % 16 ) ) ) ;
                                        /* ����ΰ�κƷ׻�(����Ĵ��) */
    if ( ifa->area_size >= ifa->max_size ) {
                                        /* ���祵��������ã����       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "workarea size is greater than max size" ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

    ifa->workarea = (ch *)realloc( ifa->workarea, ifa->area_size ) ;
                                        /* ����ΰ�γ���             */
    if ( ifa->workarea == NULL ) {      /* ����ΰ�γ��ݼ���         */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "realloc error : errno = %d", errno ) ;
                                        /* ���顼��å���������       */
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "realloc" ) ;
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �������ΰ�γ���                                                 */
/* ------------------------------------------------------------------ */
    alloc = ifa->size - ifa->data_offset + 1 +
            ( 16 - ( (ifa->size - ifa->data_offset + 1) % 16 ) ) ;
                                        /* ���ݥ������η׻�(����Ĵ��) */
    work_tmp = (ch *)malloc( alloc ) ;  /* �������ΰ�γ���         */
    if ( work_tmp == NULL ) {           /* �������ΰ�γ��ݼ���     */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                  "malloc error : errno = %d", errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "malloc" ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե�����Υ����ץ�                                                 */
/* ------------------------------------------------------------------ */
    fpin = fopen( file, "rb" ) ;        /* �ե����륪���ץ�           */
    if ( fpin == NULL ) {               /* �ե����륪���ץ���       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fopen[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fopen[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        free( work_tmp ) ;              /* �������ΰ�β���         */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե�����ݥ��󥿤���Ƭ�˰�ư                                       */
/* ------------------------------------------------------------------ */
    ret = fseek( fpin, 0L, SEEK_SET ) ; /* �ե�����ݥ��󥿤���Ƭ��   */
                                        /* ��ư����                   */
    if ( ret != 0 ) {                   /* �ե�����ݥ��󥿤ΰ�ư���� */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fseek[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fseek[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        free( work_tmp ) ;              /* �������ΰ�β���         */
        fclose( fpin ) ;                /* �ե����륯����           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ��������ʹߤΥǡ�������                                           */
/* ------------------------------------------------------------------ */
    memcpy( work_tmp, &ifa->workarea[(ifa->data_offset-1)],
            (ifa->size - ifa->data_offset + 1) ) ;
                                        /* ��������ʹߤΥǡ�������   */
/* ------------------------------------------------------------------ */
/* �ե�������ɤ߹���                                                 */
/* ------------------------------------------------------------------ */
    ret = fread( &ifa->workarea[(ifa->data_offset-1)],
                 st.st_size, 1, fpin) ; /* �ե�������ɤ߹���         */
    if ( ret != 1 ) {                   /* �ե������ɤ߹��߼���       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fread[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fread[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
        free( work_tmp ) ;              /* �������ΰ�β���         */
        fclose( fpin ) ;                /* �ե����륯����           */
        trace_end( ifa ) ;              /* �ȥ졼������               */
        return ;                        /* return - file_insert       */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* ���򤷤��ǡ���������                                               */
/* ------------------------------------------------------------------ */
    memcpy( &ifa->workarea[(ifa->data_offset-1+st.st_size)],
            work_tmp, (ifa->size - ifa->data_offset + 1) ) ;
                                        /* ���򤷤��ǡ���������       */
/* ------------------------------------------------------------------ */
/* �ؿ��θ����                                                       */
/* ------------------------------------------------------------------ */
    ifa->size += st.st_size ;           /* �ǡ������������ɲ�         */
    data_view( ifa ) ;                  /* �ǡ���ɽ���ؿ�             */

    ifa->modif = MOD_ON ;               /* ������������Ф���         */
    snprintf( ifa->inf_msg, sizeof( ifa->inf_msg ),
              "\"%s\" inserted file %d characters",
              file, (li)st.st_size ) ;  /* ����ե��᡼���������     */
    inf_msg( ifa ) ;                    /* ����ե��᡼�����ɽ��     */

    free( work_tmp ) ;                  /* �������ΰ�β���         */
    fclose( fpin ) ;                    /* �ե����륯����           */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - file_insert       */
}                                       /* end (file_insert)          */

/**********************************************************************/
