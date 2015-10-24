/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:51:37 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void				sig_handler(int signo)
{
	if (signo == SIGINT)
		ft_putchar('\n');
}

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
		execve(path, SE->arg, SE->env);
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

	if (ft_strchr(SE->name, ';'))
	{
		tmp = ft_strsplit(SE->name, ';');
		i = 0;
		while (tmp[i])
		{
			ft_clear_tab(&SE->arg);
			SE->arg = ft_strsplit(tmp[i], ' ');
			ft_get_pwd();
			ft_gest_env();
			++i;
		}
		ft_clear_tab(&tmp);
	}
	else
	{
		SE->arg = ft_strsplit(SE->name, ' ');
		ft_get_pwd();
		ft_gest_env();
	}
	return (0);
}

void				ft_prompt(void)
{
	int				ret;
	char			*line;

	ft_name_prompt();
	signal(SIGINT, sig_handler);
	if ((SE->path = malloc(sizeof(char*) * 10)) == NULL)
		return ;
	while ((ret = get_next_line(1, &line)) != 0)
	{
		SE->name = ft_strdup(line);
		free(line);
		ft_get_right_env();
		ft_point();
		stop_SEing();
		free(SE->name);
		SE->name = NULL;
		if (SE->arg != NULL)
			ft_clear_tab(&SE->arg);
		ft_name_prompt();
	}
}
