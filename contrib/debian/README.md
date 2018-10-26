
Debian
====================
This directory contains files used to package zijad/zija-qt
for Debian-based Linux systems. If you compile zijad/zija-qt yourself, there are some useful files here.

## zija: URI support ##


zija-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install zija-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your zijaqt binary to `/usr/bin`
and the `../../share/pixmaps/zija128.png` to `/usr/share/pixmaps`

zija-qt.protocol (KDE)

