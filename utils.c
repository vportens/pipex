/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 04:54:14 by user42            #+#    #+#             */
/*   Updated: 2021/09/03 21:23:58 by user42           ###   ########.fr       */
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

void	forking(t_pipe stc, char **envp, t_cmd *tmp, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < stc.ac - 3)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			clean(&stc, 40, 0);
			exit(1);
		}
		if (pid[i] == 0)
			ft_execve(stc, tmp, envp);
		close(stc.first->fd_in);
		close(stc.first->fd_out);
		stc.first = stc.first->next;
		i++;
	}
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
		waitpid(pid[i], NULL, 0);
		i++;
		tmp = tmp->next;
	}
	free(pid);
}
