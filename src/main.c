/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:38:00 by alechin           #+#    #+#             */
/*   Updated: 2025/04/02 17:38:00 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("Error: Too many arguments\n");
		return (1);
	}
	if (argc == 5)
	{
		if (pipe(pipex.fd) == -1)
			error2exit("Error: failed to create pipe\n");
		pipex.pid[0] = fork();
		if (pipex.pid[0] == -1)
			error2exit("Error: infile fork didn't work\n");
		if (pipex.pid[0] == 0)
			child(argv, pipex.fd, env);
		pipex.pid[1] = fork();
		if (pipex.pid[1] == -1)
			error2exit("Error: outfile fork didn't work\n");
		if (pipex.pid[1] == 0)
			parent(argv, pipex.fd, env);
		close_pipes(&pipex);
		waitpid(pipex.pid[0], NULL, 0);
		waitpid(pipex.pid[1], &(pipex.stat), 0);
		return (0);
	}
}
