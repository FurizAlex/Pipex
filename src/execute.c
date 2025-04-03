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

void	execute(char **argv, char **env)
{
	int		i;
	char	*prompt;
	char	**path;

	i = -1;
	prompt = ft_split(argv[i], ' ');
	path = get_path(prompt, env[i]);
	if (!path)
	{
		while (prompt[i++])
			free(prompt[i]);
		free(prompt);
		error2exit("Error: Path not found");
	}
	if (execve(path, argv[i], env[i]) == -1)
		error2exit("Error: Problem in file");
}

void	child(char **argv, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (!infile || infile == -1)
		error2exit("Error: Infile doesn't exist");
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(infile);
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
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	return (0);
}

char	get_path(char *prompt, char **env)
{
	int 	i;
	char	*path;
	char	**pathway;
	char	*path_finder;

	i = -1;
	path = NULL;
	pathway = ft_split(env[i] + 5, ":");
	while (ft_strnstr(env[i], "PATH=", 5))
		i++;
	while (pathway[++i] == NULL)
	{
		path_finder = ft_strjoin(pathway[i], "/");
		path = ft_strjoin(path_finder, prompt);
		free(path_finder);
		if (access(path, F_OK) == 0)
			return (path);
		if (!path)
			break;
		free(path);
	}
	free(pathway);
	return (NULL);
}

void	free_pipex(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		free(paths[i]);
	}
	free(paths);
}
