/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:37:57 by alechin           #+#    #+#             */
/*   Updated: 2025/04/02 17:37:57 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute()
{
	return (0);
}

void	child(char **argv, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (!infile || infile == -1)
		error2exit("Error: Infile doesn't exist");
	dup2(infile, 0);
	dup2(fd[1], 1);
	return (0);
}

void	parent(char **argv, int *fd)
{
	int	outfile;

	outfile = open(argv[3], O_WRONLY, O_TRUNC, O_CREAT);
	if (!outfile || outfile == -1)
		error2exit("Error: Outfile doesn't exist");
	dup2(fd[0], 0);
	dup2(outfile, 1);
	return (0);
}

void	get_path(char *prompt, char **env)
{
	int 	i;
	char	*path;
	char	**pathway;
	char	*path_file;

	i = -1;
	path = todo!();
	pathway = todo!();
	while (pathway[++i])
	{

	}
}
