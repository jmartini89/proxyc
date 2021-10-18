/*
*	socket
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
/*
*	signal
*/
#include <signal.h>
/*
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static void
	ft_fail(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

int
	main (int argc, char **argv)
{
	int					fd;
	unsigned int		addrlen;
	struct sockaddr_in	addr;
	int					port;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: port\n");
		exit (EXIT_FAILURE);
	}

	port = atoi(argv[1]);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		ft_fail("Socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		ft_fail("Bind");

	if (listen(fd, 10) == -1)
		ft_fail("Listen");

	addrlen = sizeof(addr);
	int new_fd;
	while (1)
	{
		new_fd = accept(fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
		if (new_fd == -1)
			ft_fail("Accept");
		printf("Activity detected on port %d from %s\n", port, inet_ntoa(addr.sin_addr));
		close (new_fd);
	}
}
