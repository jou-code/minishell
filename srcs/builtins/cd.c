#include "../../includes/minishell.h"

char	*get_key_value(t_env *list, char *key)
{
	char		*val;
	t_envnode	*node;

	node = search_key(list, key);
	if (node)
		val = ft_strdup(node->value);
	else
		val = NULL;
	return (val);
}

void	update_key_value(t_env *list, char *key, char *new_val)
{
	t_envnode	*node;

	node = search_key(list, key);
	if (node && node->value)
	{
		free(node->value);
		node->value = ft_strdup(new_val);
	}
}

int	ft_cd(char **args, t_env *env)
{
	char	*origin;
	char	*path;
	char	buf[PATH_MAX + 1];

	if (split_len(args) > 1)
		return (perror("cd:"), 1);
	if (!args || ft_strncmp(args[0], "~", 1) == 0)
	{
		path = get_key_value(env, "HOME");
		if (args && args[0][1] != '\0')
			path = ft_strfjoin(path, &args[0][1]);
	}
	else if (ft_strncmp(args[0], "-", 2) == 0)
		path = get_key_value(env, "OLDPWD");
	else
		path = ft_strdup(args[0]);
	origin = getcwd(buf, PATH_MAX + 1);
	if (chdir(path) == -1 || !origin)
	{
		perror("cd:");
		free(path);
		return (1);
	}
	update_key_value(env, "OLDPWD", origin);
	update_key_value(env, "PWD", path);
	free(path);
	return (0);
}
