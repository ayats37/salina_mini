/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:02:09 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:56:07 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_tree *node, int depth, const char *side)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf("[%s]", side);
	if (node->value)
		printf(" | value: %s", node->value);
	// 🔽 Print cmd if present
	if (node->cmd)
	{
		printf(" | cmd:");
		for (int i = 0; node->cmd[i]; i++)
			printf(" '%s'", node->cmd[i]);
	}
	if (node->redir)
	{
		printf("\nREDIR:    ");
		print_linked_list(node->redir);
	}
	printf("\n");
	print_tree(node->left, depth + 1, "L");
	print_tree(node->right, depth + 1, "R");
}

void	print_linked_list(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		printf("token->value = %s		token->type =%dtoken->has_space = %d\n",
				current->value,
				current->type,
				current->has_space);
		current = current->next;
	}
}
