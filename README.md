# WincastCE
Experimental Desktop Environment Shell for Windows CE on Sega Dreamcast
------
## How to setup
1.) Place the "211INC" folder in the directory above your Windows CE Dreamcast SDK include directory, which is typically C:\WCEDreamcast\inc. Assuming default install directory, place "211INC" in C:\WCEDreamcast\211INC

2.) Add contents of "lib" folder to a new folder in WCE SDK library directory, typically C:\WCEDreamcast\lib. For example, place the contents of "lib" in C:\WCEDreamcast\lib\WincastCE

3.) Open the "ceshell.dsw" project file

4.) Go to "Tools" --> "Options", then the "Directories" tab

5.) Set "C:\WCEDreamcast\211INC" as the highest priority include directory

6.) Set "C:\WCEDreamcast\lib\WincastCE" as a library directory, priority shouldn't matter

After that, WincastCE.exe should be ready to compile without errors
-------

Right now as of writing this, the Desktop Enviroment Shell doesn't just "work". Research for loading properly is in progress

Participate in development here
http://assemblergames.com/l/threads/windows-ce-os-gui-shell-is-possible.64930/
