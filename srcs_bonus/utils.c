/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:00 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:58:22 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char        *ft_str_add(char *s1, char *s2)
{
    char    *new;
    int     i;
    int     k;

    if (!s1 && !s2)
        return (ft_strdup(""));
    if (!s1 || !s2)
    {
        new = !s2 ? ft_strdup(s1) : ft_strdup(s1);
        !s2 ? ft_strdel(&s1) : ft_strdel(&s2);
        return (new);
    }
    if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
        exit(-1000);
    i = -1;
    while (s1[++i])
        new[i] = s1[i];
    k = -1;
    while (s2[++k])
    {
        new[i + k] = s2[k];
    }
    new[i + k] = '\0';
    ft_strdel(&s1);
    ft_strdel(&s2);
    s1 = NULL;
    s2 = NULL;
    return (new);
}

void        ft_go_to_char(char *s, int *i, char c)
{
    while (s[*i])
    {
        if (s[*i] == c)
            break ;
        *i += 1;
    }
}

char        *ft_copy_without_quote(char *buf, int len)
{
    char    *word;
    int     i;
    int     k;

    g_shell.check = 0;
    if (!(word = malloc(sizeof(char) * (len + 1))))
        exit(-1000);
    i = 0;
    k = 0;
    while (buf[i])
    {
        if (!g_shell.check && (buf[i] == 39 || buf[i] == '"'))
            g_shell.check = buf[i++];
        else if (g_shell.check == buf[i])
        {
            g_shell.check = 0;
            i++;
        }
        else if (k == len)
            break ;
        else
            word[k++] = buf[i++];
    }
    word[k] = '\0';
    return (word);
}

int         ft_len_without_quote(char *buf)
{
    int     i;
    int     len;
    int     check;

    check = 0;
    len = 0;
    i = 0;
    while (buf[i])
    {
        if (check == 0 && (buf[i] == '"' || buf[i] == 39))
            check = buf[i++];       
        else if (check == buf[i])
        {
            check = 0;
            i++;
        }
        else
        {
            i++;
            len++;
        }
    }
    return (len);
}

char        *ft_get_word(char *buf)
{
    int     i;
    int     len;
    int     save;

    i = 0;
    len = 0;
    g_shell.check = 0;
    ft_skip_space(buf, &i);
    save = i;
    while (buf[i + len])
    {
        if (g_shell.check == 0 && (!buf[i + len] || buf[i + len] == ' '))
            break ;
        if ((buf[i + len] == 39 || buf[i + len] == '"') && g_shell.check == 0)
            g_shell.check = buf[i++ + len];
        else if (g_shell.check == buf[i + len])
        {
            g_shell.check = 0;
            i++;
        }
        else
            len++;
    }
    return (ft_copy_without_quote(&buf[save], len));
}