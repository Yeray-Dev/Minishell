/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:25:02 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 15:25:02 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dblptr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static long long	atoi_overflow_core(const char *str, int *error, int sign)
{
	long long	result;
	int			i;
	long long	digit;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if ((sign == 1 && result > (LLONG_MAX - digit) / 10)
			|| (sign == -1 && - result < (LLONG_MIN + digit) / 10))
		{
			*error = 1;
			return (0);
		}
		result = result * 10 + digit;
		i++;
	}
	if (str[i] != '\0')
	{
		*error = 1;
		return (0);
	}
	return (result * sign);
}

static int	handle_sign_and_skip_spaces(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long long	atoi_overflow(const char *str, int *error)
{
	int	i;
	int	sign;

	if (error)
		*error = 0;
	if (!str)
	{
		if (error)
			*error = 1;
		return (0);
	}
	i = 0;
	sign = handle_sign_and_skip_spaces(str, &i);
	if (str[i] < '0' || str[i] > '9')
	{
		if (error)
			*error = 1;
		return (0);
	}
	return (atoi_overflow_core(&str[i], error, sign));
}
