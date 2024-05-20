/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:06:27 by tlay              #+#    #+#             */
/*   Updated: 2024/05/20 16:29:59 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	print_tab(char **tab, char *element)
//{
//	int	i;

//	i = 0;
//	while (tab[i])
//	{
//		printf("%s[%d] : %s\n", element, i, tab[i]);
//		i++;
//	}
//}

void	pipex(char **av, char **env, int pip_fds[], t_pipe *pip)
{
	exec_cmd_in(av, env, pip_fds, pip);
	exec_cmd_out(env, pip_fds, pip);
}

int	pipex_bonus(char **av, char **env, int pip_fds[], t_pipe *pip)
{
	if (pip->is_hd == false)
	{
		while (pip->i + 2 < pip->ac - 2)
		{
			if (pipe(pip_fds) == -1)
				return (perror("pipe"), pip->exit_code);
			exec_cmd_in(av, env, pip_fds, pip);
			close(pip_fds[1]);
			if (pip->prev_pip_read != -1)
				close(pip->prev_pip_read);
			pip->prev_pip_read = pip_fds[0];
			pip->i++;
		}
		exec_cmd_out(env, pip_fds, pip);
	}
	else if (pip->is_hd == true)
	{
		if (pipe(pip_fds) == -1)
			return (perror("pipe"), pip->exit_code);
		ft_here_doc(pip_fds, pip);
		close(pip->hd_fd);
		pipex(av, env, pip_fds, pip);
	}
	return (pip->exit_code);
}

int	main(int ac, char **av, char **env)
{
	int		pip_fds[2];
	t_pipe	pip;

	init_struct(ac, &pip);
	if (ac >= 5)
	{
		get_struct(av, &pip);
		if (ac == 5)
		{
			if (pipe(pip_fds) == -1)
				return (perror("pipe"), pip.exit_code);
			pipex(av, env, pip_fds, &pip);
		}
		else if (ac > 5)
			pip.exit_code = pipex_bonus(av, env, pip_fds, &pip);
		if (pip.hd_file)
		{
			unlink(pip.hd_file);
			free(pip.hd_file);
		}
	}
	else
		print_error("Wrong number of arguments.");
	return (pip.exit_code);
}
