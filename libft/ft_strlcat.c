/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:45:58 by ouel-afi          #+#    #+#             */
/*   Updated: 2024/11/14 20:51:11 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	if (!dest && destsize == 0)
		return (len_src);
	len_dest = ft_strlen(dest);
	if (len_dest >= destsize)
		return (destsize + len_src);
	while (src[i] && len_dest + i < destsize - 1)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (len_src + len_dest);
}
