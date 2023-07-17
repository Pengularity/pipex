/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:06:58 by pengu             #+#    #+#             */
/*   Updated: 2023/07/17 20:26:55 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"

char    *search_in_path(char *cmd, char **paths);
char    *get_cmd_path(char *cmd, char **envp);

int     exec_cmd1(char **av, char **env, int fdin, int *fd);
int     exec_cmd2(char **av, char **env, int fdout, int *fd);
void    pipex(int fdin, int fdout, char **av, char **env);

#endif