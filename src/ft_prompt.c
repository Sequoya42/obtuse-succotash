/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/21 11:58:53 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

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
		execve(path, SING->arg, SING->env);
	return (1);
}

void				ft_name_prompt(void)
{
	char			*tmp;
	char			*tmp2;

	tmp2 = getcwd(NULL, 0);
	tmp = ft_strrchr(tmp2, '/');
	ft_putchar('[');
	ft_putstr(tmp + 1);
	ft_putstr("] prompt>$ ");
	free(tmp2);
}

int					ft_point(void)
{
	int				i;
	char			**tmp;

	if (ft_strchr(SING->name, ';'))
	{
		tmp = ft_strsplit(SING->name, ';');
		i = 0;
		while (tmp[i])
		{
			ft_clear_tab(&SING->arg);
			SING->arg = ft_strsplit(tmp[i], ' ');
			ft_get_pwd();
			ft_gest_cmd();
			++i;
		}
		ft_clear_tab(&tmp);
	}
	else
	{
		SING->arg = ft_strsplit(SING->name, ' ');
		ft_get_pwd();
		ft_gest_cmd();
	}
	return (0);
}

void				ft_prompt(void)
{
	int				ret;
	char			*line;

	ft_name_prompt();
	signal(SIGINT, sig_handler);
	if ((SING->path = malloc(sizeof(char*) * 10)) == NULL)
		return ;
	while ((ret = get_next_line(1, &line)) != 0)
	{
		SING->name = ft_strdup(line);
		free(line);
		ft_get_right_cmd();
		ft_point();
		stop_singing();
		free(SING->name);
		SING->name = NULL;
		if (SING->arg != NULL)
			ft_clear_tab(&SING->arg);
		ft_name_prompt();
	}
}
