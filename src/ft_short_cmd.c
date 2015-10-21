/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/03/11 06:38:07 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int				ft_exit(void)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = ft_strdup(SING->name + 4);
	free(SING->name);
	SING->name = ft_strdup(tmp);
	free(tmp);
	if (ft_nb_tab(SING->arg) > 2)
		return (ft_error(NULL, "exit", "Expression syntax"));
	while (SING->name[i])
	{
		if (ft_isdigit(SING->name[i]) != 1 && SING->name[i] != ' ')
			return (ft_error(NULL, "exit", "Expression syntax"));
		++i;
	}
	exit (ft_atoi(SING->name));
}

int				ft_if_tild(char *tmp, int k)
{
	char		*tmp2;

	k = 1;
	if (SING->arg[k][0] == '~')
	{
		tmp2 = ft_strjoin(tmp, SING->arg[k] + 1);
		free(SING->arg[k]);
		SING->arg[k] = NULL;
		free(tmp);
		tmp = NULL;
		if (chdir(tmp2) == -1)
			ft_error(SING->arg[0], "No such file or Directory", tmp2);
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

	tmp = SING->arg[k];
	if (SING->arg[k] &&
(SING->arg[k][0] == '~' || (SING->arg[k][0] == '-' && SING->arg[k][1] == '-')))
	{
		if (SING->home == NULL)
			return (ft_error(SING->arg[0], NULL, "Home not found"));
		else
			tmp = ft_strdup(SING->home + 5);
		if (ft_if_tild(tmp, k) == 1)
			return (1);
		chdir(tmp);
		free(tmp);
		tmp = NULL;
		free(SING->arg[k]);
		SING->arg[k] = NULL;
		ft_update_env();
		return (1);
	}
	return (0);
}

void			stop_singing(void)
{
	if (SING->path)
		ft_clear_tab(&SING->path);
}

void			ft_get_pwd(void)
{
	int			i;

	i = 0;
	stop_singing();
	while (SING->env[i])
	{
		if (ft_strnstr(SING->env[i], "PATH=", 5) != NULL)
			SING->path = ft_strsplit(SING->env[i] + 5, ':');
		if (ft_strnstr(SING->env[i], "PWD=", 4) != NULL)
			SING->pwd = SING->env[i];
		if (ft_strnstr(SING->env[i], "OLDPWD=", 7) != NULL)
			SING->oldpwd = SING->env[i];
		if (ft_strnstr(SING->env[i], "HOME=", 5) != NULL)
			SING->home = SING->env[i];
		i++;
	}
}
