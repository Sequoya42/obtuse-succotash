/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 15:08:55 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			sig_return(int signo)
{
	if (signo == SIGINT)
		ft_putendl("");
}

t_env			*SE_env(void)
{
	static	t_env env;

	return (&env);
}

int				main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if ((SE->env = malloc(sizeof(char *) * 10)) == NULL)
		return (0);
	if (signal(SIGINT, sig_return) == SIG_ERR)
		ft_prompt();
	if (envp[0])
	{
		SE->env = ft_strdup_tab(envp);
		SE->environ = ft_strdup_tab(envp);
	}
	else
	{
		ft_putendl("Running without env  : Behavior may be undefined");
		SE->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		SE->env[1] = ft_strjoin("OLD", SE->env[0]);
		SE->environ = ft_strdup_tab(SE->env);
	}
	ft_prompt();
	return (0);
}
