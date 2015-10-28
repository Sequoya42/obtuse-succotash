/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 16:38:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/28 12:50:34 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_tmp_aff(int l, char **tmp)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (SV->arg[i])
	{
		k = 0;
		while (SV->arg[i][k])
		{
			if (SV->arg[i][k] == '=')
			{
				tmp[l++] = SV->arg[i];
				break ;
			}
			k++;
		}
		i++;
	}
	return (l);
}

int				ft_var_arg(void)
{
	char		**tmp;

	tmp = ft_strdup_tab(SV->arg + 1);
	ft_clear_tab(&SV->arg);
	SV->arg = ft_strdup_tab(tmp);
	ft_clear_tab(&tmp);
	check_path(SV->arg);
	return (0);
}

int				aff_env(void)
{
	int			i;
	int			k;
	char		**tmp;

	i = 0;
	k = 0;
	if (ft_nb_tab(SV->arg) > 1)
		return (ft_var_arg());
	tmp = ft_update_tab(SV->env);
	while (SV->env[i])
	{
		while (SV->env[i][0] == '\0' && SV->env[i + 1])
			i += 1;
		if (SV->env[i][0] != '\0')
			tmp[k++] = ft_strdup(SV->env[i]);
		i++;
	}
	tmp[k] = NULL;
	ft_clear_tab(&SV->env);
	SV->env = ft_strdup_tab(tmp);
	ft_clear_tab(&tmp);
	i = 0;
	while (SV->env[i])
		ft_putendl(SV->env[i++]);
	return (0);
}

int				check_env_error(void)
{
	int			i;

	i = 0;
	while (SV->arg[1][i])
	{
		if (SV->arg[1][i++] == '=')
		{
			ft_putendl("setenv: Syntax Error");
			return (1);
		}
	}
	i = ft_nb_tab(SV->arg);
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
	while (SV->env[i])
	{
		tmp = ft_split_char(SV->env[i], 0, '=');
		if (ft_strcmp(tmp, SV->arg[1]) == 0)
		{
			free(SV->env[i]);
			free(tmp);
			tmp = ft_strjoin(SV->arg[1], "=");
			if (SV->arg[2])
				SV->env[i] = ft_strjoin(tmp, SV->arg[2]);
			else
				SV->env[i] = tmp;
			free(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}
