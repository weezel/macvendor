#ifndef _COMMON_H_
#define _COMMON_H_

#ifndef VENDORS_FILE
#if defined __OpenBSD__
#define VENDORS_FILE "/mnt/weezel/ohjelmointi/c/macvendor/vendors.txt"
#endif
#if defined __linux__
#define VENDORS_FILE "/home/weezel/ohjelmointi/c/macvendor/vendors.txt"
#endif
#else
#define VENDORS_FILE "vendors.txt"
#endif

#endif /* _COMMON_H_ */
