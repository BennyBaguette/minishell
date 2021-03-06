/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:31:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/09 14:34:47 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	joinjoin(t_all *all, char *buff, int *inc, int i)
{
	char	*tmp;

	(*inc)--;
	tmp = ft_strdup(all->dir[*inc]);
	free(all->dir[*inc]);
	all->dir[*inc] = malloc(sizeof(char) * i + ft_strlen(tmp) + 1);
	all->dir[*inc] = ft_strncpy(all->dir[*inc], tmp, ft_strlen(tmp));
	all->dir[*inc] = ft_strncat(all->dir[*inc], buff + 2, i - 2);
	croco(all, all->dir[*inc], ft_strlen(all->dir[*inc]), *inc);
	if (itscroco(all->dir[*inc][0]) == 1 || itscroco(all->dir[*inc][1]) == 1)
		all->shouldi[*inc] = 2;
	if (all->shouldi[(*inc) + 1])
		all->shouldi[(*inc) + 1] = 1;
	free(tmp);
}

int		crontold(t_all *all)
{
	char	*tmp[2];

	while (all->buff && ft_strlen(all->buff) > 0 && all->i == 0
			&& g_freete == 0)
	{
		tmp[0] = ft_strdup(all->buff);
		free(all->buff);
		all->i = get_next_line(0, &all->buff);
		tmp[1] = ft_strdup(all->buff);
		free(all->buff);
		all->buff = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
	}
	return (1);
}
