/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:34:49 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/07 16:56:02 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		num = -num;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*number;
	size_t		count;
	long int	new_n;

	new_n = (long int)n;
	count = 0;
	if ((long int)n <= 0)
		count++;
	while ((new_n != 0))
		new_n = new_n / 10;
	number = ft_calloc(count + 1, sizeof(char));
	if (number == NULL)
		return (NULL);
	new_n = (long int)n;
	if ((long int)n < 0)
		(new_n = (long int)n * -1);
	while (count-- != 0)
	{
		number[count] = new_n % 10 + '0';
		new_n = new_n / 10;
	}
	if ((long int)n < 0)
		number[0] = '-';
	return (number);
}
