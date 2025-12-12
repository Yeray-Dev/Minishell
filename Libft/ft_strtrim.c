/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:55:27 by yblanco-          #+#    #+#             */
/*   Updated: 2024/10/04 17:01:04 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stddef.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*result;

	if ((!set) || (!s1))
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	end = len;
	while ((s1[start]) && (ft_strchr(set, s1[start]) != NULL))
		start++;
	while ((end) && (ft_strchr(set, s1[end]) != NULL))
		end--;
	result = ft_substr(s1, start, end - start + 1);
	return (result);
}
