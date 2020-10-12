/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:23:38 by lucas             #+#    #+#             */
/*   Updated: 2020/10/12 14:41:17 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_final_exec(int ret)
{
    int     i;
    int     res;
    char    buf[BUF_SIZE + 1];

    i = 0;
        ft_printf(1, "a\n");
    while (i < g_shell.pid.len)
    {
        waitpid(g_shell.pid.id[i], &res, 0);
        if (g_shell.pip.len - 1 > i)
            close(g_shell.pip.id[i][0]);
        i++;
    }
    g_shell.ret = res;
    ft_printf(1, "len = %d, fd = %d\n", g_shell.pip.len, g_shell.pip.id[g_shell.pip.len - 1][0]);
    if (g_shell.pip.len == 0 || !ret)
        return ;
    while ((res = read(g_shell.pip.id[g_shell.pip.len - 1][0], buf, BUF_SIZE)))
    {
        buf[res] = '\0';
        write(1, buf, res);
    }
}