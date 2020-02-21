/**********************************************************************/
/*  hi - バイナリエディタ                                             */
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
/* インクルードファイル                                               */
/* ================================================================== */
#include    <errno.h>
#include    <string.h>
#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/shm.h>
#include    <hi_std.h>

/**********************************************************************/
/*  共有メモリアタッチ関数 - shmem_attach                             */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   指定された共有メモリIDのセグメントにアタッチする。               */
/**********************************************************************/
vd  shmem_attach( struct ifa_s *ifa )   /* 共有メモリアタッチ関数     */
{
    li               ret ;              /* リターンコード(汎用)       */
    li               lpcnt ;            /* ループカウンタ(汎用)       */
    li               offset ;           /* オフセット値(汎用)         */
    li               shmnum ;           /* 共有メモリID数             */
    ch               w_shmid[MAX_EDIT][8] ;
                                        /* 共有メモリID(ワーク)       */
    li               shmid ;            /* 共有メモリID               */
    struct shmid_ds  buf ;              /* リターンコード(汎用)       */

    trace_start( ifa, "shmem_attach" ) ;/* トレース取得               */

/* ------------------------------------------------------------------ */
/* 指定された共有メモリセグメントIDの取り出し                         */
/* ------------------------------------------------------------------ */
    shmnum = 0 ;                        /* 共有メモリID数の初期化     */
    offset = 0 ;                        /* オフセット値の初期化       */

    for ( lpcnt = 0 ; lpcnt < strlen(ifa->shmid) ; lpcnt++ ) {
                                        /* 共有メモリID長ループ       */
        if ( ifa->shmid[lpcnt] == ',' ) {
                                        /* 共有メモリIDの区切り検知   */
            w_shmid[shmnum][offset++] = 0x00 ;
                                        /* 文字列の終端を設定         */
            shmnum++ ;                  /* 共有メモリID数の更新       */
            offset = 0 ;                /* オフセット値の初期化       */
            continue ;                  /* 次の共有メモリIDへ         */
        }                               /* end if                     */
        w_shmid[shmnum][offset++] = ifa->shmid[lpcnt] ;
                                        /* 共有メモリID(一部)の取得   */
    }                                   /* end for                    */
    w_shmid[shmnum][offset++] = 0x00 ;  /* 文字列の終端を設定         */
    shmnum++ ;                          /* 共有メモリID数の更新       */

/* ------------------------------------------------------------------ */
/* 指定された共有メモリセグメントのアタッチ                           */
/* ------------------------------------------------------------------ */
    for ( lpcnt = 0 ; lpcnt < shmnum ; lpcnt++ ) {
                                        /* 共有メモリID数ループ       */
        CHAR_TO_DEC(shmid, w_shmid[lpcnt], strlen(w_shmid[lpcnt])) ;
                                        /* 共有メモリID設定           */
        ifa->workarea = (uc *)shmat( shmid, (vd *)0, 0 ) ;
                                        /* 共有メモリアタッチ         */
        if ( ifa->workarea == ((ch *)(-1)) ) {
                                        /* 共有メモリのアタッチ失敗   */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ),
                      "shmat error : errno = %d", errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "shmat" ) ;
                                        /* エラーメッセージ設定       */
            ifa->endflg = ABORT ;       /* 強制終了指示               */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* 共有メモリ情報の取得                                               */
/* ------------------------------------------------------------------ */
        ret = shmctl( shmid, IPC_STAT, &buf ) ;
                                        /* 共有メモリ情報取得         */
        if ( ret != 0 ) {               /* 共有メモリ情報取得失敗     */
            snprintf( ifa->err_msg, sizeof( ifa->err_msg ), 
                      "shmctl error : errno = %d", errno ) ;
            snprintf( ifa->perr_msg, sizeof( ifa->perr_msg ), "shmctl" ) ;
                                        /* エラーメッセージ設定       */
            ifa->endflg = ABORT ;       /* 強制終了指示               */
            ERRINFO_SET( ifa ) ;        /* 障害情報詳細設定           */
            err_msg( ifa ) ;            /* エラーメッセージ表示       */
        }                               /* end if                     */

/* ------------------------------------------------------------------ */
/* サイズの設定                                                       */
/* ------------------------------------------------------------------ */
        ifa->size += buf.shm_segsz ;    /* データサイズの設定         */
        ifa->area_size += buf.shm_segsz ;
                                        /* 作業領域サイズの設定       */
    }                                   /* end for                    */

    trace_end( ifa ) ;                  /* トレース取得               */
    return ;                            /* return - shmem_attach      */
}                                       /* end (shmem_attach)         */

/**********************************************************************/
