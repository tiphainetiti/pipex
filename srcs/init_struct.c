/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:43 by tlay              #+#    #+#             */
/*   Updated: 2024/05/17 16:04:53 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_struct(int ac, t_pipe *pip)
{
	pip->infile = NULL;
	pip->outfile = NULL;
	pip->last_command = NULL;
	pip->i = 0;
	pip->ac = ac;
	pip->count = 0;
	pip->prev_pip_read = -1;
	pip->is_hd = false;
	pip->hd_file = NULL;
	pip->lim = NULL;
	pip->exit_code = 0;
}

void	get_struct(char **av, t_pipe *pip)
{
	pip->last_command = av[pip->ac - 2];
	pip->outfile = av[pip->ac - 1];
	pip->infile = av[1];
	if (pip->ac == 6 && pip->infile && ft_strncmp(pip->infile, "here_doc",
			ft_strlen(pip->infile)) == 0)
	{
		pip->is_hd = true;
		pip->lim = av[2];
		pip->i = 1;
	}
	if (!pip->last_command || !pip->outfile || !pip->infile)
	{
		perror("struct");
		exit(pip->exit_code);
	}
}
