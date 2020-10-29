/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:46:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/29 11:34:56 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
**	MODE 0 : Si le dernier char est un '/'
**	MODE 1 : Si la string contient un '/'
*/

int		slash(char	*str, int mode)
{
	int		i;

	i = (mode == 0 ? ft_strlen(str) : 0);
	if (i > 0 && mode == 0)
	{
		if (str[i - 1] == '/' || str[i - 1] == '.')
			return (1);
	}
	else if (mode == 1)
	{
		while (str[i])
		{
			if (str[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

int		get_error(t_all *all)
{
	if (ft_strcmp(all->dir[0], ".") == 0)
	{
		ft_put_error(
		"filename argument required\n.: usage: . filename [arguments]",
		all->dir[0], 1);
		return (2);
	}
	if (errno == 13 && slash(all->dir[0], 0))
	{
		errno = 21;
		return (-126);
	}
	else if (errno == 2 || errno == 13)
	{
		if (slash(all->dir[0], 1))
			return (-127);
		ft_put_error("command not found", all->dir[0], 1);
		return (127);
	}
	return (-1);
}

int		run_exec(t_all *all)
{
	int		ret;
	int		status;
	char	**envp;

	ret = 0;
	status = 0;
	envp = ft_list_to_tab(all->env, 0, 0);
	status = execve(all->exec, all->dir, envp);
	if (status == -1)
	{
		ret = get_error(all);
		if (ret < 0)
			ft_put_error(strerror(errno), all->dir[0], 1);
		update_return(all, ft_abs(ret));
	}
	free_tab(envp);
	return (1);
}

int		action(t_all *all, char ***env, int fd[all->tube][2])
{
	if (all->countsmc > 0)
	{
		parse_command(all, *env, fd);
		*env = update_env(all, *env);
		g_builtin = 0;
	}
	return (0);
}

int		multidir(t_all *all, char ***env, int fd[all->tube][2])
{
	all->here = 0;
	while (all->here <= all->tube)
	{
		joinquotev2(all);
		tokentranslate(all, &*all->xdir);
		free(all->kotey);
		if (all->here == 0)
			all->around = 1;
		else if (all->here == all->tube)
			all->around = 0;
		else
			all->around = 2;
		action(all, env, fd);
		all->here++;
	}
	all->countsmc--;
	all->tube = 0;
	return (0);
}