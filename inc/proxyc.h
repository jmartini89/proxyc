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

typedef struct s_thread
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pid_t			*pid_arr;
	int				active_conn;
}	t_thread;


/*
* sockets
*/
void	ft_init_socket_listen(char **argv, int *fd_listen, struct sockaddr_in *addr_listen);
void	ft_init_socket_connection(char **argv, int *fd_dst, struct sockaddr_in *addr_dst);

/* proxy */
void	ft_proxy(int fd_src, int fd_dst);

/* thread */
void	ft_thread(t_thread *thread);

/* exec */
void	ft_exec(char **argv);

/* signals */
void	ft_sig_term(int sig);
void	ft_sig_pipe(int sig);
void	ft_sig_chld(int sig);
/* fail */
void	ft_fail(char *err);
void	ft_fail_custom(char *err);
/* pid update */
void	ft_pid_lst_remove(t_thread *thread, pid_t pid);
void	ft_pid_lst_add(t_thread *thread, pid_t pid);

#endif