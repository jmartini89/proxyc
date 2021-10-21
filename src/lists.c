#include "proxyc.h"

t_list
	*ft_lstnew(pid_t pid)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->pid = pid;
		new->next = NULL;
	}
	return (new);
}

t_list
	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = NULL;
	if (lst)
	{
		ptr = lst;
		while (ptr->next)
			ptr = ptr->next;
	}
	return (ptr);
}

void
	ft_lstadd(t_list **lst, t_list *new)
{
	t_list	*ptr;

	ptr = NULL;
	if (*lst)
	{
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
	else
		*lst = new;
}
