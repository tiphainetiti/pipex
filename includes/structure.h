/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:26:39 by tlay              #+#    #+#             */
/*   Updated: 2024/05/17 16:23:50 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include <stdbool.h>

typedef struct s_pipe
{
	char	*infile;
	char	*outfile;
	char	*last_command;
	int		i;
	int		ac;
	int		count;
	int		prev_pip_read;
	bool	is_hd;
	int		hd_fd;
	char	*hd_file;
	char	*lim;
	int		exit_code;
}			t_pipe;

#endif