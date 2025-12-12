/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_burbble_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:53:04 by yblanco-          #+#    #+#             */
/*   Updated: 2025/07/19 13:53:11 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_burbble_sort(int array_to_sort[], int size)
{
	int	i;
	int	j;
	int	aux;

	i = 0;
	j = 0;
	aux = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (array_to_sort[j] > array_to_sort[j + 1])
			{
				aux = array_to_sort[j];
				array_to_sort[j] = array_to_sort[j + 1];
				array_to_sort[j + 1] = aux;
			}
			j++;
		}
		i++;
	}
}
