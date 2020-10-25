/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:25:03 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/22 17:28:20 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_print_prompt_2(void)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	if (tmp != NULL)
	{
		ft_strdel(&g_shell.dir);
		g_shell.dir = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	i = ft_strlen(g_shell.dir);
	while (i >= 0 && g_shell.dir[i] != '/')
		i--;
	if (!g_shell.ret)
		ft_printf(1, "" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET,
			&g_shell.dir[i + 1]);
	else
		ft_printf(1, "" BOLDRED "➜ " RESET BOLDCYAN " %s " RESET,
			&g_shell.dir[i + 1]);
}

int			ft_print_prompt(void)
{
	int		i;

	i = 0;
	g_shell.error = 0;
	ft_split_semi_colons(g_shell.str);
	if (g_shell.error == -1)
		return (ft_free_error(ERR_SEMI_COLONS));
	return (ft_check_parse());
}
