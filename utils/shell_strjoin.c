/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:53:43 by bgretic           #+#    #+#             */
/*   Updated: 2024/12/04 17:53:44 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sh_strjoin(char const *s1, char const *s2, int i, int j)
{
	char	*str;

	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (s1 && *s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2 && *s2)
	{
		while (s2[j] != '\0')
		{
			str[i + j] = s2[j];
			j++;
		}
	}
	return (str);
}
