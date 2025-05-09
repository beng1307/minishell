#include "../minishell.h"

int	ft_mini_strrchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i != -1)
	{
		if (str[i] == (char)c)
			return (0);
		i--;
	}
	return (1);
}
	
t_env	*ft_lstnew_spec_env(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	if (ft_mini_strrchr(content, '=') == 0)
		new_node->expp = ft_strjoin_expp("declare -x ", content);
	else
		new_node->expp = ft_strjoin("declare -x ", content);
	if (ft_mini_strrchr(content, '=') == 0)
		new_node->path = content;
	else
		new_node->path = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	free_memory_array(char **array, int index)
{
	while (index-- > 0)
		ft_free(&array[index]);
	ft_free(array);
}

char	*ft_strjoin_expp(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 4);
	if (str == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[++j] != '\0' && s2[j] != '=')
		str[i + j] = s2[j];
	str[i + j++] = '=';
	str[(i++) + j] = '\"';
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j++] = '\"';
	str[i + j] = '\0';
	return (str);
}
