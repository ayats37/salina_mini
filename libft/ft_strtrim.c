/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:54:15 by ouel-afi          #+#    #+#             */
/*   Updated: 2024/11/15 17:25:37 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_start(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		while (s1[i] != set[j] && set[j])
		{
			j++;
		}
	}
	return (i);
}

static size_t	check_end(const char *s1, const char *set)
{
	size_t	len;
	size_t	j;

	j = 0;
	len = ft_strlen(s1) - 1;
	while (len > 0)
	{
		if (s1[len] == set[j])
		{
			len--;
			j = 0;
		}
		while (s1[len] != set[j] && set[j])
		{
			j++;
		}
		if (set[j] == '\0')
			return (len);
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	j = 0;
	i = check_start(s1, set);
	len = check_end(s1, set);
	if (ft_strlen(s1) == 0 || i > len)
		return (ft_strdup(""));
	str = malloc((len - i + 1) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (i < len + 1)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
