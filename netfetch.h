#ifndef _NETFETCH_H_
#define _NETFETCH_H_

#define		URL "http://standards.ieee.org/develop/regauth/oui/oui.txt"
#define		MINPROGRESSTIME 6000
#define		PERCENTAGE(dlnow, dltotal) \
		(dlnow / dltotal * 100)

int netfetch(const char *);
size_t write_data(void *, size_t, size_t, FILE *);
int progress(void *, double, double, double, double );

#endif /* _NETFETCH_H_ */
