/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:14:00 by tolanini          #+#    #+#             */
/*   Updated: 2025/03/18 15:58:41 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}
/*
#include <ctype.h>
int main()
{
	printf("%d\n", isalpha('w'));
	printf("%d\n", ft_isalpha('w'));
}*/