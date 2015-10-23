/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 16:38:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/23 15:44:15 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_tmp_aff(int l, char **tmp)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (SING->arg[i])
	{
		k = 0;
		while (SING->arg[i][k])
		{
			if (SING->arg[i][k] == '=')
			{
				tmp[l++] = SING->arg[i];
				break ;
			}
			k++;
		}
		i++;
	}
	return (l);
}

int				ft_env_arg(void)
{
	char		**tmp;

	tmp = ft_strdup_tab(SING->arg + 1);
	ft_clear_tab(&SING->arg);
	SING->arg = ft_strdup_tab(tmp);
	ft_clear_tab(&tmp);
	check_path(SING->arg);
	return (0);
}

int				aff_env(void)
{
	int			i;
	int			k;
	char		**tmp;

	i = 0;
	k = 0;
	if (ft_nb_tab(SING->arg) > 1)
		return (ft_env_arg());
	tmp = ft_update_tab(SING->env);
	while (SING->env[i])
	{
		while (SING->env[i][0] == '\0' && SING->env[i + 1])
			i += 1;
		if (SING->env[i][0] != '\0')
			tmp[k++] = ft_strdup(SING->env[i]);
		i++;
	}
	tmp[k] = NULL;
	ft_clear_tab(&SING->env);
	SING->env = ft_strdup_tab(tmp);
	ft_clear_tab(&tmp);
	i = 0;
	while (SING->env[i])
		ft_putendl(SING->env[i++]);
	return (0);
}

int				check_env_error(void)
{
	int			i;

	i = 0;
	while (SING->arg[1][i])
	{
		if (SING->arg[1][i++] == '=')
		{
			ft_putendl("setenv: Syntax Error");
			return (1);
		}
	}
	i = ft_nb_tab(SING->arg);
	if (i > 3)
	{
		ft_putendl("setenv: too many arguments.");
		return (1);
	}
	return (0);
}

int				check_env(void)
{
	int			i;
	char		*tmp;

	i = 0;
	if (check_env_error() == 1)
		return (1);
	while (SING->env[i])
	{
		tmp = ft_split_char(SING->env[i], 0, '=');
		if (ft_strcmp(tmp, SING->arg[1]) == 0)
		{
			free(SING->env[i]);
			free(tmp);
			tmp = ft_strjoin(SING->arg[1], "=");
			if (SING->arg[2])
				SING->env[i] = ft_strjoin(tmp, SING->arg[2]);
			else
				SING->env[i] = tmp;
			free(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}
