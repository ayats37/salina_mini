/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:14:45 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:49:53 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_start(t_token *token)
{
	if (token->type == 2 || token->type == 11 || token->type == 12)
	{
		printf("bash: syntax error near unexpected token `%s'\n", token->value);
		return (1);
	}
	return (0);
}

int	newline_after_op(t_token *token)
{
	if ((token->type == 2 || token->type == 5 || token->type == 6
			|| token->type == 7 || token->type == 8 || token->type == 9
			|| token->type == 11 || token->type == 12) && !token->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	two_operator(t_token *token)
{
	if ((token->type == 2 || token->type == 5 || token->type == 6
			|| token->type == 7 || token->type == 8 || token->type == 11
			|| token->type == 12) && token->next && (token->next->type == 2
			|| token->next->type == 5 || token->next->type == 6
			|| token->next->type == 7 || token->next->type == 8
			|| token->next->type == 11 || token->next->type == 12
			|| token->next->value[0] == '&'))
	{
		printf("bash: syntax error near unexpected token `%s'\n",
			token->next->value);
		return (1);
	}
	return (0);
}

int	opr_before_close_paren(t_token *token)
{
	if ((token->type != 1 && token->type != 3 && token->type != 4
			&& token->type != 10) && token->next && token->next->type == 10)
	{
		printf("bash: syntax error near unexpected token `)'\n");
		return (1);
	}
	return (0);
}

int	check_errors(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (0);
	if (invalid_start(token))
		return (1);
	tmp = token;
	while (tmp)
	{
		if (newline_after_op(tmp))
			return (1);
		if (opr_before_close_paren(tmp))
			return (1);
		if (two_operator(tmp))
			return (1);
		if (check_before_open_paren(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
