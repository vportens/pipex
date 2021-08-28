/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:53:08 by viporten          #+#    #+#             */
/*   Updated: 2021/08/28 22:49:26 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clean(t_pipe *stc, int ret)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = NULL;
	if (stc->path)	
	{
		while (stc->path[i])
		{
			free(stc->path[i]);
			i++;
		}
		free(stc->path);
	}
	if (stc->nfd)
	{
		i = 0;
		while (i < stc->ac - 4)
		{
			free(stc->nfd[i]);
			i++;
		}
		free(stc->nfd);
	}
	while (stc->first)
	{
		stc->first->next = tmp;	
		if (stc->first->bin)
			free(stc->first->bin);
		i = 0;
		if (stc->first->arg)
		{
			while (stc->first->arg[i])
			{
				free(stc->first->arg[i]);
				i++;
			}
			free(stc->first->arg);
		}
		free(stc->first);
		stc->first = tmp;
	}
	return (0);
}


int	multi_fork(t_pipe stc, int ac, char **envp)
{
	pid_t	*pid;
	int		i;
	t_cmd	*tmp;

	tmp = stc.first;
	i = 0;
	stc.ac = ac;
	pid = malloc(sizeof(pid_t) * (ac - 3));
	if (pid == NULL)
		return (clean(&stc, 20));
	while (i < ac - 3)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (clean(&stc, 40));
		if (pid[i] == 0)
		{
			dup2(stc.first->fd_in, STDIN_FILENO);
			dup2(stc.first->fd_out, STDOUT_FILENO);
			close_fd(tmp);
			execve(stc.first->bin, stc.first->arg, envp);
		}
		stc.first = stc.first->next;
		i++;
	}
	close_fd(tmp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	stc;
	int		ret;

	(void)ac;
	stc.first = NULL;
	ret = init_stc(&stc, ac, av, envp);
	if (ret != 0)
		return (clean(&stc, ret));
	if (check_bin(&stc) == -1)
		return (0);
	if (init_fd_file(&stc, ac, av) != 0)
		return (clean(&stc, 40));
	if (init_multi_fd(&stc, ac, av) != 0)
		return (clean(&stc, 20));
	if (stc.fd_file1 < 0 || stc.fd_file2 < 0)
		return (clean(&stc, 30));
	multi_fork(stc, ac, envp);
	clean(&stc, 30);
	return (0);
}
