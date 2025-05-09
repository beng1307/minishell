/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:16:43 by bgretic           #+#    #+#             */
/*   Updated: 2024/10/02 15:01:45 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	if (!str || !*str)
		return (0);
	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	str[20] = "teststring";

	printf("The stringlenght is :%d", ft_strlen(str));
}
*/
