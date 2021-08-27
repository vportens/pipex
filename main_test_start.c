/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:53:08 by viporten          #+#    #+#             */
/*   Updated: 2021/08/27 06:25:38 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	t_pipe	stc;
	pid_t	pid2;
	int		fd[2]; // fd[0] == read | fd[1] == write;

	(void)ac;
	stc.first = NULL;
	init_stc(&stc, ac, av, envp);
	if (check_bin(&stc) == -1)
	{
		printf("bad commande line\n");
		return (0);
	}
	init_fd_file(&stc, ac, av);
	if (stc.fd_file1 < 0 || stc.fd_file2 < 0)
		return (0);
	if (pipe(fd) == -1) // error fork;
	{
		printf("error opening pipe\n");
		return (1);
	}

	pid = fork();
	if (pid == -1) // error pipe;
	{
		printf("error forking\n");
		return (2);
	}
	if (pid == 0)
	{
		write(2, "processus fils\n", 15); 
		write(2, stc.first->bin, ft_strlen(stc.first->bin)); 
		write(2, "\n", 1);
		dup2(stc.fd_file1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(stc.fd_file1);
		close(fd[0]);
		close(fd[1]);
		execve(stc.first->bin, stc.first->arg, envp);
		write(2, "bad path for execve\n", 5);

	}
	stc.first = stc.first->next;
	if (pid != 0)
	{
		waitpid(pid, NULL, 0); // grace a waitpid le ls ce fait avant le bite

		write(2, "processus pere\n", 15); 
		write(2, stc.first->bin, ft_strlen(stc.first->bin)); 
		write(2, "\n", 1);

		dup2(fd[0], STDIN_FILENO);
		dup2(stc.fd_file2, STDOUT_FILENO);
		close(stc.fd_file2);
		close(fd[0]);
		close(fd[1]);
		execve(stc.first->bin, stc.first->arg, envp);
		printf("bad path for execve 2\n");
	}
	write(1, "bite\n", 5);
	return (0);
}
