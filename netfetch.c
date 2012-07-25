/*
 * Copyright Ville Valkonen 2011
 * Partly borroved from here:
 * http://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c
 * http://curl.haxx.se/libcurl/c/progressfunc.html
 */

#include <curl/curl.h>
#include <curl/easy.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "netfetch.h"


struct progress {
	double	 lastrun;
	CURL	*curl;
};

int
netfetch(const char *fname)
{
	FILE		*fp;
	CURL		*curl;
	CURLcode	 res = 0;
	struct progress	 prog;

	if ((curl = curl_easy_init()) == NULL) {
		fprintf(stderr, "CURL initialization failed\n");
		return 1;
	}

	if (strlen(fname) >= FILENAME_MAX) {
		fprintf(stderr, "File name too long\n");
		return 10;
	}
	prog.lastrun = 0;
	prog.curl = curl;

	fp = fopen(fname, "wb");
	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &prog);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
	res = curl_easy_perform(curl);

	if (res)
		fprintf(stderr, "%s\n", curl_easy_strerror(res));

	curl_easy_cleanup(curl);

	if (fp)
		fclose(fp);

	return (int) res;
}

size_t
write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written = 0;

	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int
progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow)
{
	double		 curtime = 0;
	struct progress	*prog;
	CURL		*curl;

	prog = (struct progress *) p;
	curl = prog->curl;

	curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &curtime);
	if ((curtime - prog->lastrun) >= MINPROGRESSTIME) {
		prog->lastrun = curtime;
		fprintf(stderr, "TOTALTIME: %f\r\n", curtime);
	}

	fprintf(stderr, "%.1f kiB / %.1f kiB [%.1f%%]\r",
		dlnow / 1024, dltotal / 1024, PERCENTAGE(dlnow, dltotal));
	fflush(stderr);

	return 0;
}
