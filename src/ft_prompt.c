/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 13:57:51 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int					ft_exec(char *path)
{
	pid_t			pid;
	int				stat;

	pid = fork();
	if (pid == -1)
		ft_error("", "", "Pid error");
	if (pid > 0)
		waitpid(pid, &stat, 0);
	else
	{
		ft_putchar('\n');
		execve(path, SV->arg, SV->env);
	}
	return (1);
}

void				ft_name_prompt(void)
{
	char			*tmp;
	char			*tmp2;

	tmp2 = getcwd(NULL, 0);
	tmp = ft_strrchr(tmp2, '/');
	ft_putstr(KLGRN "sequoya:[");
	ft_putstr(tmp + 1);
	ft_putstr("] prompt>$ " KNRM);
	free(tmp2);
}

int					ft_point(void)
{
	int				i;
	char			**tmp;

	if (ft_strchr(SV->name, ';'))
	{
		tmp = ft_strsplit(SV->name, ';');
		i = 0;
		while (tmp[i])
		{
			ft_clear_tab(&SV->arg);
			SV->arg = ft_strsplit(tmp[i], ' ');
			ft_get_pwd();
			ft_gest_var();
			++i;
		}
		ft_clear_tab(&tmp);
	}
	else
	{
		SV->arg = ft_strsplit(SV->name, ' ');
		ft_get_pwd();
		ft_gest_var();
	}
	return (0);
}

void				ft_prompt(t_core *cr)
{
	char			buf[3];
	int				i;

	i = 0;
	ft_bzero(buf, 3);
	ft_name_prompt();
	if ((SV->path = malloc(sizeof(char*) * 10)) == NULL)
		return ;
	while (read(0, buf, 3))
	{
		if (SV->name && move_line(cr, buf) == 0)
			ft_putchar(SV->name[i++] = buf[0]);
		else
			i = 0;
		// print_key(buf);
		ft_bzero(buf, 3);
	}
}
