/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:04:19 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/22 17:56:37 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_del_word_in_env(int pos)
{
	int		i;
	int		k;
	char	**tmp;

	i = -1;
	k = 0;
	if (!(tmp = malloc(sizeof(char *) * (ft_avlen(g_shell.env)))))
		exit(-1000);
	while (g_shell.env[++i])
		if (i != pos)
			tmp[k++] = ft_strdup(g_shell.env[i]);
	tmp[k] = NULL;
	ft_free_av(g_shell.env);
	g_shell.env = tmp;
}

void		ft_del_word_in_export(int pos)
{
	int		i;
	int		k;
	char	**tmp;

	i = -1;
	k = 0;
	if (!(tmp = malloc(sizeof(char *) * (ft_avlen(g_shell.sort_env)))))
		exit(-1000);
	while (g_shell.sort_env[++i])
		if (i != pos)
			tmp[k++] = ft_strdup(g_shell.sort_env[i]);
	tmp[k] = NULL;
	ft_free_av(g_shell.sort_env);
	g_shell.sort_env = tmp;
}

int			ft_find_pos_in_av(char *word)
{
	int		pos[2];
	char	*equal;

	equal = ft_str_add(ft_strdup(word), ft_strdup("="));
	pos[0] = ft_find_var_in_av(g_shell.env, equal);
	pos[1] = ft_find_var_in_av(g_shell.sort_env, equal);
	ft_strdel(&equal);
	if (pos[0] != -1)
		ft_del_word_in_env(pos[0]);
	if (pos[1] != -1)
		ft_del_word_in_export(pos[1]);
	return (1);
}

void		ft_loop_unset(char *word, char *buf, char *tmp, int start)
{
	while (word[0])
	{
		if (ft_check_wrong_char_unset(word))
			ft_printf(1,
					"minishell: export: %s: not a valid identifier\n", word);
		else
			ft_find_pos_in_av(word);
		start += ft_strlen(word) + 1;
		ft_strdel(&word);
		ft_skip_space(buf, &start);
		word = ft_get_word(&buf[start], 0);
		tmp = ft_strtrim(word, " ");
		ft_strdel(&word);
		word = tmp;
	}
	ft_strdel(&word);
}

int			ft_unset(char *buf)
{
	int		i;
	char	*word;
	char	*tmp;
	int		start;

	pipe(g_shell.pip.id[g_shell.pip.i]);
	g_shell.tmp_ret = !g_shell.pip_str[g_shell.i_p + 1] ? 0 : g_shell.tmp_ret;
	if (ft_check_error_unset(buf, &start))
		return (ft_error_unset(buf));
	i = 0;
	word = ft_get_word(buf, i);
	tmp = ft_strtrim(word, " ");
	ft_strdel(&word);
	word = ft_strdup(tmp);
	ft_strdel(&tmp);
	ft_loop_unset(word, buf, tmp, start);
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.pip.i++;
	g_shell.pip.len++;
	return (3);
}
