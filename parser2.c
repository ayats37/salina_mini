/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:02 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:55:49 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_invalid_paren(t_token *token)
{
	while (token)
	{
		if (token->type == 9 || token->type == 10)
			return (1);
		token = token->next;
	}
	return (0);
}

int	fill_args_and_redirs(t_token *tmp, char **cmd_args, t_token **redir)
{
	t_token	*new_redir;
	t_token	*redir_tail;
	int		last_type;
	int		i;

	redir_tail = NULL;
	i = 0;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 3 || tmp->type == 4)
			cmd_args[i++] = ft_strdup(tmp->value);
		else if (tmp->next)
		{
			last_type = tmp->type;
			tmp = tmp->next;
			new_redir = create_token(tmp->value, 0, 0);
			new_redir->type = last_type;
			new_redir->next = NULL;
			if (!*redir)
				*redir = new_redir;
			else
				redir_tail->next = new_redir;
			redir_tail = new_redir;
		}
		tmp = tmp->next;
	}
	return (i);
}

t_tree	*parse_cmd(t_token *token)
{
	t_token	*redir;
	char	**cmd_args;
	int		nb_cmd;
	int		i;

	redir = NULL;
	i = 0;
	if (!token)
		return (NULL);
	if (has_invalid_paren(token))
	{
		printf("bash : syntax error parenthesis\n");
		return (NULL);
	}
	nb_cmd = calculate_cmd(token);
	cmd_args = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!cmd_args)
		return (NULL);
	i = fill_args_and_redirs(token, cmd_args, &redir);
	if (i == -1)
	{
		free(cmd_args);
		return (NULL);
	}
	cmd_args[i] = NULL;
	return (create_tree_node(token, cmd_args, redir));
}

t_token	*find_matching_paren(t_token *token)
{
	t_token	*tmp;
	size_t	paren;

	tmp = token;
	paren = 0;
	while (tmp)
	{
		if (tmp->type == 9)
			paren++;
		else if (tmp->type == 10)
			paren--;
		if (paren == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tree	*parse_paren(t_token *token)
{
	t_token	*closing;
	t_token	*sub_token;

	if (!token || token->type != 9)
		return (parse_cmd(token));
	closing = find_matching_paren(token);
	if (!closing)
	{
		printf("bash : syntax unmatched parenthesis\n");
		return (NULL);
	}
	sub_token = sub_left(token->next, closing);
	if (!sub_token)
	{
		printf("bash: syntax error unclosed quote\n");
		return (NULL);
	}
	return (parse_op(sub_token));
}
