# Microsoft Developer Studio Project File - Name="Slow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **
# TARGTYPE "Win32 (x86) Application" 0x0101
CFG=Slow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Slow.mak."
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Slow.mak" CFG="Slow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Slow - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Slow - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
!IF  "$(CFG)" == "Slow - Win32 Debug"
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
# ADD CPP /nologo /MTd /W3 /GR /GX /Od /I ../../src /I ../../../juce/src /I ../../../juce /I ../.. /I ../../../mpg123/src /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /D "_UNICODE" /D "UNICODE" /FD /c /Zm1024 /Gm /ZI /GZ 
# ADD BASE MTL /nologo /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /mktyplib203 /win32
# ADD MTL /nologo /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG
# ADD RSC /l 0x40c /d JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D _DEBUG
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 "C:\Program Files\Microsoft Visual Studio\VC98\LIB\shell32.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  /debug /nologo /machine:I386 /out:".\Debug\SlowBurn.exe" /subsystem:windows 
!ELSEIF  "$(CFG)" == "Slow - Win32 Release"
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
# ADD BASE CPP /nologo /W3 /GX /O3 /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG /YX /FD /c  /Zm1024
# ADD CPP /nologo /MT /W3 /GR /GX /O3 /I ../../src /I ../../../juce/src /I ../../../juce /I ../../../mpg123/src /D JUCER_MSVC6_734A9119 /D WIN32 /D _WINDOWS /D NDEBUG /D "_UNICODE" /D "UNICODE" /FD /c /Zm1024  
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
# ADD LINK32 "C:\Program Files\Microsoft Visual Studio\VC98\LIB\shell32.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  /nologo /machine:I386 /out:".\Release\SlowBurn.exe" /subsystem:windows 
!ENDIF
# Begin Target
# Name "Slow - Win32 Debug"
# Name "Slow - Win32 Release"
# Begin Group "Slow"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Source"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "audio"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "format"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "mpg123"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Copier.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Copier.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\CreateReader.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\CreateReader.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Format.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Manager.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Mpg123.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Mpg123.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\NewHandle.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\NewHandle.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Reader.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Reader.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Tags.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\format\mpg123\Tags.h"
# End Source File
# End Group
# End Group
# Begin Source File
SOURCE="..\..\src\rec\audio\stretch\StretchOnce.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\stretch\StretchOnce.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\stretch\SimpleStretcher.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\audio\stretch\SimpleStretcher.h"
# End Source File
# End Group
# Begin Group "ammf_scaler"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\AudioResampler.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\AudioResampler.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\AudioTimeScaler.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\AudioTimeScaler.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\hfft.c"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\hfft.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\mfAlloc.c"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\mfAlloc.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\mfGlobals.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\mfMacros.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\ammf_scaler\mfMath.h"
# End Source File
# End Group
# Begin Group "app"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE="..\..\src\rec\app\RecApplication.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\app\RecContainer.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\app\RecWindow.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\app\RecWindow.h"
# End Source File
# End Group
# Begin Group "base"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE="..\..\src\rec\base\basictypes.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\base\build_config.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\base\port.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\base\scoped_ptr.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\base\string_piece.h"
# End Source File
# End Group
# Begin Group "components"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE="..\..\src\rec\components\AudioSetupPage.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\AudioSetupPage.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\FileBrowserPage.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\FileBrowserPage.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\MainPageComponent.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\MainPageComponent.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\MainPageK.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\MainPageK.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\MainPageJ.cpp"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\components\MainPageJ.h"
# End Source File
# End Group
# Begin Group "util"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE="..\..\src\rec\util\Wrapper.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\util\locker.h"
# End Source File
# Begin Source File
SOURCE="..\..\src\rec\util\math.h"
# End Source File
# End Group
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
SOURCE="..\..\JuceLibraryCode\JuceLibraryCode.cpp"
# End Source File
# End Group
# End Target
# End Project
