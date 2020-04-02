#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
!include <ntwin32.mak>

!IF "$(CFG)" == ""
CFG=driver - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to driver - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "driver - Win32 Debug" && "$(CFG)" != "driver - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "driver.mak" CFG="driver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "driver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "driver - Win32 Release" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "driver - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "driver - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\driver.exe"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\driver.pch"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\driver.exe"
	-@erase ".\WinDebug\remote.obj"
	-@erase ".\WinDebug\cleanup.obj"
	-@erase ".\WinDebug\initmain.obj"
	-@erase ".\WinDebug\driver.obj"
	-@erase ".\WinDebug\misc.obj"
	-@erase ".\WinDebug\audit.obj"
	-@erase ".\WinDebug\drivedlg.obj"
	-@erase ".\WinDebug\config.obj"
	-@erase ".\WinDebug\stdafx.obj"
	-@erase ".\WinDebug\initrun.obj"
	-@erase ".\WinDebug\initconf.obj"
	-@erase ".\WinDebug\driver.res"
	-@erase ".\WinDebug\driver.ilk"
	-@erase ".\WinDebug\driver.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\bankappd" /I "..\..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\bankappd" /I\
 "..\..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "NOWHAT=1" /D "_WINDOWS" /D "_AFXDLL" /D\
 "_MBCS" /Fp"$(INTDIR)/driver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/driver.res" /d "NOWHAT=1" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/driver.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:$(CPU)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 wsock32.lib ..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows /debug /machine:$(CPU)
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=wsock32.lib ..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/driver.pdb" /debug /machine:$(CPU)\
 /out:"$(OUTDIR)/driver.exe" 
LINK32_OBJS= \
	".\WinDebug\remote.obj" \
	".\WinDebug\cleanup.obj" \
	".\WinDebug\initmain.obj" \
	".\WinDebug\driver.obj" \
	".\WinDebug\misc.obj" \
	".\WinDebug\audit.obj" \
	".\WinDebug\drivedlg.obj" \
	".\WinDebug\config.obj" \
	".\WinDebug\stdafx.obj" \
	".\WinDebug\initrun.obj" \
	".\WinDebug\initconf.obj" \
	".\WinDebug\driver.res"

"$(OUTDIR)\driver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
	$(LINK32) -out:$@ $(LINK32_FLAGS) $(LINK32_OBJS)

!ELSEIF  "$(CFG)" == "driver - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\driver.exe"

CLEAN : 
	-@erase ".\WinRel\driver.exe"
	-@erase ".\WinRel\config.obj"
	-@erase ".\WinRel\driver.pch"
	-@erase ".\WinRel\cleanup.obj"
	-@erase ".\WinRel\initconf.obj"
	-@erase ".\WinRel\driver.obj"
	-@erase ".\WinRel\initmain.obj"
	-@erase ".\WinRel\drivedlg.obj"
	-@erase ".\WinRel\initrun.obj"
	-@erase ".\WinRel\stdafx.obj"
	-@erase ".\WinRel\audit.obj"
	-@erase ".\WinRel\remote.obj"
	-@erase ".\WinRel\misc.obj"
	-@erase ".\WinRel\driver.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\bankappd" /I "..\..\..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\bankappd" /I "..\..\..\..\..\include" /D\
 "NDEBUG" /D "WIN32" /D "NOWHAT=1"  /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/driver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/driver.res" /d "NOWHAT=1" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/driver.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:$(CPU)
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 wsock32.lib ..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows /machine:$(CPU)
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=wsock32.lib ..\..\..\..\..\lib\libengine.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/driver.pdb" /machine:$(CPU)\
 /out:"$(OUTDIR)/driver.exe" 
LINK32_OBJS= \
	".\WinRel\config.obj" \
	".\WinRel\cleanup.obj" \
	".\WinRel\initconf.obj" \
	".\WinRel\driver.obj" \
	".\WinRel\initmain.obj" \
	".\WinRel\drivedlg.obj" \
	".\WinRel\initrun.obj" \
	".\WinRel\stdafx.obj" \
	".\WinRel\audit.obj" \
	".\WinRel\remote.obj" \
	".\WinRel\misc.obj" \
	".\WinRel\driver.res"

"$(OUTDIR)\driver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "driver - Win32 Debug"
# Name "driver - Win32 Release"

!IF  "$(CFG)" == "driver - Win32 Debug"

!ELSEIF  "$(CFG)" == "driver - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "driver - Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\bankappd" /I\
 "..\..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "NOWHAT=1"  /D "_WINDOWS" /D "_AFXDLL" /D\
 "_MBCS" /Fp"$(INTDIR)/driver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\driver.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "driver - Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\bankappd" /I "..\..\..\..\..\include" /D\
 "NDEBUG" /D "WIN32" /D "NOWHAT=1"  /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/driver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\driver.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\driver.cpp

!IF  "$(CFG)" == "driver - Win32 Debug"

DEP_CPP_DRIVE=\
	".\stdafx.h"\
	".\driver.h"\
	".\drivedlg.h"\
	".\..\bankappd\remote.h"\
	".\misc.h"\
	".\config.h"\
	".\..\..\..\..\..\include\Uunix.h"\
	".\..\..\..\..\..\include\tmenv.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\driver.obj" : $(SOURCE) $(DEP_CPP_DRIVE) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


!ELSEIF  "$(CFG)" == "driver - Win32 Release"

DEP_CPP_DRIVE=\
	".\stdafx.h"\
	".\driver.h"\
	".\drivedlg.h"\
	".\..\bankappd\remote.h"\
	".\misc.h"\
	".\config.h"\
	".\..\..\..\..\..\include\Uunix.h"\

	

"$(INTDIR)\driver.obj" : $(SOURCE) $(DEP_CPP_DRIVE) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\drivedlg.cpp
DEP_CPP_DRIVED=\
	".\stdafx.h"\
	".\driver.h"\
	".\drivedlg.h"\
	".\..\bankappd\remote.h"\
	".\misc.h"\
	".\config.h"\
	".\initmain.h"\
	".\audit.h"\
	".\cleanup.h"\
	

"$(INTDIR)\drivedlg.obj" : $(SOURCE) $(DEP_CPP_DRIVED) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\driver.rc
DEP_RSC_DRIVER=\
	".\res\driver.ico"\
	".\res\driver.rc2"\
	
.\res\driver.ico: .\res\driver.ico.z uudecode.exe
   uudecode.exe .\res\driver.ico.z
   copy driver.ico .\res\driver.ico
   del driver.ico

uudecode.exe: uudecode.c
   $(CPP) -c uudecode.c
   link -out:uudecode.exe -subsystem:console uudecode.obj libc.lib kernel32.lib

"$(INTDIR)\driver.res" : $(SOURCE) $(DEP_RSC_DRIVER) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt

!IF  "$(CFG)" == "driver - Win32 Debug"

!ELSEIF  "$(CFG)" == "driver - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\misc.cpp
DEP_CPP_MISC_=\
	".\stdafx.h"\
	".\driver.h"\
	".\drivedlg.h"\
	".\..\bankappd\remote.h"\
	".\misc.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\config.h"\
	".\initconf.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\initmain.cpp
DEP_CPP_INITM=\
	".\stdafx.h"\
	".\driver.h"\
	".\initmain.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\initconf.h"\
	".\initrun.h"\
	".\misc.h"\
	

"$(INTDIR)\initmain.obj" : $(SOURCE) $(DEP_CPP_INITM) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\initconf.cpp

!IF  "$(CFG)" == "driver - Win32 Debug"

DEP_CPP_INITC=\
	".\stdafx.h"\
	".\driver.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\initconf.h"\
	".\misc.h"\
	".\..\..\..\..\..\include\Uunix.h"\
	".\..\..\..\..\..\include\tmenv.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\initconf.obj" : $(SOURCE) $(DEP_CPP_INITC) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


!ELSEIF  "$(CFG)" == "driver - Win32 Release"

DEP_CPP_INITC=\
	".\stdafx.h"\
	".\driver.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\initconf.h"\
	".\misc.h"\
	".\..\..\..\..\..\include\Uunix.h"\
	

"$(INTDIR)\initconf.obj" : $(SOURCE) $(DEP_CPP_INITC) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\config.cpp

!IF  "$(CFG)" == "driver - Win32 Debug"

DEP_CPP_CONFI=\
	".\stdafx.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\misc.h"\
	".\..\..\..\..\..\include\Uunix.h"\
	".\..\..\..\..\..\include\tmenv.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\config.obj" : $(SOURCE) $(DEP_CPP_CONFI) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


!ELSEIF  "$(CFG)" == "driver - Win32 Release"

DEP_CPP_CONFI=\
	".\stdafx.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\misc.h"\
	".\..\..\..\..\..\include\Uunix.h"\
	

"$(INTDIR)\config.obj" : $(SOURCE) $(DEP_CPP_CONFI) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\initrun.cpp
DEP_CPP_INITR=\
	".\stdafx.h"\
	".\driver.h"\
	".\initrun.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\misc.h"\
	

"$(INTDIR)\initrun.obj" : $(SOURCE) $(DEP_CPP_INITR) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\audit.cpp
DEP_CPP_AUDIT=\
	".\stdafx.h"\
	".\driver.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\misc.h"\
	".\audit.h"\
	

"$(INTDIR)\audit.obj" : $(SOURCE) $(DEP_CPP_AUDIT) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cleanup.cpp
DEP_CPP_CLEAN=\
	".\stdafx.h"\
	".\driver.h"\
	".\..\bankappd\remote.h"\
	".\config.h"\
	".\misc.h"\
	".\cleanup.h"\
	

"$(INTDIR)\cleanup.obj" : $(SOURCE) $(DEP_CPP_CLEAN) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=..\bankappd\remote.cpp
DEP_CPP_REMOT=\
	".\..\bankappd\stdafx.h"\
	".\..\bankappd\remote.h"\
	".\..\bankappd\misc.h"\
	

"$(INTDIR)\remote.obj" : $(SOURCE) $(DEP_CPP_REMOT) "$(INTDIR)"\
 "$(INTDIR)\driver.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
