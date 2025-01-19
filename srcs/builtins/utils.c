#include "../../includes/minishell.h"

int	str_isname(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (((i == 0 && ft_isdigit(str[i])) || !is_name(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	return (i);
}
