/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:10:24 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/26 18:08:32 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	pipes_parent(t_all *all, int fd[all->tube][2])
{
	if (all->around == 0)
	{
		close(fd[all->here - 1][0]);
	}
	if (all->around == 1)
	{
		close(fd[all->here][1]);
	}
	if (all->around == 2)
	{
		close(fd[all->here - 1][0]);
		close(fd[all->here][1]);
	}
}

void	pipes_child(t_all *all, int fd[all->tube][2])
{
	if (all->around == 2)
	{
		if (all->fds[0] == 0)
			dup2(fd[all->here - 1][0], STDIN_FILENO);
		if (all->fds[1] == 1)
			dup2(fd[all->here][1], STDOUT_FILENO);
	}
	else if (all->around == 0 && all->fds[0] == 0)
		dup2(fd[all->here - 1][0], STDIN_FILENO);
	else if (all->around == 1 && all->fds[1] == 1)
		dup2(fd[all->here][1], STDOUT_FILENO);
	close_pipes(all, fd);
}

void	open_pipes(t_all *all, int fd[all->tube][2])
{
	int		i;

	i = 0;
	while (i < all->tube)
		pipe(fd[i++]);
}

void	close_pipes(t_all *all, int fd[all->tube][2])
{
	int		i;

	i = 0;
	while (i < all->tube)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}
