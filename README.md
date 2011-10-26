# Introduction
### What is MAC-address?
Every network card has a MAC-address which distinctly identifies the device.
The address is divided to six octets and usually octet dividers are expressed
as colons or dashes. The first three octets identifies the vendor. Vendors are
contolled by IEEE standards association.

# Purpose of the program
At times there is a need to check the vendor of an associated client in LAN or
just to check the vendor in generally.The first implementation of this program
was done in Python but I wanted to refresh my memory and decided to port the
program to C language also. Program uses CURL library for fetching the newest
vendors file. CURL lib was chosen since it's well written, BSD licensed and
actively developed.

# Install
Curl developer libraries are needed and therefore those should be present. In
Debian based system system check can be done with the following command:

	dpkg -l |grep -i libcurl |grep dev

If if returns nothing, your system likely lacks support. In Ubuntu 11.04
functionality can be achiewed this way:

	sudo apt-get install libcurl4-gnutls-dev

Then follow the steps below.

Get the source code:

	git clone git@github.com:weezel/macvendor.git

Go to source code directory:

	cd macvendor

Install `macvendor` binary under $HOME/bin

	make

# Usage
Search vendor for `00:00:00:00:00:00` MAC-address:

	macvendor 00:00:00:00:00:00

Update vendors database:

	macvendor -u


# TODO
### Done
	[X] Use getopts and add functionality for update switch

	[X] Create fetcher (curl one is ready, TODO independent fetcher?)

	[X] Separate .c to .c + .h

### High priority
	[ ] Replace strlen() calls from wrong places

	[ ] unsigned int -> size_t

	[ ] check comparefile function, looks suspicious

### Normal priority
	[ ] Use file descriptors

	[ ] Use some sane data structure for storing the addresses

### Low priority
	[ ] Check output from splint
