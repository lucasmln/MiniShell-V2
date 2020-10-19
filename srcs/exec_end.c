/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:23:38 by lucas             #+#    #+#             */
/*   Updated: 2020/10/15 17:05:06 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_final_exec(int ret)
{
	int		i;
	int		res;
	char	buf[BUF_SIZE + 1];

	i = 0;
	while (i < g_shell.pid.len)
	{
		waitpid(g_shell.pid.id[i], &res, 0);
		if (g_shell.pip.len - 1 > i)
			close(g_shell.pip.id[i][0]);
		if (g_shell.pos_error_in != -1 && i == g_shell.pos_error_in)
			res = 512;
		i++;
	}
	g_shell.ret = i > 0 ? res / 512 : g_shell.ret;
	ft_printf(1, "ret tmp = %d\n", g_shell.tmp_ret);
	g_shell.ret = g_shell.tmp_ret != -100000 ? g_shell.tmp_ret : g_shell.ret;
	if (g_shell.pip.len == 0 || !ret)
		return ;
	while ((res = read(g_shell.pip.id[g_shell.pip.len - 1][0], buf, BUF_SIZE)))
	{
		buf[res] = '\0';
		write(1, buf, res);
	}
}
