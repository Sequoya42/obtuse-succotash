/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 09:38:35 by rbaum             #+#    #+#             */
/*   Updated: 2015/03/11 04:21:51 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int				ft_env_exe(void)
{
	int			i;

	i = 1;
	if (check_current(0) == 1)
		return (1);
	ft_get_pwd();
	while (SING->path[i])
	{
		SING->path[i] = ft_strjoin(SING->path[i], "/");
		SING->path[i] = ft_strjoin(SING->path[i], SING->arg[0]);
		if ((access(SING->path[i], F_OK)) != -1)
		{
			ft_exec(SING->path[i]);
			ft_clear_tab(&SING->path);
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
	join = ft_strjoin(SING->arg[1], "=");
	if (SING->arg[2])
	{
		join2 = ft_strjoin(join, SING->arg[2]);
		free(join);
	}
	else
		join2 = join;
	return (join2);
}

int				set_env(void)
{
	int			i;
	char		**tmp;

	if (ft_nb_tab(SING->arg) == 1)
		return (aff_env());
	if (check_env() == 1)
		return (1);
	tmp = ft_strdup_tab(SING->env);
	ft_clear_tab(&SING->env);
	i = ft_nb_tab(tmp) + 1;
	if ((SING->env = malloc(sizeof(char *) * (i + 1))) == NULL)
		ft_error(NULL, NULL, "Malloc could not allocated memory");
	i = -1;
	while (tmp[++i])
		SING->env[i] = ft_strdup(tmp[i]);
	SING->env[i] = add_env();
	SING->env[i + 1] = NULL;
	ft_clear_tab(&tmp);
	return (0);
}

int				ft_unsetenv_path(int k, char *tmp, int i)
{
	while (SING->arg[++k])
	{
		if (ft_strcmp(SING->arg[k], "HOME") == 0)
			SING->home = NULL;
		if (ft_strcmp(tmp, SING->arg[k]) == 0)
			SING->env[i][0] = '\0';
	}
	return (1);
}

int				ft_unsetenv(void)
{
	int			i;
	int			k;
	char		*tmp;

	i = 0;
	if (SING->env[i] == NULL)
		return (ft_error(NULL, NULL, "There is no env left"));
	while (SING->env[i])
	{
		k = 0;
		tmp = ft_split_char(SING->env[i], 0, '=');
		ft_unsetenv_path(k, tmp, i);
		free(tmp);
		tmp = NULL;
		i++;
	}
	if (SING->arg != NULL)
		ft_clear_tab(&SING->arg);
	return (0);
}
