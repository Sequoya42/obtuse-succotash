/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 09:38:35 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/28 12:50:47 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_var_exe(void)
{
	int			i;

	i = 1;
	if (check_current(0) == 1)
		return (1);
	ft_get_pwd();
	while (SV->path[i])
	{
		SV->path[i] = ft_strjoin(SV->path[i], "/");
		SV->path[i] = ft_strjoin(SV->path[i], SV->arg[0]);
		if ((access(SV->path[i], F_OK)) != -1)
		{
			ft_exec(SV->path[i]);
			ft_clear_tab(&SV->path);
			return (1);
		}
		i++;
	}
	return (0);
}

char			*add_env(void)
{
	char		*join;
	char		*join2;

	join = NULL;
	join2 = NULL;
	join = ft_strjoin(SV->arg[1], "=");
	if (SV->arg[2])
	{
		join2 = ft_strjoin(join, SV->arg[2]);
		free(join);
	}
	else
		join2 = join;
	return (join2);
}

int				set_var(void)
{
	int			i;
	char		**tmp;

	if (ft_nb_tab(SV->arg) == 1)
		return (aff_env());
	if (check_env() == 1)
		return (1);
	tmp = ft_strdup_tab(SV->env);
	ft_clear_tab(&SV->env);
	i = ft_nb_tab(tmp) + 1;
	if ((SV->env = malloc(sizeof(char *) * (i + 1))) == NULL)
		ft_error(NULL, NULL, "Malloc could not allocated memory");
	i = -1;
	while (tmp[++i])
		SV->env[i] = ft_strdup(tmp[i]);
	SV->env[i] = add_env();
	SV->env[i + 1] = NULL;
	ft_clear_tab(&tmp);
	return (0);
}

int				ft_unsetenv_path(int k, char *tmp, int i)
{
	while (SV->arg[++k])
	{
		if (ft_strcmp(SV->arg[k], "HOME") == 0)
			SV->home = NULL;
		if (ft_strcmp(tmp, SV->arg[k]) == 0)
			SV->env[i][0] = '\0';
	}
	return (1);
}

int				ft_unsetenv(void)
{
	int			i;
	int			k;
	char		*tmp;

	i = 0;
	if (SV->env[i] == NULL)
		return (ft_error(NULL, NULL, "There is no env left"));
	while (SV->env[i])
	{
		k = 0;
		tmp = ft_split_char(SV->env[i], 0, '=');
		ft_unsetenv_path(k, tmp, i);
		free(tmp);
		tmp = NULL;
		i++;
	}
	if (SV->arg != NULL)
		ft_clear_tab(&SV->arg);
	return (0);
}
