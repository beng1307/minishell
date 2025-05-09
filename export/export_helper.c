#include "../minishell.h"

size_t	ft_strlen_to(const char *str)
{
	size_t	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length] != '=' && str[length] != '\0')
		length++;
	return (length);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while(*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void	bubble_sort(char **array, int count)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < count - 1)
	{
		while (j < count - 1 - i)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
				swap(&array[j], &array[j + 1]);
			j++;
		}
		j = 0;
		i++;
	}
}

void ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

void	swap(char **a, char **b)
{
	char *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}