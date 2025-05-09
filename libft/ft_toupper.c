/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:18:31 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/09 15:00:29 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		ch -= 32;
	}
	return (ch);
}

//test
/*
#include <stdio.h>

int	main(void)
{
    char	ch;

	ch = 'a';
	printf("%c in uppercase is represented as  %c", ch, toupper(ch));
}
*/
