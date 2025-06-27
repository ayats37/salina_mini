/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:54:02 by ouel-afi          #+#    #+#             */
/*   Updated: 2024/11/21 14:30:11 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	size_t	i;

	i = 0;
	tmp = lst;
	if (!lst)
		return (0);
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
