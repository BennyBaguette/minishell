/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:30:33 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/05 22:15:38 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** MODE = 0 : NAME
** MODE = 1 : VALUE
*/

int		get_op(char *var)
{
	if (*var == '\0')
		return (0);
	else if (*var == '=')
		return (1);
	else if (ft_strncmp(var, "+=", 2) == 0)
		return (2);
	return (-1);
}

t_env	*elem_dup(t_env *elem)
{
	t_env	*new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->next = NULL;
	if (elem)
	{
		new->name = ft_strdup(elem->name);
		new->godmode = (ft_strcmp(elem->name, "_") == 0 ? 1 : 0);
		new->op = elem->op;
		new->value = ft_strdup(elem->value);
	}
	return (new);
}

t_env	*allocate_elem(t_env *elem, char *var)
{
	if (!(elem = malloc(sizeof(t_env) + 1)))
		return (0);
	if (!(elem->name = malloc(sizeof(char) * ft_varlen(var, 0) + 1)))
	{
		free(elem);
		return (NULL);
	}
	if (!(elem->value = malloc(sizeof(char) * ft_varlen(var, 1) + 1)))
	{
		free(elem->name);
		free(elem);
		return (NULL);
	}
	return (elem);
}

t_env	*new_elem(char *var, int free_)
{
	int		i;
	int		j;
	t_env	*elem;

	i = 0;
	j = 0;
	elem = NULL;
	if (!(elem = allocate_elem(elem, var)))
		return (NULL);
	while (var[i] != '\0' && var[i] != '=' && var[i] != '+')
	{
		elem->name[i] = var[i];
		i++;
	}
	elem->name[i] = '\0';
	elem->godmode = (ft_strcmp(elem->name, "_") == 0 ? 1 : 0);
	i += (elem->op = get_op(var + i));
	while (var[i] != '\0')
		elem->value[j++] = var[i++];
	elem->value[j] = '\0';
	elem->next = NULL;
	if (free_)
		free(var);
	return (elem);
}

t_env	*ft_tab_to_list(char **tab, int erase)
{
	int		i;
	t_env	*head;
	t_env	*current;

	i = 0;
	head = NULL;
	current = NULL;
	if (tab)
	{
		if (tab[i] != NULL)
			current = new_elem(tab[i++], 0);
		head = current;
		while (tab[i] != NULL)
		{
			current->next = new_elem(tab[i++], 0);
			current = current->next;
		}
	}
	if (erase == 1)
		free_tab(tab);
	return (head);
}
