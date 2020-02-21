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
#include    <sys/stat.h>
#include    <hi_std.h>

/**********************************************************************/
/*  �ե�����񤭹��ߴؿ� - file_write                                 */
/* ------------------------------------------------------------------ */
/* �ؿ�����                                                           */
/*   ����ΰ�ξ��֤򡢥ե�����˽��Ϥ��롣                           */
/**********************************************************************/
vd  file_write( struct ifa_s *ifa )     /* �ե�����񤭹��ߴؿ�       */
{
    FILE        *fpout    ;             /* ���ϥե�����               */
    li           ret      ;             /* �꥿���󥳡���(����)       */
    ch file[256];                       /* �ե�����̾                 */

    trace_start( ifa, "file_write" ) ;  /* �ȥ졼������               */
    strlcpy(file, ifa->file, sizeof( file ) );
    if(strlen(file) > 64){
        snprintf( file, sizeof( file ) , "%s...", file);
    }
/* ------------------------------------------------------------------ */
/* �ե�����Υ����ץ�                                                 */
/* ------------------------------------------------------------------ */
    fpout = fopen(ifa->file, "wb+") ;   /* �ե����륪���ץ�           */
    if ( fpout == NULL ) {              /* �ե����륪���ץ���       */
        snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                  "fopen[%s] error : errno = %d", file, errno ) ;
        snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "fopen[%s]", file ) ;
                                        /* ���顼��å���������       */
        ERRINFO_SET( ifa ) ;            /* �㳲����ܺ�����           */
        err_msg( ifa ) ;                /* ���顼��å�����ɽ��       */
    }                                   /* end if                     */
    else {                              /* �ե����륪���ץ�����       */

/* ------------------------------------------------------------------ */
/* ����ΰ�ξ��֤򡢥ե�����˽񤭹���                               */
/* ------------------------------------------------------------------ */
        if ( ifa->size != 0 ) {         /* �оݥǡ�����¸�ߤ���       */
            ret = fwrite(ifa->workarea, ifa->size, 1, fpout) ;
                                        /* �ե�����ؽ񤭹���         */
            if ( ret != 1 ) {           /* �ե������ɤ߹��߼���       */
                snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                          "fwrite[%s] error : errno = %d", file, errno ) ;
                snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ),
                          "fwrite[%s]", file ) ;
                                        /* ���顼��å���������       */
                ERRINFO_SET( ifa ) ;    /* �㳲����ܺ�����           */
                err_msg( ifa ) ;        /* ���顼��å�����ɽ��       */
            }                           /* end if                     */
            snprintf(ifa->inf_msg, sizeof( ifa->inf_msg ),
                  "\"%s\" wrote %d characters", file, ifa->size) ;
                                        /* ����ե��᡼���������     */
            inf_msg( ifa ) ;            /* ����ե��᡼�����ɽ��     */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* �ե�����Υ�������                                                 */
/* ------------------------------------------------------------------ */
        fclose( fpout ) ;               /* �ե����륯������           */

        ifa->modif = MOD_OFF ;          /* ����̵ͭ�ν����           */
    }                                   /* end else                   */

    trace_end( ifa ) ;                  /* �ȥ졼������               */
    return ;                            /* return - file_write        */
}                                       /* end (file_write)           */

/**********************************************************************/