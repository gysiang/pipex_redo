/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:18:22 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/10 09:59:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void run_command(char *command, char **envp)
{
	char **path_from_envp;
	char **command_array;
	char *command_path;

	path_from_envp = get_path_from_env(envp);
	command_array = ft_split(command, " ");
	command_path = get_path(command, path_from_envp);
	if (execve(command_path, command_array, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(command_array[0], 2);
		ft_free_array(command_array);
		exit(0);
	}
}

void	child_process(char **av, int pipe_fd[2], char **envp)
{
	int	fd;
	int	i;

	fd = open_file(av[1], O_RDONLY, 0666);
	check_fd(fd, pipe_fd[1]);
	close(pipe_fd[1]);
	run_command(av[2], envp);
} 

void	parent_process(char **av, int pipe_fd[2], char **envp)
{
	int	fd;

	fd = open_file(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	check_fd(pipe_fd[0], fd);
	close(pipe_fd[0]);
	run_command(av[3], envp);
} 


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
