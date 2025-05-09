/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:16:58 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/09 15:01:55 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		ch += 32;
	}
	return (ch);
}

//test
/*
#include <stdio.h>
 
int	main(void)
{
	char	ch;

	ch = 'A';
	printf("%c in uppercase is represented as  %c", ch, toupper(ch));
}
*/
