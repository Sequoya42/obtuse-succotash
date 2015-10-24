/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 18:03:32 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:57:22 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_tab(char **t)
{
	char	**tmp;
	int		i;

	if (t == NULL)
		return (NULL);
	i = ft_nb_tab(t);
	tmp = malloc(sizeof(*tmp) * (i + 1));
	i = 0;
	while (t[i])
	{
		tmp[i] = ft_strdup(t[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
