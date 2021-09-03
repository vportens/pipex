/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 09:39:40 by viporten          #+#    #+#             */
/*   Updated: 2021/09/03 21:22:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/includes/libft.h"

typedef struct s_cmd	t_cmd;
typedef struct s_pipe	t_pipe;

struct		s_cmd
{
	char	*cmd;
	char	*bin;
	char	**arg;
	int		fd_in;
	int		fd_out;
	t_cmd	*next;
};

struct		s_pipe
{
	char	**path;
	t_cmd	*first;
	int		fd_file1;
	int		fd_file2;
	int		**nfd;
	int		ac;
};

char	*found_path_env(char **envp);
char	**split_path(char *str);
char	*path_cmd(char **path, char *str);
int		init_stc(t_pipe *stc, int ac, char **av, char **envp);
int		init_path(t_pipe *stc, char **envp);
int		check_bin(t_pipe *stc);
int		init_fd_file(t_pipe *stc, int ac, char **av);
int		init_multi_fd(t_pipe *stc, int ac, char **av);
void	close_fd(t_cmd *first);
void	wait_for_pid(int i, int ac, pid_t *pid, t_cmd *tmp);
int		clean_two(t_pipe *stc, int ret, t_cmd *tmp);
int		clean(t_pipe *stc, int ret, int i);
void	ft_execve(t_pipe stc, t_cmd *tmp, char **envp);
void	forking(t_pipe stc, char **envp, t_cmd *tmp, pid_t *pid);
#endif
