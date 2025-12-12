/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:22:01 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:24:45 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_basic(char type, va_list *args, int *cs)
{
	int					number;
	char				c;
	char				*str;
	unsigned long long	pointer;

	if (type == 'd' || type == 'i')
	{
		number = va_arg(*args, int);
		ft_putnbr_cs(number, 1, cs);
	}
	else if (type == 's')
	{
		str = va_arg(*args, char *);
		ft_putstr_cs(str, 1, cs);
	}
	else if (type == 'c')
	{
		c = (char)va_arg(*args, int);
		ft_putchar_cs(c, 1, cs);
	}
	else if (type == 'p')
	{
		pointer = (unsigned long long)va_arg(*args, void *);
		ft_hexa_pointer(pointer, cs);
	}
}

void	ft_print_special(char type, va_list *args, int *cs)
{
	unsigned int	unsigned_number;

	if (type == 'u')
	{
		unsigned_number = va_arg(*args, unsigned int);
		ft_itoa_unsigned(unsigned_number, cs);
	}
	else if (type == 'x')
	{
		unsigned_number = va_arg(*args, int);
		ft_hexa(unsigned_number, type, cs);
	}
	else if (type == 'X')
	{
		unsigned_number = va_arg(*args, int);
		ft_hexa(unsigned_number, type, cs);
	}
	else if (type == '%')
	{
		write(1, "%", 1);
		(*cs)++;
	}
}
