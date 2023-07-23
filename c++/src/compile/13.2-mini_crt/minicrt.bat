// make.bat

> cl /c /DWIN32 /GS- entry.c malloc.c printf.c stdio.c string.c

> lib entry.obj malloc.obj printf.obj stdio.obj string.obj /OUT:minicrt.lib

> cl /c /DWIN32 test.c

> link test.obj minicrt.lib kernel32.lib /NODEFAULTLIB /entry::mini_crt_entry

> dir test.exe

> dumpbin /IMPORTS test.exe