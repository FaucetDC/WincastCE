# Microsoft Developer Studio Project File - Name="ceshell" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=ceshell - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ceshell.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ceshell.mak" CFG="ceshell - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ceshell - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "ceshell - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ceshell - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredllmax.lib shexec.lib shell32.lib corelibc.lib comctl32.lib GWESTUBS.lib gwesmain.lib Wavelib.lib getpower.lib Acmdwrap.lib Msgbeep.lib shlwapi.lib coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /out:"WCESH4Rel/WincastCE.exe" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ceshell - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD CPP /nologo /Qsh4 /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredllmax.lib shexec.lib shell32.lib corelibc.lib comctl32.lib GWESTUBS.lib gwesmain.lib Wavelib.lib getpower.lib Acmdwrap.lib Msgbeep.lib shlwapi.lib coredll.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /out:"WCESH4Dbg/WincastCE.exe" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ceshell - Win32 (WCE SH4) Release"
# Name "ceshell - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ALTTAB.CPP
DEP_CPP_ALTTA=\
	".\minshell.h"\
	".\minshrc.h"\
	{$(INCLUDE)}"kfuncs.h"\
	
NODEP_CPP_ALTTA=\
	".\bgapi.h"\
	".\funcs.h"\
	".\indbase.h"\
	".\ipapi.h"\
	".\oolhelp.h"\
	".\syscall.h"\
	".\T\211INC\mwinbase.h"\
	".\T\211INC\pwinbase.h"\
	".\T\211INC\winbase.h"\
	".\T\211INC\windows.h"\
	".\windbas.h"\
	
# End Source File
# Begin Source File

SOURCE=.\HOUSEKP.CPP
DEP_CPP_HOUSE=\
	".\minshell.h"\
	".\minshrc.h"\
	
NODEP_CPP_HOUSE=\
	".\T\211INC\battery.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MINDESKT.CPP
DEP_CPP_MINDE=\
	".\minshell.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MINSHELL.CPP
DEP_CPP_MINSH=\
	".\minshell.h"\
	{$(INCLUDE)}"winuser.h"\
	
NODEP_CPP_MINSH=\
	".\eybd.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MINTASK.CPP
DEP_CPP_MINTA=\
	".\minshell.h"\
	{$(INCLUDE)}"winuser.h"\
	
NODEP_CPP_MINTA=\
	".\eybd.h"\
	
# End Source File
# Begin Source File

SOURCE=.\SHUTILS.CPP
NODEP_CPP_SHUTI=\
	".\ipapi.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\BLOW.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\BVERYLOW.ICO
# End Source File
# Begin Source File

SOURCE=.\MINSHELL.RC
# End Source File
# Begin Source File

SOURCE=.\RES\MVERYLOW.ICO
# End Source File
# End Group
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Target
# End Project
