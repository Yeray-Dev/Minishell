/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:34:13 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 14:12:17 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char *org_str, char *bff)
{
	size_t	i;
	size_t	n;
	char	*str;

	if (!org_str)
	{
		org_str = (char *)malloc(1 * sizeof(char));
		org_str[0] = '\0';
	}
	if (!org_str || !bff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(org_str) + ft_strlen(bff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	n = 0;
	if (org_str)
		while (org_str[++i] != '\0')
			str[i] = org_str[i];
	while (bff[n] != '\0')
		str[i++] = bff[n++];
	str[ft_strlen(org_str) + ft_strlen(bff)] = '\0';
	return (str);
}
