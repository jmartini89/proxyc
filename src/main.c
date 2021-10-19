#include "netc.h"

int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_dst;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_dst;
	unsigned int		addrlen;

	if (argc < 3)
		ft_fail_custom(HOWTO);

	addrlen = sizeof(addr_listen);
	ft_init(argv, &fd_listen, &fd_dst, &addr_listen, &addr_dst, addrlen);

	ft_proxy(fd_dst, fd_listen, &addr_listen, &addrlen);

	return (EXIT_SUCCESS);
}
