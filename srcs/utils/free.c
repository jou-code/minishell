#include "../../includes/minishell.h"

void	free_main(t_main *main)
{
	free_split(main->envp);
	free_env(main->envp_list);
	free_table(main->cmdtab);
	free(main);
}

void	free_envnode(t_envnode *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_table(t_tab *cmdtable)
{
	t_list	*cmdline;
	t_list	*keepline;
	t_node	*token;
	t_node	*keeptoken;

	cmdline = cmdtable->head;
	token = cmdline->head;
	while (cmdline != NULL && token != NULL)
	{
		keeptoken = token->next;
		free(token->value);
		free(token);
		if (keeptoken == NULL)
		{
			keepline = cmdline->next;
			free(cmdline);
			if (keepline == NULL)
				break ;
			cmdline = keepline;
			token = keepline->head;
		}
		else
			token = keeptoken;
	}
	free(cmdtable);
}

void	free_list(t_list *cmdline)
{
	t_list	*tmpline;
	t_node	*token;
	t_node	*tmptoken;

	token = cmdline->head;
	while (cmdline != NULL && token != NULL)
	{
		tmptoken = token->next;
		free(token->value);
		free(token);
		if (tmptoken == NULL)
		{
			tmpline = cmdline->next;
			free(cmdline);
			if (tmpline == NULL)
				break ;
			cmdline = tmpline;
			token = tmpline->head;
		}
		else
			token = tmptoken;
	}
}

int	free_env(t_env *env)
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
