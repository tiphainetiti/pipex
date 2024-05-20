/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:46:55 by tlay              #+#    #+#             */
/*   Updated: 2024/05/17 18:06:39 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec(int pip_fds[], char **env, char *cmd, t_pipe *pip)
{
	char	**paths;
	char	**cmds;
	char	*right_path;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
		error(pip_fds, "str", NULL, pip);
	if (ft_strrchr(cmds[0], '/') && access(cmds[0], X_OK) == 0)
	{
		if (execve(cmds[0], cmds, env) < 0)
			error_execve(cmds, pip_fds);
	}
	else
	{
		paths = get_paths(pip_fds, env, cmds, pip);
		right_path = get_right_path(pip_fds, paths, cmds, pip);
		free_tab(paths);
		if (execve(right_path, cmds, env) < 0)
		{
			free(right_path);
			error_execve(cmds, pip_fds);
		}
	}
}

void	exec_cmd_in(char **av, char **env, int pip_fds[], t_pipe *pip)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(pip_fds, "fork", NULL, pip);
	if (pid == 0)
	{
		if (pip->i == 0 || (pip->i == 1 && pip->is_hd == true))
			open_infile(pip_fds, pip);
		if (av[pip->i + 2] && ft_strlen(av[pip->i + 2]) == 0)
		{
			if (pip->prev_pip_read != -1)
				close(pip->prev_pip_read);
			error(pip_fds, "command", NULL, pip);
		}
		else if (pip->prev_pip_read > 0)
		{
			dup2(pip->prev_pip_read, STDIN_FILENO);
			close(pip->prev_pip_read);
		}
		close(pip_fds[0]);
		(dup2(pip_fds[1], STDOUT_FILENO), close(pip_fds[1]));
		exec(pip_fds, env, av[pip->i + 2], pip);
		exit(EXIT_FAILURE);
	}
}

void	exec_cmd_out(char **env, int pip_fds[], t_pipe *pip)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error(pip_fds, "fork", NULL, pip);
	if (pid == 0)
	{
		open_outfile(pip_fds, pip);
		if (pip->last_command && ft_strlen(pip->last_command) == 0)
			error(pip_fds, "command", NULL, pip);
		close(pip_fds[1]);
		dup2(pip_fds[0], STDIN_FILENO);
		close(pip_fds[0]);
		exec(pip_fds, env, pip->last_command, pip);
		exit(EXIT_FAILURE);
	}
	close(pip_fds[0]);
	close(pip_fds[1]);
	while (errno != ECHILD)
	{
		if (wait(&status) == pid && WIFEXITED(status))
			pip->exit_code = WEXITSTATUS(status);
	}
}
