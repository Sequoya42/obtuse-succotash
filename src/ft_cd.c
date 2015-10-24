/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:52:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:51:36 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_update_env(void)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (SE->env[i])
	{
		if (ft_strnstr(SE->env[i], "PWD=", 4) != NULL)
		{
			tmp2 = ft_strdup(SE->env[i]);
			free(SE->env[i]);
			tmp = getcwd(NULL, 0);
			SE->env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strnstr(SE->env[i], "OLDPWD=", 7) != NULL)
		{
			free(SE->env[i]);
			SE->env[i] = ft_strjoin("OLD", tmp2);
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
	i = ft_nb_tab(SE->arg);
	stat(SE->arg[1], &info);
	if (i == 1 && SE->home)
	{
		if (chdir(SE->home + 5) == -1)
			ft_error(SE->arg[0], NULL, "Unvalid Home");
	}
	else if (i == 1 && !SE->home)
		return (ft_error(SE->arg[0], NULL, "Home not found"));
	else if (ft_strcmp(SE->arg[1], "-") == 0)
		chdir(SE->oldpwd + 7);
	else if (chdir(SE->arg[1]) == 0)
		;
	else if (S_ISREG(info.st_mode))
		return (ft_error(SE->arg[0], "not a directory", SE->arg[1]));
	else
		ft_error(SE->arg[0], "No such file or directory", SE->arg[1]);
	ft_update_env();
	return (0);
}

int		ft_change_dir(void)
{
	int i;

	i = ft_nb_tab(SE->arg);
	if (i > 2)
		return (ft_error(SE->arg[0], NULL, "Too many arguments."));
	if (ft_tild(1) == 1)
		return (1);
	else
		ft_cd_error();
	return (0);
}
