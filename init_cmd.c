/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 22:17:31 by viporten          #+#    #+#             */
/*   Updated: 2021/08/27 06:06:25 by viporten         ###   ########.fr       */
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

void	init_fd_file(t_pipe *stc, int ac, char **av)
{
	stc->fd_file1 = open(av[1], O_RDONLY);
	stc->fd_file2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);

}

void	init_stc(t_pipe *stc, int ac, char **av, char **envp) 
{
	t_cmd	*shell;
	t_cmd	*tmp;
	int	i;

	i = 2;
	printf("nbr ac : %d\n", ac);
	tmp = NULL;
	init_path(stc, envp);
	while (i < ac  - 1)
	{
		tmp = malloc(sizeof(t_cmd));
		if (stc->first == NULL)
			stc->first = tmp;
		else
			shell->next = tmp;
		tmp->arg = ft_strsplit(av[i], ' ');
		tmp->cmd = tmp->arg[0];
		tmp->bin = path_cmd(stc->path, tmp->cmd);
		tmp->next = NULL;
		shell = tmp;
		i++;
	}
	return ;
}

/*int	main(int ac, char **av, char **envp)
{
	t_pipe	stc;
	int		i;
	
	i = 0;
	stc.first = NULL;
	init_stc(&stc, ac, av, envp);
	while (stc.first)
	{
		printf("cmd : %s \n", stc.first->cmd);
		printf("bin : %s \n", stc.first->bin);
		i = 0;
		while (stc.first->arg[i])
		{
			printf("arg numero %d : %s \n", i,  stc.first->arg[i]);
			i++;
		}
		stc.first = stc.first->next;
	}
}*/
