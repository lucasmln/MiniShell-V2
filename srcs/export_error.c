/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:57:35 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 17:59:35 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_error_export(char *buf, int type)
{
    char    *tmp;

    tmp = ft_get_word(buf, 0);
    if (type == NOT_FOUND)
        ft_printf(1, "minishell: %s: command not found\n", tmp);
    ft_strdel(&tmp);
    close(g_shell.pip.id[g_shell.pip.i][1]);
    g_shell.pip.i++;   
    g_shell.pip.len++;
    return (0);
}

int         ft_check_error_export(char *buf)
{
    int     i;
    int     cmp;
    int     check;

    i = 6;
    check = 0;
    if (buf[i] == '"' || buf[i] == 39)
    {
        check = buf[i];
        cmp = 1;
        while (check)
        {
            i++;
            if (check && buf[i] == check)
                check = 0;
            if (check && buf[i] != check)
                check = 0;
            if (!check && (buf[i] == '"' || buf[i] == 39))
                check = buf[i];
            cmp++;
        }
        if (cmp % 2 == 0)
            return (NOT_FOUND);
    }
    else if (buf[i] && buf[i] != ' ')
        return (NOT_FOUND);
    return (0);
}

int             ft_check_error_var(char *var)
{
    int     i;
    char    *buf;
    char    **tmp;

    i = 0;
    ft_skip_quote(var, &i);
    i--;
    if (ft_check_wrong_char(var) || !var[i])
    {
        ft_printf(1, "minishell: export: %s: not a valid identifier\n", var);
        return (1);
    }
    i = 0;
    buf = ft_strdup(var);
    buf = ft_change_var(buf);
    ft_check_already_exist_var(buf);
    ft_strdel(&buf);
    return (1);
}

int             ft_check_wrong_char(char *var)
{
    int     i;

    i = 0;
    while (var[i] == '"' || var[i] == 39)
        i++;
    if (!ft_isalpha(var[i]) && var[i] != '_')
        return (1);
    while (var[i])
    {
        if (var[i] == '=')
            return (0);
        if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '"' && var[i] != 39)
            return (1);
        i++;
    }
    return (0);
}