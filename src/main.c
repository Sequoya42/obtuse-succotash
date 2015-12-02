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
	choose(envp, cr);
	ft_prompt(cr);
	return (0);
}
