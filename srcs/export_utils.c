/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:54:59 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 17:56:05 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_skip_quote(char *buf, int *i)
{
    int     check;

    check = 0;
    while (buf[*i])
    {
        if (buf[*i] == '"' || buf[*i] == 39)
        {
            check = buf[*i];
            *i += 1;
            if (buf[*i] == check)
                *i += 1;
            else
                return ; 
        }
        else if (buf[*i] != '"' && buf[*i] != 39)
        {
            *i += 1;
            return ;
        }
        else
         *i += 1;
    }
}

int         ft_len_word_with_quote(char *buf)
{
    int     len;
    int     i;
    int     check;

    i = 0;
    check = 0;
    len = 0;
    while (buf[i])
    {
        len++;
        if (!check && (buf[i] == '"' || buf[i] == 39))
            check = buf[i++];
        else if (check && (buf[i] == '"' || buf[i] == 39))
        {
            check = 0;
            i++;
        }
        else if (!check && buf[i] == ' ')
            break ;
        else
            i++;
    }
    return (len);
}

char        *ft_get_word_with_quote(char *buf)
{
    int     len;
    char    *new;
    int     i;

    i = 0;
    ft_skip_space(buf, &i);

    len = ft_len_word_with_quote(&buf[i]);
    if (!(new = malloc(sizeof(char) * (len + 1))))
        exit(-1000);
    ft_strlcpy(new, &buf[i], len + 1);
    return (new);
}

int             ft_avlen(char **env)
{
    int     i;

    i = 0;
    if (!env)
        return (0);
    while (env[i])
        i++;
    return (i);
}

char            **ft_avdup(char **env)
{
    char    **new;
    int     i;

    if (!(new = malloc(sizeof(char *) * (ft_avlen(env) + 1))))
        exit(-1000);
    i = -1;
    while (env[++i])
        new[i] = ft_strdup(env[i]);
    new[i] = NULL;
    return (new);
}