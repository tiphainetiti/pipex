/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:06:27 by tlay              #+#    #+#             */
/*   Updated: 2024/05/20 16:10:27 by tlay             ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	int		pip_fds[2];
	t_pipe	pip;

	init_struct(ac, &pip);
	if (ac == 5)
	{
		get_struct(av, &pip);
		if (pipe(pip_fds) == -1)
			return (perror("pipe"), 0);
		pipex(av, env, pip_fds, &pip);
	}
	else
		print_error("Wrong number of arguments.");
	return (pip.exit_code);
}
