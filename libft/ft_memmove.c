/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:14:34 by ouel-afi          #+#    #+#             */
/*   Updated: 2024/11/13 17:11:05 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	i = 0;
	dst = (unsigned char *)dest;
	src = (unsigned char *)source;
	if (dst == src)
		return (src);
	if (dst > src)
	{
		while (i < n)
		{
			n--;
			dst[n] = src[n];
		}
	}
	else
	{
		ft_memcpy(dst, src, n);
	}
	return (dst);
}
