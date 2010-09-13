# Microsoft Developer Studio Project File - Name="library" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **
# TARGTYPE "Win32 (x86) Application" 0x0101
CFG=library - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "library.mak."
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "library.mak" CFG="library - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "library - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "library - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
!IF  "$(CFG)" == "library - Win32 Debug"
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Od /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /YX /FD /c /Gm /ZI /GZ /Zm1024
# ADD CPP /nologo /MTd /W3 /GR /GX /Od /I  /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /D "_UNICODE" /D "UNICODE" /FD /c /Zm1024 /Gm /ZI /GZ 
# ADD BASE MTL /nologo /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /mktyplib203 /win32
# ADD MTL /nologo /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG
# ADD RSC /l 0x40c /d JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 "C:\Program Files\Microsoft Visual Studio\VC98\LIB\shell32.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  /debug /nologo /machine:I386 /out:".\Debug\library.exe" /subsystem:windows 
!ELSEIF  "$(CFG)" == "library - Win32 Release"
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG /YX /FD /c  /Zm1024
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I  /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG /D "_UNICODE" /D "UNICODE" /FD /c /Zm1024  
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG /mktyplib203 /win32
# ADD MTL /nologo /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG
# ADD RSC /l 0x40c /d JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 "C:\Program Files\Microsoft Visual Studio\VC98\LIB\shell32.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  /nologo /machine:I386 /out:".\Release\library.exe" /subsystem:windows 
!ENDIF
# Begin Target
# Name "library - Win32 Debug"
# Name "library - Win32 Release"
# Begin Group "library"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Source"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# End Group
# Begin Group "Juce Library Code"
# Begin Source File
SOURCE="..\..\JuceLibraryCode\AppConfig.h"
# End Source File
# Begin Source File
SOURCE="..\..\JuceLibraryCode\JuceHeader.h"
# End Source File
# Begin Source File
SOURCE="..\..\JuceLibraryCode\JuceLibraryCode1.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\JuceLibraryCode\JuceLibraryCode2.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\JuceLibraryCode\JuceLibraryCode3.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\JuceLibraryCode\JuceLibraryCode4.cpp"
# End Source File
# End Group
# End Target
# End Project
