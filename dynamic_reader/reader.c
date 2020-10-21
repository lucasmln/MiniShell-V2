/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:44:57 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/21 11:38:25 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			ft_print_char(t_reader *r, t_keys *keys)
{
	int i;

	i = 0;
	write(1, &r->c, 1);
	write(1, &r->s[r->i], ft_strlen(&r->s[r->i]));
	while ((size_t)(i) < ft_strlen(&r->s[r->i]))
	{
		write(1, keys->k_left, 3);
		++i;
	}
}

void			fill_str(t_reader *r, t_keys *keys)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * (r->len + 2))))
		exit(-1000);
	ft_strlcpy(tmp, r->s, r->i + 1);
	tmp[r->i] = r->c;
	tmp[r->i + 1] = '\0';
	ft_strlcpy(&tmp[r->i + 1], &r->s[r->i], ft_strlen(&r->s[r->i]) + 1);
	ft_strdel(&r->s);
	r->s = tmp;
	r->i++;
	r->len++;
	ft_print_char(r, keys);
}

int				ft_exit(t_reader *r)
{
	r->exit = 1;
	write(1, "exit", 4);
	return (0);
}

int				ft_switch_keys(t_reader *r, t_keys *keys, t_historique *h)
{
	if (r->c == 4 && ft_strlen(r->s) == 0)
		return (ft_exit(r));
	else if (r->c == 3 || r->c == 12)
		ctrl(r);
	else if (r->c == 4 && ft_strlen(r->s) > 0)
		ctrl_kdel(keys, r);
	else if (r->c == 28)
		;
	if (ft_strncmp(r->k, keys->k_left, 4) == 0)
		ft_kleft(keys, r);
	if (ft_strncmp(r->k, keys->k_right, 4) == 0)
		ft_kright(keys, r);
	if (ft_strncmp(r->k, keys->k_up, 4) == 0)
		ft_kup(r, h, keys);
	if (ft_strncmp(r->k, keys->k_down, 4) == 0)
		ft_kdown(r, h, keys);
	if (ft_strncmp(r->k, keys->k_home, 4) == 0)
		ft_khome(r, keys);
	if (ft_strncmp(r->k, keys->k_end, 4) == 0)
		ft_kend(r, keys);
	else if ((r->c == 127) && r->i > 0)
		ft_kdel(keys, r);
	return (0);
}

void			ft_reader(t_reader *r, t_keys *keys,
					t_historique *h, t_term *term)
{
	set_read(r);
	while (!r->exit && !r->ent)
	{
		tcsetattr(0, 0, &term->set);
		r->c = 0;
		read(0, &r->c, 1);
		if ((r->c >= ' ' && r->c <= '~') && ft_strlen(r->k) == 0)
			fill_str(r, keys);
		if (r->c == 27 || ft_strlen(r->k) > 0)
			r->k[ft_strlen(r->k)] = r->c;
		if (ft_switch_keys(r, keys, h) > 0)
			ft_kenter(r, h);
		if (ft_strlen(r->k) >= 3)
			ft_memset(r->k, 0, 4);
		if (r->c == '\n')
		{
			write(1, "\n", 1);
			ft_kenter(r, h);
		}
		tcsetattr(0, 0, &term->backup);
	}
}
