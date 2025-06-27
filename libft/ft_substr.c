/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:03:06 by ouel-afi          #+#    #+#             */
/*   Updated: 2024/11/14 21:19:22 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (start >= n)
		return (ft_strdup(""));
	if (start + len > n)
		len = n - start;
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
