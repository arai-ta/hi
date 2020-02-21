/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/*    関数定義ヘッダ - hi_func.h                                      */
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
/*   バイナリエディタを構成する関数の型定義を行う。                   */
/**********************************************************************/
/* ================================================================== */
/* 関数型定義                                                         */
/* ================================================================== */
extern vd  address_get      ( struct ifa_s * ) ;
extern vd  address_view     ( struct ifa_s * ) ;
extern vd  area_check       ( struct ifa_s * ) ;
extern vd  area_delete      ( struct ifa_s * ) ;
extern vd  area_write       ( struct ifa_s * ) ;
extern vd  binary_edit      ( struct ifa_s * ) ;
extern vd  cur_move_c_h     ( struct ifa_s * ) ;
extern vd  cur_move_c_j     ( struct ifa_s * ) ;
extern vd  cur_move_c_k     ( struct ifa_s * ) ;
extern vd  cur_move_c_l     ( struct ifa_s * ) ;
extern vd  cur_move_h_h     ( struct ifa_s * ) ;
extern vd  cur_move_h_j     ( struct ifa_s * ) ;
extern vd  cur_move_h_k     ( struct ifa_s * ) ;
extern vd  cur_move_h_l     ( struct ifa_s * ) ;
extern vd  cur_pos_move     ( struct ifa_s * ) ;
extern vd  cur_pos_set      ( struct ifa_s * ) ;
extern vd  data_view        ( struct ifa_s * ) ;
extern vd  debug            ( struct ifa_s * ) ;
extern vd  dmy              ( struct ifa_s * ) ;
extern vd  edit_c_add       ( struct ifa_s * ) ;
extern vd  edit_c_del       ( struct ifa_s * ) ;
extern vd  edit_c_input     ( struct ifa_s * ) ;
extern vd  edit_c_rep_1     ( struct ifa_s * ) ;
extern vd  edit_c_rep_2     ( struct ifa_s * ) ;
extern vd  edit_h_add       ( struct ifa_s * ) ;
extern vd  edit_h_del       ( struct ifa_s * ) ;
extern vd  edit_h_input     ( struct ifa_s * ) ;
extern vd  edit_h_rep_1     ( struct ifa_s * ) ;
extern vd  edit_h_rep_2     ( struct ifa_s * ) ;
extern vd  env_output       ( struct ifa_s * ) ;
extern vd  err_msg          ( struct ifa_s * ) ;
extern vd  exec_get_cmd     ( struct ifa_s * ) ;
extern vd  exec_search_cmd  ( struct ifa_s * ) ;
extern vd  exec_shell       ( struct ifa_s * ) ;
extern vd  file_create      ( struct ifa_s * ) ;
extern vd  file_read        ( struct ifa_s * ) ;
extern vd  file_write       ( struct ifa_s * ) ;
extern vd  file_insert      ( struct ifa_s * ) ;
extern vd  get_cmd          ( struct ifa_s * ) ;
extern vd  half_page_down   ( struct ifa_s * ) ;
extern vd  half_page_up     ( struct ifa_s * ) ;
extern vd  head_c_input     ( struct ifa_s * ) ;
extern vd  head_disp        ( struct ifa_s * ) ;
extern vd  head_h_input     ( struct ifa_s * ) ;
extern vd  help             ( struct ifa_s * ) ;
extern vd  help_read        ( struct ifa_s * ) ;
extern vd  hex_str_cnv      ( struct ifa_s * ) ;
extern vd  hi_config        ( struct ifa_s * ) ;
extern vd  hi_end           ( struct ifa_s * ) ;
extern vd  hi_init          ( struct ifa_s * ) ;
extern vd  hi_insert        ( struct ifa_s * ) ;
extern vd  hi_regex         ( struct ifa_s *, ch *, ul *, li ) ;
extern vd  hi_reinit        ( struct ifa_s * ) ;
extern vd  hi_signal        ( li ) ;
extern vd  hi_version       ( struct ifa_s * ) ;
extern vd  image_write      ( struct ifa_s * ) ;
extern vd  inf_msg          ( struct ifa_s * ) ;
extern vd  lang_ascii       ( struct ifa_s * ) ;
extern vd  lang_ascii_ebcdic( struct ifa_s * ) ;
extern vd  lang_euc_euc     ( struct ifa_s * ) ;
extern vd  lang_euc_jis     ( struct ifa_s * ) ;
extern vd  lang_euc_sjis    ( struct ifa_s * ) ;
extern vd  lang_sjis_euc    ( struct ifa_s * ) ;
extern vd  lang_sjis_jis    ( struct ifa_s * ) ;
extern vd  lang_sjis_sjis   ( struct ifa_s * ) ;
extern li  main             ( li, ch ** ) ;
extern vd  mode_cmd         ( struct ifa_s * ) ;
extern vd  mode_dsp         ( struct ifa_s * ) ;
extern vd  page_down        ( struct ifa_s * ) ;
extern vd  page_up          ( struct ifa_s * ) ;
extern vd  print_conv_data  ( struct ifa_s * ) ;
extern vd  report_dsp       ( struct ifa_s * ) ;
extern vd  repeat_c_del     ( struct ifa_s *, li ) ;
extern vd  repeat_cmd       ( struct ifa_s * ) ;
extern vd  repeat_dmy       ( struct ifa_s *, li ) ;
extern vd  repeat_h_del     ( struct ifa_s *, li ) ;
extern vd  repeat_move_j    ( struct ifa_s *, li ) ;
extern vd  repeat_move_k    ( struct ifa_s *, li ) ;
extern vd  search_cmd       ( struct ifa_s * ) ;
extern vd  shmem_attach     ( struct ifa_s * ) ;
extern vd  str_hex_cnv      ( struct ifa_s * ) ;
extern vd  tail_c_add       ( struct ifa_s * ) ;
extern vd  tail_h_add       ( struct ifa_s * ) ;
extern vd  tail_view        ( struct ifa_s * ) ;
extern vd  top_view         ( struct ifa_s * ) ;
extern vd  move_line_start  ( struct ifa_s * ) ;
extern vd  move_line_end    ( struct ifa_s * ) ;
extern vd  tr_main          ( struct ifa_s * ) ;
extern vd  trace_end        ( struct ifa_s * ) ;
extern vd  trace_start      ( struct ifa_s *, ch * ) ;
extern vd  win_refresh      ( struct ifa_s * ) ;
extern vd  win_size         ( struct ifa_s * ) ;

#ifndef HAVE_STRLCPY
extern size_t  strlcpy      ( char *dst, const char *src, size_t siz ) ;
#endif

#ifndef HAVE_STRLCAT
extern size_t  strlcat      ( char *dst, const char *src, size_t siz ) ;
#endif

/**********************************************************************/
