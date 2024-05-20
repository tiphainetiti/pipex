/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlay <tlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:06:50 by tlay              #+#    #+#             */
/*   Updated: 2024/05/20 16:26:05 by tlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "structure.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

void	print_tab(char **table, char *element);

// my_strjoin.c
char	*my_strjoin(char *s1, char *s2);

// error.c
void	print_error(char *str);
void	error_execve(char **cmds, int pip_fds[]);
void	error(int pip_fds[], char *str, char **cmds, t_pipe *pip);

// exec.c
void	exec(int pip_fds[], char **env, char *cmd, t_pipe *pip);
void	exec_cmd_in(char **av, char **env, int pip_fds[], t_pipe *pip);
void	exec_cmd_out(char **env, int pip_fds[], t_pipe *pip);

// utils.c
void	free_tab(char **tab);
char	*str_strjoin(char *str1, char *str2);

// exec_utils.c
char	**get_paths(int pip_fds[], char **env, char **cmds, t_pipe *pip);
char	*get_right_path(int pip_fds[], char **paths, char **cmds, t_pipe *pip);
void	open_infile(int pip_fds[], t_pipe *pip);
void	open_outfile(int pip_fds[], t_pipe *pip);

// init_struct.c
void	init_struct(int ac, t_pipe *pip);
void	get_struct(char **av, t_pipe *pip);

// here_doc.c
void	create_here_doc(int pip_fds[], t_pipe *pip);
void	stop_here_doc(t_pipe *pip);
void	ft_here_doc(int pip_fds[], t_pipe *pip);

#endif