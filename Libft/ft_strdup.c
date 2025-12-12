/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:05:38 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:15:59 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str_copy;

	len = ft_strlen(s1);
	str_copy = malloc((len + 1) * (sizeof(char)));
	if (!str_copy)
		return (NULL);
	ft_strlcpy (str_copy, s1, len + 1);
	return (str_copy);
}
