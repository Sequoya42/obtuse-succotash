/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/21 11:58:37 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void			sig_return(int signo)
{
	if (signo == SIGINT)
		ft_putendl("");
}

t_cmd			*singleton(void)
{
	static	t_cmd cmd;

	return (&cmd);
}

int				main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if ((SING->env = malloc(sizeof(char *) * 10)) == NULL)
		return (0);
	if (signal(SIGINT, sig_return) == SIG_ERR)
		ft_prompt();
	if (envp[0])
	{
		SING->env = ft_strdup_tab(envp);
		SING->environ = ft_strdup_tab(envp);
	}
	else
	{
		ft_putendl("Running without env  : Behavior may be undefined");
		SING->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		SING->env[1] = ft_strjoin("OLD", SING->env[0]);
		SING->environ = ft_strdup_tab(SING->env);
	}
	ft_prompt();
	return (0);
}
