; example1.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply 
; prompts the user asking them where to install, and drops a copy of example1.nsi
; there. 

;--------------------------------

; The name of the installer
Name "qscript-installer"

; The file to write
OutFile "qscript-installer.exe"
SETCOMPRESS AUTO
SetCompressor lzma

; THE DEFAULT INSTALLATION DIRECTORY
;INSTALLDIR $DESKTOP\QSCRIPT\QSCRIPT-0.19
INSTALLDIR "F:\QSCRIPT\qscript-0.24"
LICENSETEXT "MINGW AND QSCRIPT ARE DISTRIBUTED UNDER THE GNU GPL. Please read the license below."
LicenseData "gnu-gpl-v2.txt"

; Request application privileges for Windows Vista
;RequestExecutionLevel user
RequestExecutionLevel admin

!include "EnvVarUpdate.nsh"

;--------------------------------

; Pages


Page license
Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  WriteRegStr HKCU SOFTWARE\QScript "Install_Dir" "$INSTDIR"
  WriteRegStr HKCU SOFTWARE\QScript "QSCRIPT_HOME" "$INSTDIR"
  WriteRegStr HKLM SOFTWARE\QScript "Install_Dir" "$INSTDIR"
  WriteRegStr HKLM SOFTWARE\QScript "QSCRIPT_HOME" "$INSTDIR"
  ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\..\MinGW-foo7\bin;$INSTDIR\..\MinGW-foo7\msys\1.0\bin;$INSTDIR\..\usr\bin;$INSTDIR\..\usr\lib;$INSTDIR\bin" ; Append  
  ${EnvVarUpdate} $0 "QSCRIPT_HOME" "A" "HKLM" "$INSTDIR" ; Append  
  
  ; Put file there
  SetOutPath "$INSTDIR\.."
  File gnu-gpl-v2.txt
  ;File /r MinGW-foo7
  ;SetOutPath "$INSTDIR\.."
  ;File /r usr
  ;SetOutPath "$INSTDIR\.."
  File /r qscript-0.24
  
SectionEnd ; end the section
