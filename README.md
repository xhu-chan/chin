**Chin** is a small program that downloads images from specified 4chan thread using wget.

**Cchin** is another program that uses chin to download images off entire board.

**WARNING:** cchin requires chin executable file to be in /usr/bin/, that is intended behaviour and is going to be changed in near future 

CHIN
====
**Usage: chin [URL] [DIR - optional]**

Downloads images off specified 4chan thread to ~/chin/**[DIR]**

Uses thread number as default directory name

CCHIN
=====
**Usage: cchin [URL] [DIR]**

Downloads all images off specified 4chan board to ~/cchin/**[DIR]**.

**[URL]** is a link to the board, I.E.  4chan.org/g

**[DIR]** is directory name inside ~/cchin

Examples:
=========
**chin https://boards.4chan.org/wg/res/12345 wallpapers**

Downloads all images from thread number 12345 to ~/chin/wallpapers

**cchin 4chan.org/w anime_wallpapers**

Downloads images from all current threads on /wg/ to ~/**cchin**/anime_wallpapers

Installation:
=============
Compile the sources of both files and copy executables to /usr/bin.
```
git clone https://github.com/void-null/chin
cd chin
gcc chin.c -o chin
gcc cchin.c -o cchin
sudo cp ./chin /usr/bin/chin
sudo cp ./cchin /usr/bin/cchin
```
