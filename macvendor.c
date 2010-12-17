#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef VENDORS_FILE
#define VENDORS_FILE "/home/weezel/ohjelmointi/c/macvendor/vendors.txt"
#endif

int
isInLine(char *, char *);

int
main(int argc, char *argv[])
{
    FILE *input = NULL;
    char searchitem[9], vendor[256]; /* TODO Use malloc */
    int found, i, j;
    found = i = j = 0;

    if (argc < 2) {
        extern char *__progname;
        fprintf(stderr, "usage: %s MAC-address DB-name\n", __progname);
        exit(1);
    } 

    if (strlen(argv[1]) < 8)
        errx(3, "%s", "Too short for a mac address.");

#ifndef VENDORS_FILE
    if ((input = fopen(argv[2], "r")) == NULL)
       errx(2, "Could not open the database: %s\n", argv[2]);
#else
    if ((input = fopen(VENDORS_FILE, "r")) == NULL)
       errx(2, "Could not open the database: %s\n", argv[2]);
#endif

    for (i = 0, j = 1; i < 8; i++, j++) {
        if (j % 3 == 0)
            searchitem[i] = '-';
        else
            searchitem[i] = toupper(argv[1][i]);
    }
    searchitem[8] = '\0';

    while (fgets(vendor, sizeof(vendor), input) != NULL) {
        if (isInLine(&searchitem[0], &vendor[0]) == 1) {
            fprintf(stdout, "%s", vendor);
            found = 1;
        }
    }
    fclose(input);

    if (found == 0)
        errx(3, "MAC %s not found.", searchitem);

    return 0;
}


int
isInLine(char *p, char *r)
{
    int i = 0;

    for (i = 0; i < 8; i++) {
        if (*(&p[i]) != *(&r[i]))
            return 0;
    }
    return 1;
}

