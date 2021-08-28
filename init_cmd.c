/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 22:17:31 by viporten          #+#    #+#             */
/*   Updated: 2021/08/28 23:07:06 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_fd(int **fd)
{
	int	i;

	if (fd)
	{
		i = 0;
		while (fd[i])
		{
			free(fd[i]);
			i++;
		}
		free(fd);
	}
	return (1);
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

int	init_multi_fd(t_pipe *stc, int ac, char **av)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	stc->nfd = NULL;
	stc->nfd = malloc(sizeof(int *) * (ac - 4));
	if (stc->nfd == NULL)
		return (20);
	tmp = stc->first;
	while (i < ac - 4)
	{
		stc->nfd[i] = malloc(sizeof(int) * (2));
		if (stc->nfd[i] == NULL)
			return (20);
		if (pipe(stc->nfd[i]) == -1)
			return (40);
		if (i == 0)
			tmp->fd_in = open(av[1], O_RDONLY);
		else
			tmp->fd_in = stc->nfd[i - 1][0];
		tmp->fd_out = stc->nfd[i][1];
		tmp = tmp->next;
		i++;
	}
	tmp->fd_in = stc->nfd[i - 1][0];
	tmp->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0);
}

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

int	init_fd_file(t_pipe *stc, int ac, char **av)
{
	stc->fd_file1 = open(av[1], O_RDONLY);
	stc->fd_file2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (stc->fd_file1 < 0 || stc->fd_file2 < 0)
	{
		write(1, "bad here\n", 9);
		return (30);
	}
	return (0);
}

int	init_stc(t_pipe *stc, int ac, char **av, char **envp)
{
	t_cmd	*shell;
	t_cmd	*tmp;
	int		i;

	i = 2;
	tmp = NULL;
	if (init_path(stc, envp) != 0)
		return (2);
	while (i < ac - 1)
	{
		tmp = malloc(sizeof(t_cmd));
		if (tmp == NULL)
			return (20);
		if (stc->first == NULL)
			stc->first = tmp;
		else
			shell->next = tmp;
		tmp->arg = ft_strsplit(av[i], ' ');
		tmp->cmd = tmp->arg[0];
		tmp->bin = path_cmd(stc->path, tmp->cmd);
		tmp->next = NULL;
		shell = tmp;
		if (tmp->bin == NULL)
			return (30);
		i++;
	}
	return (0);
}
