/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 09:38:35 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:51:07 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_env_exe(void)
{
	int			i;

	i = 1;
	if (check_current(0) == 1)
		return (1);
	ft_get_pwd();
	while (SE->path[i])
	{
		SE->path[i] = ft_strjoin(SE->path[i], "/");
		SE->path[i] = ft_strjoin(SE->path[i], SE->arg[0]);
		if ((access(SE->path[i], F_OK)) != -1)
		{
			ft_exec(SE->path[i]);
			ft_clear_tab(&SE->path);
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
	join = ft_strjoin(SE->arg[1], "=");
	if (SE->arg[2])
	{
		join2 = ft_strjoin(join, SE->arg[2]);
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

	if (ft_nb_tab(SE->arg) == 1)
		return (aff_env());
	if (check_env() == 1)
		return (1);
	tmp = ft_strdup_tab(SE->env);
	ft_clear_tab(&SE->env);
	i = ft_nb_tab(tmp) + 1;
	if ((SE->env = malloc(sizeof(char *) * (i + 1))) == NULL)
		ft_error(NULL, NULL, "Malloc could not allocated memory");
	i = -1;
	while (tmp[++i])
		SE->env[i] = ft_strdup(tmp[i]);
	SE->env[i] = add_env();
	SE->env[i + 1] = NULL;
	ft_clear_tab(&tmp);
	return (0);
}

int				ft_unsetenv_path(int k, char *tmp, int i)
{
	while (SE->arg[++k])
	{
		if (ft_strcmp(SE->arg[k], "HOME") == 0)
			SE->home = NULL;
		if (ft_strcmp(tmp, SE->arg[k]) == 0)
			SE->env[i][0] = '\0';
	}
	return (1);
}

int				ft_unsetenv(void)
{
	int			i;
	int			k;
	char		*tmp;

	i = 0;
	if (SE->env[i] == NULL)
		return (ft_error(NULL, NULL, "There is no env left"));
	while (SE->env[i])
	{
		k = 0;
		tmp = ft_split_char(SE->env[i], 0, '=');
		ft_unsetenv_path(k, tmp, i);
		free(tmp);
		tmp = NULL;
		i++;
	}
	if (SE->arg != NULL)
		ft_clear_tab(&SE->arg);
	return (0);
}
