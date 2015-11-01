/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 16:12:59 by rbaum            ###   ########.fr       */
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

void			ft_insert_middle(char *s, int i, char c)
{
	// int			j;
	char		*tmp;

	tmp = ft_strdup(s);
	s[i] = c;
	while (tmp[i])
	{
		s[i + 1] = tmp[i];
		i++;
	}
}

int				print_current_line(t_core *cr, int i, char c)
{
	(void)cr;
	if (!cr->v->name[i + 1])
		SV->name[i++] = c;
	else
	{
		ft_insert_middle(cr->v->name, (cr->px - MX), c);
	}
	TMCP("cr");
	TMCP("ce");
	ft_name_prompt();
	ft_putstr(SV->name);
	return (i);
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
		if (SV->name && move_line(cr, buf, i) == 0)
		{
			i = print_current_line(cr, i, buf[0]);
			cr->px++;
		}
		else
		{
			i = 0;
			// cr->px = MX;
		}
		// print_key(buf);
		ft_bzero(buf, 3);
	}
}
