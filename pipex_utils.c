/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:15:57 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/10 10:01:08 by gyong-si         ###   ########.fr       */
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

/**
 * This function will get the all the paths from envp. It will first match to get the line starting with PATH and then save it in envp_path. If not null, it will then be split by ':'.
*/
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
This function will get the correct filepath from envp depending on the
command.
**/
char *get_path(char *command, char **path_from_envp)
{
	char *partial_path;
	char *complete_path;
	char **cmd;
	int i;

	i = 0;
	cmd = ft_split(command, ' ');
	while (path_from_envp[i++])
	{
		partial_path = ft_strjoin(path_from_envp[i], "/");
		complete_path = ft_strjoin(partial_path, cmd[0]);
		free(partial_path);
		if (access(complete_path, F_OK | X_OK) == 0)
		{
			ft_free_array(cmd);
			return (complete_path);
		}
	}
	ft_free_array(cmd);
	return (command);
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
