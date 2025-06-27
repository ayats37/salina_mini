/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:17:48 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/27 15:54:22 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (ft_strchr("|<>()&", c) != NULL);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	handle_word_quote(char **result, t_lexer *lexer, int *in_quotes)
{
	char	quote;
	char	*temp;
	char	*new_result;
	size_t	start;

	quote = lexer->input[lexer->position++];
	start = lexer->position;
	*in_quotes = 1;
	while (lexer->position < lexer->lenght
		&& lexer->input[lexer->position] != quote)
		lexer->position++;
	if (lexer->position >= lexer->lenght)
	{
		ft_putstr_fd("bash : syntax error unclosed quotes\n", 2);
		return ;
	}
	temp = ft_substr(lexer->input, start, lexer->position - start);
	new_result = ft_strjoin(*result, temp);
	free(*result);
	*result = new_result;
	lexer->position++;
	*in_quotes = 0;
	free(temp);
}

void	handle_plain_word(char **result, t_lexer *lexer)
{
	size_t	start;
	char	*temp;
	char	*new_result;

	start = lexer->position;
	while (lexer->position < lexer->lenght && !ft_strchr("\"'|<>()& ",
			lexer->input[lexer->position]))
		lexer->position++;
	temp = ft_substr(lexer->input, start, lexer->position - start);
	new_result = ft_strjoin(*result, temp);
	free(temp);
	free(*result);
	*result = new_result;
}

t_token	*handle_word(t_lexer *lexer)
{
	char	*result;
	int		has_space;
	int		in_quotes;
	t_token	*token;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	in_quotes = 0;
	while (lexer->position < lexer->lenght && !is_space(lexer))
	{
		if (is_quote(lexer->input[lexer->position]))
			handle_word_quote(&result, lexer, &in_quotes);
		else if (!in_quotes && is_special_char(lexer->input[lexer->position]))
			break ;
		else
			handle_plain_word(&result, lexer);
	}
	if (lexer->position < lexer->lenght && lexer->input[lexer->position] == ' ')
		has_space = 1;
	else
		has_space = 0;
	token = create_token(result, 0, has_space);
	free(result);
	return (token);
}
