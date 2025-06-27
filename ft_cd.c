/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:19 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:52:56 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(char **cmd, char *oldpwd)
{
	char	*path;

	if (!cmd[1] || strcmp(cmd[1], "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			free(oldpwd);
			return (NULL);
		}
		return (path);
	}
	return (NULL);
}

char	*get_oldpwd_path(char **cmd, char *oldpwd)
{
	char	*path;

	if (cmd[1] && strcmp(cmd[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			printf("minishell: cd: OLDPWD not set\n");
			free(oldpwd);
			return (NULL);
		}
		printf("%s\n", path);
		return (path);
	}
	return (NULL);
}

char	*get_envvar_path(char **cmd, char *oldpwd)
{
	char	*env_name;
	char	*path;

	if (cmd[1] && cmd[1][0] == '$')
	{
		env_name = cmd[1] + 1;
		path = getenv(env_name);
		if (!path)
		{
			printf("minishell: cd: %s: undefined variable\n", cmd[1]);
			free(oldpwd);
			return (NULL);
		}
		return (path);
	}
	return (NULL);
}

char	*get_cd_path(char **cmd, char *oldpwd)
{
	char	*path;

	path = get_home_path(cmd, oldpwd);
	if (path)
		return (path);
	path = get_oldpwd_path(cmd, oldpwd);
	if (path)
		return (path);
	path = get_envvar_path(cmd, oldpwd);
	if (path)
		return (path);
	return (cmd[1]);
}

int	ft_cd(char **cmd, t_env *envlist)
{
	char	*cwd;
	char	*oldpwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (printf("minishell: cd: error retrieving current directory\n")
			, 1);
	oldpwd = ft_strdup(cwd);
	free(cwd);
	path = get_cd_path(cmd, oldpwd);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		free(oldpwd);
		return (1);
	}
	update_pwd_vars(oldpwd, envlist);
	free(oldpwd);
	return (0);
}
