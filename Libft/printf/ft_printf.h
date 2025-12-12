/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:35:19 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 15:54:53 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "../libft.h"

//. FUNCTIONS
//. ft_printf.c
int			ft_printf(char const *format, ...);
//. ft_hexa.c
void		*ft_hexa(unsigned int number, char type, int	*cs);
void		*ft_hexa_ptr(unsigned long long number, char type, int	*cs);
void		*ft_hexa_pointer(unsigned long long pointer, int	*cs);
//. ft_itoa.c
// char		*ft_itoa(int n);
void		ft_itoa_unsigned(unsigned int n, int *cs);
//. ft_redirect.c
void		ft_print_basic(char type, va_list *args, int *cs);
void		ft_print_special(char type, va_list *args, int *cs);
//. ft_printf_utils.c
void		ft_putstr_cs(char *s, int fd, int *cs);
int			is_min(int n, int fd, int *cs);
void		ft_putnbr_cs(int n, int fd, int *cs);
void		ft_putchar_cs(char c, int fd, int *cs);
int			ft_count(unsigned long int new_n, int *cs);
#endif