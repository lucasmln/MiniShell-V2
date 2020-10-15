/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:53:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:31:12 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_exec_cmd(char *buf)
{
    int     i;
    int     k;
    char    *cmd;

    i = -1;
    k = 0;
    while (buf[++i])
        if (buf[i] == '<' || buf[i] == ' ' || buf[i] == '<')
        {
            k = buf[i];
            break ;
        }
    buf[i] = '\0';
   // cmd = ft_strdup(buf);
    buf[i] = k;
    //ft_strdel(cmd);
    return (0);
}