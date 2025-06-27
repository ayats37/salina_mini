/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:45 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:53:39 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!is_alpha(*str) && *str != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!is_alphanumeric(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	parse_export_arg(char *arg, char **name, char **value, int *append)
{
	char	*equal_sign;

	*append = 0;
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign == arg)
		return (printf("minishell: export: `%s': not a valid identifier\n", arg)
			, 1);
	if (equal_sign > arg + 1 && *(equal_sign - 1) == '+')
	{
		*append = 1;
		*name = ft_substr(arg, 0, equal_sign - arg - 1);
	}
	else
		*name = ft_substr(arg, 0, equal_sign - arg);
	if (!*name || !valid_identifier(*name))
	{
		if (*name)
			free(*name);
		return (printf("minishell: export: `%s': not a valid identifier\n", arg)
			, 1);
	}
	*value = ft_strdup(equal_sign + 1);
	return (0);
}

int	process_export(char *arg, t_env **env_list)
{
	char	*name;
	char	*value;
	int		append;

	if (parse_export_arg(arg, &name, &value, &append))
		return (1);
	if (append)
		env_append(name, value, env_list);
	else
		update_env(name, value, env_list);
	free(name);
	free(value);
	return (0);
}

int	ft_export(char **cmd, t_env **env_list)
{
	int		status;
	int		i;

	status = 0;
	i = 1;
	if (!cmd || !cmd[i])
		return (1);
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '='))
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			status = 1;
		}
		else if (process_export(cmd[i], env_list) != 0)
		status = 1;
		i++;
	}
		
	return (status);
}
