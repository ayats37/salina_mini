/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:09:13 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:54:35 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_quote(t_lexer *lexer, char quote)
{
	t_token *token = NULL;
	size_t	lenght;
	size_t	start;
	char	*value;

	lexer->position += 1;
	start = lexer->position;
	while (lexer->position < lexer->lenght
		&& lexer->input[lexer->position] != quote)
		lexer->position++;
	if (lexer->position >= lexer->lenght)
	{
		ft_putstr_fd("bash : syntax error unclosed quote\n", 2);
		return (0);
	}
	lenght = lexer->position - start;
	value = ft_substr(lexer->input, start, lenght);
	lexer->position += 1;
	if (lexer->input[lexer->position] == 32)
		token = create_token(value, quote, 1);
	else
		token = create_token(value, quote, 0);
	free(value);
	return (token);
}

t_token	*handle_operations(t_lexer *lexer, char *oper, int i)
{
	char	*str;
	t_token *token;

	str = ft_substr(oper, 0, i);
	if (!str)
		return (NULL);
	lexer->position += i;
	if (lexer->input[lexer->position] == 32)
		token = create_token(str, str[0], 1);
	else
		token = create_token(str, str[0], 0);
	free(str); 
	return (token);
}

