/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:24:36 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 15:24:36 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static void	copy_str(char *dst, const char *src, size_t *j)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[*j] = src[i];
		i++;
		(*j)++;
	}
}

char	*ft_strjoin3(const char *a, const char *b, const char *c)
{
	char	*res;
	size_t	len_a;
	size_t	len_b;
	size_t	len_c;
	size_t	j;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	len_c = ft_strlen(c);
	res = malloc(len_a + len_b + len_c + 1);
	if (!res)
		return (NULL);
	j = 0;
	copy_str(res, a, &j);
	copy_str(res, b, &j);
	copy_str(res, c, &j);
	res[j] = '\0';
	return (res);
}
