/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:48:55 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 12:54:03 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_free_exit(void)
{
    ft_free_av(g_shell.pip_str);
    ft_free_av(g_shell.semi_colon);
    ft_free_av(g_shell.sort_env);
    ft_free_av(g_shell.env);
    ft_strdel(&g_shell.str);
    ft_strdel(&g_shell.dir);
    exit(g_shell.ret);
}

int			ft_check_exit(char *buf)
{
	int		i;
	int		nb;

	g_shell.legal_exit = 0;
    nb = 0;
	if ((!ft_strncmp(buf, "exit", 4) &&
									!buf[4]) || !ft_strncmp(buf, "exit ", 5))
	{
		i = 4;
		while (buf[i] == ' ')
			i++;
		while (buf[i])
		{
			nb = ft_isdigit(buf[i]) ? 1 : 0;
			if (buf[i] == ' ' && buf[i + 1] && buf[i + 1] != ' ')
			{
				ft_printf(1, "minishell: too many arguments\n");
				g_shell.legal_exit = 1;
				return ((g_shell.ret = 1) - 1);
			}
			if (!ft_isdigit(buf[i]) && buf[i] != ' ')
			{
				ft_printf(1,
				"minishell: exit: %s argument numérique nécessaire\n", &buf[5]);
				return ((g_shell.ret = 2) - 1);
			}
			i++;
		}
        ft_printf(1, "nb = %d\n", nb);
		if (nb)
			g_shell.ret = ft_atoi(&buf[5]);
		return (1);
	}
	return (0);
}