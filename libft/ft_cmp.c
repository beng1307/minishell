#include "libft.h"

bool	ft_cmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	if (!s1 || !s2)
		return (false);
	while (s1[index] == s2[index]
		&& s1[index] && s2[index])
		index++;
	return (s1[index] == s2[index]);
}