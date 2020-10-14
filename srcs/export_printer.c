/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:00:00 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 18:14:14 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_print_env(void)
{
	int		i;

	i = -1;
	while (g_shell.sort_env[++i])
	{
		ft_printf(STDOUT_FILENO, "%s", g_shell.sort_env[i]);
		write(STDOUT_FILENO, "\n", 1);
	}
}

int			ft_set_print_env(char *buf)
{
	int		i;
	int		check;
	pid_t	pid;

	i = -1;
	check = 0;
	while (buf[++i] && !check)
		if (buf[i] != ' ')
			check = 1;
	pid = fork();
	if (pid == 0)
	{
		close(g_shell.pip.id[g_shell.pip.i][0]);
		if (g_shell.out.len > 0)
			dup2(g_shell.out.fd[g_shell.out.len - 1], STDOUT_FILENO);
		else if (!g_shell.pip_str[g_shell.i_p + 1])
			;
		else
			dup2(g_shell.pip.id[g_shell.pip.i][1], STDOUT_FILENO);
		if (!g_shell.error_input)
			ft_print_env();
		exit(g_shell.error_input);
	}
	waitpid(pid, &check, 0);
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.pip.i++;
	g_shell.pip.len++;
	return (1);
}
