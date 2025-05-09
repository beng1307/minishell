/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:50:43 by bgretic           #+#    #+#             */
/*   Updated: 2024/04/29 12:10:23 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (f == NULL)
		return (NULL);
	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

//test
/* 
static char increment(unsigned int num, char c)
{   
    if (c >= 'a' && c <= 'y')
    {
        c += num;
    }        
    else if (c == 'z')
    {
        c = 'a';
    }
    return (c);
}

static char decrement(unsigned int num, char c)
{

        if (c >= 'b' && c <= 'z')
        {
                c -= num;
        }
        else if (c == 'a')
        {
                c = 'z';
        }
        return (c);
}

#include <stdio.h>

int	main(void)
{
	char 	*test;

	test = "ggg";
	char *result = ft_strmapi(test, decrement);
	char *result2 = ft_strmapi(test, increment);
	printf("%s\n", result);
	printf("%s\n", result2);
*/
