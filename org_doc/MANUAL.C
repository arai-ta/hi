SYNOPSIS


Information

    (1) hi is a cui-based binary editor.
    (2) hi is able to edit both ordinary files and shared memory segments.
    (3) Shared memory access is direct.
    (4) Ordinary file access is indirect. Data is written via [:w] command.
    (5) Work area is dynamically allocated. Initial area is file size.
        (work area size is bounded)
    (6) Many character sets are supported: ASCII, Japanese-EUC, Shift-JIS,
        JIS, EBCDIC(K). Character set is changed via [:tr] command.


Synopsis.  It's easy

    The binary editor, hi, like vi, has both a command and an edit mode.
    The program starts in command mode. Edit mode is entered using any
    of the familiar vi key commands: [i], [I], [a], [A], or [R]. [Esc]
    terminates edit mode and resumes command mode.

    NOTE: [r] and [x] change only 1 byte, and therefore immediately return
          to command mode without needing to press [Esc].


Usage

    hi { file [file...] | -m shmid [-m shmid...] | -m shmid[,shmid...] }
       [--help] [--version]

    parameter
        file [file...]
            file     : Ordinary file name. Next file reached via [:n].
        -m shmid [ -m shmid...]
            -m shmid : Shared memory segment ID. Next segment: [:n].
        -m shmid[,shmid...]
            -m shmid : Shared memory segment ID. It's like a only once segment.
        --help
            Display online manual (ignores other command line options).
        --version
            Display version information.


Motion

    (1) Command mode.

        [h] or [left allow]  : Cursor left
        [j] or [down allow]  : Cursor down
        [k] or [up allow]    : Cursor up
        [l] or [right allow] : Cursor right
        [Ctrl] + [f]         : Scroll down (page)
        [Ctrl] + [b]         : Scroll up (page)
        [Ctrl] + [d]         : Scroll down (half-page)
        [Ctrl] + [u]         : Scroll up (half-page)
        [Ctrl] + [a]         : move to cursor area
                               ( hex area <-> character area )
        [Ctrl] + [l]         : Refresh window
        [Ctrl] + [g]         : Display report on status line

        [:h]                 : Display online manual

        [:env]               : Display environment

        [:n]                 : Advance to next file in list
        [:n!]                : Advance to next file in list,
                               discarding any changes

        [:q]                 : Quit
        [:q!]                : Quit, discarding any changes
        [:w]                 : Write file
                               ( Shared memory is not supported )
        [:w (file)]          : Write to (file)
                               If format is ":(adr1),(adr2)w (file) then
                               write from adr1 to adr2 to (file)
                               eg) :^,+10w ~/tmp/foo
                                   :.,$w %_bk
        [:r (file)]          : Read (file) into file currently in editor
                               eg) :r ~/tmp/foo
                                   :r %_bk
        [:wq]                : Write file and quit
                               ( Shared memory is not supported )
        [:p (file)]          : Write screen image to (file)
        [:pa (file)]         : Append screen image to (file)

        [:pr (byte)(format)] : Print data(byte) according to format
                                 byte   : 1/2/4/n   : target data
                                 format : b/o/u/d/p : (b)inary/(o)ctal/
                                                      (u)nsigned decimal/
                                                      (d)ecimal/(p)pack
                               ex) :pr 4d is int argument is converted
                                          to signed decimal notation
                               note) byte(n) is packed only

        [:tr A]              : Change character area -> ASCII
        [:tr E]              : Change character area -> Japanese-EUC
        [:tr S]              : Change character area -> Shift-JIS
        [:tr J]              : Change character area -> JIS
        [:tr BI]             : Change character area -> EBCDIC IBM
        [:tr BH]             : Change character area -> EBCDIK HITACHI
        [:tr BN]             : Change character area -> EBCDIC NEC
        [:tr BO]             : Change character area -> EBCDIC

        [:sr=on]             : Search also in reverse
        [:sr=off]            : Do not search in reverse

        [:^]                 : Move cursor position to top of data
        [:$] or [G]          : Move cursor position to end of data
        [:(address)]         : Move cursor position to given address
                               eg) '^' is top of file.
                                   '.' is current of file.
                                   '$' is last of file.
                                   '^+10' is 10.
        [:(adr1),(adr2)x]    : delete from adr1 to adr2
                               ( Shared memory is not supported )
        [:(address)x]        : delete 1 byte at address
                               ( Shared memory is not supported )
        [(number)x]          : Delete number bytes
                               ( Shared memory is not support )

        [:!(shell-command)]  : Execute shell command

        [/(search-string)]   : Forward string search and cursor move
                                 Character data is ????
                                 Hex data is 0x????
        [?(search-string)]   : Reverse string search and cursor move
                                 Character data is ????
                                 Hex data is 0x????
        [n]                  : Repeat forward or reverse search

        [.]                  : Repeat previous command ( [x] only )
                               ( Shared memory is not supported )

    (2) Edit mode.

        [i]                  : Insert data at byte position
                               ( Shared memory is not supported )
        [I]                  : Insert data at top of file
                               ( Shared memory is not supported )
        [a]                  : Append Data at byte position
                               ( Shared memory is not supported )
        [A]                  : Append data to end of file
                               ( Shared memory is not supported )
        [r]                  : Replace one byte of data
        [R]                  : Replace more than one byte of data
        [x]                  : Delete one byte of data
                               ( Shared memory is not supported )


ENVIRONMENT

    Binary editor (hi)'s environment definition ( .hirc ) sample file.
    Please copy to your home directory and modify as needed.

      :set TR=(a/e/s/j/bi/bh/bn/bo)
                         character area language
         default=a         a   : (ascii)        
                           e   : (japanese-euc)
                           s   : (shift-jis)
                           j   : (jis)
                           bi  : (ebcdic ibm)
                           bh  : (ebcdik hitachi)
                           bn  : (ebcdic nec)
                           bo  : (ebcdic)
 
      :set CP=(h/c)      cursor position
         default=h         h   : (hex-area)
                           c   : (character-area)
 
      :set SR=(on/off)   search in reverse
         default=on        on  : (reverse search-string)
                           off : (not reverse)

      :set EO=(on/off)   upon abort, report to environment
         default=on        on  : (report to environment)
                           off : (not report to environment)

      :set AS=size       allocate size of work area
         default=1024
 
      :set MS=size       maximum allocateable size of work area
         default=2147483647
               (=0x7fffffff)


BUGS

    (1) Undo command is not supported.


LICENSE

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.


ADDRESS

    The latest version is
       URL    : http://www2.plala.or.jp/mita/download/hi/info_en.html
       E-Mail : mita@maroon.plala.or.jp


SPECIAL THANKS

    Test and porting with me, special thanks!
    Dear Michael Leslie, special thanks to attached a patch to MANUAL.C
    with corrections to English.

                    2000/10/17 Kazunori Mita(mita@maroon.plala.or.jp)
