#include "../../includes/minishell.h"

int	cmdlen(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL && input[i][0] != '|')
		i++;
	if (input[i] != NULL && input[i][0] == '|')
		i++;
	return (i);
}

void	add_node(t_node *newnode, t_list *list)
{
	t_node	*node;

	node = list->head;
	if (!node)
		list->head = newnode;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = newnode;
		newnode->prev = node;
	}
}

void	add_list(t_list *newnode, t_tab *cmdtable)
{
	t_list	*list;

	list = cmdtable->head;
	if (!list)
		cmdtable->head = newnode;
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = newnode;
		newnode->prev = list;
	}
	cmdtable->len++;
}

t_node	*new_node(char *token)
{
	t_node	*cmd;

	cmd = malloc(sizeof(t_node));
	if (!cmd)
		return (NULL);
	cmd->value = token;
	cmd->type = -1;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_list	*new_list(char **input)
{
	int		i;
	t_node	*cmd;
	t_list	*cmdlist;

	i = 0;
	cmdlist = malloc(sizeof(t_list));
	if (!cmdlist)
		return (NULL);
	cmdlist->fd[0] = 0;
	cmdlist->fd[1] = 1;
	cmdlist->prev = NULL;
	cmdlist->next = NULL;
	cmd = new_node(input[i++]);
	if (!cmd)
	{
		free_list(cmdlist);
		return (NULL);
	}
	cmdlist->head = cmd;
	cmdlist->len = 1;
	while (input[i] != NULL)
	{
		cmd = new_node(input[i]);
		if (!cmd)
		{
			free_list(cmdlist);
			return (NULL);
		}
		add_node(cmd, cmdlist);
		cmdlist->len++;
		if (input[i] && input[i][0] == '|')
			break ;
		i++;
	}
	return (cmdlist);
}
