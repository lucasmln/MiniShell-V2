/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:52:24 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/12 18:52:58 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_error_cd(char *buf, int type)
{
    char    *tmp;

    tmp = ft_get_word(buf, 0);
    if (type == NOT_FOUND)
        ft_printf(1, "minishell: %s: command not found\n", tmp);
    else if (type == NO_HOME)
        ft_printf(1, "minishell: cd: HOME not set\n");
    else if (type == NO_PWD)
        ft_printf(1, "minishell: cd: %s not set\n", buf);
    else if (type == NOT_DIR)
        ft_printf(1, "minishell: cd: %s: Not a directory\n", buf);
    ft_strdel(&tmp);
    return (0);
}