#include "netc.h"

static void
	ft_init_sockets(char *argv, int *fd_listen, int *fd_dst,
		struct sockaddr_in *addr_listen, struct sockaddr_in *addr_dst)
{
	int	optval;

	/* LISTEN INIT */
	if ((*fd_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_fail("Socket Listen");
	addr_listen->sin_family = AF_INET;
	addr_listen->sin_port = htons(SRC_PORT);
	addr_listen->sin_addr.s_addr = htonl(INADDR_ANY);
	if (setsockopt(*fd_listen, SOL_SOCKET,
		SO_REUSEADDR | SO_REUSEPORT | SO_KEEPALIVE,
		&optval, sizeof(optval)))
		ft_fail("Socket options");

	/* CONNECT INIT */
	if ((*fd_dst = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_fail("Socket Connect");
	addr_dst->sin_family = AF_INET;
	addr_dst->sin_port = htons(DST_PORT);
	if (inet_pton(AF_INET, DST_ADDRESS, &addr_dst->sin_addr) != 1)
		ft_fail_custom("Address conversion: Error");
}

static void
	ft_init_connections(int *fd_listen, int *fd_dst,
		struct sockaddr_in *addr_listen, struct sockaddr_in *addr_dst,
		unsigned int addrlen)
{
	if (connect(*fd_dst, (struct sockaddr *)addr_dst, addrlen) == -1)
		ft_fail("Connect");

	if (bind(*fd_listen, (struct sockaddr *)addr_listen, addrlen) == -1)
		ft_fail("Bind");

	if (listen(*fd_listen, 64) == -1)
		ft_fail("Listen");
}

void
	ft_init(char *argv, int *fd_listen, int *fd_dst,
		struct sockaddr_in *addr_listen, struct sockaddr_in *addr_dst,
		unsigned int addrlen)
{
	ft_init_sockets(argv, fd_listen, fd_dst, addr_listen, addr_dst);
	ft_init_connections(fd_listen, fd_dst, addr_listen, addr_dst, addrlen);
}
