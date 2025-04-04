/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:37:54 by alechin           #+#    #+#             */
/*   Updated: 2025/04/02 17:37:54 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int	fd[2];
	int	pid[2];
	int	stat;
}	t_pipex;

//Errors;
void	error2exit(char *message, int status);

//Pipex;
void	execute(char *argv, char **env);
void	child(char **argv, int *fd, char **env);
void	parent(char **argv, int *fd, char **env);
void	free_pipex(char **paths);

#endif