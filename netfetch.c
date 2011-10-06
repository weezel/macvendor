#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define HTTP_HOST "standards.ieee.org"
#define HTTP_PATH "/develop/regauth/oui/oui.txt"
#define HTTP_PORT "80"
#define USER_AGENT "Mozilla"
#define DB_NAME "dendors.txt"

static FILE	*fin;
static char *cause;
int fd_internet;

int initialize_connection(const char *, const char *);
char send_http_query(int);
void readwriter(int);

int main()
{
	int	 s;
	int	 bytes, sent, tmpres;
	char	 buffer[BUFSIZ + 1];
	char	*get;

	bytes = sent = tmpres = 0;

	get = build_http_get_query();
	s = initialize_connection(HTTP_HOST, HTTP_PORT);
	if (s == -1) {
		warn("%s", cause);
		exit(10);
	}

	fin = fdopen(s, "r+");
	/* Send the query to the server */
	while (sent < strlen(get)) {
		if ((tmpres = send(fd_internet, get + sent, strlen(get) - sent, 0)) == -1)
			err(1, "Cannot send query");
		sent += tmpres;
	}

	if ((fopen("testdb.txt", "w")) == NULL) {
		fprintf(stderr, "Error while writing to file.\n");
		exit(20);
	}

	while ((bytes = read(sock, buffer, BUFSIZ)) > 0)
	    fprintf(stdout, "%s\n", buffer);

	if (sock)
		close(sock);
	if (res)
		freeaddrinfo(res);
	if (get)
		free(get);

	return (0);
}

int
initialize_connection(const char *host, const char *serv)
{
	int error, sock = -1;
	struct addrinfo hints, *res0 = NULL, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	error = getaddrinfo(host, serv, &hints, &res0);
	if (error) {
		warnx("%s", gai_strerror(error));
		return -1;
	}

	for (res = res0; res; res = res->ai_next) {
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sock == -1) {
			cause = "socket;
			continue;
		}
again:
		if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
			int save_errno;

			if (errno == EINTR) /* TODO Make counter */
				goto again;
			save_errno = errno;
			close(sock);
			errno = save_errno;
			sock = -1;
			cause = "connect";
			continue;
		}
		break;
	}
	if (sock == -1)
		warn("cannot connect");

	freeaddrinfo(res0);

	return sock;

}

int
send_http_query(int nfd)
{
	int	len = 0;
	char	*query;
	/*
	const char *header = "GET /%s HTTP/1.1\nHost: %s\nUser-Agent: %s\n\nConnection: close\n\n";
	*/

	len = asprintf(&query, "GET /%s HTTP/1.1\nHost: %s\nUser-Agent: %s\n\nConnection: close\n\n",
		HTTP_PATH, HTTP_HOST, USER_AGENT);

	fin = open(nfd, "r+");

	free(query);
	return query;
}

void
readwriter(int nfd)
{
	int wfd = fileno(stdin);
}
