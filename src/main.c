#include "netc.h"

int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_dst;
	int					fd_src;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_dst;
	unsigned int		addrlen;

	if (argc < 3)
		ft_fail_custom(HOWTO);

	addrlen = sizeof(addr_listen);
	ft_init(argv, &fd_listen, &fd_dst, &addr_listen, &addr_dst, addrlen);

	if ((fd_src = accept(
		fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen)) == -1)
		ft_fail("Accept");

	close (fd_listen);

	ft_proxy(fd_src, fd_dst);

	return (EXIT_SUCCESS);
}
