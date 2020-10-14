/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:02:30 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 18:07:26 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_check_error_redir(char *buf)
{
    int     i;

    i = -1;
    while (buf[++i])
    {
        if (buf[i] == '>' || buf[i] == '<')
        {
            i++;
            ft_printf(1, "c = %c\n", buf[i]);
            if (buf[i] && buf[i] == '>')
                i++;
            ft_skip_space(buf, &i);
            if (buf[i] == '\0' || buf[i] == '<' || buf[i] == '>')
            {
                ft_printf(1, "minishell: syntax error near unexpected token\n");
                return ((g_shell.ret = 258));
            }
        }
    }
    return (0);
}

void        ft_skip_redir(char *buf, int *i)
{
    int     check;

    *i = buf[*i] == '>' && buf[*i + 1] == '>' ? *i + 2 : *i + 1;
    ft_skip_space(buf, i);
    check = 0;
    while (buf[*i])
    {
        if (!check && (buf[*i] == '"' || buf[*i] == 39))
            check = buf[*i];
        else if (check == buf[*i])
            check = 0;
        else if (buf[*i] == ' ' && !check)
            break ;
        *i += 1;
    }
}

int         ft_len_without_redir(char *buf)
{
    int     i;
    int     len;
    int     check;
    int     redir;

    i = 0;
    check = 0;
    len = 0;
    redir = 0;
    while (buf[i])
    {
        if (!(!check && (buf[i] == '<' || buf[i] == '>')))
            len++;
        if (!check && (buf[i] == '<' || buf[i] == '>'))
            ft_skip_redir(buf, &i);
        else if (!check && (buf[i] == '"' || buf[i] == 39))
            check = buf[i++];
        else if (check == buf[i])
        {
            check = 0;
            i++;
        }
        else
            i++;
    }
    return (len);
}

char        *ft_copy_without_redir(char *buf, char *new)
{
    int     i;
    int     check;
    int     k;

    i = 0;
    k = 0;
    check = 0;
    while (buf[i])
    {
        if (!check && (buf[i] == '"' || buf[i] == 39))
        {
            new[k++] = buf[i];
            check = buf[i++];
        }
        else if (check == buf[i])
        {
            check = 0;
            new[k++] = buf[i++];
        }
        else if (!check && (buf[i] == '<' || buf[i] == '>'))
            ft_skip_redir(buf, &i);
        else
            new[k++] = buf[i++];
    }
    new[k] = '\0';
    return (new);
}

char        *ft_del_redir(char *buf)
{
    char    *new;
    int     len;
    int     i;

    len = ft_len_without_redir(buf);
    if (!(new = malloc(sizeof(char) * (len + 1))))
        exit(-1000);
    new = ft_copy_without_redir(buf, new);
    ft_strdel(&buf);
    return (new);   
}