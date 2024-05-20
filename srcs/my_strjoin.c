/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:25:06 by tlay              #+#    #+#             */
/*   Updated: 2024/05/03 17:33:43 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	size;
	char	*table;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = -1;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	table = (char *)malloc((size + 1) * sizeof(char));
	if (table == NULL)
		return (NULL);
	while (s1[++i])
		table[i] = s1[i];
	table[i++] = '/';
	while (s2[j])
		table[i++] = s2[j++];
	table[i] = '\0';
	return (table);
}

// int	main(void)
//{
//	char	*s1;
//	char	*s2;
//	char	*path;

//	s1 = "path";
//	s2 = "ls";
//	path = my_strjoin(s1, s2);
//	printf("path: %s\n", path);
//	free(path);
//	return (0);
//}
