/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:51:38 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void				ft_get_right_env(void)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	tmp = ft_strdup(SE->name);
	while ((tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	j = i;
	while (tmp[i])
	{
		if (tmp[i] == '\t')
			tmp[i] = ' ';
		i++;
	}
	free(SE->name);
	SE->name = ft_strdup(tmp + j);
	free(tmp);
}

int					tmp_env(char *tmp, int k)
{
	struct stat		info;

	if ((access(tmp, F_OK)) != -1 && stat(tmp, &info) == 0 &&
		!S_ISDIR(info.st_mode) && info.st_mode & S_IXUSR)
	{
		ft_exec(tmp);
		free(tmp);
		return (1);
	}
	else if ((access(SE->arg[k], F_OK)) != -1 &&
stat(SE->arg[k], &info) == 0 &&
!S_ISDIR(info.st_mode) && info.st_mode & S_IXUSR)
	{
		ft_exec(SE->arg[k]);
		free(tmp);
		return (1);
	}
	return (0);
}

int					check_current(int k)
{
	char			*tmp;
	char			*tmp2;
	int				i;

	i = 0;
	ft_tild(0);
	while (SE->env[i])
	{
		if (ft_strnstr(SE->env[i], "PWD=", 4) != NULL)
			tmp = SE->env[i] + 4;
		i++;
	}
	tmp2 = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp2, SE->arg[k]);
	free(tmp2);
	if (tmp_env(tmp, k) == 1)
		return (1);
	free(tmp);
	return (0);
}

int					check_path(char **arg)
{
	int				i;
	char			*tmp;
	char			*tmp2;
	struct stat		info;

	i = 0;
	ft_get_pwd();
	if ((check_current(0) == 1))
		return (1);
	if (SE->path == NULL)
		return (ft_error(NULL, arg[0], "Command not found."));
	while (SE->path[i])
	{
		tmp = ft_strjoin(SE->path[i], "/");
		free(SE->path[i]);
		tmp2 = ft_strjoin(tmp, arg[0]);
		SE->path[i] = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		if ((access(SE->path[i], F_OK)) != -1 && stat(SE->path[i], &info)
			== 0 && !S_ISDIR(info.st_mode) && info.st_mode & S_IXUSR)
			return (ft_exec(SE->path[i]));
		i++;
	}
	return (ft_error(NULL, arg[0], "Command not found."));
}

void				ft_gest_env(void)
{
	if (ft_strcmp(SE->arg[0], "exit") == 0)
		ft_exit_sh();
	else if (ft_strcmp(SE->arg[0], "setenv") == 0)
		set_env();
	else if (ft_strcmp(SE->arg[0], "env") == 0)
		aff_env();
	else if (ft_strcmp(SE->arg[0], "unsetenv") == 0)
		ft_unsetenv();
	else if (ft_strcmp(SE->arg[0], "cd") == 0)
		ft_change_dir();
	else if (ft_strcmp(SE->arg[0], "resetenv") == 0)
	{
		ft_clear_tab(&SE->env);
		SE->env = ft_strdup_tab(SE->environ);
	}
	else if (SE->arg[0] == '\0')
		SE->name = SE->name;
	else if (SE->arg[0][0] == '/' && ft_strlen(SE->arg[0]) == 1)
		ft_putendl("Permission denied");
	else
		check_path(SE->arg);
	stop_SEing();
}
