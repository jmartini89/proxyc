#ifndef NETC_H
# define NETC_H
# define SRC_PORT 4242
# define BUFFER 4096
# define HOWTO "Usage: [bin] [destination address] [destination port] [proxy port]\nProxy port is optional. Default: 4242"

/* socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

/**/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* functions */
void	ft_fail(char *err);
void	ft_fail_custom(char *err);
void	ft_init(char **argv, int *fd_listen, int *fd_dst,
			struct sockaddr_in *addr_listen, struct sockaddr_in *addr_dst, unsigned int addrlen);
void	ft_proxy(int fd_dst, int fd_listen, struct sockaddr_in *addr_listen, int *addrlen);

#endif