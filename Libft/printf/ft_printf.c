/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:49:50 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 13:56:46 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_type(char type, va_list *args, int *cs)
{
	if (type == 'd' || type == 'i')
		ft_print_basic(type, args, cs);
	else if (type == 's')
		ft_print_basic(type, args, cs);
	else if (type == 'c')
		ft_print_basic(type, args, cs);
	else if (type == 'p')
		ft_print_basic(type, args, cs);
	else if (type == 'u')
		ft_print_special(type, args, cs);
	else if (type == 'x')
		ft_print_special(type, args, cs);
	else if (type == 'X')
		ft_print_special(type, args, cs);
	else if (type == '%')
		ft_print_special(type, args, cs);
}

int	ft_printf(char const *format, ...)
{
	int	i;
	int	*cs;

	va_list(args);
	va_start(args, format);
	i = 0;
	cs = malloc(sizeof(int) * 1);
	*cs = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i++])
			ft_print_type(format[i], &args, cs);
		else
		{
			write(1, &format[i], 1);
			(*cs)++;
		}
		i++;
	}
	va_end(args);
	i = cs[0];
	free(cs);
	return (i);
}
