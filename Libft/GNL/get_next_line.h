/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:17:03 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:11:31 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft.h"

char	*ft_read(int fd, char *str);
char	*get_next_line(int fd);
char	*ft_line(char *str);
char	*ft_next_str(char *str);
char	*ft_strjoin_gnl(char *org_str, char *bff);

#endif