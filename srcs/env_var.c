/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:09:43 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/09 14:58:54 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char        *ft_check_exist_var(char *str, int *i, int save, char c)
{
    int     pos[2];
    char    *new;

    pos[0] = save;
    pos[1] = ft_find_var_in_av(g_shell.env, &str[save + 1]);
    if (pos[1] == -1)
        new = ft_inexist_var(str, save, c, i);
    else
        new = ft_exist_var(str, pos, c, i);
    return (new);
}

char        *ft_replace_var(char *str, int *i)
{
    int     save;
    int     pos;
    char    c;
    int     k;
    char    *new;

    save = *i;
    if (str[*i + 1] && (str[*i + 1] == '"' || str[*i + 1] == '$'))
    {
        if (str[*i + 1] == '$')
            *i += 1;
        *i += 1;
        return (str);
    }
    k = *i;
    ft_go_to_char(str, i, ' ');
    ft_go_to_char(str, &k, '"');
    *i = k < *i ? k : *i;
    k = save + 1;
    ft_go_to_char(str, &k, '$');
    *i = k < *i ? k : *i;
    if (g_shell.check == str[*i - 1])
        *i -= 1;
    c = str[*i];
    str[*i] = '\0';
    new = ft_check_exist_var(str, i, save, c);
    str[*i] = c;
    ft_strdel(&str);
    *i = save - 1;
    return (new);
}

char        *ft_get_env_var(char *str)
{
    int     i;

    g_shell.check = 0;
    i = -1;
    while (str[++i])
    {
        if ((str[i] == 39 || str[i] == '"') && !g_shell.check)
            g_shell.check = str[i];
        else if (g_shell.check == str[i])
            g_shell.check = 0;
        else if ((!g_shell.check || g_shell.check == '"') &&
                        str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
            str = ft_replace_var(str, &i);
    }
    return (str);
}

void        ft_check_env_var(void)
{
    int     i;

    i = -1;
    while (g_shell.pip_str[++i])
        g_shell.pip_str[i] = ft_get_env_var(g_shell.pip_str[i]);
}