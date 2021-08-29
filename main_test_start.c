/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:53:08 by viporten          #+#    #+#             */
/*   Updated: 2021/08/30 00:29:20 by victor           ###   ########.fr       */
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
	write(2, "la\n", 3);
	if (stc.first->fd_in < 0 || stc.first->fd_out < 0)
		exit(1);
	execve(stc.first->bin, stc.first->arg, envp);
	write(2, "pipex: command not found: ", ft_strlen("pipex: command not found: "));
	write(2, stc.first->cmd, ft_strlen(stc.first->cmd));
	write(2, "\n", 1);
	write(2, "test\n", 5);
	exit(1);
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
		return (clean(&stc, 20, 0));
	while (i < ac - 3)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (clean(&stc, 40, 0));
		if (pid[i] == 0)
			ft_execve(stc, tmp, envp);
		close(stc.first->fd_in);
		close(stc.first->fd_out);
		stc.first = stc.first->next;
		i++;
	}
	stc.first = tmp;
	wait_for_pid(0, ac, pid, stc.first);
	write(2, "end_pid\n", 8);
	close_fd(tmp);
	stc.first = tmp;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	stc;
	int		ret;

	stc.first = NULL;
	stc.path = NULL;
	stc.nfd = NULL;
	ret = init_stc(&stc, ac, av, envp);
	if (ret != 0)
	{
	//	write(2, ft_itoa(ret), ft_strlen(ft_itoa(ret)));
		return (clean(&stc, ret, 0));
	}
	write(2, "end init\n", 9);
	if (check_bin(&stc) == -1)
		return (0);
	write(2, "check_bin\n", 10);
	if (init_fd_file(&stc, ac, av) != 0)
		return (clean(&stc, 40, 0));
	write(2, "end init_fd\n", 12);
	if (init_multi_fd(&stc, ac, av) != 0)
		return (clean(&stc, 20, 0));
	write(2, "end init_nfd\n", 13);
//	if (stc.fd_file1 < 0 || stc.fd_file2 < 0)
//		return (clean(&stc, 30, 0));
	multi_fork(stc, ac, envp);
	write(2, "end fork\n", 9);
	clean(&stc, 30, 0);
	return (0);
}
