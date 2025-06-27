/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:42 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:53:29 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_args(char **cmd)
{
	int	argc;

	argc = 0;
	while (cmd[argc])
		argc++;
	if (argc >= 2 && !is_num(cmd[1]))
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	if (argc > 2)
	{
		printf("exit\nbash: exit: too many arguments\n");
		return (-1);
	}
	if (argc == 2)
		return (atoi(cmd[1]));
	return (0);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	ft_exit(char **cmd, t_env *env_list)
{
	int	status;

	status = check_exit_args(cmd);
	if (status == -1)
		return (1);
	free_env_list(env_list);
	printf("exit\n");
	exit(status);
	return (0);
}
