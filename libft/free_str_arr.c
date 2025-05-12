/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdocekal <tdocekal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:32:11 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/08 20:36:54 by tdocekal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str_arr(char ***arr)
{
	int	index;

	if (!arr || !*arr)
		return ;
	index = 0;
	while ((*arr)[index])
	{
		free((*arr)[index]);
		(*arr)[index++] = NULL;
	}
	free(*arr);
	*arr = NULL;
}
