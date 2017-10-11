# makefile
# date 2017-09-05
# Copyright 2017 Mamoru kaminaga
CC = C:\"Program Files (x86)"\"Microsoft Visual Studio"\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX86\x86\cl.exe
LINK = C:\"Program Files (x86)"\"Microsoft Visual Studio"\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX86\x86\link.exe
OUTDIR = build
TARGET = test.exe
PDB = test.pdb
MAP = test.map
RES =
SRC = test.cc util.cc sat.cc
OBJ = $(OUTDIR)/test.obj $(OUTDIR)/util.obj $(OUTDIR)/sat.obj
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib"\
"advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib"\
"odbc32.lib" "odbccp32.lib" "tle/v2.1.0/tle.lib"

# Debug build
CPPFLAGS = /nologo /W4 /Zi /O2 /MT /D"UNICODE" /D"_UNICODE" /D"DEBUG"\
	/EHsc /Fd"$(OUTDIR)/" /D"NOMINMAX" /D"WIN32" /D"WIN32"
LFLAGS = $(LIBS) /NOLOGO /SUBSYSTEM:CONSOLE /PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)

.cc{$(OUTDIR)}.obj:
	@[ -d $(OUTDIR) ] || mkdir $(OUTDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OUTDIR)\\" /c $<
