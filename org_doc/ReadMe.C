
            README   - binary editor Version 2.2 Release 2 -


Table of Contents

    1.  Introduction
    2.  Synopsis
    3.  Support
    4.  Install files
    5.  Installation
    6.  Uninstallation
    7.  Usage
    8.  Setup
    9.  License
    10. Address
    11. Porting
    12. Special thanks


1. Introduction.

    I want to cui-based binary editor. It's must are display to hex
    and character. I try searche it for internet. I din't find it.
    Made it by own.


2. Synopsis.

    This program is a cui-based binary editor, hi, like vi, has both
    a command and an edit mode. hi is able to edit both ordinary files
    and shared memory segments.
    The program starts in command mode. Edit mode is entered using any
    of the familiar vi key commands: [i], [I], [a], [A], or [R]. [Esc]
    terminates edit mode and resumes command mode.
    Many character sets are supported: ASCII, Japanese-EUC, Shift-JIS,
    JIS, EBCDIC(K). Character set is changed via [:tr] command.
    The program is able to edit both character and hex-code.

    NOTE: [r] and [x] change only 1 byte, and therefore immediately
          return to command mode without needing to press [Esc].


3. Support.

    First build OS   : TurboLinux 2.0 (Kernel 2.0.33) i386
    Later build OS   : TurboLinux 6.0 (Kernel 2.2.13-33) Pentium(i586)
    Build Language   : ANSI standard C programs. Comment is Japanese EUC
    Test             : TurboLinux 6.0 (Kernel 2.2.13-33) Pentium(i586)
    Libraly          : ncurses-5.0-11
                     : termcap-11.0.1-1
                     : gawk-3.0.4-2
                     : glibc-2.1.2-19
                     : gcc-2.95.2-1
                     : gmake-3.78.1
    Others           : Window-size is more 76x4


4. Install files.

     (1) MANUAL.C ------------- Manual(English)
     (2) MANUAL.EUC ----------- Manual(Japanese-EUC)
     (3) MANUAL.SJIS ---------- Manual(Shift-JIS)
     (4) Makefile ------------- Makefile
     (5) ReadMe.C ------------- README(English)
     (6) ReadMe.EUC ----------- README(Japanese-EUC)
     (7) ReadMe.SJIS ---------- README(Shift-JIS)
     (8) Release.C ------------ Release information(English)
     (9) Release.EUC ---------- Release information(Japansese-EUC)
    (10) Release.SJIS --------- Release information(Shift-JIS)
    (11) conf ----------------- Configuration directory
    (12) head ----------------- Header file directory
    (13) load ----------------- Load-module directory
    (14) obj ------------------ Object-module directory
    (15) src ------------------ Source-code directory
    (16) .hirc ---------------- Environment file (sample)


5. Installation.

    5.1 tgz version

        cd /usr/local/lib (*1)
        gunzip -c hi-2.2-2.src.tgz | tar xvf -
        ln -sf hi-2.2-1 hi
        cd /usr/local/lib/hi
        make init
        make config
        make clean
        make all
        make install

        (*1) If hi setup directory changed, setup your configuration.

    5.2 rpm (binary package) version

        rpm -ivh hi-2.2-2.i386.rpm

    5.3 rpm (source package) version

        rpm --rebuild hi-2.2-2.src.rpm


6. Uninstallation.

    6.1 tgz version

        cd /usr/local/lib/hi (*1)
        make uninstall
        cd ..
        rm -f ./hi
        rm -rf ./hi-2.2-2

        (*1) If hi setup directory changed, setup your configuration.

    6.2 rpm (binary package) version

        rpm -e hi-2.2-2


7. Usage.

    Prease look at MANUAL.?


8. Setup

    Added $PATH(The search path for commands) : /usr/local/bin
    * If hi install directory changed, added your directory.

    ex) Installing module under /home/guest/bin
       export PATH=$PATH:/home/guest/bin

    Binary editor (hi)'s environment definition ( .hirc ) sample file.
    Please copy to your home directory and modify as needed.


9. License

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.


10. Address

    The latest version is
       URL    : http://www2.plala.or.jp/mita/download/hi/info_en.html
       E-Mail : mita@maroon.plala.or.jp


11. Porting

    I want to porting information. If success to build, mail to me.
    If you found some bugs, report to bug information.


12. Special thanks

    Test and porting with me, special thanks!
    Dear Michael Leslie, special thanks to attached a patch to MANUAL.C
    with corrections to English.

                    2000/10/17 Kazunori Mita(mita@maroon.plala.or.jp)
