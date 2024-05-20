/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:45:24 by tlay              #+#    #+#             */
/*   Updated: 2024/05/17 18:10:56 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_paths(int pip_fds[], char **env, char **cmds, t_pipe *pip)
{
	char	**paths;
	int		i;
	bool	path_exist;

	i = 0;
	path_exist = false;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path_exist = true;
			break ;
		}
		i++;
	}
	if (path_exist == false)
	{
		free_tab(cmds);
		error(pip_fds, "path", NULL, pip);
	}
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_right_path(int pip_fds[], char **paths, char **cmds, t_pipe *pip)
{
	int		i;
	char	*right_path;

	i = 0;
	while (paths[i])
	{
		right_path = ft_strjoin(paths[i], "/");
		right_path = str_strjoin(right_path, cmds[0]);
		if (access(right_path, X_OK) == 0)
			return (right_path);
		free(right_path);
		i++;
	}
	free_tab(paths);
	error(pip_fds, "command", cmds, pip);
	return (NULL);
}

void	open_infile(int pip_fds[], t_pipe *pip)
{
	int	fdin;

	if (pip->is_hd == true)
		fdin = open(pip->hd_file, O_RDONLY | 0644);
	else
		fdin = open(pip->infile, O_RDONLY, 0644);
	if (fdin == -1)
		error(pip_fds, "open infile", NULL, pip);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	open_outfile(int pip_fds[], t_pipe *pip)
{
	int	fdout;

	if (pip->is_hd == true)
		fdout = open(pip->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fdout = open(pip->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		error(pip_fds, "open outfile", NULL, pip);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}
