/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:18:22 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/08 13:05:30 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

/**
This function will get the correct filepath from envp depending on the 
command. 
**/
char	*get_path(char *command, char **path_from_envp)
{
	char	*partial_path;
	char	*complete_path;
	char	**cmd;
	int	i;

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

/**
void	child_process(char **av, int pipe_fd[2], char **envp)
{
	int	fd;
	int	i;

	fd = open_file(av[1], 0_RDONLY, 0666);
	check_fd(fd, pipe_fd[1]);
	close(pipe_fd[1]);
	run_command(av[3], envp);
} **/

/**
void	parent_process(char **av, int pipe_fd[2], char **envp)
{
	int	fd;

	fd = open_file(av[4], 1);
	check_fd(pipe_fd[0], fd);
	close(pipe_fd[0]);
	run_command(av[4], envp);
} **/


int	main(int ac, char **av, char **envp)
{
	int	pipe_fd[2];
	pid_t	pid;

	if (ac < 5)
	{
		ft_putstr_fd("Usage: <infile> <cmd1> <cmd2> ... <outfile>\n", 2);
		exit(0);
	}
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(av, pipe_fd, envp);
	else
		parent_process(av, pipe_fd, envp);
}
