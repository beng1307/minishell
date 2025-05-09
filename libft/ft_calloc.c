/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:11:41 by bgretic           #+#    #+#             */
/*   Updated: 2024/05/21 12:41:27 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memp;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	memp = malloc(nmemb * size);
	if (memp == NULL)
		return (NULL);
	ft_bzero(memp, nmemb * size);
	return (memp);
}

//test
/*
#include <stdio.h>

int main(void)
{
	char	*test = "Hello World!";

	printf("%p\n", test);
	printf("%s\n", test);
	
	test = ft_calloc(13, sizeof(char));
	
	printf("%p\n", test);
	printf("%s\n", test);
	free(test);
}
*/
