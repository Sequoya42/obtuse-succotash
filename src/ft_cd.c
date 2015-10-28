/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:52:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/28 12:51:08 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_update_env(void)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (SV->env[i])
	{
		if (ft_strnstr(SV->env[i], "PWD=", 4) != NULL)
		{
			tmp2 = ft_strdup(SV->env[i]);
			free(SV->env[i]);
			tmp = getcwd(NULL, 0);
			SV->env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strnstr(SV->env[i], "OLDPWD=", 7) != NULL)
		{
			free(SV->env[i]);
			SV->env[i] = ft_strjoin("OLD", tmp2);
			free(tmp2);
		}
		i++;
	}
}

int		ft_cd_error(void)
{
	int				i;
	struct stat		info;

	ft_get_pwd();
	i = ft_nb_tab(SV->arg);
	stat(SV->arg[1], &info);
	if (i == 1 && SV->home)
	{
		if (chdir(SV->home + 5) == -1)
			ft_error(SV->arg[0], NULL, "Unvalid Home");
	}
	else if (i == 1 && !SV->home)
		return (ft_error(SV->arg[0], NULL, "Home not found"));
	else if (ft_strcmp(SV->arg[1], "-") == 0)
		chdir(SV->oldpwd + 7);
	else if (chdir(SV->arg[1]) == 0)
		;
	else if (S_ISREG(info.st_mode))
		return (ft_error(SV->arg[0], "not a directory", SV->arg[1]));
	else
		ft_error(SV->arg[0], "No such file or directory", SV->arg[1]);
	ft_update_env();
	return (0);
}

int		ft_change_dir(void)
{
	int i;

	i = ft_nb_tab(SV->arg);
	if (i > 2)
		return (ft_error(SV->arg[0], NULL, "Too many arguments."));
	if (ft_tild(1) == 1)
		return (1);
	else
		ft_cd_error();
	return (0);
}
