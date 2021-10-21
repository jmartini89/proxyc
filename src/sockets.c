#include "proxyc.h"

void
	ft_socket_tcp_listen(char **argv, int *fd_listen, struct sockaddr_in *addr_listen)
{
	int			optval;
	int			src_port;
	unsigned	addrlen;

	src_port = atoi(argv[3]);
	addrlen = sizeof(*addr_listen);

	/* SOCKET INIT */
	if ((*fd_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_fail("socket listen");
	addr_listen->sin_family = AF_INET;
	addr_listen->sin_port = htons(src_port);
	addr_listen->sin_addr.s_addr = htonl(INADDR_ANY);
	if (setsockopt(*fd_listen, SOL_SOCKET,
		SO_REUSEADDR | SO_REUSEPORT,
		&optval, sizeof(optval)))
		ft_fail("socket options");

	/* EXECUTE */
	if (bind(*fd_listen, (struct sockaddr *)addr_listen, addrlen) == -1)
		ft_fail("bind");
	if (listen(*fd_listen, 128) == -1)
		ft_fail("listen");

	fprintf(stderr, "Proxy listening on port %d\n", src_port);
}

void
	ft_socket_tcp_connect(char **argv, int *fd_dst, struct sockaddr_in *addr_dst)
{
	int			optval;
	int			dst_port;
	char		*dst_address;
	unsigned	addrlen;


	dst_address = argv[1];
	dst_port = atoi(argv[2]);
	addrlen = sizeof(*addr_dst);

	/* SOCKET INIT */
	if ((*fd_dst = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_fail("socket connect");
	addr_dst->sin_family = AF_INET;
	addr_dst->sin_port = htons(dst_port);
	if (inet_pton(AF_INET, dst_address, &addr_dst->sin_addr) != 1)
		ft_fail_custom("address conversion: Error");
	if (setsockopt(*fd_dst, SOL_SOCKET,
		SO_REUSEADDR | SO_REUSEPORT,
		&optval, sizeof(optval)))
		ft_fail("socket options");

	/* EXECUTE */
	if (connect(*fd_dst, (struct sockaddr *)addr_dst, addrlen) == -1)
		perror("connect");
}
