/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:01:17 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:06:21 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_cs(char *s, int fd, int *cs)
{
	int	i;

	if (!s)
	{
		write(1, "(null)", 6);
		(*cs) += 6;
		return ;
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
		(*cs)++;
	}
}

int	is_min(int n, int fd, int *cs)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		(*cs) += 11;
		return (0);
	}
	return (1);
}

void	ft_putnbr_cs(int n, int fd, int *cs)
{
	int		i;
	int		count;
	char	*number;

	i = 0;
	count = 0;
	if (!is_min(n, fd, cs))
		return ;
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		count = 1;
	}
	number = ft_itoa(n);
	if (!number)
		return ;
	while (number[i])
		write(fd, &number[i++], 1);
	free(number);
	(*cs) += (i + count);
}

void	ft_putchar_cs(char c, int fd, int *cs)
{
	write(fd, &c, 1);
	(*cs)++;
}

int	ft_count(unsigned long int new_n, int *cs)
{
	size_t	count;

	count = 0;
	if (new_n == 0)
	{
		write(1, "0", 1);
		(*cs)++;
		return (0);
	}
	while ((new_n != 0))
		new_n = new_n / 10;
	(*cs) += count;
	return (count);
}
