/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:17:42 by rbaum             #+#    #+#             */
/*   Updated: 2015/12/02 17:17:48 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			sig_return(int signo)
{
	if (signo == SIGINT)
		ft_putendl("");
}

t_var			*sing_var(void)
{
	static	t_var env;

	return (&env);
}

t_core			*get_ready(void)
{
	t_core		*cr;

	if (!(cr = malloc(sizeof(t_core))))
		ft_exit("Failed malloc\n!");
	cr->v = sing_var();
	if ((cr->v->env = malloc(sizeof(char *) * 10)) == NULL)
		ft_exit("Failed malloc\n");
	cr->s = singleton();
	if ((cr->v->name = malloc(sizeof(char) * 1024)))
		ft_bzero(cr->v->name, 1024);
	cr->s->term = malloc(sizeof(struct termios));
	if (modif_term(cr->s->term) == -1)
		ft_exit("Failed termcaps\n");
	cr->px = MX;
	cr->py = MY;
	ft_resize(1);
	return (cr);
}

void			choose(char **envp, t_core *cr)
{
	if (envp[0])
	{
		cr->v->env = ft_strdup_tab(envp);
		cr->v->environ = ft_strdup_tab(envp);
	}
	else
	{
		ft_putendl("Running without env : Behavior may be undefined");
		cr->v->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		cr->v->env[1] = ft_strjoin("OLD", cr->v->env[0]);
		cr->v->environ = ft_strdup_tab(cr->v->env);
	}
}
