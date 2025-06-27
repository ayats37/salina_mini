/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:23:48 by ouel-afi          #+#    #+#             */
/*   Updated: 2024/11/19 23:10:47 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void print_str(unsigned int i, char *s)
// {
// 	printf("Index: %d, Value: %c\n", i, *s);
// }

// int main()
// {
// 	void (*f)(char *, void (unsigned int, char *)) = ft_striteri;

// 	char s[] = "abcd";
// 	f(s,print_str);
// }