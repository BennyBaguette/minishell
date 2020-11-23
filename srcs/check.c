/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:40:00 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/23 13:44:05 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		bouclebis(char *buff, int i, char quote)
{
	i++;
	while (buff[i] && buff[i] != quote)
		i++;
	if (buff[i] != quote)
		return (-666);
	else if (buff[i] == quote)
		i++;
	return (i);
}

int		whilewell(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] && buff[i] == 34)
		{
			if (bouclebis(buff, i, 34) < i)
				return (0);
			else
				i = bouclebis(buff, i, 34);
		}
		else if (buff[i] && buff[i] == 39)
		{
			if (bouclebis(buff, i, 39) < i)
				return (0);
			else
				i = bouclebis(buff, i, 39);
		}
		else
			i = (buff[i]) ? i + 1 : i;
	}
	return (1);
}

int		checkquote(t_all all, char *buff)
{
	if (pipecount(all, buff, '|') < 0)
		return (1);
	if (!whilewell(buff))
		return (1);
	return (0);
}

int		checksquote(char *buff)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		while (buff[i] && (buff[i] != 39))
			i++;
		if (buff[i] && buff[i] == 39)
		{
			a++;
			i++;
		}
	}
	return (a);
}

int		checkdquote(char *buff)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		while (buff[i] && (buff[i] != 34))
			i++;
		if (buff[i] && buff[i] == 34)
		{
			a++;
			i++;
		}
	}
	return (a);
}
