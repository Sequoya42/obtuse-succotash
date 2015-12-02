/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/28 12:50:57 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_exit_sh(void)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = ft_strdup(SV->name + 4);
	free(SV->name);
	SV->name = ft_strdup(tmp);
	free(tmp);
	if (ft_nb_tab(SV->arg) > 2)
		return (ft_error(NULL, "exit", "Expression syntax"));
	while (SV->name[i])
	{
		if (ft_isdigit(SV->name[i]) != 1 && SV->name[i] != ' ')
			return (ft_error(NULL, "exit", "Expression syntax"));
		++i;
	}
	exit (ft_atoi(SV->name));
}

int				ft_if_tild(char *tmp, int k)
{
	char		*tmp2;

	k = 1;
	if (SV->arg[k][0] == '~')
	{
		tmp2 = ft_strjoin(tmp, SV->arg[k] + 1);
		free(SV->arg[k]);
		SV->arg[k] = NULL;
		free(tmp);
		tmp = NULL;
		if (chdir(tmp2) == -1)
			ft_error(SV->arg[0], "No such file or Directory", tmp2);
		free(tmp2);
		tmp2 = NULL;
		ft_update_env();
		return (1);
	}
	return (0);
}

int				ft_tild(int k)
{
	char		*tmp;

	tmp = SV->arg[k];
	if (SV->arg[k] &&
(SV->arg[k][0] == '~' || (SV->arg[k][0] == '-' && SV->arg[k][1] == '-')))
	{
		if (SV->home == NULL)
			return (ft_error(SV->arg[0], NULL, "Home not found"));
		else
			tmp = ft_strdup(SV->home + 5);
		if (ft_if_tild(tmp, k) == 1)
			return (1);
		chdir(tmp);
		free(tmp);
		tmp = NULL;
		free(SV->arg[k]);
		SV->arg[k] = NULL;
		ft_update_env();
		return (1);
	}
	return (0);
}

void			stop_SEing(void)
{
	if (SV->path)
		ft_clear_tab(&SV->path);
}

void			ft_get_pwd(void)
{
	int			i;

	i = 0;
	stop_SEing();
	while (SV->env[i])
	{
		if (ft_strnstr(SV->env[i], "PATH=", 5) != NULL)
			SV->path = ft_strsplit(SV->env[i] + 5, ':');
		if (ft_strnstr(SV->env[i], "PWD=", 4) != NULL)
			SV->pwd = SV->env[i];
		if (ft_strnstr(SV->env[i], "OLDPWD=", 7) != NULL)
			SV->oldpwd = SV->env[i];
		if (ft_strnstr(SV->env[i], "HOME=", 5) != NULL)
			SV->home = SV->env[i];
		i++;
	}
}
