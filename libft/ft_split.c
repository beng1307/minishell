/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:29:54 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/29 11:30:06 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_lenghtcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		count = 0;
		while (*s == c)
			s++;
		while (*s && *s != c)
		{
			count++;
			s++;
		}
		break ;
	}
	return (count);
}

static int	ft_split_wordcount(char const *s, char c)
{
	int	count;
	int	is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
		{
			is_word = 1;
			s++;
		}
		if (is_word == 1)
		{
			count++;
			is_word = 0;
		}
	}
	return (count);
}

static int	ft_freemem(char **str, int array)
{
	int	i;

	i = 0;
	while (i < array)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static char	**ft_splitcpy(char **str, const char *s, char c)
{
	int		i;
	int		array;

	i = 0;
	array = 0;
	while (*s)
	{
		if (ft_split_lenghtcount(s, c) == 0)
			return (str);
		str[array] = ft_calloc(ft_split_lenghtcount(s, c) + 1, sizeof(char));
		if (str[array] == NULL)
			return (ft_freemem(str, array), NULL);
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			str[array][i++] = *s;
			s++;
		}
		array++;
		i = 0;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**str;
	size_t		wordcount;

	if (!s)
		return (NULL);
	wordcount = ft_split_wordcount(s, c);
	str = ft_calloc((wordcount + 1), sizeof(char *));
	if (str == NULL)
		return (NULL);
	str[wordcount] = NULL;
	if (!(ft_splitcpy(str, s, c)))
		return (NULL);
	return (str);
}

//test
/*
#include <stdio.h>

int	main(void)
{
	char	*test = "^^^1^^2a,^^^^3^^^^--h^^^^";
	char	seperator = '^';
	char	**test2 = ft_split(test, seperator);

	int i = 0;	
	while (test2[i])
	{
		printf("%s\n", test2[i]);
		i++;
	}
}
*/
