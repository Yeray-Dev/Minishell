/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:43:36 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:15:41 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c1;
	char			*string;
	size_t			len;

	c1 = (unsigned char) c;
	len = ft_strlen(s);
	string = (char *) s;
	if (c1 == '\0')
		return (&string[len]);
	while (len > 0)
	{
		if (string[len - 1] == c1)
			return (&string[len - 1]);
		len--;
	}
	return (NULL);
}
