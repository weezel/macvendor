#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define HTTP_ADDRESS "http://standards.ieee.org/regauth/oui/oui.txt"
#define HTTP_PORT "80"
#define USER_AGENT "Mozilla"

int main()
{
	int				bytes, sock, gaierr;
	struct addrinfo hints, *res;
	char			buffer[BUFSIZ + 1];
	char			*hostname = "time.nist.gov";

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((gaierr = getaddrinfo(hostname,
					HTTP_PORT, &hints, &res)) != 0) {
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

	while ((bytes = read(sock, buffer, BUFSIZ)) > 0)
		fprintf(stdout, "%s\n", buffer);
		/*write(stdout, buffer, bytes);*/

	close(sock);
	freeaddrinfo(res);

	return (0);
}

