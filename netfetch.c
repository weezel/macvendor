/*
 * Copyright Ville Valkonen 2011
 * Partly borroved from here:
 * http://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c
 * http://curl.haxx.se/libcurl/c/progressfunc.html
 */

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

#define URL "http://standards.ieee.org/develop/regauth/oui/oui.txt"

size_t write_data(void *, size_t, size_t, FILE *);
static int progress(void *, double, double, double, double );

void
netfetch(void)
{
	char	 outfilename[FILENAME_MAX] = VENDORS_FILE;
	FILE	*fp;
	CURL	*curl;
	CURLcode res = 0;

	curl = curl_easy_init();

	if (curl == NULL)
		err(1, NULL);

	fp = fopen(outfilename, "wb");
	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	res = curl_easy_perform(curl);

	if (res != 0)
		fprintf(stderr, "%s\n", curl_easy_strerror(res));

	curl_easy_cleanup(curl);

	if (fp)
		fclose(fp);
}


size_t
write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written = 0;

	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

static int
progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow)
{
	int percentage;

	percentage = dlnow / dltotal * 100;
	fflush(stderr);
	fprintf(stderr, "Progress: %d%%\r", percentage);

	return 0;
}
