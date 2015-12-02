/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/30 15:25:53 by rbaum            ###   ########.fr       */
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
int				main(int argc, char **argv, char **envp)
{
	t_core		*cr;

	(void)argc;
	(void)argv;
    signal(SIGWINCH, ft_resize);
    signal(SIGTSTP, ft_z);
    signal(SIGCONT, ft_fg);
    signal(SIGINT, sig_exit);
    signal(SIGQUIT, sig_exit);
	cr = get_ready();
		cr->v = sing_var();
	if ((cr->v->env = malloc(sizeof(char *) * 10)) == NULL)
		ft_exit("Failed malloc\n");
	if ((cr->v->name = malloc(sizeof(char) * 1024)))
		ft_bzero(cr->v->name, 1024);

	choose(envp, cr);
	ft_prompt(cr);
	return (0);
}
