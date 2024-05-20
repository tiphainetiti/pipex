/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:08:30 by tlay              #+#    #+#             */
/*   Updated: 2024/05/20 16:10:19 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	create_here_doc(int pip_fds[], t_pipe *pip)
{
	int		i;
	char	*str_i;

	i = 0;
	while (1)
	{
		str_i = ft_itoa(i);
		if (!str_i)
			error(pip_fds, "str", NULL, pip);
		pip->hd_file = ft_strjoin("here_doc_", str_i);
		free(str_i);
		if (!pip->hd_file)
			error(pip_fds, "str", NULL, pip);
		if (access(pip->hd_file, F_OK) == -1)
			break ;
		free(pip->hd_file);
		i++;
	}
	pip->hd_fd = open(pip->hd_file, O_CREAT | O_WRONLY, 0644);
	if (pip->hd_fd == -1)
		error(pip_fds, "create here_doc", NULL, pip);
}

void	stop_here_doc(t_pipe *pip)
{
	write(2, "\nwarning: here-document delimited by end-of-file (wanted '", 59);
	write(2, pip->lim, ft_strlen(pip->lim));
	write(2, "')\n", 3);
}

void	ft_here_doc(int pip_fds[], t_pipe *pip)
{
	char	*str;
	size_t	len_str;

	create_here_doc(pip_fds, pip);
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
		{
			stop_here_doc(pip);
			break ;
		}
		len_str = ft_strlen(str) - 1;
		if (ft_strncmp(str, pip->lim, ft_strlen(pip->lim)) == 0
			&& (len_str == ft_strlen(pip->lim)))
			break ;
		write(pip->hd_fd, str, ft_strlen(str));
		free(str);
	}
	if (str)
		free(str);
}
