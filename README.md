**WARNING:** CHIN does not work with semantic URLs. Link to the thread should end with a number without "/". 

**WARNING:** Installation instructions have changed! Please check them out.

**CHIN** is a small program that downloads images from specified 4chan thread using libcurl or wget.

**CCHIN** is another program that uses chin to download images off entire board.



Features
========
* Can be used to download images from single thread or entire board
* Doesn't redownload existing images, running it again would simply update already existing image database
* Uses either wget or libcurl(default), no other dependencies
* Partial text archiving (keeps .json files)

CHIN
====
**Usage: chin URL DIR**

Downloads images off specified 4chan thread to ~/chin/**DIR**

Uses thread number as default directory name

CCHIN
=====
**Usage: cchin URL DIR**

Downloads all images off specified 4chan board to ~/cchin/**DIR**.

**URL** is a link to the board without '/' at the end, I.E.  4chan.org/g

**DIR** is directory name inside ~/cchin

Examples:
=========
**chin https://boards.4chan.org/wg/res/12345 wallpapers**

Downloads all images from thread number 12345 to ~/chin/wallpapers

**cchin 4chan.org/w anime_wallpapers**

Downloads images from all current threads on /wg/ to ~/**cchin**/anime_wallpapers

Installation:
=============
Download and compile the sources, copy resulting executable files to /usr/bin.
```
git clone https://github.com/void-null/chin
cd chin
gcc chin.c -lcurl -o chin
gcc cchin.c -lcurl -o cchin
sudo cp ./chin /usr/bin/chin
sudo cp ./cchin /usr/bin/cchin
```

Facts:
======

* **CHIN** stands for **CHIN Hoards Images Nicely**
* Shell script with same functionaity would contain less than 10 strings
* Ability to locally archive images off entire board is surpisingly useful and useless at the same time

Feedback:
========
If you encounter any issues, want to make a suggestion or to provide feedback - please contact me
here or at my e-mail: **voidnull_at_cock.li**
