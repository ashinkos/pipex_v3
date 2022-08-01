/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:40:16 by aaouni            #+#    #+#             */
/*   Updated: 2022/08/02 00:44:31 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int len_2d(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	free_2d(char ** str)
{
	int i;
	
	i=0;
	while (str[i])
	{	
		free(str[i]);
		i++;
	}
	free(str);
}

char	**get_path_env(char **env)
{
	char	**path;
	char	**path_slash;
	char	*path_str;
	int		i;
	int		j;
	
	j = 0;
	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path_str = env[i] + 5;
			path = ft_split(path_str, ':');
			path_slash = malloc (sizeof(char *) * (len_2d(path)+ 1));
			if (!path_slash)
				return (NULL);
			while(path[j])
			{
				path_slash[j] = ft_strjoin(path[j], "/");
				j++;	
			}
			free_2d(path);
			path_slash[j] = NULL;
			return (path_slash);
		}
		i++;
	}
	return (NULL);
}

char	**get_path_cmd(char *str, char **path)
{
	char	**cmd;
	char	*path_cmd;
	
	cmd = ft_split(str, ' ');
	if(access(cmd[0], X_OK) == 0)
		return(cmd);
	while(*path)
	{
		path_cmd = ft_strjoin(*path, cmd[0]);
		if(access(path_cmd, X_OK) == 0)
		{
			free (cmd [0]);
			cmd[0] = ft_strdup(path_cmd);
			free(path_cmd);
			return (cmd);
			
		}
		free(path_cmd);
		path++;	
	}
	return (NULL);
}