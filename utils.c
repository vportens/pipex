/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 04:54:14 by user42            #+#    #+#             */
/*   Updated: 2021/08/29 06:08:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	i = 0;
	while (i < ac - 3)
	{
	//	write(2, "before\n", 7);
	//	if (tmp->bin == tmp->arg[0])
	//		i++;
	//	else
	//	{
			write(2, tmp->bin, ft_strlen(tmp->bin));
			waitpid(pid[i], NULL, 0);
			write(2, "ici2\n", 5);
			i++;
	//	}
		tmp = tmp->next;
	}
	free(pid);
}
