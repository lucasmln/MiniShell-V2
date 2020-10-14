/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:36:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 18:09:55 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_add_var(char *buf, int start)
{
	char	*word;
	char	*tmp;

	word = ft_get_word_with_quote(&buf[start]);
	tmp = ft_strtrim(word, " ");
	ft_strdel(&word);
	word = tmp;
	ft_check_error_var(word);
	ft_strdel(&word);
}

int			ft_export(char *buf)
{
	int		start;
	int		end;
	char	*word;
	char	*tmp;

	pipe(g_shell.pip.id[g_shell.pip.i]);
	if (ft_check_error_export(buf))
		return (ft_error_export(buf, NOT_FOUND));
	start = 6;
	ft_skip_quote(buf, &start);
	word = ft_get_word_with_quote(&buf[start]);
	if (!word[0] && buf[start] != '"' && buf[start] != 39)
	{
		ft_strdel(&word);
		return (ft_set_print_env(&buf[start]));
	}
	while (1)
	{
		tmp = ft_strtrim(word, " ");
		ft_strdel(&word);
		word = tmp;
		if (!word[0])
			break ;
		ft_add_var(buf, start);
		start += ft_strlen(word);
		ft_strdel(&word);
		ft_skip_quote(buf, &start);
		word = ft_get_word_with_quote(&buf[start]);
	}
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.pip.i++;
	g_shell.pip.len++;
	ft_strdel(&word);
	return (1);
}
