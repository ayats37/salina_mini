/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:52:12 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:49:23 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env *envlist)
{
	t_env	*current;

	current = envlist;
	while (current)
	{
		if (strcmp(current->name, "PATH") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	**get_paths(t_env **envlist)
{
	char	*path_string;
	char	**paths;

	if (!envlist || !*envlist)
		return (NULL);
	path_string = get_path(*envlist);
	if (!path_string)
	{
		perror("path not found");
		return (NULL);
	}
	paths = ft_split(path_string, ':');
	if (!paths)
		perror("path split failed");
	return (paths);
}

char	*build_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*check_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		full_path = build_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_env **envlist)
{
	char	**paths;
	char	*result;

	if (!cmd)
		return (NULL);
	paths = get_paths(envlist);
	if (!paths)
		return (NULL);
	result = check_paths(paths, cmd);
	ft_free_arr(paths);
	return (result);
}
