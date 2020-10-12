/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:25:03 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/12 14:33:40 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_print_prompt(void)
{
	int		i;
	int		ret;

	ft_strdel(&g_shell.dir);
	g_shell.dir = getcwd(g_shell.dir, BUF_SIZE);
	i = ft_strlen(g_shell.dir);
	while (i >= 0 && g_shell.dir[i] != '/')
		i--;
	ft_printf(1, "" BOLDGREEN "➜ " RESET BOLDCYAN " %s " RESET,
														&g_shell.dir[i + 1]);
	ft_strdel(&g_shell.dir);
	ret = read(0, g_shell.buf, BUF_SIZE);
	g_shell.buf[ret] = '\0';
	if (g_shell.buf[ft_strlen(g_shell.buf) - 1] == '\n')
		g_shell.buf[ft_strlen(g_shell.buf) - 1] = '\0';
	i = 0;
	ft_skip_space(g_shell.buf, &i);
	g_shell.str = ft_strdup(&g_shell.buf[i]);
	g_shell.error = 0;
	ft_split_semi_colons(g_shell.str);
	if (g_shell.error == -1)
		return (ft_free_error(ERR_SEMI_COLONS));
	return (ft_check_parse(g_shell.str));
}
