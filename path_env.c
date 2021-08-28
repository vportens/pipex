/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 17:36:21 by viporten          #+#    #+#             */
/*   Updated: 2021/08/29 00:43:12 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_cmd(char **path, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], str);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		if (tmp)
			free(tmp);
		i++;
	}
	write(2, "pipex: command not found : ", ft_strlen("pipex: command not found : "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (str);
}

char	**split_path(char *str)
{
	char	**path;
	int		i;
	char	*tmp;

	i = 0;
	path = ft_strsplit(str, ':');
	if (str)
		free(str);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (tmp == NULL)
			return (NULL);
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return (path);
}

char	*found_path_env(char **envp)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) > 0)
		{
			str = ft_strdup(envp[i] + 5);
			return (str);
		}
		i++;
	}
	return (str);
}

int	init_path(t_pipe *stc, char **envp)
{
	char	*path_tmp;

	path_tmp = found_path_env(envp);
	if (path_tmp == NULL)
		return (2);
	stc->path = split_path(path_tmp);
	return (0);
}
