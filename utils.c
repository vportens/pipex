/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 04:54:14 by user42            #+#    #+#             */
/*   Updated: 2021/08/29 22:48:20 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "pipex.h"

int	check_bin(t_pipe *stc)
{
	t_cmd	*tmp;

	tmp = stc->first;
	while (tmp)
	{
		if (tmp->bin == NULL)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	close_fd(t_cmd *first)
{
	while (first)
	{
		close(first->fd_in);
		close(first->fd_out);
		first = first->next;
	}
}

void	wait_for_pid(int i, int ac, pid_t *pid, t_cmd *tmp)
{	
	char *nbr;

	i = 0;
	while (i < ac - 3)
	{
	//	write(2, "before\n", 7);
	//	if (tmp->bin == tmp->arg[0])
	//		i++;
	//	else
	//	{
			write(2, tmp->bin, ft_strlen(tmp->bin));
			nbr = ft_itoa(pid[i]);
			write(2, nbr, ft_strlen(nbr));
			write(2, "\n", 1);
			waitpid(pid[i], NULL, 0);
			write(2, "ici2\n", 5);
			i++;
	//	}
		tmp = tmp->next;
	}
	free(pid);
}
