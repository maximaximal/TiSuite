TiUtils
=======

This directory contains all utility features of the suite (like an emulator, serial connection, other libraries, ...).

TilEm
-----

To make the emulator work on linux, the makefile in the gui subdirectory was changed. `-lm` was added to the libs according to [a stackoverflow answer](http://superuser.com/a/708921). 

In addition, the linking directory was changed to a relative path using `-Wl,-R,'$ORIGIN/../lib'`.
