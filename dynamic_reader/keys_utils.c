/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:09:00 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/21 11:23:45 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_kdel(t_keys *keys, t_reader *r)
{
	int		i;

	ft_strlcpy(&r->s[r->i - 1], &r->s[r->i], ft_strlen(&r->s[r->i]) + 1);
	r->i--;
	write(1, keys->k_left, 3);
	write(1, &r->s[r->i], ft_strlen(&r->s[r->i]));
	write(1, " ", 1);
	i = 0;
	while ((size_t)(i) <= ft_strlen(&r->s[r->i]))
	{
		write(1, keys->k_left, 3);
		i++;
	}
	r->len--;
	return (1);
}

void		ft_kdown_zero(t_reader *r, t_historique *h, t_keys *keys)
{
	int		i;

	i = 0;
	while ((size_t)++i <= ft_strlen(r->s) - ft_strlen(&r->s[r->i]))
		write(1, keys->k_left, 3);
	i = 0;
	while ((size_t)++i <= ft_strlen(r->s))
		write(1, " ", 1);
	i = 0;
	while ((size_t)++i <= ft_strlen(r->s))
		write(1, keys->k_left, 3);
	ft_strdel(&r->s);
	if (h->size >= 2)
	{
		r->s = ft_strdup(h->tmp);
		write(1, r->s, ft_strlen(r->s));
	}
	else
		r->s = ft_strdup("");
	r->i = ft_strlen(r->s);
	r->len = ft_strlen(r->s);
	h->i--;
}

void		ft_add_input(t_reader *r, t_historique *h)
{
	char	**tmp;
	int		i;

	tmp = ft_new_tab(r->s, h->tab);
	ft_free_av(h->tab);
	h->tab = tmp;
}

char		**ft_new_tab(char *var, char **env)
{
	int		i;
	char	**new;

	if (!(new = malloc(sizeof(char *) * (ft_avlen(env) + 2))))
		exit(-1000);
	i = 0;
	new[0] = ft_strdup(var);
	while (env[i])
	{
		new[i + 1] = ft_strdup(env[i]);
		i++;
	}
	new[i + 1] = NULL;
	return (new);
}
