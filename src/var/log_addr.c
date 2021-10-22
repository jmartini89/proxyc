#include "proxyc.h"

void
	ft_log_addr(struct sockaddr_in *addr)
{
	char		buf[INET_ADDRSTRLEN];
	unsigned	addrlen;

	addrlen = sizeof(*addr);

	if (inet_ntop(AF_INET, (struct in_addr *)&addr->sin_addr.s_addr, buf, addrlen) == NULL)
		ft_fail("inet_ntop");

	fprintf(stderr, "accept: %s\n", buf);
}
