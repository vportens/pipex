/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 22:17:31 by viporten          #+#    #+#             */
/*   Updated: 2021/08/29 23:28:56 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipe(t_pipe *stc, t_cmd *tmp, char **av, int i)
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
	return (0);
}

int	init_multi_fd(t_pipe *stc, int ac, char **av)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	stc->nfd = NULL;
	stc->nfd = malloc(sizeof(int *) * (ac - 3));
	if (stc->nfd == NULL)
		return (20);
	tmp = stc->first;
	while (i < ac - 4)
	{
		if (init_pipe(stc, tmp, av, i) != 0)
			return (20);
		tmp = tmp->next;
		i++;
	}
	stc->nfd[i] = NULL;
	tmp->fd_in = stc->nfd[i - 1][0];
	tmp->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0);
}

int	init_fd_file(t_pipe *stc, int ac, char **av)
{
	stc->fd_file1 = open(av[1], O_RDONLY);
	stc->fd_file2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (stc->fd_file1 < 0)
	{
		write(2, "pipex: aucun fichier ou dossier de ce type: ", ft_strlen("pipex: aucun fichier ou dossier de ce type: "));
		write(2, av[1], ft_strlen(av[1]));
		write(2, "\n", 1);
	}
	return (0);
}

void	init_cmd(t_pipe *stc, t_cmd *tmp, char **av, int i)
{
	tmp->arg = ft_strsplit(av[i], ' ');
	tmp->cmd = tmp->arg[0];
	tmp->bin = path_cmd(stc->path, tmp->cmd);
	tmp->next = NULL;
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
		init_cmd(stc, tmp, av, i);
		shell = tmp;
		if (tmp->bin == NULL)
			return (30);
		i++;
	}
	return (0);
}
