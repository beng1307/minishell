/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_table_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:53:46 by tdocekal          #+#    #+#             */
/*   Updated: 2024/12/19 16:42:58 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocate_command(t_cmd **lastlst, t_tokens *tokens_copy)
{
	int	size_count;

	size_count = 0;
	while (tokens_copy && tokens_copy->type == WORD)
	{
		size_count++;
		tokens_copy = tokens_copy->next;
	}
	(*lastlst)->command = ft_calloc(size_count + 1, sizeof(char *));
	if (!(*lastlst)->command)
		return (terminator());
}
