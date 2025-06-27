/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:04:35 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 16:05:11 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthesis(t_token *token)
{
	int		paren;
	t_token	*tmp;

	paren = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == 9)
			paren++;
		else if (tmp->type == 10)
			paren--;
		tmp = tmp->next;
	}
	if (paren != 0)
	{
		ft_putstr_fd("bash : syntax unmatched parenthesis\n", 2);
		return (paren);
	}
	return (0);
}

int	check_before_open_paren(t_token *token)
{
	if ((token->type == 10 || token->type == 5 || token->type == 6
			|| token->type == 7 || token->type == 8) && token->next
		&& token->next->type == 9)
	{
		printf("bash: syntax error near unexpected token `('\n");
		return (1);
	}
	return (0);
}
