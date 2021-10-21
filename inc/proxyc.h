#ifndef PROXYC_H
# define PROXYC_H
# define BUFFER 1024
# define HOWTO "Usage: proxyc [destination address] [destination port] [proxy listening port]"

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
#include <pthread.h>

typedef struct s_list
{
	pid_t			pid;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_thread
{
	pthread_t		init;
	pthread_mutex_t	mutex;
	t_list			*list;
}	t_thread;

/* fail */
void	ft_fail(char *err);
void	ft_fail_custom(char *err);

/* init sockets */
void	ft_init_socket_listen(char **argv, int *fd_listen, struct sockaddr_in *addr_listen);
void	ft_init_socket_connection(char **argv, int *fd_dst, struct sockaddr_in *addr_dst);

/* signals */
void	ft_sig_term(int sig);
void	ft_sig_pipe(int sig);
void	ft_sig_chld(int sig);

/* proxy */
void	ft_proxy(int fd_src, int fd_dst);

/* exec */
void	ft_exec(char **argv);

/* lists */
t_list	*ft_lstnew(pid_t pid);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd(t_list **lst, t_list *new);

#endif