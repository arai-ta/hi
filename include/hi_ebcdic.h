/**********************************************************************/
/*  hi - バイナリエディタ                                             */
/*    EBCDIC→ASCIIコード変換テーブル - hi_ebcidc.h                   */
/* ------------------------------------------------------------------ */
/* @(#) Author  : Kazunori Mita (mita@maroon.plala.or.jp)             */
/* @(#) Date    : Dec 1998 - Oct 2000                                 */
/* @(#) Version : 2.2                                                 */
/* @(#) Release : 1                                                   */
/* ------------------------------------------------------------------ */
/*    Copyright (c) 1998-2000 Kazunori Mita. All right reserved.      */
/* ------------------------------------------------------------------ */
/* ヘッダ概要                                                         */
/*   EBCDIC(K)コードをASCIIコードに変換するための変換テーブル         */
/**********************************************************************/
struct ebcdic_tbl {
    uc            C_ASCII        ;      /* ASCIIコード                */
    uc            C_EBCDIC_IBM   ;      /* IBM EBCDIC(カナ)           */
    uc            C_EBCDIK_HITAC ;      /* HITACHI EBCDIK(カナ)       */
    uc            C_EBCDIC_NEC   ;      /* NEC EBCDIC(カナ)           */
    uc            C_EBCDIC       ;      /* EBCDIC                     */
} ;

struct ebcdic_tbl ebcdic[] = {
            {0x00,0x00,0x00,0x00,0x00}, /* NUL                        */
            {0x01,0x01,0x01,0x01,0x01}, /* SOX                        */
            {0x02,0x02,0x02,0x02,0x02}, /* STX                        */
            {0x03,0x03,0x03,0x03,0x03}, /* ETX                        */
            {0x04,0x37,0x37,0x37,0x37}, /* EOT                        */
            {0x05,0x2d,0x2d,0x2d,0x2d}, /* ENQ                        */
            {0x06,0x2e,0x2e,0x2e,0x2e}, /* ACK                        */
            {0x07,0x2f,0x2f,0x2f,0x2f}, /* BEL                        */
            {0x08,0x16,0x16,0x16,0x16}, /* BS                         */
            {0x09,0x05,0x05,0x05,0x05}, /* HT                         */
            {0x0a,0x25,0x15,0x25,0x25}, /* LF                         */
            {0x0b,0x0b,0x0b,0x0b,0x0b}, /* VT                         */
            {0x0c,0x0c,0x0c,0x0c,0x0c}, /* FF                         */
            {0x0d,0x0d,0x0d,0x0d,0x0d}, /* CR                         */
            {0x0e,0x0e,0x0e,0x0e,0x0e}, /* SO                         */
            {0x0f,0x0f,0x0f,0x0f,0x0f}, /* SI                         */
            {0x10,0x10,0x10,0x10,0x10}, /* DLE                        */
            {0x11,0x11,0x11,0x11,0x11}, /* DC1                        */
            {0x12,0x12,0x12,0x12,0x12}, /* DC2                        */
            {0x13,0x13,0x13,0x13,0x13}, /* DC3                        */
            {0x14,0x3c,0x3c,0x3c,0x3c}, /* DC4                        */
            {0x15,0x3d,0x3d,0x3d,0x3d}, /* NAC                        */
            {0x16,0x32,0x32,0x32,0x32}, /* SYN                        */
            {0x17,0x26,0x26,0x26,0x26}, /* ETB                        */
            {0x18,0x18,0x18,0x18,0x18}, /* CAN                        */
            {0x19,0x19,0x19,0x19,0x19}, /* EM                         */
            {0x1a,0x3f,0x1a,0x3f,0x3f}, /* SUB                        */
            {0x1b,0x27,0x27,0x27,0x27}, /* ESC                        */
            {0x1c,0x1c,0x1c,0x1c,0x1c}, /* FS                         */
            {0x1d,0x1d,0x1d,0x1d,0x1d}, /* GS                         */
            {0x1e,0x1e,0x1e,0x1e,0x1e}, /* RS                         */
            {0x1f,0x1f,0x1f,0x1f,0x1f}, /* US                         */
            {0x20,0x40,0x40,0x40,0x40}, /* SP                         */
            {0x21,0x5a,0x4f,0x4f,0x4f}, /* !                          */
            {0x22,0x7f,0x7f,0x7f,0x7f}, /* "                          */
            {0x23,0x7b,0x7b,0x7b,0x7b}, /* #                          */
            {0x24,0xe0,0x5b,0xe0,0x5b}, /* $                          */
            {0x25,0x6c,0x6c,0x6c,0x6c}, /* %                          */
            {0x26,0x50,0x50,0x50,0x50}, /* &                          */
            {0x27,0x7d,0x7d,0x7d,0x7d}, /* '                          */
            {0x28,0x4d,0x4d,0x4d,0x4d}, /* (                          */
            {0x29,0x5d,0x5d,0x5d,0x5d}, /* )                          */
            {0x2a,0x5c,0x5c,0x5c,0x5c}, /* *                          */
            {0x2b,0x4e,0x4e,0x4e,0x4e}, /* +                          */
            {0x2c,0x6b,0x6b,0x6b,0x6b}, /* ,                          */
            {0x2d,0x60,0x60,0x60,0x60}, /* -                          */
            {0x2e,0x4b,0x4b,0x4b,0x4b}, /* .                          */
            {0x2f,0x61,0x61,0x61,0x61}, /* /                          */
            {0x30,0xf0,0xf0,0xf0,0xf0}, /* 0                          */
            {0x31,0xf1,0xf1,0xf1,0xf1}, /* 1                          */
            {0x32,0xf2,0xf2,0xf2,0xf2}, /* 2                          */
            {0x33,0xf3,0xf3,0xf3,0xf3}, /* 3                          */
            {0x34,0xf4,0xf4,0xf4,0xf4}, /* 4                          */
            {0x35,0xf5,0xf5,0xf5,0xf5}, /* 5                          */
            {0x36,0xf6,0xf6,0xf6,0xf6}, /* 6                          */
            {0x37,0xf7,0xf7,0xf7,0xf7}, /* 7                          */
            {0x38,0xf8,0xf8,0xf8,0xf8}, /* 8                          */
            {0x39,0xf9,0xf9,0xf9,0xf9}, /* 9                          */
            {0x3a,0x7a,0x7a,0x7a,0x7a}, /* :                          */
            {0x3b,0x5b,0x5e,0x5e,0x5e}, /* ;                          */
            {0x3c,0x4c,0x4c,0x4c,0x4c}, /* <                          */
            {0x3d,0x7e,0x7e,0x7e,0x7e}, /* =                          */
            {0x3e,0x6e,0x6e,0x6e,0x6e}, /* >                          */
            {0x3f,0x6f,0x6f,0x6f,0x6f}, /* ?                          */
            {0x40,0x7c,0x7c,0x7c,0x7c}, /* @                          */
            {0x41,0xc1,0xc1,0xc1,0xc1}, /* A                          */
            {0x42,0xc2,0xc2,0xc2,0xc2}, /* B                          */
            {0x43,0xc3,0xc3,0xc3,0xc3}, /* C                          */
            {0x44,0xc4,0xc4,0xc4,0xc4}, /* D                          */
            {0x45,0xc5,0xc5,0xc5,0xc5}, /* E                          */
            {0x46,0xc6,0xc6,0xc6,0xc6}, /* F                          */
            {0x47,0xc7,0xc7,0xc7,0xc7}, /* G                          */
            {0x48,0xc8,0xc8,0xc8,0xc8}, /* H                          */
            {0x49,0xc9,0xc9,0xc9,0xc9}, /* I                          */
            {0x4a,0xd1,0xd1,0xd1,0xd1}, /* J                          */
            {0x4b,0xd2,0xd2,0xd2,0xd2}, /* K                          */
            {0x4c,0xd3,0xd3,0xd3,0xd3}, /* L                          */
            {0x4d,0xd4,0xd4,0xd4,0xd4}, /* M                          */
            {0x4e,0xd5,0xd5,0xd5,0xd5}, /* N                          */
            {0x4f,0xd6,0xd6,0xd6,0xd6}, /* O                          */
            {0x50,0xd7,0xd7,0xd7,0xd7}, /* P                          */
            {0x51,0xd8,0xd8,0xd8,0xd8}, /* Q                          */
            {0x52,0xd9,0xd9,0xd9,0xd9}, /* R                          */
            {0x53,0xe2,0xe2,0xe2,0xe2}, /* S                          */
            {0x54,0xe3,0xe3,0xe3,0xe3}, /* T                          */
            {0x55,0xe4,0xe4,0xe4,0xe4}, /* U                          */
            {0x56,0xe5,0xe5,0xe5,0xe5}, /* V                          */
            {0x57,0xe6,0xe6,0xe6,0xe6}, /* W                          */
            {0x58,0xe7,0xe7,0xe7,0xe7}, /* X                          */
            {0x59,0xe8,0xe8,0xe8,0xe8}, /* Y                          */
            {0x5a,0xe9,0xe9,0xe9,0xe9}, /* Z                          */
            {0x5b,0x70,0x4a,0x4a,0x4a}, /* [                          */
            {0x5c,0x5b,0xe0,0x5b,0xe0}, /* \                          */
            {0x5d,0x80,0x5a,0x5a,0x5a}, /* ]                          */
            {0x5e,0xb0,0x5f,0x5f,0x5f}, /* ^                          */
            {0x5f,0x6d,0x6d,0x6d,0x6d}, /* _                          */
            {0x60,0x79,0x79,0x79,0x79}, /* `                          */
            {0x61,0x62,0x59,0x57,0x81}, /* a                          */
            {0x62,0x63,0x62,0x59,0x82}, /* b                          */
            {0x63,0x64,0x63,0x62,0x83}, /* c                          */
            {0x64,0x65,0x64,0x63,0x84}, /* d                          */
            {0x65,0x66,0x65,0x64,0x85}, /* e                          */
            {0x66,0x67,0x66,0x65,0x86}, /* f                          */
            {0x67,0x68,0x67,0x66,0x87}, /* g                          */
            {0x68,0x69,0x68,0x67,0x88}, /* h                          */
            {0x69,0x71,0x69,0x68,0x89}, /* i                          */
            {0x6a,0x72,0x70,0x69,0x91}, /* j                          */
            {0x6b,0x73,0x71,0x70,0x92}, /* k                          */
            {0x6c,0x74,0x72,0x71,0x93}, /* l                          */
            {0x6d,0x75,0x73,0x72,0x94}, /* m                          */
            {0x6e,0x76,0x74,0x73,0x95}, /* n                          */
            {0x6f,0x77,0x75,0x74,0x96}, /* o                          */
            {0x70,0x78,0x76,0x75,0x97}, /* p                          */
            {0x71,0x8b,0x77,0x76,0x98}, /* q                          */
            {0x72,0x9b,0x78,0x77,0x99}, /* r                          */
            {0x73,0xab,0x80,0x78,0xa2}, /* s                          */
            {0x74,0xb3,0x8b,0x80,0xa3}, /* t                          */
            {0x75,0xb4,0x9b,0x8b,0xa4}, /* u                          */
            {0x76,0xb5,0x9c,0x9b,0xa5}, /* v                          */
            {0x77,0xb6,0xa0,0x9c,0xa6}, /* w                          */
            {0x78,0xb7,0xab,0xa0,0xa7}, /* x                          */
            {0x79,0xb8,0xb0,0xab,0xa8}, /* y                          */
            {0x7a,0xb9,0xb1,0xb0,0xa9}, /* z                          */
            {0x7b,0xc0,0xc0,0xc0,0xc0}, /* {                          */
            {0x7c,0x6a,0x6a,0x6a,0x6a}, /* |                          */
            {0x7d,0xd0,0xd0,0xd0,0xd0}, /* }                          */
            {0x7e,0xa0,0xa1,0xa1,0xa1}, /* ~                          */
            {0x7f,0x07,0x07,0x07,0x07}, /* DEL                        */
            {0x80,0x20,0x04,0x20,0x20}, /*                            */
            {0x81,0x21,0x06,0x21,0x21}, /*                            */
            {0x82,0x22,0x08,0x22,0x22}, /*                            */
            {0x83,0x23,0x09,0x23,0x23}, /*                            */
            {0x84,0x24,0x0a,0x24,0x24}, /* IND                        */
            {0x85,0x15,0x14,0x15,0x15}, /* NEL                        */
            {0x86,0x06,0x25,0x06,0x06}, /* SSA                        */
            {0x87,0x17,0x17,0x17,0x17}, /* ESA                        */
            {0x88,0x28,0x1b,0x28,0x28}, /* HTS                        */
            {0x89,0x29,0x20,0x29,0x29}, /* HTJ                        */
            {0x8a,0x2a,0x21,0x2a,0x2a}, /* VTS                        */
            {0x8b,0x2b,0x22,0x2b,0x2b}, /* PLD                        */
            {0x8c,0x2c,0x23,0x2c,0x2c}, /* PLU                        */
            {0x8d,0x09,0x24,0x09,0x09}, /* RI                         */
            {0x8e,0x0a,0x28,0x0a,0x0a}, /* SS2                        */
            {0x8f,0x1b,0x29,0x1b,0x1b}, /* SS3                        */
            {0x90,0x30,0x2a,0x30,0x30}, /* DCS                        */
            {0x91,0x31,0x2b,0x31,0x31}, /* PU1                        */
            {0x92,0x1a,0x2c,0xa1,0x1a}, /* PU2                        */
            {0x93,0x33,0x30,0x33,0x33}, /* STS                        */
            {0x94,0x34,0x31,0x34,0x34}, /* CCH                        */
            {0x95,0x35,0x33,0x35,0x35}, /* MW                         */
            {0x96,0x36,0x34,0x36,0x36}, /* SPA                        */
            {0x97,0x08,0x35,0x08,0x08}, /* EPA                        */
            {0x98,0x38,0x36,0x38,0x38}, /*                            */
            {0x99,0x39,0x38,0x39,0x39}, /*                            */
            {0x9a,0x3a,0x39,0x3a,0x3a}, /*                            */
            {0x9b,0x3b,0x3a,0x3b,0x3b}, /* CSI                        */
            {0x9c,0x04,0x3b,0x04,0x04}, /* ST                         */
            {0x9d,0x14,0x3e,0x14,0x14}, /* OSC                        */
            {0x9e,0x3e,0x3f,0x3e,0x3e}, /* PM                         */
            {0x9f,0xe1,0xb7,0xe1,0xe1}, /* APC                        */
            {0xa0,0x4a,0x57,0xb1,0x41}, /*                            */
            {0xa1,0x41,0x41,0x41,0x42}, /*                            */
            {0xa2,0x42,0x42,0x42,0x43}, /*                            */
            {0xa3,0x43,0x43,0x43,0x44}, /*                            */
            {0xa4,0x44,0x44,0x44,0x45}, /*                            */
            {0xa5,0x45,0x45,0x45,0x46}, /*                            */
            {0xa6,0x46,0x46,0x46,0x47}, /*                            */
            {0xa7,0x47,0x47,0x47,0x48}, /*                            */
            {0xa8,0x48,0x48,0x48,0x49}, /*                            */
            {0xa9,0x49,0x49,0x49,0x51}, /*                            */
            {0xaa,0x51,0x51,0x51,0x52}, /*                            */
            {0xab,0x52,0x52,0x52,0x53}, /*                            */
            {0xac,0x53,0x53,0x53,0x54}, /*                            */
            {0xad,0x54,0x54,0x54,0x55}, /*                            */
            {0xae,0x55,0x55,0x55,0x56}, /*                            */
            {0xaf,0x56,0x56,0x56,0x57}, /*                            */
            {0xb0,0x58,0x58,0x58,0x58}, /*                            */
            {0xb1,0x81,0x81,0x81,0x59}, /*                            */
            {0xb2,0x82,0x82,0x82,0x62}, /*                            */
            {0xb3,0x83,0x83,0x83,0x63}, /*                            */
            {0xb4,0x84,0x84,0x84,0x64}, /*                            */
            {0xb5,0x85,0x85,0x85,0x65}, /*                            */
            {0xb6,0x86,0x86,0x86,0x66}, /*                            */
            {0xb7,0x87,0x87,0x87,0x67}, /*                            */
            {0xb8,0x88,0x88,0x88,0x68}, /*                            */
            {0xb9,0x89,0x89,0x89,0x69}, /*                            */
            {0xba,0x8a,0x8a,0x8a,0x70}, /*                            */
            {0xbb,0x8c,0x8c,0x8c,0x71}, /*                            */
            {0xbc,0x8d,0x8d,0x8d,0x72}, /*                            */
            {0xbd,0x8e,0x8e,0x8e,0x73}, /*                            */
            {0xbe,0x8f,0x8f,0x8f,0x74}, /*                            */
            {0xbf,0x90,0x90,0x90,0x75}, /*                            */
            {0xc0,0x91,0x91,0x91,0x76}, /*                            */
            {0xc1,0x92,0x92,0x92,0x77}, /*                            */
            {0xc2,0x93,0x93,0x93,0x78}, /*                            */
            {0xc3,0x94,0x94,0x94,0x80}, /*                            */
            {0xc4,0x95,0x95,0x95,0x8a}, /*                            */
            {0xc5,0x96,0x96,0x96,0x8b}, /*                            */
            {0xc6,0x97,0x97,0x97,0x8c}, /*                            */
            {0xc7,0x98,0x98,0x98,0x8d}, /*                            */
            {0xc8,0x99,0x99,0x99,0x8e}, /*                            */
            {0xc9,0x9a,0x9a,0x9a,0x8f}, /*                            */
            {0xca,0x9d,0x9d,0x9d,0x90}, /*                            */
            {0xcb,0x9e,0x9e,0x9e,0x9a}, /*                            */
            {0xcc,0x9f,0x9f,0x9f,0x9b}, /*                            */
            {0xcd,0xa2,0xa2,0xa2,0x9c}, /*                            */
            {0xce,0xa3,0xa3,0xa3,0x9d}, /*                            */
            {0xcf,0xa4,0xa4,0xa4,0x9e}, /*                            */
            {0xd0,0xa5,0xa5,0xa5,0x9f}, /*                            */
            {0xd1,0xa6,0xa6,0xa6,0xa0}, /*                            */
            {0xd2,0xa7,0xa7,0xa7,0xaa}, /*                            */
            {0xd3,0xa8,0xa8,0xa8,0xab}, /*                            */
            {0xd4,0xa9,0xa9,0xa9,0xac}, /*                            */
            {0xd5,0xaa,0xaa,0xaa,0xad}, /*                            */
            {0xd6,0xac,0xac,0xac,0xae}, /*                            */
            {0xd7,0xad,0xad,0xad,0xaf}, /*                            */
            {0xd8,0xae,0xae,0xae,0xb0}, /*                            */
            {0xd9,0xaf,0xaf,0xaf,0xb1}, /*                            */
            {0xda,0xba,0xba,0xba,0xb2}, /*                            */
            {0xdb,0xbb,0xbb,0xbb,0xb3}, /*                            */
            {0xdc,0xbc,0xbc,0xbc,0xb4}, /*                            */
            {0xdd,0xbd,0xbd,0xbd,0xb5}, /*                            */
            {0xde,0xbe,0xbe,0xbe,0xb6}, /*                            */
            {0xdf,0xbf,0xbf,0xbf,0xb7}, /*                            */
            {0xe0,0x4f,0xb8,0xb2,0xb8}, /*                            */
            {0xe1,0x57,0xb9,0xb3,0xb9}, /*                            */
            {0xe2,0x59,0xb2,0xb4,0xba}, /*                            */
            {0xe3,0x5f,0xb3,0xb5,0xbb}, /*                            */
            {0xe4,0x9c,0xb4,0xb6,0xbc}, /*                            */
            {0xe5,0xa1,0xb5,0xb7,0xbd}, /*                            */
            {0xe6,0xb1,0xb6,0xb8,0xbe}, /*                            */
            {0xe7,0xb2,0xca,0xb9,0xbf}, /*                            */
            {0xe8,0xca,0xcb,0xca,0xca}, /*                            */
            {0xe9,0xcb,0xcc,0xcb,0xcb}, /*                            */
            {0xea,0xcc,0xcd,0xcc,0xcc}, /*                            */
            {0xeb,0xcd,0xce,0xcd,0xcd}, /*                            */
            {0xec,0xce,0xcf,0xce,0xce}, /*                            */
            {0xed,0xcf,0xda,0xcf,0xcf}, /*                            */
            {0xee,0xda,0xdb,0xda,0xda}, /*                            */
            {0xef,0xdb,0xdc,0xdb,0xdb}, /*                            */
            {0xf0,0xdc,0xdd,0xdc,0xdc}, /*                            */
            {0xf1,0xdd,0xde,0xdd,0xdd}, /*                            */
            {0xf2,0xde,0xdf,0xde,0xde}, /*                            */
            {0xf3,0xdf,0xe1,0xdf,0xdf}, /*                            */
            {0xf4,0xea,0xea,0xea,0xea}, /*                            */
            {0xf5,0xeb,0xeb,0xeb,0xeb}, /*                            */
            {0xf6,0xec,0xec,0xec,0xec}, /*                            */
            {0xf7,0xed,0xed,0xed,0xed}, /*                            */
            {0xf8,0xee,0xee,0xee,0xee}, /*                            */
            {0xf9,0xef,0xef,0xef,0xef}, /*                            */
            {0xfa,0xfa,0xfa,0xfa,0xfa}, /*                            */
            {0xfb,0xfb,0xfb,0xfb,0xfb}, /*                            */
            {0xfc,0xfc,0xfc,0xfc,0xfc}, /*                            */
            {0xfd,0xfd,0xfd,0xfd,0xfd}, /*                            */
            {0xfe,0xfe,0xfe,0xfe,0xfe}, /*                            */
            {0xff,0xff,0xff,0xff,0xff}  /*                            */
} ;

/**********************************************************************/
