/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:43:04 by tlay              #+#    #+#             */
/*   Updated: 2024/05/20 16:20:18 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	error_execve(char **cmds, int pip_fds[])
{
	write(2, "command couldn't be execute\n", 28);
	free_tab(cmds);
	close(pip_fds[0]);
	close(pip_fds[1]);
	exit(EXIT_FAILURE);
}

void	specify_error(char *str, char **cmds, t_pipe *pip)
{
	if (ft_strncmp(str, "command", ft_strlen(str)) == 0)
	{
		pip->exit_code = 127;
		if (cmds)
		{
			write(2, cmds[0], ft_strlen(cmds[0]));
			free_tab(cmds);
		}
		str = ": command not found\n";
	}
	else if (ft_strncmp(str, "path", ft_strlen(str)) == 0)
		str = "path: path not found\n";
	else if (ft_strncmp(str, "open infile", ft_strlen(str)) == 0)
	{
		write(2, pip->infile, ft_strlen(pip->infile));
		str = ": Bad file descriptor\n";
	}
	else if (ft_strncmp(str, "open outfile", ft_strlen(str)) == 0)
	{
		write(2, pip->outfile, ft_strlen(pip->outfile));
		str = ": Bad file descriptor\n";
	}
	write(2, str, ft_strlen(str));
	exit(pip->exit_code);
}

void	error(int pip_fds[], char *str, char **cmds, t_pipe *pip)
{
	pip->exit_code = 1;
	if (pip_fds[0] > 0)
		close(pip_fds[0]);
	if (pip_fds[1] > 0)
		close(pip_fds[1]);
	if (ft_strncmp(str, "command", ft_strlen(str)) == 0 || ft_strncmp(str,
			"path", ft_strlen(str)) == 0 || ft_strncmp(str, "open infile",
			ft_strlen(str)) == 0 || ft_strncmp(str, "open outfile",
			ft_strlen(str)) == 0)
		specify_error(str, cmds, pip);
	else
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}
