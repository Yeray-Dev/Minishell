/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:34:49 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:42:08 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// char	*ft_itoa(int n)
// {
// 	char		*number;
// 	size_t		count;
// 	long int	new_n;

// 	new_n = (long int)n;
// 	count = 0;
// 	if ((long int)n <= 0)
// 		count++;
// 	while ((new_n != 0) && (count++ >= 0))
// 		new_n = new_n / 10;
// 	number = ft_calloc(count + 1, sizeof(char));
// 	if (number == NULL)
// 		return (NULL);
// 	new_n = (long int)n;
// 	if ((long int)n < 0)
// 		(new_n = (long int)n * -1);
// 	while (count-- != 0)
// 	{
// 		number[count] = new_n % 10 + '0';
// 		new_n = new_n / 10;
// 	}
// 	if ((long int)n < 0)
// 		number[0] = '-';
// 	return (number);
// }

void	ft_itoa_unsigned(unsigned int n, int *cs)
{
	char				*number;
	size_t				count;
	unsigned long int	new_n;

	new_n = (unsigned long int)n;
	count = ft_count(new_n, cs);
	if (new_n == 0)
		return ;
	number = (char *)ft_calloc(count + 1, sizeof(char));
	if (number == NULL)
		return ;
	while (count-- != 0)
	{
		number[count] = new_n % 10 + '0';
		new_n /= 10;
	}
	count = 0;
	while (number[count])
		write(1, &number[count++], 1);
	free(number);
}
