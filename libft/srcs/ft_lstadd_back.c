/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:43:47 by tlay              #+#    #+#             */
/*   Updated: 2024/04/22 19:23:49 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*element;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	element = *lst;
	while (element && element->next)
		element = element->next;
	element->next = new;
	return ;
}
