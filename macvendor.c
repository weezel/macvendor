/*
 * Copyright Ville Valkonen 2010-2012
 */

#include <ctype.h>
#include <err.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macvendor.h"
#include "netfetch.h"


int
main(int argc, char *argv[])
{
	FILE	*input = NULL;
	char	 ch;
	char	 searchitem[MAC_LEN + 1], vendor[256];
	int	 found = 0, i = 0, j = 0, uflag = 0;

	if (argc < 2)
		usage();

	while ((ch = getopt(argc, (char *const *)argv, "u")) != -1) {
		switch ((char)ch) {
		case 'u':
			uflag = 1;
			fprintf(stdout, "Updating vendors database\n");
			if (netfetch(VENDORS_FILE) != 0) {
				fprintf(stderr, "Error while updating vendors file\n");
				return 100;
			}
			return 0;
		default:
			usage();
		}
	}

	if (strlen(argv[argc - 1]) < MAC_LEN)
		errx(3, "%s", "Too short for a MAC-address.");

	if ((input = fopen(VENDORS_FILE, "r+")) == NULL)
		errx(2, "Could not open the database: %s\n", VENDORS_FILE);

	/* Capitalize octets and unify octet dividers */
	for (i=0, j=1; i < MAC_LEN; i++, j++) {
		if (j % 3 == 0)
			searchitem[i] = '-';
		else
			searchitem[i] = toupper(argv[argc - 1][i]);
	}
	searchitem[MAC_LEN] = '\0';

	while (fgets(vendor, sizeof(vendor), input) != NULL) {
		if (isinline(&searchitem[0], &vendor[0]) == 1) {
			fprintf(stdout, "%s", vendor);
			found = 1;
		}
	}
	fclose(input);

	if (found == 0)
		fprintf(stdout, "MAC %s not found.", searchitem);

	return EXIT_SUCCESS;
}


void
usage(void)
{
	extern char *__progname;

	(void)fprintf(stderr, "usage: %s [-u] MAC-address\n", __progname);
	exit(EXIT_FAILURE);
}


int
isinline(char *p, char *r)
{
	int i = 0;

	for (i = 0; i < MAC_LEN; i++) {
		if (*(&p[i]) != *(&r[i]))
			return 0;
	}
	return 1;
}

