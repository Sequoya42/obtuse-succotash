/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 16:38:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:51:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_tmp_aff(int l, char **tmp)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (SE->arg[i])
	{
		k = 0;
		while (SE->arg[i][k])
		{
			if (SE->arg[i][k] == '=')
			{
				tmp[l++] = SE->arg[i];
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

	tmp = ft_strdup_tab(SE->arg + 1);
	ft_clear_tab(&SE->arg);
	SE->arg = ft_strdup_tab(tmp);
	ft_clear_tab(&tmp);
	check_path(SE->arg);
	return (0);
}

int				aff_env(void)
{
	int			i;
	int			k;
	char		**tmp;

	i = 0;
	k = 0;
	if (ft_nb_tab(SE->arg) > 1)
		return (ft_env_arg());
	tmp = ft_update_tab(SE->env);
	while (SE->env[i])
	{
		while (SE->env[i][0] == '\0' && SE->env[i + 1])
			i += 1;
		if (SE->env[i][0] != '\0')
			tmp[k++] = ft_strdup(SE->env[i]);
		i++;
	}
	tmp[k] = NULL;
	ft_clear_tab(&SE->env);
	SE->env = ft_strdup_tab(tmp);
	ft_clear_tab(&tmp);
	i = 0;
	while (SE->env[i])
		ft_putendl(SE->env[i++]);
	return (0);
}

int				check_env_error(void)
{
	int			i;

	i = 0;
	while (SE->arg[1][i])
	{
		if (SE->arg[1][i++] == '=')
		{
			ft_putendl("setenv: Syntax Error");
			return (1);
		}
	}
	i = ft_nb_tab(SE->arg);
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
	while (SE->env[i])
	{
		tmp = ft_split_char(SE->env[i], 0, '=');
		if (ft_strcmp(tmp, SE->arg[1]) == 0)
		{
			free(SE->env[i]);
			free(tmp);
			tmp = ft_strjoin(SE->arg[1], "=");
			if (SE->arg[2])
				SE->env[i] = ft_strjoin(tmp, SE->arg[2]);
			else
				SE->env[i] = tmp;
			free(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}
