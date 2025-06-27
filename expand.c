/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:50:23 by taya              #+#    #+#             */
/*   Updated: 2025/06/27 15:52:18 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_value(char *token, int *i, t_env *env_list)
{
	int		start;
	int		len;
	char	*var_name;
	char	*val;

	start = *i;
	while (token[*i] && (is_alphanumeric(token[*i]) || token[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = strndup(&token[start], len);
	val = get_env_value(var_name, env_list);
	free(var_name);
	if (val)
		return (strdup(val));
	return (strdup(""));
}

char	*expand_dollar_var(char *token, int *i, t_env *env_list, int last_exit_status)
{
	if (token[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_exit_status));
	}
	if (token[*i] && (token[*i] == '_' || is_alpha(token[*i])))
		return (get_variable_value(token, i, env_list));
	(*i)++;
	return (strdup("$"));
}

char	*expand_token(char *token, t_env *env_list, int last_exit_status)
{
	int		i = 0;
	char	*exp;
	char	*result = strdup("");

	if (!result)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			exp = expand_dollar_var(token, &i, env_list, last_exit_status);
		}
		else
			exp = char_to_str(token[i++]);

		if (!exp)
			return (free(result), NULL);
		result = str_join_free(result, exp);
		free(exp);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	**split_whitespace(char *str)
{
	char	**words;
	int		count = 0;
	int 	i = 0;
	int j;
	int k;

	if (!str || !*str)
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
				i++;
		}
	}
	if (count == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i] && k < count)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			j = i;
			while (str[j] && str[j] != ' ' && str[j] != '\t')
				j++;
			words[k] = strndup(&str[i], j - i);
			if (!words[k])
			{
				while (k > 0)
					free(words[--k]);
				free(words);
				return (NULL);
			}
			k++;
			i = j;
		}
	}
	words[k] = NULL;
	return (words);
}

int	count_tokens(char **tokens)
{
	int count = 0;
	while (tokens && tokens[count])
		count++;
	return count;
}

void	free_token_array(char **tokens)
{
	int i = 0;
	while (tokens && tokens[i])
		free(tokens[i++]);
	free(tokens);
}

char	**insert_tokens(char **tokens, int i, char **new_words)
{
	int old_count = count_tokens(tokens);
	int new_count = count_tokens(new_words);
	int total = old_count - 1 + new_count;

	char **new_tokens = malloc(sizeof(char *) * (total + 1));
	if (!new_tokens)
		return NULL;

	int j = 0;
	int k = 0;
	while (j < i)
	{
		new_tokens[j] = tokens[j];
		j++;
	}
	while (new_words[k])
		new_tokens[j++] = new_words[k++];
	free(tokens[i]);
	i++;
	while (tokens[i])
		new_tokens[j++] = tokens[i++];
	new_tokens[j] = NULL;
	free(tokens); 
	return new_tokens;
}

char **expand_variables(char **tokens, int last_exit_status, t_env *env_list)
{
	int		i = 0, j = 0, k;
	char	**split_words;
	char	**expanded_all;

	expanded_all = malloc(sizeof(char *) * 1024);
	if (!expanded_all)
		return (NULL);
	while (tokens[i])
	{
		char *expanded = expand_token(tokens[i], env_list, last_exit_status);
		if (!expanded)
		{
			i++;
			continue;
		}

		if (ft_strchr(tokens[i], '=') != NULL)
		{
			expanded_all[j++] = expanded;
		}
		else
		{
			split_words = split_whitespace(expanded);
			free(expanded);
			if (split_words)
			{
				k = 0;
				while (split_words[k])
					expanded_all[j++] = split_words[k++];
				free(split_words);
			}
		}
		i++;
	}
	expanded_all[j] = NULL;
	return (expanded_all);
}
