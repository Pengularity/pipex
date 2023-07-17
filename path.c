/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:48:38 by pengu             #+#    #+#             */
/*   Updated: 2023/07/17 20:41:39 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_in_path(char *cmd, char **paths)
{
	char	*full_path;
	int		j;

	full_path = NULL;
	j = 0;
	while (paths[j])
	{
		full_path = ft_strjoin(ft_strjoin(paths[j], "/"), cmd);
		if (access(full_path, F_OK) != -1)
			break ;
		free(full_path);
		full_path = NULL;
		j++;
	}
	return (full_path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;
	int		j;

	paths = NULL;
	full_path = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
	{
		paths = ft_split(envp[i] + 5, ':');
		full_path = search_in_path(cmd, paths);
		j = 0;
		while (paths[j])
		{
			free(paths[j]);
			j++;
		}
		free(paths);
	}
	return (full_path);
}
