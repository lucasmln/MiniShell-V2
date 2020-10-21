/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_read.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:21:14 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 14:41:33 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_READ_H
# define DYNAMIC_READ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include "get_next_line.h" 

# define H_NAME ".Historic.txt"

typedef	struct s_term
{
	struct	termios	set;
	struct	termios	backup;
}				t_term;

typedef	struct	s_keys
{
	char		k_left[4];
	char		k_right[4];
	char		k_up[4];
	char		k_down[4];
	char		k_home[4];
	char		k_end[4];
}				t_keys;

typedef	struct	s_reader
{
	char		c;
	char		*s;
	char		k[4];
	int			i;
	int			len;
	int			exit;
	int			ent;
}				t_reader;

typedef	struct	s_historique
{
	int			i;
	char		*tmp;
	char		**tab;
	int			size;
	int			line;
}				t_historique;


void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strncat(char *dest, const char c, int nb);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_kleft(t_keys *keys, t_reader *reader);
int		ft_kright(t_keys *keys, t_reader *reader);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_kdel(t_keys *keys, t_reader *reader);
int		ft_kup(t_reader *r, t_historique *h, t_keys *keys);
int		ft_kdown(t_reader *r, t_historique *h, t_keys *keys);
int		ft_kenter(t_reader *r, t_historique *h);
int		ft_avlen(char **env);
void	ft_add_input(t_reader *r, t_historique *h);
char	**ft_new_tab(char *var, char **env);
void	ft_kdown_zero(t_reader *r, t_historique *h, t_keys *keys);
int		create_history(t_historique *h);
int		fill_history_b(t_historique *h);
int		fill_history_a(t_historique *h, t_reader *r);
void	set_read(t_reader *r);
void	ft_reader(t_reader *r, t_keys *keys, t_historique *h, t_term *term);
void	ft_strdel(char **s);
void	ft_free_av(char **av);
void	ft_strdel_av(char ***av);
void	free_histo(t_reader *r, t_historique *h);
int		ctrl(t_reader *r);
int		ctrl_kdel(t_keys *keys, t_reader *r);
int		ft_kend(t_reader *r, t_keys *keys);
int		ft_khome(t_reader *r, t_keys *keys);

#endif
