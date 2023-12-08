/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:15:57 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/08 11:47:47 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "libft/libft.h"

int	open_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("open");
		if (errno == ENOENT)
			perror("Error: No such file or directory\n");
		else if (errno == EACCES)
			perror("Error: Permission Denied\n");
		else
			perror("Error: Unable to open\n");
		exit(0);
	}
	return (fd);
}

char	**get_path_from_env(char **envp)
{
	int	i;
	char	*envp_path;
	char	**envp_all_paths;

	i = 0;
	while (envp[i++])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = envp[i] + 5;
			break ;
		}
	}
	if (envp_path != NULL)
	{
		envp_all_paths = ft_split(envp_path, ':');
	}
	return (envp_all_paths);
}
/**
char	*get_path_from_env(char **envp, char *command)
{
	int			i;
	char		*env_path;
	char		*path;
	char		*partial_path;
	char		**allpartialpath;
	char		**cmd_array;

	i = 0;
	while (array[i] != NULL) 
	{
		if (ft_strncmp(array[i], "PATH=", 5) == 0)
		{
			env_path = array[i] + 5;
			break ;
		}
		i++;
	}
	i = 0;
	allpartialpath = ft_split(env_path, ':');
	cmd_array = ft_split(command, ' ');
	while (allpartialpath[++i])
	{
		partial_path = ft_strjoin(allpartialpath[i], "/");
		path = ft_strjoin(partial_path, cmd_array[0]);
		free(partial_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_array(cmd_array);
			return (path);
		}
		free(path);
	}
	ft_free_array(allpartialpath);
	ft_free_array(cmd_array);
	return (command);
}
**/
/**
This function will get a path from the envp that has PATH in its string
It looks something like this PATH=/bin/user:/local/sbin:/local/bin/....
Our next task is to ft_split by :
**/

/**
char	*get_path(char **array, char *cmd)
{
	int			i;
	char		*allpath;
	char		*tmp;
	char		**path_array;
	char		**cmd_array;
	
	i = -1;
	while (array[i] != NULL) 
	{
		if (ft_strncmp(array[i], "PATH=", 5) == 0)
		{
			allpath = array[i] + 5;
			break ;
		}
		i++;
	}
	path_array = ft_split(path, ':');
	cmd_array = ft_split(cmd, ' ');
	while (path_array[i++])
	{
		

	}

	return (path);
}

char	**get_path_array(char *cmd, char *path)
{
	char	*tmp;
	char	**path_array;
	int		i;

	i = 0;
	path_array = ft_split(path, ':');
	while (path_array[i] != NULL)
	{
		tmp = add_slash(path_array[i]);
		if (tmp == NULL)
		{
			ft_free_array(path_array);
			return (NULL);
		}
		free(path_array[i]);
		path_array[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (path_array[i] == NULL)
		{
			ft_free_array(path_array);
			return (NULL);
		}
		i++;
	}
	return (path_array);
}

void	check_fd(int int_fd, int out_fd)
{
	if (int_fd != STDIN_FILENO)
	{
		dup2(int_fd, STDIN_FILENO);
		close(int_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}
**/
