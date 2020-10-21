/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:06:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 15:06:36 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_add_to_export(char **tmp, char *var)
{
	tmp = ft_add_var_to_env(var, g_shell.sort_env);
	ft_free_av(g_shell.sort_env);
	g_shell.sort_env = ft_avdup(tmp);
	ft_free_av(tmp);
}

char		*ft_change_var_utils(char *buf, char *new, int k, int check)
{
	if (check == -1)
		new[k++] = '"';
	new[k] = '\0';
	ft_strdel(&buf);
	return (new);
}
