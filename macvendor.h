#ifndef _MACVENDOR_H_
#define _MACVENDOR_H_

#ifndef VENDORS_FILE
#if defined __OpenBSD__
#define VENDORS_FILE "/home/weezel/mnt/store/ohjelmointi/c/macvendor/vendors.txt"
#endif
#if defined __linux__
#include <strings.h> /* Silent compiler warning */
#define VENDORS_FILE "/home/weezel/mnt/store/ohjelmointi/c/macvendor/vendors.txt"
#endif
#else
#define VENDORS_FILE "vendors.txt"
#endif

#define MAC_LEN 8

void usage(void);
int isinline(char *, char *);

#endif /* _MACVENDOR_H_ */
