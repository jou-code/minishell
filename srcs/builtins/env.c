#include "../../includes/minishell.h"

t_envnode	*new_envnode(char *str)
{
	int			pos;
	char		*split;
	t_envnode	*node;

	split = ft_strchr(str, '=');
	if (!split || str - split == 0)
		return (NULL);
	pos = (split - str);
	node = malloc(sizeof(t_envnode));
	if (!node)
		return (NULL);
	node->key = strndup(str, pos);
	node->value = ft_strdup(&str[++pos]);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	addback_env(t_envnode *newnode, t_env *list)
{
	t_envnode	*node;

	node = list->head;
	if (!node)
	{
		list->head = newnode;
		list->tail = newnode;
		list->len++;
		return ;
	}
	node = list->tail;
	newnode->prev = node;
	node->next = newnode;
	list->tail = newnode;
	list->len++;
}

t_env	*get_env_list(char **envp)
{
	int			i;
	t_env		*env;
	t_envnode	*node;

	i = 0;
	if (!envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	env->len = 0;
	env->head = NULL;
	env->tail = env->head;
	while (envp[i] != NULL)
	{
		node = new_envnode(envp[i]);
		addback_env(node, env);
		i++;
	}
	node = new_envnode("?=0");
	addback_env(node, env);
	env->tail = node;
	return (env);
}

int	ft_env(t_env *env)
{
	t_envnode	*node;

	if (!env || !env->head)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		if (node->key[0] != '?')
		{
			ft_putstr_fd(node->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(node->value, 1);
			ft_putchar_fd('\n', 1);
		}
		node = node->next;
	}
	return (0);
}
