#include "../../includes/minishell.h"

int	ft_unset(char **args, t_env *env)
{
	int			count;
	t_envnode	*node;

	count = 0;
	while (args && args[count] != NULL)
	{
		node = search_key(env, args[count]);
		if (!node)
			return (0);
		if (node->next)
			node->next->prev = node->prev;
		if (node->prev)
			node->prev->next = node->next;
		free(node->key);
		free(node->value);
		free(node);
		count++;
	}
	return (0);
}
