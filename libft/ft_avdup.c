/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:36:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/26 17:08:28 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_avdup(char **env)
{
	char	**new;
	int		i;

	if (!(new = malloc(sizeof(char *) * (ft_avlen(env) + 1))))
		exit(-1000);
	i = -1;
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	new[i] = NULL;
	return (new);
}
