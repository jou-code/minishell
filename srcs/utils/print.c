#include "../../includes/minishell.h"

void	print_split(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%d: <%s>\n", i, array[i]);
		i++;
	}
}

void	print_list(t_list *list)
{
	t_node	*node;

	node = list->head;
	if (!node)
	{
		printf("no list!!\n\n");
		return ;
	}
	node = list->head;
	while (node != NULL)
	{
		printf("{value = !%s! \\ type = %i}->", node->value, node->type);
		node = node->next;
	}
	printf("NULL\n");
}

void	print_tab(t_tab *table)
{
	t_list	*list;
	int		size;
	int		count;

	if (!table)
	{
		printf("No tabLe!!\n");
		return ;
	}
	list = table->head;
	if (!list)
	{
		printf("Head empty!!\n");
		return ;
	}
	size = 0;
	while (list != NULL)
	{
		printf("\n");
		count = 0;
		while (count < size)
		{
			printf("\t");
			count++;
		}
		printf("-----------------------------------\n");
		count = 0;
		while (count < size)
		{
			printf("\t");
			count++;
		}
		printf("len = %i\n", list->len);
		count = 0;
		while (count < size)
		{
			printf("\t");
			count++;
		}
		size++;
		print_list(list);
		list = list->next;
	}
}
