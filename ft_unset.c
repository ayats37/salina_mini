/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:52 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:54:00 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(t_env **env_list, char *name)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (strcmp(name, curr->name) == 0)
		{
			if (!prev)
				*env_list = curr->next;
			else
				prev->next = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **cmd, t_env **env_list)
{
	int	i;

	i = 1;
	if (!cmd || !cmd[i])
		return (1);
	while (cmd[i])
	{
		unset_var(env_list, cmd[i]);
		i++;
	}
	return (1);
}
