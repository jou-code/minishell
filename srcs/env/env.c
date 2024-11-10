#include "../../includes/minishell.h"

int	str_isname(char *str)
{
	int	i = 0;

	while (str[i] != '\0')
	{
		if (((i == 0 && ft_isdigit(str[i])) || !is_name(str[i])))
			return(0);
		i++;
	}
	return(1);
}
t_envnode	*new_envnode(char *str)
{
	int	pos;
	char *split;
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
	int	i = 0;
	t_env	*env;
	t_envnode	*node;

	if (!envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	env->len = 0;
	env->head = NULL;
	env->tail = env->head;
	env->envp = envp;
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

int	minienv(t_env *env)
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

int	export(char **args, t_env *env)
{
	int	ret = 0;
	int	count = 0;
	t_envnode	*node;
	
	while (args && args[count] != NULL)
	{
		// TODO: validar caso de prompt '1asd' nao printar erro
		node = new_envnode(args[count]);
		if (node && str_isname(node->key))
			addback_env(node, env);
		else if (node)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(node->key, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			free(node->key);
			free(node->value);
			free(node);
			ret = 1;
		}
		else
			ret = 1;
		count++;
	}
	return(ret);
}

int	unset(char **args, t_env *env)
{
	int	count = 0;
	t_envnode	*node;
	
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

int	destroy_env(t_env *env)
{
	t_envnode	*node;
	t_envnode	*temp;
	
	if (!env || !env->head)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		temp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	free(env);
	return (0);
}

char	*ft_getenv(t_env *list, char *key)
{
	int	len = ft_strlen(key);
	t_envnode	*env;

	env = list->head;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, len + 1) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_strdup(env->value));
}

int	miniexit(char **args, t_env *env, t_tab *cmdtab)
{
	int	len = splitlen(args);
	int	i = 0;
	int	nbr = 1;

	ft_putstr_fd("exit\n", 1);
	if (args[0][i] == '-')
		i++;
	while (args && args[0][i] != '\0')
	{
		if (!ft_isdigit(args[0][i]))
		{
			nbr = 0;
			break;
		}
		i++;
	}
	if (!nbr || i >= 20)
		nbr = minierror("exit", args[0], "numeric argument required", 2);
	else
	{
		if (len > 1)
			return (minierror("exit", NULL, "too many arguments", 1));
		if (len == 1)
			nbr = ft_atoi(args[0]); // trocar por atol
		else
			nbr = ft_atoi(ft_getenv(env, "?")); // trocar por atol
	}
	free_split(args);
	destroy_env(env);
	destroy_table(cmdtab);
	exit (nbr);
}
