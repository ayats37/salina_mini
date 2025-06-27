/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:20:13 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:51:14 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*create_tree_node(t_token *token, char **cmd, t_token *redir)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);

    node->cmd = NULL;
    node->redir = NULL;
    node->value = NULL;
    node->left = NULL;
    node->right = NULL;
    node->has_space = 0;
    node->type = 0;

	if (cmd != NULL)
		node->cmd = cmd;
	if (redir)
		node->redir = redir;
	else if (!redir)
		node->redir = NULL;
	node->has_space = token->has_space;
	node->type = token->type;
	if (token->next && token->next->next
		&& token->next->next->type == 1 && (token->type == 5
			|| token->type == 6 || token->type == 7 || token->type == 8))
	{
		node->value = token->next->next->value;
		node->type = 1;
	}
	else
		node->value = token->value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
