/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:31:48 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:51:39 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	
	new_node->next = NULL;
	equal_sign = strchr(env_var, '=');
	
	if (equal_sign)
	{
		new_node->name = strndup(env_var, equal_sign - env_var);
		if (!new_node->name)
		{
			free(new_node);
			return (NULL);
		}
		new_node->value = strdup(equal_sign + 1);
		if (!new_node->value)
		{
			free(new_node->name);
			free(new_node);
			return (NULL);
		}
	}
	else
	{
		new_node->name = strdup(env_var);
		if (!new_node->name)
		{
			free(new_node);
			return (NULL);
		}
		new_node->value = NULL;
	}
	return (new_node);
}

void	add_to_env_list(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (*head == NULL)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_env_list(head); 
			return (NULL);
		}
		add_to_env_list(&head, new_node);
		i++;
	}
	return (head);
}

char	**env_list_to_array(t_env *env_list)
{
	char	**env_array;
	int		count;
	int		i;
	t_env	*curr;

	if (!env_list)
		return (NULL);
	count = count_env_nodes(env_list);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	curr = env_list;
	i = 0;
	while (curr)
	{
		env_array[i] = build_env_string(curr->name, curr->value);
		if (!env_array[i])
			return (free_env_array_partial(env_array, i), NULL);
		curr = curr->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*build_env_string(char *name, char *value)
{
	char	*temp;
	char	*result;

	if (!name)
		return (NULL);
	if (!value)
		return (ft_strdup(name));
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}
