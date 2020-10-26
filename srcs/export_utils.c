/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:54:59 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/26 16:25:41 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_skip_quote(char *buf, int *i)
{
	int		check;

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
			return ;
		else
			*i += 1;
	}
}

int			ft_len_word_with_quote(char *buf)
{
	int		len;
	int		i;
	int		check;

	i = 0;
	check = 0;
	len = 0;
	while (buf[i])
	{
		len++;
		if (!check && (buf[i] == '"' || buf[i] == 39))
			check = buf[i++];
		else if (check && check == buf[i])
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

char		*ft_get_word_with_quote(char *buf)
{
	int		len;
	char	*new;
	int		i;

	i = 0;
	ft_skip_space(buf, &i);
	len = ft_len_word_with_quote(&buf[i]);
	if (!(new = malloc(sizeof(char) * (len + 1))))
		exit(-1000);
	ft_strlcpy(new, &buf[i], len + 1);
	return (new);
}

void		ft_switch_word(char **word, char **tmp)
{
	ft_strdel(word);
	*word = ft_strdup(*tmp);
	ft_strdel(tmp);
}

int			ft_incremente_export(char *word)
{
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.pip.i++;
	g_shell.pip.len++;
	(void)word;
	return (1);
}

void		ft_incremente_start(char *buf, int *start, int init)
{
	if (init)
		*start = 6;
	ft_skip_space(buf, start);
	ft_skip_quote(buf, start);
}
