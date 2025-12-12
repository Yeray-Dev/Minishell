/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:22:55 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 18:23:00 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	value;

	result = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			value = *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			value = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			value = *str - 'a' + 10;
		else
			break ;
		if (value >= base)
			break ;
		result = result * base + value;
		str++;
	}
	return (result);
}
