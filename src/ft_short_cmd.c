/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:51:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_exit_sh(void)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = ft_strdup(SE->name + 4);
	free(SE->name);
	SE->name = ft_strdup(tmp);
	free(tmp);
	if (ft_nb_tab(SE->arg) > 2)
		return (ft_error(NULL, "exit", "Expression syntax"));
	while (SE->name[i])
	{
		if (ft_isdigit(SE->name[i]) != 1 && SE->name[i] != ' ')
			return (ft_error(NULL, "exit", "Expression syntax"));
		++i;
	}
	exit (ft_atoi(SE->name));
}

int				ft_if_tild(char *tmp, int k)
{
	char		*tmp2;

	k = 1;
	if (SE->arg[k][0] == '~')
	{
		tmp2 = ft_strjoin(tmp, SE->arg[k] + 1);
		free(SE->arg[k]);
		SE->arg[k] = NULL;
		free(tmp);
		tmp = NULL;
		if (chdir(tmp2) == -1)
			ft_error(SE->arg[0], "No such file or Directory", tmp2);
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

	tmp = SE->arg[k];
	if (SE->arg[k] &&
(SE->arg[k][0] == '~' || (SE->arg[k][0] == '-' && SE->arg[k][1] == '-')))
	{
		if (SE->home == NULL)
			return (ft_error(SE->arg[0], NULL, "Home not found"));
		else
			tmp = ft_strdup(SE->home + 5);
		if (ft_if_tild(tmp, k) == 1)
			return (1);
		chdir(tmp);
		free(tmp);
		tmp = NULL;
		free(SE->arg[k]);
		SE->arg[k] = NULL;
		ft_update_env();
		return (1);
	}
	return (0);
}

void			stop_SEing(void)
{
	if (SE->path)
		ft_clear_tab(&SE->path);
}

void			ft_get_pwd(void)
{
	int			i;

	i = 0;
	stop_SEing();
	while (SE->env[i])
	{
		if (ft_strnstr(SE->env[i], "PATH=", 5) != NULL)
			SE->path = ft_strsplit(SE->env[i] + 5, ':');
		if (ft_strnstr(SE->env[i], "PWD=", 4) != NULL)
			SE->pwd = SE->env[i];
		if (ft_strnstr(SE->env[i], "OLDPWD=", 7) != NULL)
			SE->oldpwd = SE->env[i];
		if (ft_strnstr(SE->env[i], "HOME=", 5) != NULL)
			SE->home = SE->env[i];
		i++;
	}
}
