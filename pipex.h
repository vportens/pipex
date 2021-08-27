/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:56:05 by viporten          #+#    #+#             */
/*   Updated: 2021/08/27 06:07:26 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/includes/libft.h"

typedef struct s_cmd t_cmd;
typedef struct s_pipe t_pipe;

struct		s_cmd
{
	char	*cmd;
	char	*bin;
	char	**arg;
	

	t_cmd	*next;
};

struct		s_pipe
{
	char	**path;
	t_cmd	*first;
	int		fd_file1;
	int		fd_file2;
};

char	*found_path_env(char **envp);
char	**split_path(char *str);
char	*path_cmd(char **path, char *str);
void	init_stc(t_pipe *stc, int ac, char **av, char **envp);
void	init_path(t_pipe *stc, char **envp);
int		check_bin(t_pipe *stc);
void	init_fd_file(t_pipe *stc, int ac, char **av);
#endif
