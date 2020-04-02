#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
!include <ntwin32.mak>

!IF "$(CFG)" == ""
CFG=bankappd - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to bankappd - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "bankappd - Win32 Debug" && "$(CFG)" !=\
 "bankappd - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "bankappd.mak" CFG="bankappd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bankappd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "bankappd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "bankappd - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\bankappd.exe"

CLEAN : 
	-@erase ".\WinDebug\bankappd.exe"
	-@erase ".\WinDebug\stdafx.obj"
	-@erase ".\WinDebug\bankappd.obj"
	-@erase ".\WinDebug\bankappd.pch"
	-@erase ".\WinDebug\bankadlg.obj"
	-@erase ".\WinDebug\bankappd.res"
	-@erase ".\WinDebug\misc.obj"
	-@erase ".\WinDebug\remote.obj"
	-@erase ".\WinDebug\bankappd.ilk"
	-@erase ".\WinDebug\bankappd.pdb"
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "NOWHAT=1" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
#CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\..\include" /D "_DEBUG"
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\..\include" /D "_DEBUG"\
 /D "WIN32" /D "NOWHAT=1" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/bankappd.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/bankappd.res" /d "_DEBUG" /d "NOWHAT=1"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bankappd.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:$(CPU)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows /debug /machine:$(CPU)
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/bankappd.pdb" /debug /machine:$(CPU)\
 /out:"$(OUTDIR)/bankappd.exe" 
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/bankappd.obj" \
	"$(INTDIR)/bankadlg.obj" \
	"$(INTDIR)/misc.obj" \
	"$(INTDIR)/remote.obj" \
	"$(INTDIR)/bankappd.res"

"$(OUTDIR)\bankappd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
	$(LINK32) -out:$@ $(LINK32_FLAGS) $(LINK32_OBJS)

!ELSEIF  "$(CFG)" == "bankappd - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\bankappd.exe"

CLEAN : 
	-@erase ".\WinRel\bankappd.exe"
	-@erase ".\WinRel\stdafx.obj"
	-@erase ".\WinRel\bankappd.obj"
	-@erase ".\WinRel\bankappd.pch"
	-@erase ".\WinRel\bankadlg.obj"
	-@erase ".\WinRel\bankappd.res"
	-@erase ".\WinRel\misc.obj"
	-@erase ".\WinRel\remote.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
#CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\include" /D "NDEBUG" /D
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\include" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/bankappd.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/bankappd.res" /d "NDEBUG" /D "NOWHAT=1"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bankappd.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:$(CPU)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows /machine:$(CPU)
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/bankappd.pdb" /machine:$(CPU)\
 /out:"$(OUTDIR)/bankappd.exe" 
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/bankappd.obj" \
	"$(INTDIR)/bankadlg.obj" \
	"$(INTDIR)/misc.obj" \
	"$(INTDIR)/remote.obj" \
	"$(INTDIR)/bankappd.res"

"$(OUTDIR)\bankappd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
	$(LINK32) -out:$@ $(LINK32_FLAGS) $(LINK32_OBJS)

!ENDIF 

MTL_PROJ=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "bankappd - Win32 Debug"
# Name "bankappd - Win32 Release"

!IF  "$(CFG)" == "bankappd - Win32 Debug"

!ELSEIF  "$(CFG)" == "bankappd - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "bankappd - Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

#	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\..\include" /D "_DEBUG"
BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\..\include" /D "_DEBUG"\
 /D "WIN32" /D "NOWHAT=1" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/bankappd.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\bankappd.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "bankappd - Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\include" /D "NDEBUG" /D "WIN32"\
 /D "NOWHAT=1" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/bankappd.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\bankappd.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bankappd.cpp
DEP_CPP_BANKA=\
	".\stdafx.h"\
	".\bankappd.h"\
	".\remote.h"\
	".\misc.h"\
	".\bankadlg.h"\
	"..\..\..\..\..\include\Uunix.h"\
	"..\..\..\..\..\include\tmenv.h"\

"$(INTDIR)\bankappd.obj" : $(SOURCE) $(DEP_CPP_BANKA) "$(INTDIR)"\
 "$(INTDIR)\bankappd.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bankadlg.cpp
DEP_CPP_BANKAD=\
	".\stdafx.h"\
	".\bankappd.h"\
	".\remote.h"\
	".\misc.h"\
	".\bankadlg.h"\
	

"$(INTDIR)\bankadlg.obj" : $(SOURCE) $(DEP_CPP_BANKAD) "$(INTDIR)"\
 "$(INTDIR)\bankappd.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bankappd.rc
DEP_RSC_BANKAP=\
	".\res\bankappd.ico"\
	".\res\bankappd.rc2"\
	".\uudecode.c"
	

"$(INTDIR)\bankappd.res" : $(SOURCE) $(DEP_RSC_BANKAP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)

.\res\bankappd.ico: .\res\bankappd.ico.z uudecode.exe
	uudecode.exe .\res\bankappd.ico.z
	copy bankappd.ico .\res\bankappd.ico
	del bankappd.ico

uudecode.exe: uudecode.c
	$(CPP) -c uudecode.c
	link -out:uudecode.exe -subsystem:console uudecode.obj libc.lib kernel32.lib

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt

!IF  "$(CFG)" == "bankappd - Win32 Debug"

!ELSEIF  "$(CFG)" == "bankappd - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\misc.cpp
DEP_CPP_MISC_=\
	".\stdafx.h"\
	".\misc.h"\
	

"$(INTDIR)\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"\
 "$(INTDIR)\bankappd.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\remote.cpp
DEP_CPP_REMOT=\
	".\stdafx.h"\
	".\remote.h"\
	".\misc.h"\
	

"$(INTDIR)\remote.obj" : $(SOURCE) $(DEP_CPP_REMOT) "$(INTDIR)"\
 "$(INTDIR)\bankappd.pch"


# End Source File
# End Target
# End Project
################################################################################
