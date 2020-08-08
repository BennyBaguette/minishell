/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:30:12 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/08 13:19:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end(char *buff)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(buff, ' ');
	if (arg[1])
	{
		while (arg[1][i] && ft_isdigit(arg[1][i]) == 0)
			i++;
		if (i == ft_strlen(arg[1]))
		{
			write(1, "bash: exit: ls: numeric argument required\n", 42);
			return (255);
		}
		else
			return (atoi(arg[1]));
	}
	return (0);
}

/* A FAIRE : REMETTRE A LA LIGNE APRES AFFICHAGE ET NE PAS AFFICHER LE REPERTOIRE SUR ANCIENNE LIGNE
** MODE = 0 : NE PAS AFFICHER VAR
** MODE = 1 : AFFICHER VAR
*/
int	ft_put_error(char *error, char *var, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd(" \'", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("\':", 2);
	}
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(error, 2);
	return (-1);
}
