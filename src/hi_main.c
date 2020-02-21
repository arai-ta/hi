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
#include    <string.h>
#include    <stdlib.h>
#include    <signal.h>
#include    <hi_std.h>

struct ifa_s  *ext_ifa[MAX_EDIT] ;      /* インターフェースエリア     */
li             ext_entry ;              /* エントリ番号               */

/**********************************************************************/
/*  バイナリエディタメイン - main                                     */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   カーサスを使用する為の準備を行い、バイナリエディタを起動する。   */
/*   終了時、カーサスの終了処理を行う。                               */
/**********************************************************************/
li  main( li argc, ch **argv )          /* メイン関数                 */
{
    extern ch    *optarg        ;       /*                            */
    li            Arg           ;       /*                            */
    li            lpcnt         ;       /* ループカウンタ             */
    li            optcnt        ;       /* オプションカウンタ         */
    li            option_index  ;       /* オプションインデックス     */
    struct ifa_s  ifa[MAX_EDIT] ;       /* インターフェースエリア     */
    struct option long_option[4];       /* オプション                 */

/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    memset( ifa, 0, sizeof(ifa) ) ;     /* インターフェースエリアの   */
                                        /* 初期化                     */
    for ( lpcnt = 0 ; lpcnt < MAX_EDIT ; lpcnt++ ) {
                                        /* 配列数ループ               */
        ext_ifa[lpcnt] = &ifa[lpcnt] ;  /* 外部変数にアドレス設定     */
        ifa[lpcnt].status      = NON_SERVICE ;
                                        /* 状態フラグの初期化         */
        ifa[lpcnt].endflg      = CONTINUE ;
                                        /* 終了フラグの初期化         */
        ifa[lpcnt].envout      = ENVOUT ;
                                        /* 動作環境表示フラグの初期化 */
        ifa[lpcnt].curses      = NOT_INIT ;
                                        /* カーサスフラグの初期化     */
        ifa[lpcnt].option      = FIL ;  /* 操作対象(デフォルト)設定   */
        ifa[lpcnt].view_offset = 0 ;    /* 表示オフセット値の初期化   */
        ifa[lpcnt].data_offset = 1 ;    /* データオフセット値の初期化 */
        ifa[lpcnt].hex_pos     = CUR_LEFT ;
                                        /* カーソル位置の初期化       */
        ifa[lpcnt].modif       = MOD_OFF ;
                                        /* 修正有無の初期化           */
        ifa[lpcnt].target      = HEX_DATA ;
                                        /* 修正対象の初期化           */
        ifa[lpcnt].lang        = LANG_ASCII ;
                                        /* 言語の初期化               */
        ifa[lpcnt].reverse     = REVERSE ;
                                        /* 検索文字列反転種別の初期化 */
        ifa[lpcnt].alloc_size  = ALLOC_SIZE ;
                                        /* 追加作業領域サイズ         */
        ifa[lpcnt].max_size    = MAX_SIZE ;
                                        /* 最大作業領域サイズ         */
        ifa[lpcnt].func_dep    = 0 ;    /* 関数トレースの深さの初期化 */
    }                                   /* end for                    */

/* ------------------------------------------------------------------ */
/* シグナル登録                                                       */
/* ------------------------------------------------------------------ */
    signal( SIGBUS,  (void *)hi_signal ) ;
                                        /* シグナル受信関数           */
    signal( SIGSEGV, (void *)hi_signal ) ;
                                        /* シグナル受信関数           */
/* ------------------------------------------------------------------ */
/* オプション定義                                                     */
/* ------------------------------------------------------------------ */
    option_index = 0 ;                  /* オプションインデックス設定 */
    long_option[0].name    = "version" ;/* オプション名の設定         */
    long_option[0].has_arg = 0 ;        /* 引数を取らない             */
    long_option[0].flag    = 0 ;        /* 返り値として'v'を返す      */
    long_option[0].val     = 'v' ;      /* 返り値                     */

    long_option[1].name    = "m" ;      /* オプション名の設定         */
    long_option[1].has_arg = 1 ;        /* 引数を取る                 */
    long_option[1].flag    = 0 ;        /* 返り値として'm'を返す      */
    long_option[1].val     = 'm' ;      /* 返り値                     */

    long_option[2].name    = "help" ;   /* オプション名の設定         */
    long_option[2].has_arg = 0 ;        /* 引数を取らない             */
    long_option[2].flag    = 0 ;        /* 返り値として'h'を返す      */
    long_option[2].val     = 'h' ;      /* 返り値                     */

    long_option[3].name    = 0 ;        /* ストッパ                   */
    long_option[3].has_arg = 0 ;        /* ストッパ                   */
    long_option[3].flag    = 0 ;        /* ストッパ                   */
    long_option[3].val     = 0 ;        /* ストッパ                   */

/* ------------------------------------------------------------------ */
/* 引数チェック                                                       */
/* ------------------------------------------------------------------ */
    optcnt = 0 ;                        /* オプションカウンタの初期化 */
    while( ( Arg = getopt_long(argc, argv, "m:h:v",
                               long_option, &option_index)) != EOF ) {
                                        /* 引数チェック               */
        switch ( Arg ) {                /* 各引数判定                 */

/* ------------------------------------------------------------------ */
/* 操作対象指示                                                       */
/* ------------------------------------------------------------------ */
            case 'm' :                  /* 操作対象指示               */
                ifa[optcnt].option = SHM ;
                                        /* 操作対象:共有メモリ        */
                strlcpy( ifa[optcnt].shmid, optarg,
                         sizeof( ifa[optcnt].shmid ) ) ;
                                        /* 共有メモリID設定           */
                optcnt++ ;              /* オプションカウンタの更新   */
                break ;                 /* break switch               */

/* ------------------------------------------------------------------ */
/* ヘルプ表示指示                                                     */
/* ------------------------------------------------------------------ */
            case 'h' :                  /* ヘルプ表示指示             */
                hi_init( &ifa[0] ) ;    /* 初期設定関数               */
                help( &ifa[0] ) ;       /* ヘルプ関数                 */
                move(ifa[0].inf_msg_y, ifa[0].inf_msg_x) ;
                                        /* インフォメーションエリアに */
                                        /* 移動                       */
                clrtobot() ;            /* インフォメーションエリアの */
                                        /* クリア                     */
                refresh() ;             /* 画面の再描画               */
                ifa[0].endflg = N_END ; /* 終了指示                   */
                hi_end( &ifa[0] ) ;     /* 終了処理関数               */
                exit(0) ;               /* end program                */

/* ------------------------------------------------------------------ */
/* オプション                                                         */
/* ------------------------------------------------------------------ */
            case 'v' :                  /* オプション                 */
                hi_version( &ifa[0] ) ; /* バージョン表示関数         */
                exit(0) ;               /* end program                */

/* ------------------------------------------------------------------ */
/* 規定外                                                             */
/* ------------------------------------------------------------------ */
            case '?' :                  /* 規定外                     */
                printf( USAGE ) ;       /* 使用方法の表示             */
                exit(1) ;               /* end program                */
        }                               /* end switch                 */
    }                                   /* end while                  */

/* ------------------------------------------------------------------ */
/* 入力ファイル/共有メモリデータの読み込み                            */
/* ------------------------------------------------------------------ */
    if ( optcnt == 0 ) {                /* 操作対象:ファイル          */
        if ( argc < 2 ) {               /* ファイル名未指定           */
            printf( USAGE ) ;           /* 使用方法の表示             */
            exit(1) ;                   /* end program                */
        }                               /* end if                     */
        for ( lpcnt = 1 ; lpcnt < argc ; lpcnt++ ) {
                                        /* 引数ループ                 */
            strlcpy( ifa[optcnt].file, argv[lpcnt],
                     sizeof( ifa[optcnt].file ) ) ;
                                        /* ファイル名称取得           */
            optcnt++ ;                  /* オプションカウンタの更新   */
        }                               /* end for                    */
    }                                   /* end if                     */

/* ------------------------------------------------------------------ */
/* 対象ファイル(共有メモリ)単位の起動                                 */
/* ------------------------------------------------------------------ */
    for ( lpcnt = 0 ; lpcnt < optcnt ; lpcnt++ ) {
                                        /* オプション数ループ         */
/* ------------------------------------------------------------------ */
/* バイナリエディタの初期設定                                         */
/* ------------------------------------------------------------------ */
        ext_entry = lpcnt ;             /* エントリ番号の設定         */
        hi_init( &ifa[lpcnt] ) ;        /* 初期設定関数               */

/* ------------------------------------------------------------------ */
/* 入力ファイル/共有メモリデータの読み込み                            */
/* ------------------------------------------------------------------ */
        if ( ifa[lpcnt].option == FIL ) {
                                        /* 操作対象がファイル         */
            file_read( &ifa[lpcnt] ) ;  /* 入力ファイルの読み込み     */
        }                               /* end if                     */
        else {                          /* 操作対象が共有メモリ       */
            shmem_attach( &ifa[lpcnt] ) ;
                                        /* 共有メモリアタッチ関数     */
        }                               /* end else                   */

/* ------------------------------------------------------------------ */
/* ヘッダ情報の表示                                                   */
/* ------------------------------------------------------------------ */
        head_disp( &ifa[lpcnt] ) ;      /* ヘッダ表示関数             */

/* ------------------------------------------------------------------ */
/* バイナリエディタ起動                                               */
/* ------------------------------------------------------------------ */
        ifa[lpcnt].maxent = optcnt ;    /* ファイル総数の設定         */
        ifa[lpcnt].entry  = lpcnt + 1 ; /* ファイルエントリの設定     */
        ifa[lpcnt].status = SERVICE ;   /* サービス開始               */
        binary_edit( &ifa[lpcnt] ) ;    /* バイナリエディタ起動       */
        hi_end( &ifa[lpcnt] ) ;         /* 終了処理関数               */

/* ------------------------------------------------------------------ */
/* バイナリエディタの終了処理                                         */
/* ------------------------------------------------------------------ */
        if (( ifa[lpcnt].endflg == N_END )||
            ( ifa[lpcnt].endflg == D_END )) {
                                        /* 終了指示又は、強制終了指示 */
            break ;                     /* break for                  */
        }                               /* end if                     */
    }                                   /* end for                    */
    return(0) ;                         /* end program                */
}                                       /* end (main)                 */

#ifndef HAVE_GETOPT_LONG
/**********************************************************************/
/*  getopt_long(FreeBSD/HP-UX/Solaris対応版) - getopt_long            */
/* ------------------------------------------------------------------ */
/* 関数概要                                                           */
/*   FreeBSD/HP-UX/Solaris用に、getopt_longを提供する。               */
/**********************************************************************/
int getopt_long( int argc,
                 char **argv,
                 char *shortopts,
                 struct option *longopts,
                 int *longind )
                                        /* getopt_long関数            */
{
    li            index         ;       /* オプションインデックス数   */
    li            lparg         ;       /* カウンタ(引数用)           */
    li            lpopt         ;       /* カウンタ(インデックス用)   */

/* ------------------------------------------------------------------ */
/* 初期設定                                                           */
/* ------------------------------------------------------------------ */
    index = 0 ;                         /* インデックス数初期化       */
                                        /* 初期化                     */
    while ( 1 ) {                       /* オプション数のチェック     */
        if ( longopts[index].name == 0x00 ) {
                                        /* ループ終了                 */
            break ;                     /* break while                */
        }                               /* end if                     */
        index++ ;                       /* インデックス数更新         */
    }                                   /* end while                  */

/* ------------------------------------------------------------------ */
/* 引数チェック                                                       */
/* ------------------------------------------------------------------ */
    for ( lparg = 0 ; lparg < argc ; lparg++ ) {
                                        /* 引数チェック               */
        if ( memcmp( argv[lparg], "--", 2 ) == 0 ) {
                                        /* オプション検知             */
            for ( lpopt = 0 ; lpopt < index ; lpopt++ ) {
                                        /* オプションチェック         */
                if ( memcmp( &argv[lparg][2], longopts[lpopt].name,
                             strlen( &argv[lparg][2] ) ) == 0 ) {
                                        /* 引数：正常                 */
                    if ( longopts[lpopt].has_arg == 1 ) {
                                        /* 値を必要としている         */
                        optarg = argv[lparg+1] ;
                                        /* 値の設定                   */
                    }                   /* end if                     */
                    return( longopts[lpopt].val ) ;
                                        /* return - getopt_long       */
                }                       /* end if                     */
            }                           /* end for                    */
            fprintf( stderr, "hi: unrecognized option '--%c'\n",
                             argv[lparg][2] ) ;
                                        /* エラーメッセージ表示       */
            return( '?' ) ;             /* return - getopt_long       */
        }                               /* end if                     */
        else if ( argv[lparg][0] == '-' ) {
                                        /* オプション検知             */
            for ( lpopt = 0 ; lpopt < index ; lpopt++ ) {
                                        /* オプションチェック         */
                if ( memcmp( &argv[lparg][1], longopts[lpopt].name,
                             strlen( &argv[lparg][1] ) ) == 0 ) {
                                        /* 引数：正常                 */
                    if ( longopts[lpopt].has_arg == 1 ) {
                                        /* 値を必要としている         */
                        optarg = argv[lparg+1] ;
                                        /* 値の設定                   */
                    }                   /* end if                     */
                    return( longopts[lpopt].val ) ;
                                        /* return - getopt_long       */
                }                       /* end if                     */
            }                           /* end for                    */
            for ( lpopt = 0 ; lpopt < index ; lpopt++ ) {
                                        /* オプションチェック         */
                if ( argv[lparg][1] == (char)longopts[lpopt].val ) {
                                        /* 引数：正常                 */
                    fprintf( stderr,
                             "hi: option requires an argument -- %c\n",
                              argv[lparg][1] ) ;
                                        /* エラーメッセージ表示       */
                    return( '?' ) ;     /* return - getopt_long       */
                }                       /* end if                     */
            }                           /* end for                    */
            fprintf( stderr, "hi: invalid option --%c\n",
                             argv[lparg][1] ) ;
                                        /* エラーメッセージ表示       */
            return( '?' ) ;             /* return - getopt_long       */
        }                               /* end else                   */
    }                                   /* end for                    */

    return( EOF ) ;                     /* return - getopt_long       */
}                                       /* end (getopt_long)          */
#endif

/**********************************************************************/
