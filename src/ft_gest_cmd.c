/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 19:14:31 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void				ft_get_right_var(void)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	tmp = ft_strdup(SV->name);
	while ((tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	j = i;
	while (tmp[i])
	{
		if (tmp[i] == '\t')
			tmp[i] = ' ';
		i++;
	}
	free(SV->name);
	SV->name = ft_strdup(tmp + j);
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
	else if ((access(SV->arg[k], F_OK)) != -1 &&
stat(SV->arg[k], &info) == 0 &&
!S_ISDIR(info.st_mode) && info.st_mode & S_IXUSR)
	{
		ft_exec(SV->arg[k]);
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
	while (SV->env[i])
	{
		if (ft_strnstr(SV->env[i], "PWD=", 4) != NULL)
			tmp = SV->env[i] + 4;
		i++;
	}
	tmp2 = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp2, SV->arg[k]);
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
	if (SV->path == NULL)
		return (ft_error("\n", arg[0], "Command not found."));
	while (SV->path[i])
	{
		tmp = ft_strjoin(SV->path[i], "/");
		free(SV->path[i]);
		tmp2 = ft_strjoin(tmp, arg[0]);
		SV->path[i] = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		if ((access(SV->path[i], F_OK)) != -1 && stat(SV->path[i], &info)
			== 0 && !S_ISDIR(info.st_mode) && info.st_mode & S_IXUSR)
			return (ft_exec(SV->path[i]));
		i++;
	}
	return (ft_error("\n", arg[0], "Command not found."));
}

void				ft_gest_var(void)
{
	if (ft_strcmp(SV->arg[0], "exit") == 0)
		ft_exit_sh();
	else if (ft_strcmp(SV->arg[0], "setenv") == 0)
		set_var();
	else if (ft_strcmp(SV->arg[0], "env") == 0)
		aff_env();
	else if (ft_strcmp(SV->arg[0], "unsetenv") == 0)
		ft_unsetenv();
	else if (ft_strcmp(SV->arg[0], "cd") == 0)
		ft_change_dir();
	else if (ft_strcmp(SV->arg[0], "resetenv") == 0)
	{
		ft_clear_tab(&SV->env);
		SV->env = ft_strdup_tab(SV->environ);
	}
	else if (SV->arg[0] == '\0')
		ft_putchar('\n');
	else if (SV->arg[0][0] == '/' && ft_strlen(SV->arg[0]) == 1)
		ft_putendl("Permission denied");
	else
		check_path(SV->arg);
	stop_SEing();
}
