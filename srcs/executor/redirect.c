#include "../../includes/minishell.h"

int	redirect(t_list *cmdlist)
{
	int	fd[2];
	t_node *token= cmdlist->head;
	char *input;

	while (token != NULL && token->next != NULL)
	{
		if (token->type == REDIRECT_IN)
		{
			fd[0] = open(token->next->value, O_RDONLY);
			if (fd[0] < 0 || dup2(fd[0], 0) < 0)
			{
				perror("minishell: redirect");
				close(fd[0]);
				return (1);
			}
			close(fd[0]);
			token = token->next->next;
		}
		else if (token->type == HEREDOC)
		{
			if (pipe(fd) < 0)
			{
				perror(token->next->value);
				return (1);
			}
			input = readline("> ");
			while (ft_strncmp(input, token->next->value, ft_strlen(token->next->value) + 1) != 0) 
			{
				write(fd[1], input, ft_strlen(input));
				write(fd[1], "\n", 1);
				free(input);
				input = readline("> ");
			}
			if (dup2(fd[0], 0) < 0)
			{
				perror("minishell");
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
			close(fd[0]);
			close(fd[1]);
			token = token->next->next;
		}
		else if (token->type == REDIRECT_OUT || token->type == APPEND)
		{
			if (token->type == APPEND)
				fd[1] = open(token->next->value, O_CREAT | O_RDWR, 0664);
			else
				fd[1] = open(token->next->value, O_CREAT | O_TRUNC | O_RDWR, 0664);
			if (fd[1] < 0 || dup2(fd[1], 1) < 0)
			{
				perror("minishell");
				close(fd[1]);
				return (1);
			}
			close(fd[1]);
			token = token->next->next;
		}
		else
			token = token->next;
	}
	return (0);
}
