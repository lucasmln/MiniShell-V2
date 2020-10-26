/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <jvaquer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:25:04 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/26 22:39:53 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		set_keys(t_keys *keys)
{
	keys->k_left[0] = 27;
	keys->k_left[1] = '[';
	keys->k_left[2] = 'D';
	keys->k_left[3] = 0;
	keys->k_right[0] = 27;
	keys->k_right[1] = '[';
	keys->k_right[2] = 'C';
	keys->k_right[3] = 0;
	keys->k_up[0] = 27;
	keys->k_up[1] = '[';
	keys->k_up[2] = 'A';
	keys->k_up[3] = 0;
	keys->k_down[0] = 27;
	keys->k_down[1] = '[';
	keys->k_down[2] = 'B';
	keys->k_down[3] = 0;
	keys->k_home[0] = 27;
	keys->k_home[1] = '[';
	keys->k_home[2] = 'H';
	keys->k_home[3] = '\0';
	keys->k_end[0] = 27;
	keys->k_end[1] = '[';
	keys->k_end[2] = 'F';
	keys->k_end[3] = '\0';
}

int			ft_setup_main(const char **env, t_term *term, t_reader *r,
		t_historique *h)
{
	g_shell.ret = 0;
	r->exit = 0;
	r->tmp = NULL;
	r->tab = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (tcgetattr(0, &term->backup) == -1)
		return (0);
	if (tcgetattr(0, &term->set) == -1)
		return (0);
	term->set.c_lflag &= ~(ICANON | ECHO | ISIG);
	ft_init_fd_tab();
	if (!(ft_copy_env(env)))
		return (0);
	if (!(create_history(h)))
		return (0);
	if (!(fill_history_b(h)))
		return (0);
	return (1);
}

int			ft_check_empty_cmd(void)
{
	int		i;

	i = 0;
	if (ft_strlen(g_shell.str) &&
			g_shell.str[ft_strlen(g_shell.str) - 1] == '\n')
		g_shell.str[ft_strlen(g_shell.str) - 1] = '\0';
	ft_skip_space(g_shell.str, &i);
	if (!g_shell.str[i])
	{
		ft_strdel(&g_shell.str);
		return (0);
	}
	ft_print_prompt();
	return (1);
}

int			main(int ac, char **av, const char **env)
{
	t_term			term;
	t_keys			keys;
	t_reader		r;
	t_historique	h;
	int				i;

	(void)ac;
	(void)av;
	set_keys(&keys);
	if (!ft_setup_main(env, &term, &r, &h))
		return (1);
	while (!r.exit)
	{
		ft_print_prompt_2();
		ft_reader(&r, &keys, &h, &term);
		i = 0;
		ft_skip_space(r.s, &i);
		g_shell.str = ft_strdup(&r.s[i]);
		ft_strdel(&r.s);
		if (ft_check_empty_cmd())
			ft_free_all();
	}
	if (!(fill_history_a(&h, &r)))
		return (0);
	return (0);
}
