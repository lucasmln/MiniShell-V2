/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:17:22 by lucas             #+#    #+#             */
/*   Updated: 2020/10/11 18:03:08 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_get_path(t_exe *ex)
{
    int     pos;

    pos = ft_find_var_in_av(g_shell.env, "PATH=");
    if (pos == -1)
    {
        ex->error = 1;
        ex->path = ft_strdup("");
    }
    else
        ex->path = ft_strdup(&g_shell.env[pos][5]);
}

int        ft_pass_word(char *buf, int *i)
{
    int     check;

    if (!buf[*i])
        return (0);
    check = 0;
    while (buf[*i])
    {
        if (!check && buf[*i] == ' ')
        {
            ft_skip_space(buf, i);
            return (1);
        }
        else if (!check && (buf[*i] == '"' || buf[*i] == 39))
           check = buf[*i];
        else if (check && buf[*i] == check)
            check = 0;
        *i += 1;            
    }
    return (1);
}

char        *ft_del_quote_av(char *s)
{
    int     len;
    char    *trim;
    char    *new;

    len = ft_len_without_quote(s);
    trim = ft_strtrim(s, " ");
    ft_strdel(&s);
    new = ft_copy_without_quote(trim, len);
    ft_strdel(&trim);
    return (new);
}