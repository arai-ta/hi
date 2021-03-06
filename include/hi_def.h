/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/*    定数定義ヘッダ - hi_def.h                                       */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Modifier: Tatsuyoshi                                          */
/* @(#) Date    : Nov 2006                                            */
/* @(#) Version : 2.4                                                 */
/* @(#) Release : 3t                                                  */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/*    Copyright (c) 2004-2006 Tatsuyoshi                              */
/* ------------------------------------------------------------------ */
/* ヘッダ概要                                                         */
/*   バイナリエディタで使用する定数を定義する。                       */
/**********************************************************************/
/* ================================================================== */
/* データ型定義                                                       */
/* ================================================================== */
typedef     double               db ;   /* 符号有り倍精度整数型(8byte)*/
typedef     int                  li ;   /* 符号付き整数型(4byte)      */
typedef     unsigned int         ul ;   /* 符号無し整数型(4byte)      */
typedef     short int            si ;   /* 符号付き整数型(2byte)      */
typedef     unsigned short int   us ;   /* 符号無し整数型(2byte)      */
typedef     char                 ch ;   /* 符号付き文字型             */
typedef     unsigned char        uc ;   /* 符号無し文字型             */
typedef     void                 vd ;   /* 値無し                     */

/* ================================================================== */
/* 定数定義                                                           */
/* ================================================================== */
/* ------------------------------------------------------------------ */
/* バージョン情報                                                     */
/* ------------------------------------------------------------------ */
#define     VERSION        "2.4"        /* バージョン番号             */
#define     RELEASE        "2t"          /* リリース番号              */

/* ------------------------------------------------------------------ */
/* 環境ファイル                                                       */
/* ------------------------------------------------------------------ */
#define     HI_CONFIG      ".hirc"      /* 環境ファイル名             */

/* ------------------------------------------------------------------ */
/* 状態フラグ                                                         */
/* ------------------------------------------------------------------ */
#define     NON_SERVICE    'n'          /* サービス状態以外           */
#define     SERVICE        's'          /* サービス状態               */

/* ------------------------------------------------------------------ */
/* 終了フラグ                                                         */
/* ------------------------------------------------------------------ */
#define     N_END          '1'          /* 終了指示         : [q]     */
#define     D_END          '2'          /* 強制終了指示     : [q!]    */
#define     ABORT          '3'          /* 強制終了指示               */
#define     CONTINUE       '4'          /* 処理継続                   */
#define     CHANGE         '5'          /* 編集対象切り替え : [n][n!] */

/* ------------------------------------------------------------------ */
/* カーサスフラグ                                                     */
/* ------------------------------------------------------------------ */
#define     INIT           0x01         /* 初期化済み                 */
#define     NOT_INIT       0x00         /* 未初期化                   */

/* ------------------------------------------------------------------ */
/* 制御文字                                                           */
/* ------------------------------------------------------------------ */
#define     BACK_SPACE     (KEY_BACKSPACE)
                                        /* 後退キー                   */
#define     ESCAPE         (KEY_ESCAPE) /* エスケープキー             */

/* ------------------------------------------------------------------ */
/* 関数番号(コマンド振り分け用)                                       */
/* ------------------------------------------------------------------ */
#define     FUNC_MAX       40           /* 関数MAX                    */
#define     FUNC_DMY       0            /* ダミー関数                 */
#define     FUNC_HDN       1            /* カーソル下移動関数(HEX)    */
#define     FUNC_CDN       2            /* カーソル下移動関数(文字)   */
#define     FUNC_HUP       3            /* カーソル上移動関数(HEX)    */
#define     FUNC_CUP       4            /* カーソル上移動関数(文字)   */
#define     FUNC_HLF       5            /* カーソル左移動関数(HEX)    */
#define     FUNC_CLF       6            /* カーソル左移動関数(文字)   */
#define     FUNC_HRI       7            /* カーソル右移動関数(HEX)    */
#define     FUNC_CRI       8            /* カーソル右移動関数(文字)   */
#define     FUNC_GCM       9            /* 制御コマンド関数           */
#define     FUNC_SCM       10           /* サーチコマンド関数         */
#define     FUNC_SCE       11           /* サーチコマンド実行関数     */
#define     FUNC_CMV       12           /* カーソル位置切替関数       */
#define     FUNC_WRF       13           /* 画面再描画関数             */
#define     FUNC_RPT       14           /* 画面再描画関数             */
#define     FUNC_HIN       15           /* データ挿入関数(HEX)        */
#define     FUNC_CIN       16           /* データ挿入関数(文字)       */
#define     FUNC_HHI       17           /* データ挿入(先頭)関数(HEX)  */
#define     FUNC_CHI       18           /* データ挿入(先頭)関数(文字) */
#define     FUNC_HAD       19           /* データ追加関数(HEX)        */
#define     FUNC_CAD       20           /* データ追加(最終)関数(文字) */
#define     FUNC_HTA       21           /* データ追加(最終)関数(HEX)  */
#define     FUNC_CTA       22           /* データ追加関数(文字)       */
#define     FUNC_HR1       23           /* データ変換関数(単一:HEX)   */
#define     FUNC_CR1       24           /* データ変換関数(単一:文字)  */
#define     FUNC_HR2       25           /* データ変換関数(複数:HEX)   */
#define     FUNC_CR2       26           /* データ変換関数(複数:文字)  */
#define     FUNC_HDL       27           /* データ削除関数(HEX)        */
#define     FUNC_CDL       28           /* データ削除関数(文字)       */
#define     FUNC_PRP       29           /* ページスクロール関数(上)   */
#define     FUNC_NXP       30           /* ページスクロール関数(下)   */
#define     FUNC_PHP       31           /* 半ページスクロール関数(上) */
#define     FUNC_NHP       32           /* 半ページスクロール関数(下) */
#define     FUNC_HOM       33           /* カーソル移動関数(先頭)     */
#define     FUNC_END       34           /* カーソル移動関数(最終)     */
#define     FUNC_AGT       35           /* アドレス取得関数           */
#define     FUNC_REP       36           /* 繰り返しコマンド関数       */
#define     FUNC_CWQ       37           /* ZZ(:wq)用                  */
#define     FUNC_LST       38           /* 行先頭に移動関数           */
#define     FUNC_LED       39           /* 行最終に移動関数           */

/* ------------------------------------------------------------------ */
/* 関数番号(言語決定用)                                               */
/* ------------------------------------------------------------------ */
#define     FUNC_T_MAX     4            /* 関数MAX                    */
#define     FUNC_T_A       0            /* 端末の言語属性:[ASCII]     */
#define     FUNC_T_E       1            /* 端末の言語属性:[EUC]       */
#define     FUNC_T_S       2            /* 端末の言語属性:[SJIS]      */
#define     FUNC_T_O       3            /* 端末の言語属性:その他      */

#define     FUNC_L_MAX     5            /* 関数MAX                    */
#define     FUNC_L_A       0            /* 言語:[ASCII]               */
#define     FUNC_L_E       1            /* 言語:[EUC]                 */
#define     FUNC_L_S       2            /* 言語:[SJIS]                */
#define     FUNC_L_J       3            /* 言語:[JIS]                 */
#define     FUNC_L_B       4            /* 言語:[EBCDIC]              */

/* ------------------------------------------------------------------ */
/* 環境                                                               */
/* ------------------------------------------------------------------ */
#define     MAX_EDIT       10           /* 編集対象ファイルMAX数      */
#define     MIN_COLS       76           /* 最低桁数                   */
#define     MIN_LINES      4            /* 最低行数                   */
#define     ALLOC_SIZE     1024         /* 追加作業領域サイズ         */
#define     MAX_SIZE       0x7fffffff   /* 最大作業領域サイズ         */
#define     USAGE          \
"Usage : hi { file [file...] | -m shmid [-m shmid...] | \
-m shmid[,shmid...] } [ --help ] [ --version ]\n\n"
                                        /* 使用方法                   */
/* ------------------------------------------------------------------ */
/* ダンプ編集                                                         */
/* ------------------------------------------------------------------ */
#define     MASK           0x0f         /* ビットマスク               */
#define     SPACE          0x20         /* ( )スペース                */
#define     ZERO           0x30         /* (0)ゼロ                    */
#define     TEN            '.'          /* (.)点                      */

/* ------------------------------------------------------------------ */
/* ファイル有無                                                       */
/* ------------------------------------------------------------------ */
#define     EXIST          0x01         /* ファイル有無:存在する      */
#define     NOT_EXIST      0x00         /* ファイル有無:存在しない    */

/* ------------------------------------------------------------------ */
/* 操作対象                                                           */
/* ------------------------------------------------------------------ */
#define     SHM            's'          /* 操作対象:共有メモリ        */
#define     FIL            'f'          /* 操作対象:ファイル          */

/* ------------------------------------------------------------------ */
/* 言語                                                               */
/* ------------------------------------------------------------------ */
#define     LANG_ASCII     'A'          /* 言語:ASCII                 */
#define     LANG_EUC       'E'          /* 言語:EUC                   */
#define     LANG_SJIS      'S'          /* 言語:Shift-JIS             */
#define     LANG_JIS       'J'          /* 言語:JIS                   */
#define     LANG_UTF8      'U'          /* Lang:UTF-8                 */
#define     LANG_EBCDIC    'B'          /* 言語:EBCDIC                */

/* ------------------------------------------------------------------ */
/* EBCDIC(K)の種類                                                    */
/* ------------------------------------------------------------------ */
#define     EBCDIC_IBM     'I'          /* EBCDIC IBM                 */
#define     EBCDIK_HITAC   'H'          /* EBCDIK HITAC               */
#define     EBCDIC_NEC     'N'          /* EBCDIC NEC                 */
#define     EBCDIC         'O'          /* EBCDIC                     */

/* ------------------------------------------------------------------ */
/* エスケープシーケンス[JIS編]                                        */
/* ------------------------------------------------------------------ */
#define     JIS_ASCII      "\033(B"     /* ASCII                      */
#define     JIS_ROMAN_SET  "\033(J"     /* X 0201-1976 Roman Set      */
#define     JIS_HALF_KANA  "\033(I"     /* X 0201-1976 片仮名         */
#define     JIS_X0208_OLD  "\033$@"     /* X 0208-1978 (通称:旧JIS)   */
#define     JIS_X0208_NEW  "\033$B"     /* X 0208-1978 (通称:新JIS)   */
#define     JIS_X0208_ADD  "\033&@\033$B"
                                        /* X 0208-1990 (第2水準 追加) */
#define     JIS_X0212      "\033$(D"    /* X 0212-1990 (第3水準 定義) */

/* ------------------------------------------------------------------ */
/* データ変換フォーマット                                             */
/* ------------------------------------------------------------------ */
#define     CONV_BIN       ((li)'b')    /* 2進数指定                  */
#define     CONV_OCT       ((li)'o')    /* 8進数指定                  */
#define     CONV_UDC       ((li)'u')    /* 符号無し10進数指定         */
#define     CONV_DEC       ((li)'d')    /* 符号有り10進数指定         */
#define     CONV_PAC       ((li)'p')    /* パック指定                 */

/* ------------------------------------------------------------------ */
/* 検索文字列反転属性                                                 */
/* ------------------------------------------------------------------ */
#define     REVERSE        'y'          /* 言語:反転表示する          */
#define     NOT_REVERSE    'n'          /* 言語:反転表示しない        */

/* ------------------------------------------------------------------ */
/* 動作環境表示属性                                                   */
/* ------------------------------------------------------------------ */
#define     ENVOUT         'o'          /* 動作環境:表示する          */
#define     NOT_ENVOUT     'n'          /* 動作環境:表示しない        */

/* ------------------------------------------------------------------ */
/* サーチ方向                                                         */
/* ------------------------------------------------------------------ */
#define     NEXT_SEARCH    'n'          /* サーチ方向:順検索          */
#define     PREV_SEARCH    'p'          /* サーチ方向:逆検索          */

/* ------------------------------------------------------------------ */
/* 表示位置                                                           */
/* ------------------------------------------------------------------ */
#define     VERSION_Y      0            /* バージョン領域(Y座標)      */
#define     VERSION_X      20           /* バージョン領域(X座標)      */
#define     HEAD_Y1        0            /* ヘッダ領域(Y座標1)         */
#define     HEAD_Y2        1            /* ヘッダ領域(Y座標2)         */
#define     HEAD_X1_1      0            /* ヘッダ領域(X座標1_1)       */
#define     HEAD_X1_2      45           /* ヘッダ領域(X座標1_2)       */
#define     HEAD_X1_3      60           /* ヘッダ領域(X座標1_3)       */
#define     HEAD_X2_1      0            /* ヘッダ領域(X座標2_1)       */
#define     HEAD_X2_2      10           /* ヘッダ領域(X座標2_2)       */
#define     HEAD_X2_3      59           /* ヘッダ領域(X座標2_3)       */
#ifdef DISP_LINE2
#define     BASE_Y         2            /* ベース領域(Y座標)          */
#else
#define     BASE_Y         1            /* ベース領域(Y座標)          */
#endif
#define     BASE_X1        0            /* ベース領域(X座標1)         */
#define     BASE_X2        10           /* ベース領域(X座標2)         */
#define     BASE_X3        59           /* ベース領域(X座標3)         */
#define     OFST_Y         0            /* オフセット領域(Y座標)      */
#define     OFST_X         35           /* オフセット領域(X座標)      */
#define     MODE_Y         0            /* モード領域(Y座標)          */
#define     MODE_X         50           /* モード領域(X座標)          */

/* ------------------------------------------------------------------ */
/* 表示データ                                                         */
/* ------------------------------------------------------------------ */
#define     HEAD_STRING_1_1 "binary editor hi ver       offset:[        ]"
                                        /* ヘッダ1.1                  */
#define     HEAD_STRING_1_2 "mode:"     /* ヘッダ1.2                  */
#ifdef DISP_LINE2
#define     HEAD_STRING_2_1 " [HEX]  "  /* ヘッダ2.1                  */
#define     HEAD_STRING_2_2 \
                      "+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +a +b +c +d +e +f"
                                        /* ヘッダ2.2                  */
#define     HEAD_STRING_2_3 "0123456789abcdef+"
                                        /* ヘッダ2.3                  */
#endif
#define     MODE_STR_CMD   "COMMAND"    /* コマンドモード             */
#define     MODE_STR_INS   "INSERT "    /* 挿入モード                 */
#define     MODE_STR_REP   "REPLACE"    /* 変更モード                 */
#define     MODE_STR_DEL   "DELETE "    /* 削除モード                 */

/* ------------------------------------------------------------------ */
/* カーソル位置                                                       */
/* ------------------------------------------------------------------ */
#define     CUR_LEFT       0x01         /* カーソル位置:上位バイト    */
#define     CUR_RIGHT      0x02         /* カーソル位置:下位バイト    */

/* ------------------------------------------------------------------ */
/* モード                                                             */
/* ------------------------------------------------------------------ */
#define     MODE_CMD       'c'          /* モード:コマンド            */
#define     MODE_EDT       'e'          /* モード:編集                */

/* ------------------------------------------------------------------ */
/* 修正対象                                                           */
/* ------------------------------------------------------------------ */
#define     HEX_DATA       'H'          /* HEXデータエリア            */
#define     CHAR_DATA      'C'          /* 文字データエリア           */

/* ------------------------------------------------------------------ */
/* 画面イメージ出力種別                                               */
/* ------------------------------------------------------------------ */
#define     CREATE         'c'          /* 新規                       */
#define     ADD            'a'          /* 追加                       */

/* ------------------------------------------------------------------ */
/* 修正有無                                                           */
/* ------------------------------------------------------------------ */
#define     MOD_ON         0x01         /* 修正有り                   */
#define     MOD_OFF        0x00         /* 修正無し                   */

/* ------------------------------------------------------------------ */
/* カーソル制御コマンド                                               */
/* ------------------------------------------------------------------ */
#define     CMD_CUR_DOWN   ((li)'j')    /* カーソル下移動コマンド     */
#define     CMD_CUR_UP     ((li)'k')    /* カーソル上移動コマンド     */
#define     CMD_CUR_LEFT   ((li)'h')    /* カーソル左移動コマンド     */
#define     CMD_CUR_RIGHT  ((li)'l')    /* カーソル右移動コマンド     */
#define     CMD_PREV_PAGE  (KEY_CTRL_B) /* ページスクロール(上)       */
#define     CMD_NEXT_PAGE  (KEY_CTRL_F) /* ページスクロール(下)       */
#define     CMD_PREV_HALF  (KEY_CTRL_U) /* 半ページスクロール(上)     */
#define     CMD_NEXT_HALF  (KEY_CTRL_D) /* 半ページスクロール(下)     */
#define     CMD_TAIL       ((li)'G')    /* ファイルの最後に移動       */
#define     CMD_LINE_START ((li)'0')    /* ファイルの最後に移動       */
#define     CMD_LINE_END   ((li)'$')    /* ファイルの最後に移動       */
#define     CMD_CPOS_MOVE  (KEY_CTRL_A) /* カーソル位置切替           */
#define     CMD_CPOS_MOV2  ((li)'\t')   /* カーソル位置切替           */
#define     CMD_ADRS_JMP   (KEY_CTRL_J) /* アドレス読み込み移動       */
#define     CMD_CHG_CHAR   (KEY_CTRL_T) /* 文字コード切り替え         */
#define     CMD_BIGZ       ((li)'Z')    /* ZZ 用                      */

/* ------------------------------------------------------------------ */
/* データ編集コマンド                                                 */
/* ------------------------------------------------------------------ */
#define     CMD_REPEAT     ((li)'.')    /* 繰り返し                   */
#define     CMD_INPUT      ((li)'i')    /* データの挿入               */
#define     CMD_TOP_INPUT  ((li)'I')    /* 先頭からデータの挿入       */
#define     CMD_ADD        ((li)'a')    /* データの追加               */
#define     CMD_LAST_ADD   ((li)'A')    /* 最後からデータの追加       */
#define     CMD_REPLACE_1  ((li)'r')    /* データの変換(単一)         */
#define     CMD_REPLACE_2  ((li)'R')    /* データの変換(複数)         */
#define     CMD_DELETE     ((li)'x')    /* データの削除               */

/* ------------------------------------------------------------------ */
/* 画面制御コマンド                                                   */
/* ------------------------------------------------------------------ */
#define     CMD_REFRESH    (KEY_CTRL_L) /* 画面のリフレッシュ         */
#define     CMD_REPORT     (KEY_CTRL_G) /* レポート表示               */

/* ------------------------------------------------------------------ */
/* サーチコマンド                                                     */
/* ------------------------------------------------------------------ */
#define     CMD_SEARCH     ((li)'/')    /* サーチコマンド             */
#define     CMD_RSEARCH    ((li)'?')    /* 逆サーチコマンド           */
#define     CMD_NEXT       ((li)'n')    /* 再検索コマンド             */
#define     CMD_REVERSE    ((li)'N')    /* 再逆検索コマンド           */

/* ------------------------------------------------------------------ */
/* 制御コマンド(':'で指定する)                                        */
/* ------------------------------------------------------------------ */
#define     CMD_CNTRL      ((li)':')    /* 制御コマンド開始           */

#define     CNTL_CMD_CHG01 "n"          /* 対象ファイル変更           */
#define     CNTL_CMD_CHG02 "n!"         /* 対象ファイル強制変更       */
#define     CNTL_CMD_QUIT1 "q"          /* 終了                       */
#define     CNTL_CMD_QUIT2 "q!"         /* 強制終了                   */
#define     CNTL_CMD_WQ    "wq"         /* 書き込み終了               */
#define     CNTL_CMD_WRITE ((ch)'w')    /* 上書き、又は別名保管       */
#define     CNTL_CMD_READ  ((ch)'r')    /* ファイル読み込み機能       */
#define     CNTL_CMD_HELP  "h"          /* ヘルプ表示                 */
#define     CNTL_CMD_ENV   "env"        /* 動作環境表示               */
#define     CNTL_CMD_TOP   ((ch)'^')    /* 先頭指定                   */
#define     CNTL_CMD_CRNT  ((ch)'.')    /* カレント指定               */
#define     CNTL_CMD_LAST  ((ch)'$')    /* 最終指定                   */
#define     CNTL_CMD_PLUS  ((ch)'+')    /* オフセット(+)指定          */
#define     CNTL_CMD_MINUS ((ch)'-')    /* オフセット(-)指定          */
#define     CNTL_CMD_HOME  ((li)'~')    /* ホームディレクトリ         */
#define     CNTL_CMD_FILE  ((li)'%')    /* 自ファイル名称             */
#define     CNTL_CMD_ADRS  "0x"         /* 指定アドレスに移動         */
#define     CNTL_CMD_SHELL ((ch)'!')    /* シェルコマンド             */
#define     CNTL_CMD_TR    "tr"         /* 言語設定                   */
#define     CNTL_CMD_SR_ON "sr=on"      /* 反転表示                   */
#define     CNTL_CMD_SR_OF "sr=off"     /* 反転表示解除               */
#define     CNTL_CMD_P     ((ch)'p')    /* 画面イメージ出力           */
#define     CNTL_CMD_PA    "pa"         /* 画面イメージ追加出力       */
#define     CNTL_CMD_PR    "pr"         /* データ変換表示             */
#define     CNTL_CMD_FNAME "f"          /* ファイル名表示             */

/* ------------------------------------------------------------------ */
/* ヘルプ関係                                                         */
/* ------------------------------------------------------------------ */
#define     HELP_PATH      "./"
                                        /* ヘルプファイルパス         */
#define     HELP_INFO      "< [n]:next-page, [p]:prev-page, [q]:quit >"
                                        /* ヘルプインフォメーション   */
#define     HELP_CMD_NEXT  0x6e         /* 次ページ表示               */
#define     HELP_CMD_PREV  0x70         /* 前ページ表示               */
#define     HELP_CMD_QUIT  0x71         /* ヘルプ終了                 */

/* ------------------------------------------------------------------ */
/* 動作環境表示関係                                                   */
/* ------------------------------------------------------------------ */
/*#define     E_MAIL_ADDRESS "mita@maroon.plala.or.jp"
                                           送付先メールアドレス       */
#define     ENV_OUT_FILE   "/var/tmp/hi_env"
                                        /* 動作環境出力ファイル       */
#define     ENV_INFO \
    "< [n]:next-page, [p]:prev-page, [w]:write, [q]:quit >"
                                        /* 動作環境インフォメーション */
#define     ENV_LINE       81           /* 動作環境情報の行数         */
#define     ENV_CMD_NEXT   0x6e         /* 次ページ表示               */
#define     ENV_CMD_NEXT2  0x20         /* 次ページ表示2              */
#define     ENV_CMD_PREV   0x70         /* 前ページ表示               */
#define     ENV_CMD_PREV2  0x62         /* 前ページ表示2              */
#define     ENV_CMD_WRITE  0x77         /* 動作環境出力               */
#define     ENV_CMD_QUIT   0x71         /* 動作環境出力終了           */

/* ------------------------------------------------------------------ */
/* デバッグファイル                                                   */
/* ------------------------------------------------------------------ */
#define     DEBUG_FILE     "/var/tmp/hi_debug"
                                        /* デバッグファイル           */
/**********************************************************************/
