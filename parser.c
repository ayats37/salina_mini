/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:17:05 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:55:37 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*sub_left(t_token *token, t_token *opr)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*new_node;
	t_token	*current;

	head = NULL;
	current = token;
	while (current)
	{
		if (current == opr)
			break ;
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (NULL);
		new_node->value = ft_strdup(current->value);
		new_node->type = current->type;
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
		current = current->next;
	}
	return (head);
}

t_token	*get_last_opr(t_token *token, int nb)
{
	size_t	paren;
	t_token	*opr;
	t_token	*tmp;

	opr = NULL;
	paren = 0;
	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == 9)
			paren++;
		else if (tmp->type == 10)
			paren--;
		else if ((tmp->type == 11 || tmp->type == 12) && paren == 0 && nb == 1)
			opr = tmp;
		else if (tmp->type == 2 && paren == 0 && nb == 0)
			opr = tmp;
		tmp = tmp->next;
	}
	return (opr);
}

t_tree	*parse_op(t_token *token)
{
	t_token	*opr;
	t_token	*left_token;
	t_token	*right_token;
	t_token	*tmp;
	t_tree	*node;

	opr = get_last_opr(token, 1);
	left_token = NULL;
	right_token = NULL;
	tmp = token;
	if (opr)
	{
		node = create_tree_node(opr, NULL, NULL);
		left_token = sub_left(tmp, opr);
		right_token = opr->next;
		node->left = parse_op(left_token);
			free_token_list(left_token);
		if (!node->left)
		{
			free(node);
			return (NULL);
		}
		node->right = parse_op(right_token);
		if (!node->right)
		{
			free_tree(node->left);
			free(node);
			return (NULL);
		}
		return (node);
	}
	return (parse_pipes(token));
}

t_tree	*parse_pipes(t_token *token)
{
	t_token	*pipe;
	t_token	*left_token;
	t_token	*right_token;
	t_token	*tmp;
	t_tree	*node;

	pipe = get_last_opr(token, 0);
	left_token = NULL;
	right_token = NULL;
	tmp = token;
	if (pipe)
	{
		node = create_tree_node(pipe, NULL, NULL);
		left_token = sub_left(tmp, pipe);
		right_token = pipe->next;
		node->left = parse_pipes(left_token);
		free_token_list(left_token);
		if (!node->left)
		{
			free(node);
			return (NULL);
		}
		node->right = parse_pipes(right_token);
		if (!node->right)
		{
			free_tree(node->left);
			free(node);
			return (NULL);
		}
		return (node);
	}
	return (parse_paren(token));
}

int	calculate_cmd(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 3 || tmp->type == 4)
			count++;
		if (tmp->type == 5 || tmp->type == 6 || tmp->type == 7
			|| tmp->type == 8)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}
