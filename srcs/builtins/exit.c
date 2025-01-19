#include "../../includes/minishell.h"
#include <readline/readline.h>

int	ft_atol(const char *nptr)
{
	int		i;
	long		convnum;
	int		sign;

	i = 0;
	convnum = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		convnum = convnum * 10 + (nptr[i] - 48);
		i++;
	}
	return (convnum * sign);
}

int	ft_exit(char **args, t_main *main)
{
	int		len;
	int		i;
	int		nbr;
	char	*tmp;

	len = split_len(args);
	i = 0;
	nbr = 1;
	ft_putstr_fd("exit\n", 1);
	if (args && args[0] && args[0][i] == '-')
		i++;
	while (args && args[0] && args[0][i] != '\0')
	{
		if (!ft_isdigit(args[0][i]))
		{
			nbr = 0;
			break ;
		}
		i++;
	}
	if (!nbr || i >= 20)
	{
		perror("exit:");
		nbr = 2;
	}
	else
	{
		if (len > 1)
			return (perror("exit:"), 1);
		if (len == 1)
			nbr = ft_atol(args[0]);
		else
		{
			tmp = get_key_value(main->envp_list, "?");
			nbr = ft_atol(tmp);
			free(tmp);
		}
	}
	rl_clear_history();
	close(main->fd[0]);
	close(main->fd[1]);
	free_main(main);
	free_split(args);
	exit(nbr);
}

int	ft_exit_nbr(int nbr, t_main *main)
{
	ft_putstr_fd("exit\n", 1);
	free_main(main);
	exit(nbr);
}
