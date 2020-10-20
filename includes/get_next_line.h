/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:07:52 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/20 13:32:56 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#define MAX 1024

#define BUFFER_SIZE 32

int		        get_next_line(int fd, char **line);
size_t	        ft_strlen2(const char *str);
char            *ft_strcpy(char *dest, char *src);
char	        *ft_substr(char const *s, unsigned int start, size_t len);
char	        *ft_strchr(const char *s, int c);

#endif
