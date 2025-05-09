/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linelen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:07:47 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/09 17:52:48 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_linelen(char **str_arr)
{
	size_t	length;

	length = 0;
	while (str_arr[length] != NULL)
	{
		length++;
	}
	return (length);
}
