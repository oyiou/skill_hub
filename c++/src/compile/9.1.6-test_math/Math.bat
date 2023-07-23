> cl /LDd Math.c

> dumpbin /EXPORTS Math.dll

> cl /c TestMath.c

> link TextMath.obj Math.dll

> cl RumtimeLoadDLL.c

