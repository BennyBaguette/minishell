/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:26:01 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/27 19:04:58 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_putenv(t_env *env)
{
	int i;
	char **new;

	i = 0;
	new = ft_list_to_tab(env, 0);
	while (new[i] != 0)
	{
		ft_putstr_fd(new[i++], 1);
		write(1, "\n", 1);
	}
	free_tab(new);
}

char *remove_space(char *str)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[j] != '\0')
	{
		while (str[j] != '\0' && str[j] == ' ' && i == 0)
			j++;
		while (str[j] != '\0' && str[j] != ' ')
			new[i++] = str[j++];
		if (str[j] != '\0' && str[j] == ' ' && (j) < ft_strlen(str))
		{
			new[i++] = ' ';
			while (str[j] != '\0' && str[j] == ' ')
				j++;
		}
	}
	new[i] = '\0';
	free(str);
	return (new);
}
/*
t_env	*get_biggest(char *name, t_env *current, t_env *biggest)
{
	int len;

	len = 0;
	biggest = NULL;
	while (current != NULL)
	{
		if (!ft_strncmp(name, current->name, ft_strlen(current->name)))
		{
			if (ft_strlen(current->name) > len)
			{
				biggest = current;
				len = ft_strlen(current->name);
			}
		}
		current = current->next;
	}
	return (biggest);
}

char *ft_getenv(t_all *all, char *name, int mode)
{
	char *value;
	t_env *current;

	value = NULL;
	if (all->env)
		current = all->env;
	if (name == NULL || name == NULL)
		return (NULL);
	if (name[0] == '?')
		return (all->ret->value);
	value = ft_getenv2(name, current, mode);
	return (value);
}*/

/*
** MODE = 0 : pas de quote donc token tel quel
** MODE = 1 : double quote donc token trim
*/

char *ft_getenv2(char *name, t_env *current, int mode)
{
	if (!(ft_strcmp(name, current->name)))
	{
		if (mode == 0)
			return (ft_strdup(current->value));
		else
			return (remove_space(ft_strdup(current->value)));
	}
	return (NULL);
}

char *ft_getenv(t_all *all, char *name, int mode)
{
    int i;
    int j;
    char *value;
	t_env *current;

    i = 0;
    value = NULL;
	if (all->env)
		current = all->env;
//    if (name == NULL)
//        return (NULL);
	if (name[0] == '?')
		return (all->ret->value);
    while (current != NULL)
    {
        j = 0;
        if (!(ft_strcmp(name, current->name)))
        {
            value = ft_getenv2(name, current, mode);
            break;
        }
        current = current->next;
    }
	value = (current == NULL ? ft_strdup("\0") : value);
    return (value);
}