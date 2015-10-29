/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 07:42:22 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/29 17:27:55 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_update_tab(char **t)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	if (t == NULL)
		return (NULL);
	while (t[i])
	{
		if (t[i][0] == '\0')
			k++;
		i++;
	}
	if ((tmp = malloc(sizeof(*t) * (i - k) + 1)) == NULL)
		ft_error(NULL, NULL, NULL);
	return (tmp);
}

void		ft_print_tab(char **t)
{
	int		i;

	i = 0;
	while (t[i])
		ft_putendl(t[i++]);
}
