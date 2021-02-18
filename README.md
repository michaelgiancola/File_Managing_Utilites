# File_Managing_Utilites
Used [VirtualBox](https://www.virtualbox.org/) virtual machine to access Linux-based [Raspberry Pi Desktop](https://www.raspberrypi.org/software/raspberry-pi-desktop/) C++ compiler to create custom system utilities for file management.

## Practical Take-Away Experience
*	C++
*	Virtual machines ([VirtualBox](https://www.virtualbox.org/))
*	Object-oriented programming, language constructs, classes, and data types
*	Linux manual pages and documentation
*	Linux-based [Raspberry Pi Desktop](https://www.raspberrypi.org/software/raspberry-pi-desktop/) system and services
*	ssh, scp, sftp

## Utilities
*	mymv ----- Used to move and rename files ([mv](https://manpages.debian.org/stretch/coreutils/mv.1.en.html))
*	mycp ------ Used to copy files from source to destination named as parameters ([cp](https://manpages.debian.org/stretch/coreutils/cp.1.en.html))
*	myls ------- Used to list contents of directories and list names of other files ([ls](https://manpages.debian.org/stretch/coreutils/ls.1.en.html))
*	myls–l ----- Used to list long form of ls (name, permissions, owner, group, size, time) ([ls](https://manpages.debian.org/stretch/coreutils/ls.1.en.html))
*	mycat ----- Used to display contents of files named as parameters ([cat](https://manpages.debian.org/stretch/coreutils/cat.1.en.html))
*	myrm ----- Used to remove files named as parameters ([rm](https://manpages.debian.org/stretch/coreutils/rm.1.en.html))
*	mydiff ----- Used to compare two files named as parameters ([diff](https://manpages.debian.org/buster/diffutils/diff.1.en.html))
*	mystat ---- Used to output all information of file named as parameter ([stat](https://manpages.debian.org/buster/coreutils/stat.1.en.html))

Commands also support full error tracking and reporting to the user.

## Structure
This project was designed through a file manager class that encapsulates both file information pulled from the system, as well as operations that can be performed on said files. Each file manager instance handles a single file, which includes the following information:
*	Name
*	Type
*	Size
*	Owner
*	Group
*	Permissions
*	Access time
*	Modification time
*	Status change time
*	Block size
*	Children
*	Error number
