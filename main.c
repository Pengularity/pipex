/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:04:06 by pengu             #+#    #+#             */
/*   Updated: 2023/07/17 20:20:29 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd1(char **av, char **env, int fdin, int *fd)
{
	int		pid;
	char	*cmd1_path;
	char	**cmd1;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(fdin, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		cmd1_path = get_cmd_path(av[2], env);
		if (cmd1_path == NULL)
			(perror("Command 1 not found"), exit(EXIT_FAILURE));
		cmd1 = ft_split(cmd1_path, ' ');
		execve(cmd1[0], cmd1, env);
		(perror("execve"), ft_free(cmd1), free(cmd1_path), exit(EXIT_FAILURE));
	}
	return (pid);
}

int	exec_cmd2(char **av, char **env, int fdout, int *fd)
{
	int		pid;
	char	*cmd2_path;
	char	**cmd2;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(fd[1]);
		cmd2_path = get_cmd_path(av[3], env);
		if (cmd2_path == NULL)
			(perror("Command 2 not found"), exit(EXIT_FAILURE));
		cmd2 = ft_split(cmd2_path, ' ');
		execve(cmd2[0], cmd2, env);
		(perror("execve"), ft_free(cmd2), free(cmd2_path), exit(EXIT_FAILURE));
	}
	return (pid);
}

void	pipex(int fdin, int fdout, char **av, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (pipe(fd) == -1)
		(perror("pipe"), exit(EXIT_FAILURE));
	pid1 = exec_cmd1(av, env, fdin, fd);
	pid2 = exec_cmd2(av, env, fdout, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}



int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;

	if (ac != 5)
	{
		write(2, "Error: invalid number of arguments\n", 35);
		return (1);
	}
	fdin = open(av[1], O_RDONLY, 0777);
	if (fdin == -1)
		(perror("infile"), exit(EXIT_FAILURE));
	fdout = open(av[4], O_WRONLY, O_CREAT | O_TRUNC, 0666);
	if (fdout == -1)
		(perror("outfile"), exit(EXIT_FAILURE));
	pipex(fdin, fdout, av, env);
	close(fdin);
	close(fdout);
	return (0);
}
