/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:19:00 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/18 15:58:41 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb)
{
	void	*arr;

	arr = malloc(nmemb);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, nmemb);
	return (arr);
}
// #include <stdio.h>
// #include <stdlib.h>
// int main() {
//     int *arr;
//     size_t num_elements = 5;
//     arr = (int *)ft_calloc(num_elements, sizeof(int));
// 	size_t i = 0;
//     while (i < num_elements) {
//         printf("arr[%zu] = %d\n", i, arr[i]);
// 		i++;
//     }
//     free(arr);
//     return 0;
// }
