/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <jvaquer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:55:31 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/22 15:25:28 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			set_read(t_reader *r)
{
	ft_memset(r->k, 0, 4);
	if (r->tab == 2)
	{
		ft_strdel(&r->s);
		r->s = ft_strdup(r->tmp);
		r->len = ft_strlen(r->s);
		r->i = r->len;
		write(1, r->s, r->len);
	}
	else
	{
		r->s = ft_calloc(2, sizeof(char));
		r->i = 0;
		r->len = 0;
	}
	r->exit = 0;
	r->ent = 0;
	r->tab = 0;
}

void			free_histo(t_historique *h)
{
	ft_free_av(h->tab);
	ft_strdel(&h->tmp);
}
