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

static char	*get_path(char *prompt, char **env);

void	execute(char *argv, char **env)
{
	int		i;
	char	**prompt;
	char	*path;

	i = -1;
	prompt = ft_split(argv, ' ');
	path = get_path(prompt[0], env);
	if (!path)
	{
		while (prompt[++i])
			free(prompt[i]);
		free(prompt);
		free(path);
		error2exit("Error: Path not found\n", 127);
	}
	if (execve(path, prompt, env) == -1)
		error2exit("Error: Problem in file\n", 1);
}

void	child(char **argv, int *fd, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (!infile || infile == -1)
		error2exit("Error: Infile doesn't exist\n", 1);
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(argv[2], env);
}

void	parent(char **argv, int *fd, char **env)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!outfile || outfile == -1)
		error2exit("Error: Outfile doesn't exist\n", 1);
	dup2(fd[0], 0);
	dup2(outfile, 1);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(argv[3], env);
}

static char	*get_path(char *prompt, char **env)
{
	int		i;
	char	*path;
	char	**pathway;
	char	*path_finder;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	pathway = ft_split(env[i] + 5, ':');
	i = -1;
	while (pathway[++i])
	{
		path_finder = ft_strjoin(pathway[i], "/");
		path = ft_strjoin(path_finder, prompt);
		free(path_finder);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_pipex(pathway);
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
