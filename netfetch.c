#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define HTTP_HOST "standards.ieee.org"
#define HTTP_PATH "/develop/regauth/oui/oui.txt"
#define HTTP_PORT "80"
#define USER_AGENT "Mozilla"

char *build_get_query();
char *open_socket(addrinfo *, *);

int main()
{
	struct	 addrinfo hints, *res;
	int	*writedbfile;
	int	 bytes, gaierr, sent, sock, tmpres;
	char	 buffer[BUFSIZ + 1];
	char	*get;

	bytes = sent = tmpres = 0;

	memset(&buffer, 0, sizeof(buffer));
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((gaierr = getaddrinfo(HTTP_HOST, HTTP_PORT, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrres error %d: %s\n",
				gaierr, gai_strerror(gaierr));
		return (2);
	}

	if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
		perror("socket");
		return (2);
	}

	if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
		perror("connect");
		close(sock);
		return (2);
	}

	get = build_get_query();

	/* Send the query to the server */
	while (sent < strlen(get)) {
		if ((tmpres = send(sock, get + sent, strlen(get) - sent, 0)) == -1)
			err(1, "Cannot send query");
		sent += tmpres;
	}

	if ((fopen("testdb.txt", "w")) == NULL) {
		fprintf(stderr, "Error while writing to file.\n");
		exit(20);
	}

	while ((bytes = read(sock, buffer, BUFSIZ)) > 0)
	    fprintf(stdout, "%s\n", buffer);

	/*write(writedbfile, buffer, sizeof(buffer));*/
	/*write(stdout, buffer, bytes);*/

	if (sock)
		close(sock);
	if (writedbfile)
		close(*writedbfile);
	if (res)
		freeaddrinfo(res);
	if (get)
		free(get);

	return (0);
}

char
*build_get_query()
{
	int	 qsize = 0;
	char	*query = NULL;
	const char *header = "GET /%s HTTP/1.1\nHost: %s\nUser-Agent: %s\n\nConnection: close\n\n";

	/* -5 is to consider the %s %s %s in tpl and the ending \0 */
	qsize = strlen(HTTP_HOST) + strlen(HTTP_PATH) + strlen(USER_AGENT) + strlen(header) - 5;

	if ((query = calloc(qsize, sizeof(char *))) == NULL)
		  err(1, "calloc failure in build_get_query");
	sprintf(query, header, HTTP_PATH, HTTP_HOST, USER_AGENT);

	return query;
}

