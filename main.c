/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:53:08 by viporten          #+#    #+#             */
/*   Updated: 2021/09/03 21:21:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "pipex.h"

int	clean_two(t_pipe *stc, int ret, t_cmd *tmp)
{
	int	i;

	while (stc->first)
	{
		if (stc->first->bin && stc->first->bin != stc->first->arg[0])
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
		tmp = stc->first->next;
		free(stc->first);
		stc->first = tmp;
	}
	return (ret);
}

int	clean(t_pipe *stc, int ret, int i)
{
	t_cmd	*tmp;

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
		while (stc->nfd[i])
		{
			free(stc->nfd[i]);
			i++;
		}
		free(stc->nfd);
	}
	return (clean_two(stc, ret, tmp));
}

void	ft_execve(t_pipe stc, t_cmd *tmp, char **envp)
{
	dup2(stc.first->fd_in, STDIN_FILENO);
	dup2(stc.first->fd_out, STDOUT_FILENO);
	close_fd(tmp);
	if (stc.first->fd_in < 0 || stc.first->fd_out < 0)
		exit(1);
	execve(stc.first->bin, stc.first->arg, envp);
	write(2, "pipex: command not found: ",
		ft_strlen("pipex: command not found: "));
	write(2, stc.first->cmd, ft_strlen(stc.first->cmd));
	write(2, "\n", 1);
	exit(1);
}

int	multi_fork(t_pipe stc, int ac, char **envp)
{
	pid_t	*pid;
	t_cmd	*tmp;

	tmp = stc.first;
	stc.ac = ac;
	pid = malloc(sizeof(pid_t) * (ac - 3));
	if (pid == NULL)
		return (clean(&stc, 20, 0));
	forking(stc, envp, tmp, pid);
	stc.first = tmp;
	wait_for_pid(0, ac, pid, stc.first);
	close_fd(tmp);
	stc.first = tmp;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	stc;
	int		ret;

	if (ac != 5)
		return (0);
	stc.first = NULL;
	stc.path = NULL;
	stc.nfd = NULL;
	ret = init_stc(&stc, ac, av, envp);
	if (ret != 0)
		return (clean(&stc, ret, 0));
	if (check_bin(&stc) == -1)
		return (0);
	if (init_fd_file(&stc, ac, av) != 0)
		return (clean(&stc, 40, 0));
	if (init_multi_fd(&stc, ac, av) != 0)
		return (clean(&stc, 20, 0));
	multi_fork(stc, ac, envp);
	clean(&stc, 30, 0);
	return (0);
}
